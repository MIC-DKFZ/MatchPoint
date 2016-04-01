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

			typedef map::core::functors::TransformGenerationFunctor<2, 2>::InFieldRepresentationType
			InFieldRepresentationType;

			InFieldRepresentationType::Pointer spInField = InFieldRepresentationType::New();
			TestFieldGenerationFunctor<2, 2>::Pointer spTestFieldGenerationFunctor =
				TestFieldGenerationFunctor<2, 2>::New(spInField);

			CHECK(spInField == spTestFieldGenerationFunctor->getInFieldRepresentation());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
