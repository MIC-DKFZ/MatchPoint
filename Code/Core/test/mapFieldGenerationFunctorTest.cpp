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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapFieldGenerationFunctorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapTestFieldGenerationFunctor.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		int mapFieldGenerationFunctorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef map::core::functors::FieldGenerationFunctor<2, 2>::InFieldRepresentationType InFieldRepresentationType;

			InFieldRepresentationType::Pointer spInField = InFieldRepresentationType::New();
			TestFieldGenerationFunctor<2, 2>::Pointer spTestFieldGenerationFunctor = TestFieldGenerationFunctor<2, 2>::New(spInField);

			CHECK(spInField == spTestFieldGenerationFunctor->getInFieldRepresentation());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
