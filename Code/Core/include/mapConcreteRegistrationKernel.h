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

#ifndef __CONCRETE_REGISTRATION_KERNEL_H
#define __CONCRETE_REGISTRATION_KERNEL_H

#include "mapRegistrationKernelBase.h"

/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
	namespace core
	{

		/*! Concrete RegistrationKernelBase implementation.
		 * This class is the base class for field based registration kernels,
		 * that define the mapping via a deformation vector field.
		 * The concrete transform management behavior will be defined by the TransformPolicy.
		 * @ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions, template <unsigned int, unsigned int> class TTransformPolicy >
		class ConcreteRegistrationKernel : public
			RegistrationKernel<VInputDimensions, VOutputDimensions>,
		public TTransformPolicy <VInputDimensions, VOutputDimensions>
		{
		public:
			typedef ConcreteRegistrationKernel<VInputDimensions, VOutputDimensions, TTransformPolicy>
			Self;
			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;
			typedef TTransformPolicy <VInputDimensions, VOutputDimensions> TransformPolicyType;

			itkTypeMacro(ConcreteRegistrationKernel, RegistrationKernelBase);
			itkNewMacro(Self);

      typedef typename Superclass::TransformType TransformType;
			typedef typename Superclass::RepresentationDescriptorType RepresentationDescriptorType;
			typedef typename Superclass::RepresentationDescriptorPointer RepresentationDescriptorPointer;
			typedef typename Superclass::RepresentationDescriptorConstPointer
			RepresentationDescriptorConstPointer;
			typedef typename Superclass::InputPointType  InputPointType;
			typedef typename Superclass::OutputPointType OutputPointType;

			/*! @brief gets the largest possible representation descriptor. The descriptor defines
			 * the space the kernel guarantees to map.
			 * @return Smart pointer to the descriptor (may be generated dynamicaly)
			 * @retval NULL there is no descriptor. If hasLimitedRepresentation returns false, the kernel
			 * has no mapping limitations and covers the total input space.
			  @eguarantee strong
			 */
			virtual RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const;

      /*! Returns pointer to the transform model used by the kernel
      @eguarantee strong
      @return const pointer to the internal tranform model
      */
      virtual const TransformType* getTransformModel() const;

			/*! @brief forces kernel to precompute, even if it is a LazyFieldKernel
			  @eguarantee strong
			 */
			virtual void precomputeKernel();

      virtual const MappingVectorType& getNullVector() const;

      virtual bool usesNullVector() const;

		protected:
			ConcreteRegistrationKernel();
			virtual ~ConcreteRegistrationKernel();

			virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:

			//No copy constructor allowed
			ConcreteRegistrationKernel(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapConcreteRegistrationKernel.tpp"
#endif

#endif
