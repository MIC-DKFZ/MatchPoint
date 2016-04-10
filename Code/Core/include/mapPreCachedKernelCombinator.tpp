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


#ifndef __MAP_PRE_CACHED_KERNEL_COMBINATOR_TPP
#define __MAP_PRE_CACHED_KERNEL_COMBINATOR_TPP

#include "itkMatrixOffsetTransformBase.h"
#include "itkCompositeTransform.h"
#include "mapPreCachedKernelCombinator.h"
#include "mapServiceException.h"

namespace map
{
    namespace core
    {

        template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        class PreCachedKernelCombinatorHelper
        {
        public:
            typedef typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::Kernel1Type Kernel1Type;
            typedef typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::Kernel2Type Kernel2Type;
            typedef typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::RequestType RequestType;
            typedef typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::InputFieldRepresentationType InputFieldRepresentationType;
            typedef typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::PaddingVectorType PaddingVectorType;
            typedef typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::CombinedKernelBasePointer CombinedKernelBasePointer;

            static inline
                CombinedKernelBasePointer
                combineKernels(const RequestType& request,
                const InputFieldRepresentationType* pInputFieldRepresentation,
                bool usePadding,
                const PaddingVectorType& paddingVector)
            {
                mapExceptionStaticMacro(ExceptionObject,
                    << "Error unsymmetric field inversion not implemented yet.");
                return NULL;
            }
        };

        template <unsigned int VDimensions>
        class PreCachedKernelCombinatorHelper < VDimensions, VDimensions, VDimensions >
        {
        public:
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::Kernel1Type Kernel1Type;
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::Kernel2Type Kernel2Type;
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::RequestType RequestType;
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::InputFieldRepresentationType InputFieldRepresentationType;
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::PaddingVectorType PaddingVectorType;
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::CombinedKernelBaseType CombinedKernelBaseType;
            typedef typename PreCachedKernelCombinator< VDimensions, VDimensions, VDimensions >::CombinedKernelBasePointer CombinedKernelBasePointer;

            static inline
                CombinedKernelBasePointer
                combineKernels(const RequestType& request,
                const InputFieldRepresentationType* pInputFieldRepresentation,
                bool usePadding,
                const PaddingVectorType& paddingVector)
            {
                const Kernel1Type* pKernel1 = dynamic_cast<const Kernel1Type*>(request._spKernel1.GetPointer());
                const Kernel2Type* pKernel2 = dynamic_cast<const Kernel2Type*>(request._spKernel2.GetPointer());

                if (pKernel1 == NULL)
                {
                    mapExceptionStaticMacro(ServiceException,
                        << "Error: cannot combine kernels. Reason: cannot cast first kernel to ModelBasedRegistrationKernel: "
                        << pKernel1);
                }

                if (pKernel2 == NULL)
                {
                    mapExceptionStaticMacro(ServiceException,
                        << "Error: cannot combine kernels. Reason: cannot cast second kernel to ModelBasedRegistrationKernel: "
                        << pKernel2);
                }

                CombinedKernelBasePointer spResult = combineAsMatrixKernels(pKernel1, pKernel2);

                if (spResult.IsNull())
                { //composite approach
                    typedef itk::CompositeTransform<::map::core::continuous::ScalarType, VDimensions> CompositeType;
                    CompositeType::Pointer composite = CompositeType::New();
                    //we decided to const cast instead of cloning (the composite transform can only take non const transforms),
                    //1) to avoid the payload of copying (e.g. fields),
                    //2) the compsite transform will be const, so the const removal will only be temporary 
                    //Remark: The composite transform applies in reversed order, thus 2nd kernel is added first.
                    composite->AddTransform(const_cast<Kernel2Type::TransformType*>(pKernel2->getTransformModel()));
                    composite->AddTransform(const_cast<Kernel1Type::TransformType*>(pKernel1->getTransformModel()));
                    typedef map::core::PreCachedRegistrationKernel<VDimensions, VDimensions> NewKernelType;
                    typename NewKernelType::Pointer newKernel = NewKernelType::New();
                    newKernel->setTransformModel(composite);
                    spResult = dynamic_cast<CombinedKernelBaseType*>(newKernel.GetPointer());
                }

                assert(spResult.IsNotNull());

                return spResult;
            }

