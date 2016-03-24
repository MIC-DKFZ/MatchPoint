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


#ifndef __MAP_TEST_LOAD_POLICY_H
#define __MAP_TEST_LOAD_POLICY_H

#include "mapTestServiceProvider.h"
#include "mapGenericStaticLoadPolicyBase.h"

namespace map
{
	namespace testing
	{

		class  TestLoadPolicy: public core::services::GenericStaticLoadPolicyBase<TestServiceProviderBase>
		{
		protected:
			virtual void doLoading()
			{
				::map::core::services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(_pLoadInterface);
				loader.addProviderByPolicy(TestServiceProvider<1>::New());
				loader.addProviderByPolicy(TestServiceProvider<2>::New());
			};

			TestLoadPolicy() {};
			~TestLoadPolicy() {};
		private:
			TestLoadPolicy(const TestLoadPolicy&);  //purposely not implemented
			void operator=(const TestLoadPolicy&);  //purposely not implemented
		};

	} //namespace testing
} //namespace map

#endif
