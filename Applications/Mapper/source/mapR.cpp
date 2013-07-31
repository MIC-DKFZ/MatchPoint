// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Applications/Mapper/source/mapR.cpp $
*/


#include "mapRApplicationData.h"
#include "mapImageMappingTask.h"
#include "mapGenericImageReader.h"
#include "mapRegistrationFileReader.h"
#include "mapConvert.h"

#include "itkImageFileWriter.h"
#include "itkStdStreamLogOutput.h"
#include "itkImageSeriesWriter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkGDCMImageIO.h"
#include "itkVersion.h"

#include "gdcmUIDGenerator.h"

#ifdef MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER
/* The mapR needs the IO factories to be registered in cases where
   MatchPoint is built without auto registration (e.g. for use in MITK)
   mapR has to add the registration helper manually.*/
#include "itkImageIOFactoryRegisterManager.h"
#endif //MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER

map::apps::MapR::ApplicationData appData;

void onMAPEvent(::itk::Object *, const itk::EventObject &event, void *)
{
	std::cout << " > > > ";
	event.Print(std::cout);
	std::cout << std::endl;
}



template <typename TImageType>
std::vector<itk::MetaDataDictionary *> generateDictionaries(TImageType *pImage, const map::core::String &uidPrefix)
{
	// Copy the dictionary from the image
	itk::MetaDataDictionary mappedDict;
	mappedDict = pImage->GetMetaDataDictionary();

	if (appData._loadedMetaDataDictArray.size())
	{
		mappedDict = appData._loadedMetaDataDictArray[0];
	}

	std::vector<itk::MetaDataDictionary *> outputArray;

	////////////////////////////////////////////
	//Step 1: set everything that is valid for all slices

	// To keep the new series in the same study as the original we need
	// to keep the same study UID. But we need new series and frame of
	// reference UID's.
	gdcm::UIDGenerator suid;
	std::string seriesUID = suid.Generate();
	gdcm::UIDGenerator fuid;
	std::string frameOfReferenceUID = fuid.Generate();

	if (appData._loadedRefMetaDataDictArray.size())
	{
		//result has the same frame of reference UID then template image
		itk::ExposeMetaData<std::string>(appData._loadedRefMetaDataDictArray[0], "0020|0052", frameOfReferenceUID);
	}

	// Set the UID's for the study, series and frame of reference
	itk::EncapsulateMetaData<std::string>(mappedDict, "0020|000e", seriesUID);
	itk::EncapsulateMetaData<std::string>(mappedDict, "0020|0052", frameOfReferenceUID);

	map::core::OStringStream stream;
	// Series Description - Append new description to current series
	// description
	std::string oldSeriesDesc;
	itk::ExposeMetaData<std::string>(mappedDict, "0008|103e", oldSeriesDesc);

	stream.str("");
	stream << "regd_" << oldSeriesDesc;
	// This is an long string and there is a 64 character limit in the
	// standard
	unsigned lengthDesc = stream.str().length();

	std::string seriesDesc(stream.str(), 0, lengthDesc > 64 ? 64 : lengthDesc);
	itk::EncapsulateMetaData<std::string>(mappedDict, "0008|103e", seriesDesc);


	// Derivation Description - How this image was derived
	stream.str("");
	stream << "mapped by using \"" << map::core::FileDispatch::getFullName(appData._regFileName) << "\" registration file; software: mapR; MatchPoint version: " << MAP_SOURCE_VERSION << ", itk version:" << ITK_SOURCE_VERSION;

	lengthDesc = stream.str().length();
	std::string derivationDesc(stream.str(), 0, lengthDesc > 1024 ? 1024 : lengthDesc);
	itk::EncapsulateMetaData<std::string>(mappedDict, "0008|2111", derivationDesc);

	// Slice Thickness: For now, we store the z spacing
	stream.str("");
	stream << pImage->GetSpacing()[2];
	itk::EncapsulateMetaData<std::string>(mappedDict, "0018|0050", stream.str());
	// Spacing Between Slices
	itk::EncapsulateMetaData<std::string>(mappedDict, "0018|0088", stream.str());

	///////////////////////////////////////////////
	//Step 2: Generate a dictionary per slice and
	//        adapt slice specific values

	itk::ImageRegion<3>::SizeValueType sliceCount = pImage->GetLargestPossibleRegion().GetSize(2);

	for (itk::ImageRegion<3>::SizeValueType currentSliceIndex = 0; currentSliceIndex < sliceCount; ++currentSliceIndex)
	{
		// Create a new dictionary for this slice
		itk::MetaDataDictionary *pDict = new itk::MetaDataDictionary;

		// Copy the dictionary from the first slice
		*pDict = mappedDict;

		// Set the UID's for the SOP
		gdcm::UIDGenerator sopuid;
		std::string sopInstanceUID = sopuid.Generate();

		itk::EncapsulateMetaData<std::string>(*pDict, "0008|0018", sopInstanceUID);
		itk::EncapsulateMetaData<std::string>(*pDict, "0002|0003", sopInstanceUID);

		// Change fields that are slice specific
		map::core::OStringStream value;
		value.str("");
		value << currentSliceIndex + 1;

		// Image Number
		itk::EncapsulateMetaData<std::string>(*pDict, "0020|0013", value.str());

		// Image Position Patient: This is calculated by computing the
		// physical coordinate of the first pixel in each slice.
		typename TImageType::PointType position;
		typename TImageType::IndexType index;
		index[0] = 0;
		index[1] = 0;
		index[2] = currentSliceIndex;
		pImage->TransformIndexToPhysicalPoint(index, position);

		value.str("");
		value << position[0] << "\\" << position[1] << "\\" << position[2];
		itk::EncapsulateMetaData<std::string>(*pDict, "0020|0032", value.str());
		// Slice Location: For now, we store the z component of the Image
		// Position Patient.
		value.str("");
		value << position[2];
		itk::EncapsulateMetaData<std::string>(*pDict, "0020|1041", value.str());

		// Save the dictionary
		outputArray.push_back(pDict);
	}

	return outputArray;
}


