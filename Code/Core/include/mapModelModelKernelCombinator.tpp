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


#ifndef __MAP_MODEL_MODEL_KERNEL_COMBINATOR_TPP
#define __MAP_MODEL_MODEL_KERNEL_COMBINATOR_TPP

#include "itkMatrixOffsetTransformBase.h"

#include "mapModelModelKernelCombinator.h"
#include "mapServiceException.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		typename ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::CombinedKernelBasePointer
		ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		combineKernels(const RequestType& request,
					   const InputFieldRepresentationType* pInputFieldRepresentation,
					   bool usePadding,
					   const PaddingVectorType& paddingVector) const
		{
			const Kernel1Type* pKernel1 = dynamic_cast<const Kernel1Type*>(request._spKernel1.GetPointer());
			const Kernel2Type* pKernel2 = dynamic_cast<const Kernel2Type*>(request._spKernel2.GetPointer());

			if (pKernel1 == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot combine kernels. Reason: cannot cast first kernel to ModelBasedRegistrationKernel: "
								  << pKernel1);
			}

			if (pKernel2 == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot combine kernels. Reason: cannot cast second kernel to ModelBasedRegistrationKernel: "
								  << pKernel2);
			}

      CombinedKernelBasePointer spResult = this->combineAsMatrixKernels(pKernel1, pKernel2);
      
      if(spResult.IsNull())
      {
			  /*!@todo Must implement combination of non matrix based transform models. Therefore a kinde of itk::CombinationTransform is needed.
			   current insight journal implementation of Steiner is a good start but has flaws (only access to the parameters of the second transform)
			   Exception is a reminder for the open business.
			   */
			  mapExceptionMacro(ServiceException, << "Error: TransformModel combination for non matrix based transformation models is not implemented yet.");
      }

			return spResult;
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		typename ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::CombinedKernelBasePointer
		ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
    combineAsMatrixKernels(const Kernel1Type* kernel1, const Kernel2Type* kernel2) const
    {

      CombinedKernelBasePointer result;

			if (kernel1->getTransformModel() == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot combine kernels. Reason: 1st ModelBasedRegistrationKernel has undefined transform model (NULL).");
			}

			if (kernel2->getTransformModel() == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot combine kernels. Reason: 2nd ModelBasedRegistrationKernel has undefined transform model (NULL).");
			}

      if (VInputDimensions==VInterimDimensions && VInterimDimensions == VOutputDimensions)
      {
      /**@Remark: The current implementation only implements the combination of kernels with same input and output dimension (square matrices)
         Because of the limited api of the used MatrixOffsetTransformBase and the usage of the cloned second kernel*/
        typedef itk::MatrixOffsetTransformBase<Kernel1Type::TransformType::ScalarType,VOutputDimensions,VOutputDimensions> Transform1Type;
        typedef itk::MatrixOffsetTransformBase<Kernel2Type::TransformType::ScalarType,VOutputDimensions,VOutputDimensions> Transform2Type;
        typedef map::core::ModelBasedRegistrationKernel<VOutputDimensions,VOutputDimensions> NewKernelType; 

        const Transform1Type* transform1 = dynamic_cast<const Transform1Type*>(kernel1->getTransformModel()->getTransform());
        const Transform2Type* transform2 = dynamic_cast<const Transform2Type*>(kernel2->getTransformModel()->getTransform());

        if (transform1 && transform2)
        {
          typename NewKernelType::TransformType::Pointer newModel = dynamic_cast<typename NewKernelType::TransformType*>(kernel2->getTransformModel()->clone().GetPointer());

          Transform2Type* resultTransform = dynamic_cast<Transform2Type*>(newModel->getTransform());

          if (resultTransform)
          {
            resultTransform->Compose(transform1,true);

            typename NewKernelType::Pointer newKernel = NewKernelType::New();
            newKernel->setTransformModel(newModel);
            result = dynamic_cast<CombinedKernelBaseType*>(newKernel.GetPointer());
          }
        }
      }

      return result;
    };

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		bool
		ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		canHandleRequest(const RequestType& request) const
		{
			// get the two kernels from the request (which is a RegistrationCombinationRequest object)
			// and check if they are both FieldKernels
			const Kernel1Type* pKernel1 = dynamic_cast<const Kernel1Type*>(request._spKernel1.GetPointer());
			const Kernel2Type* pKernel2 = dynamic_cast<const Kernel2Type*>(request._spKernel2.GetPointer());

			return ((pKernel1 != NULL) && (pKernel2 != NULL));
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		String
		ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		String
		ModelModelKernelCombinator<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "ModelModelKernelCombinator<" << VInputDimensions << "," << VInterimDimensions << "," <<
			   VOutputDimensions << ">";
			return os.str();
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		String
		ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		getDescription() const
		{
			OStringStream os;
			os << "ModelModelKernelCombinator, VInputDimensions: " << VInputDimensions <<
			   ", VInterimDimensions: " << VInterimDimensions << ", VOutputDimensions: " << VOutputDimensions <<
			   ".";
			return os.str();
		}


	} // end namespace core
} // end namespace map

#endif
