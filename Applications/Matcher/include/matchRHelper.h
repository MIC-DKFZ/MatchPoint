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

#include <mapImageRegistrationAlgorithmInterface.h>
#include <mapRegistrationAlgorithmInterface.h>
#include <mapIterativeAlgorithmInterface.h>
#include <mapMultiResRegistrationAlgorithmInterface.h>
#include <mapAlgorithmEvents.h>
#include <mapAlgorithmWrapperEvent.h>
#include <mapRegistrationAlgorithm.h>
#include <mapMetaPropertyInfo.h>
#include <mapMetaPropertyBase.h>

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
      /** Helper function to load the meta parameter map for the algorithm into the passed app data structure.*/
      void loadParameterMap(ApplicationData& appData);

      ::map::core::MetaPropertyBase::Pointer
        wrapMetaProperty(const ::map::algorithm::MetaPropertyInfo* pInfo, const ::map::core::String& valueStr);

			template <unsigned int IDim>
			class ProcessingLogic
			{
			public:
				typedef ::map::core::Registration<IDim, IDim> RegistrationType;
        typedef ::map::algorithm::RegistrationAlgorithm<IDim, IDim> AlgorithmType;

        void onMapAlgorithmEvent(::itk::Object*, const itk::EventObject& event)
        {
          const map::events::AlgorithmEvent* pAlgEvent = dynamic_cast<const map::events::AlgorithmEvent*>
            (&event);
          const map::events::AlgorithmIterationEvent* pIterationEvent =
            dynamic_cast<const map::events::AlgorithmIterationEvent*>(&event);
          const map::events::AlgorithmWrapperEvent* pWrapEvent =
            dynamic_cast<const map::events::AlgorithmWrapperEvent*>(&event);
          const map::events::AlgorithmResolutionLevelEvent* pLevelEvent =
            dynamic_cast<const map::events::AlgorithmResolutionLevelEvent*>(&event);

          const map::events::InitializingAlgorithmEvent* pInitEvent =
            dynamic_cast<const map::events::InitializingAlgorithmEvent*>(&event);
          const map::events::StartingAlgorithmEvent* pStartEvent =
            dynamic_cast<const map::events::StartingAlgorithmEvent*>(&event);
          const map::events::StoppingAlgorithmEvent* pStoppingEvent =
            dynamic_cast<const map::events::StoppingAlgorithmEvent*>(&event);
          const map::events::StoppedAlgorithmEvent* pStoppedEvent =
            dynamic_cast<const map::events::StoppedAlgorithmEvent*>(&event);
          const map::events::FinalizingAlgorithmEvent* pFinalizingEvent =
            dynamic_cast<const map::events::FinalizingAlgorithmEvent*>(&event);
          const map::events::FinalizedAlgorithmEvent* pFinalizedEvent =
            dynamic_cast<const map::events::FinalizedAlgorithmEvent*>(&event);

          if (pInitEvent)
          {
            std::cout << "Initializing algorithm ..." << std::endl;
          }
          else if (pStartEvent)
          {
            std::cout << "Starting algorithm ..." << std::endl;
          }
          else if (pStoppingEvent)
          {
            std::cout << "Stopping algorithm ..." << std::endl;
          }
          else if (pStoppedEvent)
          {
            std::cout << "Stopped algorithm ..." << std::endl;

            if (!pStoppedEvent->getComment().empty())
            {
              std::cout << "Stopping condition: " << pStoppedEvent->getComment() << std::endl;
            }
          }
          else if (pFinalizingEvent)
          {
            std::cout << "Finalizing algorithm and results ..." << std::endl;
          }
          else if (pFinalizedEvent)
          {
            std::cout << "Finalized algorithm ..." << std::endl;
          }
          else if (pIterationEvent)
          {
            if (_appData->_detailedOutput)
            {
              typedef map::algorithm::facet::IterativeAlgorithmInterface IIterativeAlgorithm;

              const IIterativeAlgorithm* pIterative = dynamic_cast<const IIterativeAlgorithm*>
                (this->_appData->_algorithm.GetPointer());

              IIterativeAlgorithm::IterationCountType count = 0;

              std::cout << "[";
              if (pIterative && pIterative->hasIterationCount())
              {
                std::cout << pIterative->getCurrentIteration();
              }
              std::cout << "] " << pIterationEvent->getComment() << std::endl;
            }
            else
            {
              std::cout << ".";
            }
          }
          else if (pLevelEvent)
          {
            if (_appData->_detailedOutput)
            {
              typedef map::algorithm::facet::MultiResRegistrationAlgorithmInterface IMultiResAlgorithm;
              const IMultiResAlgorithm* pResAlg = dynamic_cast<const IMultiResAlgorithm*>
                (this->_appData->_algorithm.GetPointer());

              map::algorithm::facet::MultiResRegistrationAlgorithmInterface::ResolutionLevelCountType count = 0;

              std::cout << std::endl << "**************************************" << std::endl;
              std::cout << "New resolution level";
              if (pResAlg && pResAlg->hasLevelCount())
              {
                std::cout << " [# " << pResAlg->getCurrentLevel() + 1 << "]";
              }
              std::cout << std::endl << "**************************************" << std::endl << std::endl;
            }
            else
            {
              std::cout << std::endl;
            }
          }
          else if (pAlgEvent && !pWrapEvent)
          {
            std::cout << pAlgEvent->getComment() << std::endl;
          }
        };

        /**write the registration data according to the settings in appData.
				* @pre pReg must point to a valid instance.*/
        void doWriting(RegistrationType* pReg)
				{
					if (!pReg)
					{
						mapDefaultExceptionStaticMacro( << "Cannot write data. Passed registration pointer is invalid (NULL).");
					}

					std::cout << std::endl << "save output file ... ";
  				std::cout << "(" << this->_appData->_outputFileName << ")... ";

					typedef ::map::io::RegistrationFileWriter<IDim, IDim> WriterType;
					typename WriterType::Pointer spWriter  = WriterType::New();
          spWriter->setExpandLazyKernels(false);
					spWriter->write(pReg, this->_appData->_outputFileName);

					std::cout << "done." << std::endl;
				};

				typename RegistrationType::Pointer doRegistration()
				{
					typedef typename ::map::core::discrete::Elements<IDim>::InternalImageType ImageType;

          //Now cast to the right interface (ImageRegistrationAlgorithmBase)
          //to set the images
          typedef map::algorithm::facet::ImageRegistrationAlgorithmInterface<ImageType, ImageType>
            ImageRegistrationAlgorithmInterfaceType;
          ImageRegistrationAlgorithmInterfaceType* pImageInterface =
            dynamic_cast<ImageRegistrationAlgorithmInterfaceType*>(this->_appData->_algorithm.GetPointer());

          if (pImageInterface)
          {
            const ImageType* moving = dynamic_cast<const ImageType*>(this->_appData->_spMovingImage.GetPointer());
            const ImageType* target = dynamic_cast<const ImageType*>(this->_appData->_spTargetImage.GetPointer());
            pImageInterface->setMovingImage(moving);
            pImageInterface->setTargetImage(target);
          }
          else
          {
            mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. Image Registration interface is missing. Check DLL.");
          }

          //Add observer for algorithm events.
          typename ::itk::MemberCommand< ProcessingLogic<IDim> >::Pointer command = ::itk::MemberCommand< ProcessingLogic<IDim> >::New();
          command->SetCallbackFunction(this, &ProcessingLogic<IDim>::onMapAlgorithmEvent);

          unsigned long observerID = this->_appData->_algorithm->AddObserver(map::events::AlgorithmEvent(), command);

          //Set meta properties
          ::map::algorithm::facet::MetaPropertyAlgorithmInterface* pMetaInterface =
            dynamic_cast< ::map::algorithm::facet::MetaPropertyAlgorithmInterface*>(this->_appData->_algorithm.GetPointer());

          if (pMetaInterface)
          {
            for (auto paramItr : this->_appData->_parameterMap)
            {
              ::map::algorithm::MetaPropertyInfo::Pointer info = pMetaInterface->getPropertyInfo(paramItr.first);

              if (info.IsNotNull() && info->isWritable())
              {
                std::cout << "Set meta property: " << paramItr.first << " = " <<paramItr.second << std::endl;
                ::map::core::MetaPropertyBase::Pointer prop = wrapMetaProperty(info, paramItr.second);
                if (prop.IsNull())
                {
                  mapDefaultExceptionStaticMacro(<< "Error. Cannot set specified meta property. Type conversion is not supported or value cannot be converted into type. Property name: " << info->getName() << "; property type: " << info->getTypeName());
                }
                else
                {
                  pMetaInterface->setProperty(paramItr.first, prop);
                }
              }
            }
          }

          //Cast algorithm, start the registration and get the result
          typename RegistrationType::Pointer result;
          AlgorithmType* castedAlgorithm = dynamic_cast<AlgorithmType*>(this->_appData->_algorithm.GetPointer());
          if (castedAlgorithm)
          {
            result = castedAlgorithm->getRegistration();
          }
          else
          {
            mapDefaultExceptionStaticMacro("Error. Wrong algorithm seemed to be loaded. Cannot be casted to determine the registration. Check DLL.");
          }

					return result;
				};

				void processData()
				{
          typename RegistrationType::Pointer reg = doRegistration();
					doWriting(reg);
        };

        ProcessingLogic(const ApplicationData& appData) : _appData(&appData)
        {
        };

      protected:

          const ApplicationData* _appData;
			};


		}
	}
}


#endif