template <typename TPixelType, unsigned int Dimensions>
void doWriting(::itk::Image<TPixelType, Dimensions> *pImage)
{
	typedef ::itk::Image<TPixelType, Dimensions> ImageType;
	std::cout << std::endl << "save output file ... ";

	/** @TODO should this method be reworked
	* right now the tags of dicom image will only be transfered if they are 3D and the series read style is set to DICOM or GDCM.
	* Thus 2D DICOM images are missed as well as 3D DICOM images that are stored as one image file (default series style).*/

	if (appData._loadedDimensions > 2 &&
	        (appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::Dicom || appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::Numeric || appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::GDCM))
	{
		typedef ::itk::Image < TPixelType, Dimensions - 1 > OutputImageType;
		typedef ::itk::NumericSeriesFileNames OutputNamesGeneratorType;
		typedef ::itk::ImageSeriesWriter< ImageType, OutputImageType  > SeriesWriterType;
		typedef ::itk::GDCMImageIO ImageIOType;
		ImageIOType::Pointer spGDCMIO = ImageIOType::New();

		OutputNamesGeneratorType::Pointer outputNames = OutputNamesGeneratorType::New();

		outputNames->SetStartIndex(1);
		outputNames->SetEndIndex(pImage->GetLargestPossibleRegion().GetSize(pImage->GetImageDimension() - 1));

		// Generate the file names
		map::core::String tempLen = map::core::convert::toStr(outputNames->GetEndIndex());
		map::core::String seriesFormat = map::core::FileDispatch::createFullPath(map::core::FileDispatch::getPath(appData._outputFileName), map::core::FileDispatch::getName(appData._outputFileName) + ".%0" + map::core::convert::toStrGeneric(tempLen.length()) + "d" + map::core::FileDispatch::getExtension(appData._outputFileName));

		std::cout << "(" << seriesFormat << ")... ";

		outputNames->SetSeriesFormat(seriesFormat.c_str());

		// do the output
		typename SeriesWriterType::Pointer spSeriesWriter = SeriesWriterType::New();
		spSeriesWriter->SetInput(pImage);
		spSeriesWriter->SetFileNames(outputNames->GetFileNames());

		std::vector<itk::MetaDataDictionary *> outputArray = generateDictionaries(pImage, spGDCMIO->GetUIDPrefix());

		if ((appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::Dicom) ||
		        (appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::GDCM))
		{
			spGDCMIO->KeepOriginalUIDOn();
			spSeriesWriter->SetImageIO(spGDCMIO);
			spSeriesWriter->SetMetaDataDictionaryArray(&outputArray);
		}

		spSeriesWriter->Update();

		for (std::vector<itk::MetaDataDictionary *>::iterator pos = outputArray.begin(); pos != outputArray.end(); ++pos)
		{
			delete *pos;
		}
	}
	else
	{
		std::cout << "(" << appData._outputFileName << ")... ";
		typedef ::itk::ImageFileWriter< ImageType  > ImageWriterType;
		typename ImageWriterType::Pointer spImageWriter  = ImageWriterType::New();

		spImageWriter->SetInput(pImage);
		spImageWriter->SetFileName(appData._outputFileName.c_str());
		spImageWriter->Update();
	}

	std::cout << "done." << std::endl;
};