            static CombinedKernelBasePointer
                combineAsMatrixKernels(const Kernel1Type* kernel1, const Kernel2Type* kernel2)
            {

                CombinedKernelBasePointer result;

                if (kernel1->getTransformModel() == NULL)
                {
                    mapExceptionStaticMacro(ServiceException,
                        << "Error: cannot combine kernels. Reason: 1st ModelBasedRegistrationKernel has undefined transform model (NULL).");
                }

                if (kernel2->getTransformModel() == NULL)
                {
                    mapExceptionStaticMacro(ServiceException,
                        << "Error: cannot combine kernels. Reason: 2nd ModelBasedRegistrationKernel has undefined transform model (NULL).");
                }

                /**@Remark: The current implementation only implements the combination of kernels with same input and output dimension (square matrices)
                Because of the limited api of the used MatrixOffsetTransformBase and the usage of the cloned second kernel*/
                typedef itk::MatrixOffsetTransformBase < typename Kernel1Type::TransformType::ScalarType, VDimensions, VDimensions >
                    Transform1Type;
                typedef itk::MatrixOffsetTransformBase < typename Kernel2Type::TransformType::ScalarType, VDimensions, VDimensions >
                    Transform2Type;
                typedef map::core::PreCachedRegistrationKernel<VDimensions, VDimensions> NewKernelType;

                const Transform1Type* transform1 = dynamic_cast<const Transform1Type*>
                    (kernel1->getTransformModel());
                const Transform2Type* transform2 = dynamic_cast<const Transform2Type*>
                    (kernel2->getTransformModel());

                if (transform1 && transform2)
                {
                    typename Transform2Type::Pointer newModel = dynamic_cast<Transform2Type*>(transform2->Clone().GetPointer());

                    if (newModel)
                    {
                        newModel->Compose(transform1, true);

                        typename NewKernelType::Pointer newKernel = NewKernelType::New();
                        newKernel->setTransformModel(newModel);
                        result = dynamic_cast<CombinedKernelBaseType*>(newKernel.GetPointer());
                    }
                }

                return result;
            };

        };

        template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        typename PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::CombinedKernelBasePointer
            PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
            combineKernels(const RequestType& request,
            const InputFieldRepresentationType* pInputFieldRepresentation,
            bool usePadding,
            const PaddingVectorType& paddingVector) const
        {
            return PreCachedKernelCombinatorHelper<VInputDimensions, VInterimDimensions, VOutputDimensions>::combineKernels(request, pInputFieldRepresentation, usePadding, paddingVector);
        }

        template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        bool
            PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
            canHandleRequest(const RequestType& request) const
        {
            // get the two kernels from the request (which is a RegistrationCombinationRequest object)
            // and check if they are both FieldKernels
            const Kernel1Type* pKernel1 = dynamic_cast<const Kernel1Type*>(request._spKernel1.GetPointer());
            const Kernel2Type* pKernel2 = dynamic_cast<const Kernel2Type*>(request._spKernel2.GetPointer());

            return ((pKernel1 != NULL) && (pKernel2 != NULL)) && (VInputDimensions == VInterimDimensions && VInterimDimensions == VOutputDimensions);
        }

        template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        String
            PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
            getProviderName() const
        {
            return Self::getStaticProviderName();
        }

        template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        String
            PreCachedKernelCombinator<VInputDimensions, VInterimDimensions, VOutputDimensions>::
            getStaticProviderName()
        {
            OStringStream os;
            os << "PreCachedKernelCombinator<" << VInputDimensions << "," << VInterimDimensions << "," <<
                VOutputDimensions << ">";
            return os.str();
        }

        template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        String
            PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
            getDescription() const
        {
            OStringStream os;
            os << "PreCachedKernelCombinator, VInputDimensions: " << VInputDimensions <<
                ", VInterimDimensions: " << VInterimDimensions << ", VOutputDimensions: " << VOutputDimensions <<
                ".";
            return os.str();
        }


    } // end namespace core
} // end namespace map

#endif
