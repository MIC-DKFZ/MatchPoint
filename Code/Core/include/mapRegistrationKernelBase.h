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


#ifndef __REGISTRATION_KERNEL_BASE_H
#define __REGISTRATION_KERNEL_BASE_H

#include "mapFieldRepresentationDescriptor.h"
#include "mapDimensionlessRegistrationKernelBase.h"
#include "mapRegistrationTopology.h"

#include "itkObject.h"

namespace map
{
    namespace core
    {

        /*! @class RegistrationKernelBase
            This class is the base class for the registration kernels.
            @ingroup RegKernel
            */
        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        class RegistrationKernelBase : public DimensionlessRegistrationKernelBase
        {
        public:
            using Self = RegistrationKernelBase<VInputDimensions, VOutputDimensions>;
            using Superclass = DimensionlessRegistrationKernelBase;
            using Pointer = itk::SmartPointer<Self>;
            using ConstPointer = itk::SmartPointer<const Self>;

            itkTypeMacro(RegistrationKernelBase, DimensionlessRegistrationKernelBase);
            itkCloneMacro(Self);

            itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
            itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

            using InputPointType = typename continuous::Elements<VInputDimensions>::PointType;
            using OutputPointType = typename continuous::Elements<VOutputDimensions>::PointType;
            typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType
                MappingVectorType;

            typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectTransformType TransformType;
            using OutputVectorType = typename TransformType::OutputVectorType;

            using RepresentationDescriptorType = FieldRepresentationDescriptor<VInputDimensions>;
            using RepresentationDescriptorPointer = typename RepresentationDescriptorType::Pointer;
            using RepresentationDescriptorConstPointer = typename RepresentationDescriptorType::ConstPointer;

            /*! maps a point as long as it is within the field representation of the kernel by calling doMapPoint()
              @param inPoint Point that should be mapped.
              @param outPoint Mapping result. If the input point cannot be mapped the return of the method will be false and outPoint will be zero.
              @eguarantee strong
              @return success of operation
              @retval true Point was mapped
              @retval false Point was not in the represented region of the kernel and thus not mapped.
              By default outPoint will then be zero.
              */
            bool mapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const;


            /*! @brief determines if there is a limit in the data representation of the kernel
              @eguarantee strong
              @return if the registration kernel has limited representation
              @retval true if the data representation is limited
              @retval false if the data representation is not limited
              */
            bool hasLimitedRepresentation() const override;

            /*! @brief gets the largest possible representation descriptor. The descriptor defines
             * the space the kernel guarantees to map.
             * @return Smart pointer to the descriptor (may be generated dynamically)
             * @retval NULL there is no descriptor. If hasLimitedRepresentation returns false, the kernel
             * has no mapping limitations and covers the total input space.
             @eguarantee strong
             */
            virtual RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const = 0;

            /*! @brief forces kernel to precompute, even if it is a LazyFieldKernel
              @eguarantee strong
              */
            void precomputeKernel() const override = 0;

            /*! @brief Gets the number of input dimensions
            @eguarantee no fail
            */
            unsigned int getInputDimensions() const override
            {
                return InputDimensions;
            };

            /*! @brief Gets the number of output dimensions
            @eguarantee no fail
            */
            unsigned int getOutputDimensions() const override
            {
                return OutputDimensions;
            };

        protected:

            /*! Methods invoked by itk::LightObject::Print().  */
            void PrintSelf(std::ostream& os, itk::Indent indent) const override;

            /*! Maps the point from input to output space. Is used by mapPoint()
              @eguarantee strong
              */
            virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const = 0;

            RegistrationKernelBase();
            ~RegistrationKernelBase() override;

        private:
            //No copy constructor allowed
            RegistrationKernelBase(const Self& source);
            void operator=(const Self&);  //purposely not implemented

        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        std::ostream& operator<< (std::ostream& os,
            const RegistrationKernelBase<VInputDimensions, VOutputDimensions>& p)
        {
            p.Print(os);
            return os;
        }

    }  // namespace core
}  // namespace map


#ifndef MatchPoint_MANUAL_TPP
#include "mapRegistrationKernelBase.tpp"
#endif

#endif