template <typename TPixelType, unsigned int Dimensions>
int doMapping()
{
	int result = 0;
	typedef ::itk::Image<TPixelType, Dimensions> ImageType;
	typedef ::itk::ImageBase<Dimensions> TemplateImageType;
	typedef map::core::Registration<Dimensions, Dimensions> RegistrationType;

	typedef map::core::ImageMappingTask<RegistrationType, ImageType, ImageType> MapperType;

	typename MapperType::Pointer spMapper = MapperType::New();

	ImageType *pCastedInput = dynamic_cast<ImageType *>(appData._spInputImage.GetPointer());
	typename ImageType::Pointer spResult;
	RegistrationType *pCastedReg = dynamic_cast<RegistrationType *>(appData._spReg.GetPointer());

	typename MapperType::ResultImageDescriptorType::Pointer spResultDesc = NULL;

	if (appData._spRefImage.IsNotNull())
	{
		TemplateImageType *pCastedTemplate = dynamic_cast<TemplateImageType *>(appData._spRefImage.GetPointer());

		spResultDesc = map::core::createFieldRepresentation(*pCastedTemplate);
	}

	try
	{

		std::cout << std::endl << "map input file... ";
		spMapper->setInputImage(pCastedInput);
		spMapper->setRegistration(pCastedReg);
		spMapper->setResultImageDescriptor(spResultDesc);
		spMapper->setPaddingValue(appData._paddingValue);
		spMapper->execute();
		spResult = spMapper->getResultImage();
		std::cout << "done." << std::endl;

		doWriting<TPixelType, Dimensions>(spResult);
	}
	catch (::itk::ExceptionObject &e)
	{
		std::cerr << "Error!!!" << std::endl;
		std::cerr << e << std::endl;
		result = 9;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error!!!" << std::endl;
		std::cerr << e.what() << std::endl;
		result = 9;
	}
	catch (...)
	{
		std::cerr << "Error!!! unkown error while mapping image." << std::endl;
		result = 9;
	}

	return result;
};



