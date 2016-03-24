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

#ifndef __MAP_TEST_SERVICE_PROVIDER_H
#define __MAP_TEST_SERVICE_PROVIDER_H

#include "mapServiceProvider.h"

namespace map
{
	namespace testing
	{
		typedef core::services::ServiceProvider<int> TestServiceProviderBase;

		template<unsigned int VLegalRequest>
		class TestServiceProvider : public TestServiceProviderBase
		{
		public:
			/*! Standard class typedefs. */
			typedef TestServiceProvider<VLegalRequest>  Self;
			typedef TestServiceProviderBase Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TestServiceProvider, TestServiceProviderBase);

			static Pointer New(void)
			{
				Pointer smartPtr = new Self;
				smartPtr->UnRegister();
				return smartPtr;
			}

			virtual bool canHandleRequest(const RequestType& request) const
			{
				return request == VLegalRequest;
			};

			virtual std::string getProviderName() const
			{
				::map::core::OStringStream stream;
				stream << "TestServiceProvider_" << VLegalRequest;
				return stream.str();
			};

			virtual std::string getDescription() const
			{
				return "a simple test provider";
			};

		protected:
			TestServiceProvider() {};
			virtual ~TestServiceProvider() {};

		private:
			TestServiceProvider(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};


	} // end namespace testing
} // end namespace map

#endif
