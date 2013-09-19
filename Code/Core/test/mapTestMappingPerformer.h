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


#ifndef __MAP_TEST_MAPPING_PERFORMER_H
#define __MAP_TEST_MAPPING_PERFORMER_H

#include "mapMappingPerformerBase.h"
#include "mapPointSetMappingPerformerRequest.h"
#include "mapModelBasedRegistrationKernel.h"

namespace map
{
	namespace testing
	{
		/*! @class TestMappingPerformer
		* @brief Test class used for registration task tests.
		*/
		template <class TRequestType, class TBase = core::MappingPerformerBase<TRequestType> >
		class TestMappingPerformer : public TBase
		{
		public:
			typedef TRequestType RequestType;
			/*! Standard class typedefs. */
			typedef TestMappingPerformer<RequestType, TBase>  Self;
			typedef TBase	 Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TestMappingPerformer, TBase);
			itkNewMacro(Self);

			typedef typename Superclass::RegistrationType		    RegistrationType;

			typedef typename Superclass::InputDataType			    InputDataType;
			typedef typename Superclass::InputDataConstPointer	InputDataConstPointer;
			typedef typename Superclass::ResultDataType			    ResultDataType;
			typedef typename Superclass::ResultDataPointer	    ResultDataPointer;

			mutable ResultDataPointer _spCurrentResult;
			mutable RequestType* _pCurrentRequest;
			mutable bool _handleRequest;
			mutable unsigned _performanceCount;

			virtual ResultDataPointer performMapping(const RequestType& request) const
			{
				delete _pCurrentRequest;
				_pCurrentRequest = new RequestType(request);
				++_performanceCount;
				return _spCurrentResult;
			};

			virtual bool canHandleRequest(const RequestType& request) const
			{
				delete _pCurrentRequest;
				_pCurrentRequest = new RequestType(request);
				return _handleRequest;
			};

			virtual std::string getProviderName() const
			{
				return getStaticProviderName();
			};

			static std::string getStaticProviderName()
			{
				return "TestMappingPerformer";
			};

			virtual std::string getDescription() const
			{
				return getStaticProviderName();
			};

		protected:

			TestMappingPerformer()
			{
				_handleRequest = false;
				_performanceCount = 0;
				_pCurrentRequest = 0;
			};

			virtual ~TestMappingPerformer()
			{
				delete _pCurrentRequest;
			};

		private:
			TestMappingPerformer(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace testing
} // end namespace map


#endif