template <unsigned int IDimension>
int handleGenericImage(::itk::ImageIOBase::IOComponentType &loadedComponentType)
{
	switch (loadedComponentType)
	{
		case ::itk::ImageIOBase::UCHAR:
		{
			return doMapping<unsigned char, IDimension>();
		}

		case ::itk::ImageIOBase::CHAR:
		{
			return doMapping<char, IDimension>();
		}

		case ::itk::ImageIOBase::USHORT:
		{
			return doMapping<unsigned short, IDimension>();
		}

		case ::itk::ImageIOBase::SHORT:
		{
			return doMapping<short, IDimension>();
		}

		case ::itk::ImageIOBase::UINT:
		{
			return doMapping<unsigned int, IDimension>();
		}

		case ::itk::ImageIOBase::INT:
		{
			return doMapping<int, IDimension>();
		}

		case ::itk::ImageIOBase::ULONG:
		{
			return doMapping<unsigned long, IDimension>();
		}

		case ::itk::ImageIOBase::LONG:
		{
			return doMapping<long, IDimension>();
		}

		case ::itk::ImageIOBase::FLOAT:
		{
			return doMapping<float, IDimension>();
		}

		case ::itk::ImageIOBase::DOUBLE:
		{
			return doMapping<double, IDimension>();
		}

		default:
		{
			mapDefaultExceptionStaticMacro( << "The file uses a pixel component type that is not supported in this application.");
		}
	}
}


