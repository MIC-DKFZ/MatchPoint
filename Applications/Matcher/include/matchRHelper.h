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
// @version $Revision: 1261 $ (last changed revision)
// @date    $Date: 2016-02-29 18:23:44 +0100 (Mo, 29 Feb 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/include/matchRHelper.h $
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

#include "matchRApplicationData.h"

namespace map
{
	namespace apps
	{
		namespace matchR
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
				void loadAlgorithm();
				void loadMovingImage();
				void loadTargetImage();
			protected:
				ApplicationData& _appData;
			};


			template <typename TPixelType, unsigned int IDim>
			class ProcessingLogic
			{
			public:
				typedef ::itk::Image<TPixelType, IDim> ImageType;

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


				static typename ImageType::Pointer doRegistration(const ApplicationData& appData)
				{
					typedef ::itk::ImageBase<IDim> TemplateImageType;
					typedef map::core::Registration<IDim, IDim> RegistrationType;

					typedef map::core::ImageMappingTask<RegistrationType, ImageType, ImageType> MapperType;

					typename MapperType::Pointer spMapper = MapperType::New();

					ImageType* pCastedMoving = dynamic_cast<ImageType*>(appData._spMovingImage.GetPointer());
					typename ImageType::Pointer spResult;
					RegistrationType* pCastedReg = dynamic_cast<RegistrationType*>(appData._spReg.GetPointer());

					typename MapperType::ResultImageDescriptorType::Pointer spResultDesc = NULL;

					if (appData._spTargetImage.IsNotNull())
					{
						TemplateImageType* pCastedTemplate = dynamic_cast<TemplateImageType*>
						                                     (appData._spTargetImage.GetPointer());

						spResultDesc = map::core::createFieldRepresentation(*pCastedTemplate);
					}

					try
					{

						std::cout << std::endl << "map input file... ";
						spMapper->setMovingImage(pCastedMoving);
						spMapper->setRegistration(pCastedReg);
						spMapper->setResultImageDescriptor(spResultDesc);
						spMapper->setPaddingValue(appData._paddingValue);
						spMapper->setImageInterpolator(generateInterpolator(appData._interpolatorType));
            if (appData._noFailOnErrors)
            {
                spMapper->setThrowOnMappingError(false);
                spMapper->setErrorValue(appData._paddingValue);
            }
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
