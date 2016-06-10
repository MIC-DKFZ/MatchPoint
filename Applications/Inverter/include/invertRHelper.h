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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/include/invertRHelper.h $
*/


#ifndef __MAP_R_HELPER_H
#define __MAP_R_HELPER_H

#include "itkStdStreamLogOutput.h"
#include "itkVersion.h"

#include "gdcmUIDGenerator.h"

#include "mapConvert.h"
#include "mapExceptionObjectMacros.h"
#include "mapGenericImageReader.h"
#include "mapRegistrationFileReader.h"
#include "mapRegistrationFileWriter.h"

#include "mapRegistrationManipulator.h"
#include "mapInverseRegistrationKernelGenerator.h"

#include "invertRApplicationData.h"

namespace map
{
	namespace apps
	{
		namespace invertR
		{

			/** Helper class that contains the logic that handles the data loading according to the settings in appData.
			* the loaded data will be stored in app data. */
			class LoadingLogic
			{
			public:
				LoadingLogic(ApplicationData& appData);
				void loadRegistration();
				void loadReferenceImage();
			protected:
				ApplicationData& _appData;
			};


      template <unsigned int IMDim, unsigned int ITDim>
			class ProcessingLogic
			{
			public:
				typedef ::itk::ImageBase<IMDim> MovingImageType;
        typedef ::itk::ImageBase<ITDim> TovingImageType;
        typedef ::map::core::Registration<ITDim, IMDim> InvertedRegType;
        typedef ::map::core::Registration<IMDim, ITDim> RegType;

				/**write the inverted registration according to the settings in appData.
				* @pre pReg must point to a valid instance.*/
        static void doWriting(const InvertedRegType* pReg, const ApplicationData& appData)
				{
          if (!pReg)
					{
						mapDefaultExceptionStaticMacro( << "Cannot write data. Passed registration pointer is invalid (NULL).");
					}

					std::cout << std::endl << "save output registration file ... ";
					std::cout << "(" << appData._outputFileName << ")... ";

          typedef ::map::io::RegistrationFileWriter<ITDim, IMDim> RegFileWriterType;

          typename RegFileWriterType::Pointer writer = RegFileWriterType::New();

          writer->expandLazyKernels(true);
          if (writer->write(pReg, appData._outputFileName))
          {
            std::cout << "done." << std::endl;
          }
          else
          {
            std::cout << "failed." << std::endl;
          }

				};

        static typename InvertedRegType::Pointer doInversion(const ApplicationData& appData)
				{
          typedef map::core::RegistrationManipulator<InvertedRegType> RegistrationManipulatorType;

          const RegType* pReg = dynamic_cast<const RegType*>(appData._spReg);

          if (!pReg)
          {
            mapDefaultExceptionStaticMacro(<< "Cannot invert reg. Passed registration pointer is invalid (NULL).");
          }

          typename InvertedRegType::Pointer spIReg = InvertedRegType::New();
          RegistrationManipulatorType manipulator(spIReg);

          manipulator.setDirectMapping(pReg->getInverseMapping());
          manipulator.setInverseMapping(pReg->getDirectMapping());
          manipulator.getTagValues()[tags::AlgorithmUID] = "map::InverteR";
          std::string sourceID = "unknown";
          pReg->getTagValue(map::tags::RegistrationUID, sourceID);
          manipulator.getTagValues()["SourceRegistrationUID"] = sourceID;

          return spIReg;
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
