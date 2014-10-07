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

#include "mapInvertingFieldBasedRegistrationKernel.h"
#include "litCheckMacros.h"
#include "mapModelBasedRegistrationKernel.h"

namespace map
{
	namespace testing
	{

		int mapInvertingFieldBasedRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

      typedef core::InvertingFieldBasedRegistrationKernel<3, 2> KernelType;
			typedef core::ModelBasedRegistrationKernel<2, 3> SourcelKernelType;

			SourcelKernelType::Pointer spSourceKernel = SourcelKernelType::New();
      KernelType::Pointer spKernel = KernelType::New();

      //just check the additions to the "normal" lazy field kernel

			CHECK(spKernel->getSourceKernel() == NULL); //default must be null

      CHECK_NO_THROW(spKernel->setSourceKernel(spSourceKernel));
      
      CHECK(spKernel->getSourceKernel() == spSourceKernel.GetPointer());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
