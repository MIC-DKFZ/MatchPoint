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

#ifndef __COMBINED_REGISTRATION_KERNEL_H
#define __COMBINED_REGISTRATION_KERNEL_H

#include "mapLazyRegistrationKernel.h"
#include "mapCombinationFunctorInterface.h"


/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
    namespace core
    {

        /*!@brief  CombinedRegistrationKernel is a special implementation of a lazy registration kernel.
         * This implementation uses a combination functor to generate its field. In contrast to the normal lazy kernel
         * implementation, this kernel maps points directly by using its functor given source kernels. Thus no field will generated
         * just for mapping points. The field must be generated explicitly by calling gernerateField().
         * @ingroup RegKernel
         */
        template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        class CombinedRegistrationKernel : public
            LazyRegistrationKernel < VInputDimensions, VOutputDimensions >
        {
        public:
            typedef CombinedRegistrationKernel < VInputDimensions, VInterimDimensions, VOutputDimensions >
                Self;
            typedef LazyRegistrationKernel<VInputDimensions, VOutputDimensions>	Superclass;
            typedef itk::SmartPointer<Self> Pointer;
            typedef itk::SmartPointer<const Self> ConstPointer;

            itkTypeMacro(CombinedRegistrationKernel, LazyRegistrationKernel);
            itkNewMacro(Self);

            typedef typename Superclass::RepresentationDescriptorType RepresentationDescriptorType;
            typedef typename Superclass::RepresentationDescriptorPointer RepresentationDescriptorPointer;
            typedef typename Superclass::RepresentationDescriptorConstPointer
                RepresentationDescriptorConstPointer;
            typedef typename Superclass::TransformGenerationFunctorType TransformGenerationFunctorType;
            typedef typename Superclass::InputPointType  InputPointType;
            typedef typename Superclass::OutputPointType OutputPointType;

            /*! sets the field's functor
            @eguarantee no fail
            @param functor Pointer to the functor that is responsible for generating the field
            @pre functor must point to a valid instance.
            */
            virtual void setTransformFunctor(const TransformGenerationFunctorType* functor) override;

        protected:
            typedef functors::CombinationFunctorInterface < VInputDimensions, VInterimDimensions, VOutputDimensions >
                CombinationFunctorInterfaceType;
            typedef typename CombinationFunctorInterfaceType::SourceKernel1BaseType SourceKernel1BaseType;
            typedef typename CombinationFunctorInterfaceType::SourceKernel2BaseType SourceKernel2BaseType;

            const CombinationFunctorInterfaceType* _pCombinationInterface;

            /*! maps a given point by using both source kernel. In contrast to other LazyRegistrationKernel classes,
             * calling this methos will not trigger the generation of the kernel field.
             @eguarantee no fail
             @param functor Reference to the functor that is responsible for generating the field
             @pre Functor must have implemented CombinationFunctorInterface
             */
            virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const;

            CombinedRegistrationKernel();
            virtual ~CombinedRegistrationKernel();


            /*! Methods invoked by itk::LightObject::Print().  */
            virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

        private:

            //No copy constructor allowed
            CombinedRegistrationKernel(const Self& source);
            void operator=(const Self&);  //purposely not implemented

        };

    }
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapCombinedRegistrationKernel.tpp"
#endif

#endif
