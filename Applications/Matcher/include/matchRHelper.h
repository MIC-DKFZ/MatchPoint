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

#include "itkStdStreamLogOutput.h"

#include "mapConvert.h"
#include "mapExceptionObjectMacros.h"
#include "mapRegistration.h"
#include "mapGenericImageReader.h"
#include "mapRegistrationFileWriter.h"
#include "mapImageRegistrationAlgorithmInterface.h"
#include "mapMaskedRegistrationAlgorithmInterface.h"
#include "mapMetaPropertyAlgorithmInterface.h"

#include "matchRApplicationData.h"

namespace map
{
	namespace apps
	{
		namespace matchR
		{

			/** Helper function to load the algorithm into the passed app data structure.*/
      void loadAlgorithm(ApplicationData& appData);
      /** Helper function to load the algorithm into the passed app data structure.*/
      void loadMovingImage(ApplicationData& appData);
      /** Helper function to load the algorithm into the passed app data structure.*/
      void loadTargetImage(ApplicationData& appData);

      void onMapAlgorithmEvent(::itk::Object*, const itk::EventObject& event);


			template <unsigned int IDim>
			class ProcessingLogic
			{
			public:
				typedef ::map::core::Registration<IDim, IDim> RegistrationType;

				/**write the registration data according to the settings in appData.
				* @pre pReg must point to a valid instance.*/
        void doWriting(RegistrationType* pReg)
				{
					if (!pReg)
					{
						mapDefaultExceptionStaticMacro( << "Cannot write data. Passed registration pointer is invalid (NULL).");
					}

					std::cout << std::endl << "save output file ... ";
  				std::cout << "(" << appData._outputFileName << ")... ";

					typedef ::map::io::RegistrationFileWriter<IDim, IDim> WriterType;
					typename WriterType::Pointer spWriter  = WriterType::New();

					spWriter->write(pReg, appData._outputFileName);

					std::cout << "done." << std::endl;
				};

				typename RegistrationType::Pointer doRegistration()
				{
					typedef ::map::core::discrete::Elements<IDim>::InternalImageType ImageType;

          //Now cast to the right interface (ImageRegistrationAlgorithmBase)
          //to set the images
          typedef map::algorithm::facet::ImageRegistrationAlgorithmInterface<ImageType, ImageType>
            ImageRegistrationAlgorithmInterfaceType;
          ImageRegistrationAlgorithmInterfaceType* pImageInterface =
            dynamic_cast<ImageRegistrationAlgorithmInterfaceType*>(appData._algorithm.GetPointer());

          if (pImageInterface)
          {
            const ImageType* moving = dynamic_cast<const ImageType*>(appData._spMovingImage.GetPointer());
            const ImageType* target = dynamic_cast<const ImageType*>(appData._spTargetImage.GetPointer());
            pImageInterface->setMovingImage(moving);
            pImageInterface->setTargetImage(target);
          }
          else
          {
            mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. Image Registration interface is missing. Check DLL.");
          }

          //Add observer for algorithm events.
          ::itk::MemberCommand< ProcessingLogic<IDim> >::Pointer command = ::itk::MemberCommand< ProcessingLogic<IDim> >::New();
          command->SetCallback(this, &ProcessingLogic<IDim>::onRegistrationEvent);

          unsigned long oservID = _appData._algorithm->AddObserver(map::events::AlgorithmEvent(), command);


					return spResult;
				};

				void processData()
				{
          typename RegistrationType::Pointer reg = doRegistration();
					doWriting(reg);
				}

        ProcessLogic(const ApplicationData* appData) : _appData(appData)
        {
        }

        protected:

        const ApplicationData* _appData
			};


		}
	}
}


#endif
