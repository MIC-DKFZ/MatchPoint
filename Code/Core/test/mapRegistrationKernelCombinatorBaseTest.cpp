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

#include "mapRegistrationKernelCombinatorBase.h"

#include "litCheckMacros.h"


namespace map
{
	namespace testing
	{

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class TestRegistrationKernelCombinatorBase: public
			core::RegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>
		{
		public:

			typedef TestRegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>
			Self;
			typedef core::RegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>
			Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			typedef typename Superclass::CombinedKernelBasePointer CombinedKernelBasePointer;
			typedef typename Superclass::RequestType RequestType;
			typedef typename Superclass::InputFieldRepresentationType InputFieldRepresentationType;
			typedef typename Superclass::PaddingVectorType PaddingVectorType;

			itkNewMacro(Self);

			CombinedKernelBasePointer combineKernels(const RequestType& request,
					const InputFieldRepresentationType* pInputFieldRepresentation,
					bool usePadding = false,
					const PaddingVectorType& paddingVector = PaddingVectorType(0.0)) const
			{
				CombinedKernelBasePointer spDummy;
				return spDummy;
			}

			virtual bool canHandleRequest(const RequestType& request) const
			{
				return false;
			}

			virtual std::string getProviderName() const
			{
				return "dummy";
			}

			virtual std::string getDescription() const
			{
				return "dummy";
			}

		};

		int mapRegistrationKernelCombinatorBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef TestRegistrationKernelCombinatorBase<2, 2, 2> BaseType;
			CHECK_NO_THROW(BaseType::Pointer spCombinator = BaseType::New());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
