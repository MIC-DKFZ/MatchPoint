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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/test/mapDeploymentDLLHelperTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapDummyImageRegistrationAlgorithm.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
    mapGenerateAlgorithmUIDPolicyMacro(DeploymentDLLHelperTestAlgUIDPolicy,"de.dkfz.matchpoint","DeploymentDLLHelperTest","1.0.0","profile");

		int mapDeploymentDLLHelperTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
			typedef map::algorithm::DummyImageRegistrationAlgorithm<ImageType, ImageType, DeploymentDLLHelperTestAlgUIDPolicy> AlgorithmType;

			typedef map::deployment::DeploymentDLLHelper<AlgorithmType> DLLHelperType;

			//test UID retrieve
			map::algorithm::UID::Pointer spUIDRef = DeploymentDLLHelperTestAlgUIDPolicy::UID();

			map::algorithm::UID::Pointer spUID;

			CHECK_NO_THROW(spUID = DLLHelperType::mapGetRegistrationAlgorithmUID());

			CHECK(spUID.IsNotNull());
			CHECK_EQUAL(spUIDRef->getNamespace(), spUID->getNamespace());
			CHECK_EQUAL(spUIDRef->getName(), spUID->getName());
			CHECK_EQUAL(spUIDRef->getVersion(), spUID->getVersion());
			CHECK_EQUAL(spUIDRef->getBuildTag(), spUID->getBuildTag());

			//test algorithm retrieve
			map::algorithm::RegistrationAlgorithmBase::Pointer spAlgorithm;

			CHECK_NO_THROW(spAlgorithm = DLLHelperType::mapGetRegistrationAlgorithmInstance(NULL));

			CHECK(spAlgorithm.IsNotNull());

			CHECK(dynamic_cast<AlgorithmType *>(spAlgorithm.GetPointer()));

			CHECK_NO_THROW(spUID = spAlgorithm->getUID());

			CHECK(spUID.IsNotNull());
			CHECK_EQUAL(spUIDRef->getNamespace(), spUID->getNamespace());
			CHECK_EQUAL(spUIDRef->getName(), spUID->getName());
			CHECK_EQUAL(spUIDRef->getVersion(), spUID->getVersion());
			CHECK_EQUAL(spUIDRef->getBuildTag(), spUID->getBuildTag());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
