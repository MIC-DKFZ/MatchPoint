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
// @version $Revision: 1285 $ (last changed revision)
// @date    $Date: 2016-03-30 17:47:52 +0200 (Mi, 30 Mrz 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapRegistrationKernel.h $
*/

#ifndef __LAZY_REGISTRATION_KERNEL_H
#define __LAZY_REGISTRATION_KERNEL_H

#include "mapRegistrationKernel.h"
#include "mapLazyRegistrationKernelInterface.h"
#include "itkSimpleFastMutexLock.h"

/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
    namespace core
    {

        /*! This class is the implementation of a lazy kernel. The lazy kernel
     * establishes its internal transformation when it is needed the first time
     * on the fly by using its generation functor.
     * @ingroup RegKernel
     */
        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        class LazyRegistrationKernel : public RegistrationKernel<VInputDimensions, VOutputDimensions>,
            public LazyRegistrationKernelInterface < VInputDimensions, VOutputDimensions >
        {
        public:
            typedef LazyRegistrationKernel<VInputDimensions, VOutputDimensions>	Self;
            typedef RegistrationKernel<VInputDimensions, VOutputDimensions> Superclass;
            using Pointer = itk::SmartPointer<Self>;
            using ConstPointer = itk::SmartPointer<const Self>;

            itkNewMacro(Self);
            itkTypeMacro(LazyRegistrationKernel, RegistrationKernel);

            using TransformType = typename Superclass::TransformType;
            using RepresentationDescriptorType = typename Superclass::RepresentationDescriptorType;
            using RepresentationDescriptorPointer = typename Superclass::RepresentationDescriptorPointer;
            using RepresentationDescriptorConstPointer = typename Superclass::RepresentationDescriptorConstPointer;
            using InputPointType = typename Superclass::InputPointType;
            using OutputPointType = typename Superclass::OutputPointType;
            using MappingVectorType = typename Superclass::MappingVectorType;


            typedef functors::TransformGenerationFunctor < VInputDimensions, VOutputDimensions >
                TransformGenerationFunctorType;
            using TransformGenerationFunctorConstPointer = typename TransformGenerationFunctorType::ConstPointer;

            /*! sets the field's functor
            @eguarantee no fail
            @param functor Pointer to the functor that is responsible for generating the field
            @pre functor must point to a valid instance.
            */
            void setTransformFunctor(const TransformGenerationFunctorType* functor) override;

            /*! gets the field's functor
            @eguarantee no fail
            @return Pointer to the field functor that is used to generate the field on demand.
            */
            const TransformGenerationFunctorType*  getTransformFunctor() const override;

            /*! Returns if the transform was already created (true) or if the generation still is pending / wasn't necessary (false).
            @eguarantee strong
            */
            bool transformExists() const override;

            /*! @brief gets the largest possible representation descriptor. The descriptor defines
             * the space the kernel guarantees to map.
             * @return Smart pointer to the descriptor (may be generated dynamicaly)
             * @retval NULL there is no descriptor. If hasLimitedRepresentation returns false, the kernel
             * has no mapping limitations and covers the total input space.
             * @eguarantee strong
             */
            RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const override;

            /*! Returns pointer to the transform model used by the kernel
            @eguarantee strong
            @return const pointer to the internal tranform model
            */
            const TransformType* getTransformModel() const override;

            const OutputPointType getNullPoint() const override;

            bool usesNullPoint() const override;

        protected:
            LazyRegistrationKernel();
            virtual ~LazyRegistrationKernel();

            using TransformPointer = typename TransformType::Pointer;
            //is mutable because it is a cache for the functor result, thus it may be changed by checkAndPrepareTransform()
            mutable TransformPointer _spTransform;

            TransformGenerationFunctorConstPointer _spGenerationFunctor;

            /*! checks the transform that has been set for correctness and prepares it to be used
            @eguarantee strong
            @return the success of the operation
            */
            bool checkAndPrepareTransform() const override;

            /*! Methods invoked by itk::LightObject::Print().  */
            virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

            /** @reimplementation
            Reimplementation of the itk::LightObject::InternalClone*/
            virtual ::itk::LightObject::Pointer	InternalClone()	const;

        private:
            using MutexType = ::itk::SimpleFastMutexLock;
            /*!Mutex to make the checks of the policy thread safe*/
            mutable MutexType _checkMutex;
            /*!Mutex to make the generation of the fields thread safe and to avoid paralel
            * generation of fields because of a racing condition of two checkAndPrepare calls*/
            mutable MutexType _generateMutex;

            //No copy constructor allowed
            LazyRegistrationKernel(const Self& source);
            void operator=(const Self&);  //purposely not implemented

        };

    }  // namespace core
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapLazyRegistrationKernel.tpp"
#endif

#endif
