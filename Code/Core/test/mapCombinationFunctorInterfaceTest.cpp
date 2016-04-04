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

#include "mapCombinationFunctorInterface.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		// create derived class from interface to be able to instantiate interface class standalone
		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class TestCombinationFunctorInterface: public
			::map::core::functors::CombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
		{
		public:
        typedef core::functors::CombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
			Superclass;

        TestCombinationFunctorInterface()
			{}

			virtual const typename Superclass::SourceKernel1BaseType* get1stSourceKernelBase(void) const
			{
				//illegal post condition, but not relevant for this test class
				return NULL;
			};

			virtual const typename Superclass::SourceKernel2BaseType* get2ndSourceKernelBase(void) const
			{
				//illegal post condition, but not relevant for this test class
				return NULL;
			};

		};



		int mapCombinationFunctorInterfaceTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

      typedef TestCombinationFunctorInterface<2, 2, 2> InterfaceType;

			InterfaceType ifc;

			// check for correct default values
			CHECK_EQUAL(false, ifc.getUsePadding());
			InterfaceType::PaddingVectorType testVector;
			testVector.Fill(0.0);
			CHECK_EQUAL(testVector, ifc.getPaddingVector());

			// test setters and getters
			CHECK_NO_THROW(ifc.setUsePadding(true));
			CHECK_EQUAL(true, ifc.getUsePadding());

			testVector.Fill(4.0);
			CHECK_NO_THROW(ifc.setPaddingVector(testVector));
			CHECK_EQUAL(testVector, ifc.getPaddingVector());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
