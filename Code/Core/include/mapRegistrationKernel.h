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

#ifndef __REGISTRATION_KERNEL_H
#define __REGISTRATION_KERNEL_H

#include "mapRegistrationKernelBase.h"

/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
    namespace core
    {

        /*! RegistrationKernel implementation.
         * This class is the base class for concrete implemented registration kernels,
         * that define the mapping via a itk transformation model.
         * The concrete transform management behavior will be implemented by derived classes.
         * @ingroup RegKernel
         */
        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        class RegistrationKernel : public
            RegistrationKernelBase < VInputDimensions, VOutputDimensions >
        {
        public:
            typedef RegistrationKernel < VInputDimensions, VOutputDimensions >
                Self;
            typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
            typedef itk::SmartPointer<Self> Pointer;
            typedef itk::SmartPointer<const Self> ConstPointer;

            itkTypeMacro(RegistrationKernel, RegistrationKernelBase);

            typedef typename Superclass::TransformType TransformType;
            typedef typename Superclass::RepresentationDescriptorType RepresentationDescriptorType;
            typedef typename Superclass::RepresentationDescriptorPointer RepresentationDescriptorPointer;
            typedef typename Superclass::RepresentationDescriptorConstPointer
                RepresentationDescriptorConstPointer;
            typedef typename Superclass::InputPointType  InputPointType;
            typedef typename Superclass::OutputPointType OutputPointType;

            /*! Returns pointer to the transform model used by the kernel
            @eguarantee strong
            @return const pointer to the internal tranform model
            */
            virtual const TransformType* getTransformModel() const = 0;

            /*! @brief forces kernel to precompute, even if it is a LazyFieldKernel
              @eguarantee strong
              */
            virtual void precomputeKernel() override;

            /*! Returns if the transform was already created or if the generation still is pending / wasn't necessary.
            @eguarantee strong
            */
            virtual bool transformExists() const = 0;

            /*! gets the name of the model
            @eguarantee strong
            @return an String containing the model name
            */
            virtual String getModelName() const;

            typedef itk::Matrix<continuous::ScalarType, VOutputDimensions, VInputDimensions> MatrixType;

            /*! Tries to decompose the transform model into an affine matrix and an offset. It is indecated by the return value if
            * the actual modell can be decomposed.\n
            * Usage of the return values: Point_trans = Matrix*Point + Offset
            *
            * @eguarantee strong
            * @remark Implement the function for special transform model classes.
            * @param [out] matrix Reference to the matrix that define the affine non-translation part (e.g. rotation and scaling).
            * @param [out] offset Reference to a vector that defines the translation offset.
            * @return Indicates if the transform model can be decomposed in a affine transformation matrix plus offset. If it returns false, it cannot be decomposed
            * and the referenced output parameters are invalid.*/
            virtual bool getAffineMatrixDecomposition(MatrixType& matrix, OutputVectorType& offset) const;

            virtual const OutputPointType getNullPoint() const = 0;

            virtual bool usesNullPoint() const = 0;

        protected:
            RegistrationKernel();
            virtual ~RegistrationKernel();

            virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const override;

            /*! checks the transform that has been set for correctness and prepares it to be used
            @eguarantee strong
            @return the success of the operation
            */
            virtual bool checkAndPrepareTransform() const = 0;

            /*! Methods invoked by itk::LightObject::Print().  */
            virtual void PrintSelf(std::ostream& os, itk::Indent indent) const override;

        private:

            //No copy constructor allowed
            RegistrationKernel(const Self& source);
            void operator=(const Self&);  //purposely not implemented

        };

    }
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapRegistrationKernel.tpp"
#endif

#endif