int main(int argc, char **argv)
{
	int result = 0;

	std::cout << "mapR - Generic image mapping tool for MatchPoint." << std::endl;

	switch (appData.ParseArguments(argc, argv))
	{
		case 1:
		{
			//showed version or help info. Done.
			return 1;
		}

		case 2:
		{
			std::cerr << "Missing Parameters. Use one of the following flags for more information:" << std::endl;
			std::cerr << "-? or --help" << std::endl;
			return 2;
		}

		case 3:
		{
			//wrong option usage.
			return 3;
		}
	}

	if (appData._fileCount < 2)
	{
		std::cerr << "Missing Parameters. Use one of the following flags for more information:" << std::endl;
		std::cerr << "-? or --help" << std::endl;
		return 1;
	}

	::itk::StdStreamLogOutput::Pointer spStreamLogOutput = ::itk::StdStreamLogOutput::New();
	spStreamLogOutput->SetStream(std::cout);
	map::core::Logbook::addAdditionalLogOutput(spStreamLogOutput);

	if (appData._detailedOutput)
	{
		map::core::Logbook::setLogbookToDebugMode();
	}

	std::cout << std::endl << "*******************************************" << std::endl;
	std::cout << "Input file:        " << appData._inputFileName << std::endl;
	std::cout << "Registration file: " << appData._regFileName << std::endl;
	std::cout << "Series read style: " << appData._seriesReadStyleStr << std::endl;
	std::cout << "Series write style: " << appData._seriesWriteStyleStr << std::endl;

	if (!(appData._refFileName.empty()))
	{
		std::cout << "Template file:     " << appData._refFileName << std::endl;
	}

	map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();

	spReader->setSeriesReadStyle(appData._seriesReadStyle);
	spReader->setFileName(appData._inputFileName);
	spReader->setUpperSeriesLimit(appData._upperSeriesLimit);

	map::io::RegistrationFileReader::Pointer spRegReader = map::io::RegistrationFileReader::New();

	try
	{
		std::cout << std::endl << "read input file... ";
		appData._spInputImage = spReader->GetOutput(appData._loadedDimensions, appData._loadedPixelType, appData._loadedComponentType);
		appData._loadedMetaDataDictArray = spReader->getMetaDictionaryArray();

		if (appData._spInputImage.IsNotNull())
		{
			std::cout << "done." << std::endl;
		}
		else
		{
			std::cerr << "Error!!! unable to load input image. File is not existing or has an unsupported format." << std::endl;
			return 4;
		}

		if (appData._detailedOutput)
		{
			std::cout << "Input image info:" << std::endl;
			appData._spInputImage->Print(std::cout);
			std::cout << std::endl << "Input image meta properties:" << std::endl;
			appData._spInputImage->Print(std::cout);
			std::cout << std::endl;
		}
	}
	catch (::itk::ExceptionObject &e)
	{
		std::cerr << "Error!!!" << std::endl;
		std::cerr << e << std::endl;
		return 4;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error!!!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 4;
	}
	catch (...)
	{
		std::cerr << "Error!!! unknown error while reading input image." << std::endl;
		return 4;
	}

	if (appData._loadedPixelType != ::itk::ImageIOBase::SCALAR)
	{
		std::cerr << "Error!!! Unsupported input image. Only simple scalar images are supported in this version." << std::endl;

		return 4;
	}

	if (appData._loadedDimensions < 2 || appData._loadedDimensions > 3)
	{
		std::cerr << "Error!!! Unsupported input image. Only 2D and 3D images are supported in this version." << std::endl;

		return 4;
	}

	try
	{
		std::cout << std::endl << "read registration file... ";
		appData._spReg = spRegReader->read(appData._regFileName);
		std::cout << "done." << std::endl;

		if (appData._detailedOutput)
		{
			std::cout << std::endl << "Registration info:" << std::endl;
			appData._spReg->Print(std::cout);
			std::cout << std::endl;
		}
	}
	catch (::itk::ExceptionObject &e)
	{
		std::cerr << "Error!!!" << std::endl;
		std::cerr << e << std::endl;
		return 5;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error!!!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 5;
	}
	catch (...)
	{
		std::cerr << "Error!!! unknown error while reading registration file." << std::endl;
		return 5;
	}

	if (appData._spReg->getMovingDimensions() != appData._spReg->getTargetDimensions() || appData._spReg->getMovingDimensions() != appData._loadedDimensions)
	{
		std::cerr << "Error!!! Loaded registration and loaded image have no equal dimensionality. Registration cannot be used to map the image." << std::endl;

		return 5;
	}

	if (!(appData._refFileName.empty()))
	{
		map::io::GenericImageReader::Pointer spTemplateReader = map::io::GenericImageReader::New();
		spTemplateReader->setSeriesReadStyle(appData._seriesReadStyle);
		spTemplateReader->setFileName(appData._refFileName);
		spTemplateReader->setUpperSeriesLimit(appData._upperSeriesLimit);

		map::io::GenericImageReader::LoadedPixelType _loadedTempPixelType;
		map::io::GenericImageReader::LoadedComponentType _loadedTempComponentType;
		unsigned int _loadedTempDimensions;

		try
		{
			std::cout << std::endl << std::endl << "read template file... ";
			appData._spRefImage = spTemplateReader->GetOutput(_loadedTempDimensions, _loadedTempPixelType, _loadedTempComponentType);
			appData._loadedRefMetaDataDictArray = spReader->getMetaDictionaryArray();

			if (appData._spRefImage.IsNotNull())
			{
				std::cout << "done." << std::endl;
			}
			else
			{
				std::cerr << "Error!!! unable to load template image. File is not existing or has an unsupported format." << std::endl;
				return 4;
			}

			if (appData._detailedOutput)
			{
				std::cout << "Template image info:" << std::endl;
				appData._spRefImage->Print(std::cout);
				std::cout << std::endl;
			}
		}
		catch (::itk::ExceptionObject &e)
		{
			std::cerr << "Error!!!" << std::endl;
			std::cerr << e << std::endl;
			return 6;
		}
		catch (std::exception &e)
		{
			std::cerr << "Error!!!" << std::endl;
			std::cerr << e.what() << std::endl;
			return 6;
		}
		catch (...)
		{
			std::cerr << "Error!!! unknown error while reading template image." << std::endl;
			return 6;
		}

		if (_loadedTempDimensions != appData._spReg->getTargetDimensions())
		{
			std::cerr << "Error!!! Unsupported template image. Template image dimension does not match registration." << std::endl;
			return 6;
		}

	}

	if (appData._loadedDimensions == 2)
	{
		result = handleGenericImage<2>(appData._loadedComponentType);
	}
	else if (appData._loadedDimensions == 3)
	{
		result = handleGenericImage<3>(appData._loadedComponentType);
	}

	std::cout << std::endl;

	return result;
}
