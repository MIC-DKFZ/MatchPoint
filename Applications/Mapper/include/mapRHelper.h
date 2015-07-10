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
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/


#ifndef __MAP_R_HELPER_H
#define __MAP_R_HELPER_H

#include "itkImageFileWriter.h"
#include "itkStdStreamLogOutput.h"
#include "itkImageSeriesWriter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkGDCMImageIO.h"
#include "itkVersion.h"

#include <itkInterpolateImageFunction.h>
#include <itkNearestNeighborInterpolateImageFunction.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkBSplineInterpolateImageFunction.h>
#include <itkWindowedSincInterpolateImageFunction.h>

#include "gdcmUIDGenerator.h"

#include "mapConvert.h"
#include "mapExceptionObjectMacros.h"
#include "mapImageMappingTask.h"
#include "mapGenericImageReader.h"
#include "mapRegistrationFileReader.h"

#include "mapRApplicationData.h"

namespace map
{
	namespace apps
	{
		namespace mapR
		{

			template <unsigned int IDimension, template <typename TPixelType, unsigned int IDim> class TProcessingPolicy>
			void handleGenericImage(const ApplicationData& appData)
			{
				switch (appData._loadedComponentType)
				{
					case ::itk::ImageIOBase::UCHAR:
					{
						TProcessingPolicy<unsigned char, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::CHAR:
					{
						TProcessingPolicy<char, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::USHORT:
					{
						TProcessingPolicy<unsigned short, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::SHORT:
					{
						TProcessingPolicy<short, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::UINT:
					{
						TProcessingPolicy<unsigned int, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::INT:
					{
						TProcessingPolicy<int, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::ULONG:
					{
						TProcessingPolicy<unsigned long, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::LONG:
					{
						TProcessingPolicy<long, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::FLOAT:
					{
						TProcessingPolicy<float, IDimension>::processData(appData);
						break;
					}

					case ::itk::ImageIOBase::DOUBLE:
					{
						TProcessingPolicy<double, IDimension>::processData(appData);
						break;
					}

					default:
					{
						mapDefaultExceptionStaticMacro( <<
						                                "The file uses a pixel component type that is not supported in this application.");
					}
				}
			}

			/** Helper class that contains the logic that handles the data loading according to the settings in appData.
			* the loaded data will be stored in app data. */
			class LoadingLogic
			{
			public:
				LoadingLogic(ApplicationData& appData);
				void loadRegistration();
				void loadInputImage();
				void loadReferenceImage();
			protected:
				ApplicationData& _appData;
			};


			template <typename TPixelType, unsigned int IDim>
			class ProcessingLogic
			{
			public:
				typedef ::itk::Image<TPixelType, IDim> ImageType;

				/** Generates meta data dictionaries with the correct meta data (correlated with needed DICOM tags) to ensure
				* the correct dicom file generation for each slice of the passed image.
				* @pre pImage must point to a valid instance.*/
				static std::vector<itk::MetaDataDictionary*> generateSliceDictionaries(ImageType* pImage,
				        const map::core::String& uidPrefix, const ApplicationData& appData)
				{
					if (!pImage)
					{
						mapDefaultExceptionStaticMacro( <<
						                                "Cannot generate slice dictionaries. Passed image pointer is invalid (NULL).");
					}

					// Copy the dictionary from the image
					itk::MetaDataDictionary mappedDict;
					mappedDict = pImage->GetMetaDataDictionary();

					if (appData._loadedMetaDataDictArray.size())
					{
						mappedDict = appData._loadedMetaDataDictArray[0];
					}

					std::vector<itk::MetaDataDictionary*> outputArray;

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
						itk::ExposeMetaData<std::string>(appData._loadedRefMetaDataDictArray[0], "0020|0052",
						                                 frameOfReferenceUID);
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
					stream << "mapped by using \"" << map::core::FileDispatch::getFullName(
					           appData._regFileName) << "\" registration file; software: mapR; MatchPoint version: " <<
					       MAP_SOURCE_VERSION << ", itk version:" << ITK_SOURCE_VERSION;

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

					for (itk::ImageRegion<3>::SizeValueType currentSliceIndex = 0; currentSliceIndex < sliceCount;
					     ++currentSliceIndex)
					{
						// Create a new dictionary for this slice
						itk::MetaDataDictionary* pDict = new itk::MetaDataDictionary;

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
						typename ImageType::PointType position;
						typename ImageType::IndexType index;
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

				/**write the image data according to the settings in appData.
				* @pre pImage must point to a valid instance.
				* @TODO should this method be reworked
				* right now the tags of dicom image will only be transfered if they are 3D and the series read style is set to DICOM or GDCM.
				* Thus 2D DICOM images are missed as well as 3D DICOM images that are stored as one image file (default series style).*/
				static void doWriting(ImageType* pImage, const ApplicationData& appData)
				{
					if (!pImage)
					{
						mapDefaultExceptionStaticMacro( << "Cannot write data. Passed image pointer is invalid (NULL).");
					}

					std::cout << std::endl << "save output file ... ";

					if (appData._loadedDimensions > 2 &&
					    (appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::Dicom
					     || appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::Numeric
					     || appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::GDCM))
					{
						typedef ::itk::Image < TPixelType, IDim - 1 > OutputImageType;
						typedef ::itk::NumericSeriesFileNames OutputNamesGeneratorType;
						typedef ::itk::ImageSeriesWriter< ImageType, OutputImageType  > SeriesWriterType;
						typedef ::itk::GDCMImageIO ImageIOType;
						ImageIOType::Pointer spGDCMIO = ImageIOType::New();

						OutputNamesGeneratorType::Pointer outputNames = OutputNamesGeneratorType::New();

						outputNames->SetStartIndex(1);
						outputNames->SetEndIndex(pImage->GetLargestPossibleRegion().GetSize(pImage->GetImageDimension() -
						                         1));

						// Generate the file names
						map::core::String tempLen = map::core::convert::toStr(outputNames->GetEndIndex());
						map::core::String seriesFormat = map::core::FileDispatch::createFullPath(
						                                     map::core::FileDispatch::getPath(appData._outputFileName),
						                                     map::core::FileDispatch::getName(appData._outputFileName) + ".%0" +
						                                     map::core::convert::toStrGeneric(tempLen.length()) + "d" + map::core::FileDispatch::getExtension(
						                                             appData._outputFileName));

						std::cout << "(" << seriesFormat << ")... ";

						outputNames->SetSeriesFormat(seriesFormat.c_str());

						// do the output
						typename SeriesWriterType::Pointer spSeriesWriter = SeriesWriterType::New();
						spSeriesWriter->SetInput(pImage);
						spSeriesWriter->SetFileNames(outputNames->GetFileNames());

						std::vector<itk::MetaDataDictionary*> outputArray = generateSliceDictionaries(pImage,
						        spGDCMIO->GetUIDPrefix(), appData);

						if ((appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::Dicom) ||
						    (appData._seriesWriteStyle == map::io::ImageSeriesReadStyle::GDCM))
						{
							spGDCMIO->KeepOriginalUIDOn();
							spSeriesWriter->SetImageIO(spGDCMIO);
							spSeriesWriter->SetMetaDataDictionaryArray(&outputArray);
						}

						spSeriesWriter->Update();

						for (std::vector<itk::MetaDataDictionary*>::iterator pos = outputArray.begin();
						     pos != outputArray.end(); ++pos)
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

				static typename ::itk::InterpolateImageFunction< ImageType >::Pointer generateInterpolator(
				    ImageMappingInterpolator::Type interpolatorType)
				{
					typedef ::itk::InterpolateImageFunction< ImageType > BaseInterpolatorType;
					typename BaseInterpolatorType::Pointer result;

					switch (interpolatorType)
					{
						case ImageMappingInterpolator::NearestNeighbor:
						{
							result = ::itk::NearestNeighborInterpolateImageFunction<ImageType>::New();
							break;
						}

						case ImageMappingInterpolator::BSpline_3:
						{
							typename ::itk::BSplineInterpolateImageFunction<ImageType>::Pointer spInterpolator
							    = ::itk::BSplineInterpolateImageFunction<ImageType>::New();
							spInterpolator->SetSplineOrder(3);
							result = spInterpolator;
							break;
						}

						case ImageMappingInterpolator::WSinc_Hamming:
						{
							result = ::itk::WindowedSincInterpolateImageFunction<ImageType, 4>::New();
							break;
						}

						case ImageMappingInterpolator::WSinc_Welch:
						{
							result = ::itk::WindowedSincInterpolateImageFunction<ImageType, 4, ::itk::Function::WelchWindowFunction<4> >::New();
							break;
						}

						default:
						{
							result = ::itk::LinearInterpolateImageFunction<ImageType>::New();
							break;
						}

					}

					return result;
				};

				static typename ImageType::Pointer doMapping(const ApplicationData& appData)
				{
					typedef ::itk::ImageBase<IDim> TemplateImageType;
					typedef map::core::Registration<IDim, IDim> RegistrationType;

					typedef map::core::ImageMappingTask<RegistrationType, ImageType, ImageType> MapperType;

					typename MapperType::Pointer spMapper = MapperType::New();

					ImageType* pCastedInput = dynamic_cast<ImageType*>(appData._spInputImage.GetPointer());
					typename ImageType::Pointer spResult;
					RegistrationType* pCastedReg = dynamic_cast<RegistrationType*>(appData._spReg.GetPointer());

					typename MapperType::ResultImageDescriptorType::Pointer spResultDesc = NULL;

					if (appData._spRefImage.IsNotNull())
					{
						TemplateImageType* pCastedTemplate = dynamic_cast<TemplateImageType*>
						                                     (appData._spRefImage.GetPointer());

						spResultDesc = map::core::createFieldRepresentation(*pCastedTemplate);
					}

					try
					{

						std::cout << std::endl << "map input file... ";
						spMapper->setInputImage(pCastedInput);
						spMapper->setRegistration(pCastedReg);
						spMapper->setResultImageDescriptor(spResultDesc);
						spMapper->setPaddingValue(appData._paddingValue);
						spMapper->setImageInterpolator(generateInterpolator(appData._interpolatorType));
						spMapper->execute();
						spResult = spMapper->getResultImage();
						std::cout << "done." << std::endl;
					}
					catch (::itk::ExceptionObject& e)
					{
						std::cerr << "Error!!!" << std::endl;
						std::cerr << e << std::endl;
					}
					catch (std::exception& e)
					{
						std::cerr << "Error!!!" << std::endl;
						std::cerr << e.what() << std::endl;
					}
					catch (...)
					{
						std::cerr << "Error!!! Unkown error while mapping image." << std::endl;
					}

					return spResult;
				};

				static void processData(const ApplicationData& appData)
				{
					typename ImageType::Pointer mappedImage = doMapping(appData);
					doWriting(mappedImage, appData);
				}

			};


		}
	}
}


#endif
