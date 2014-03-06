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

#ifndef __MODEL_BASED_REGISTRATION_KERNEL_H
#define __MODEL_BASED_REGISTRATION_KERNEL_H

#include "mapString.h"
#include "mapModelBasedRegistrationKernelInterface.h"
#include "mapRegistrationKernelBase.h"
#include "mapTransformModelBase.h"

/*! @namespace map The namespace map::core is for the library of MatchPoint
*/
namespace map
{
	namespace core
	{

		/*! @class ModelBasedRegistrationKernel
		    This class is the base class for model based registration kernels.
		    @ingroup RegKernel
		*/
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class ModelBasedRegistrationKernel : public ModelBasedRegistrationKernelInterface,
			public RegistrationKernelBase<VInputDimensions, VOutputDimensions>
		{

		public:
			typedef TransformModelBase<continuous::ScalarType, VInputDimensions, VOutputDimensions>
			TransformType;

			typedef ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions> Self;
			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(ModelBasedRegistrationKernel, RegistrationKernelBase);
			itkNewMacro(Self);

			typedef typename TransformType::InputVectorType InputVectorType;
			typedef typename TransformType::OutputVectorType OutputVectorType;
			typedef typename Superclass::InputPointType InputPointType;
			typedef typename Superclass::OutputPointType OutputPointType;
			typedef typename Superclass::RepresentationDescriptorType        RepresentationDescriptorType;
			typedef typename Superclass::RepresentationDescriptorPointer        RepresentationDescriptorPointer;
			typedef typename Superclass::RepresentationDescriptorConstPointer
			RepresentationDescriptorConstPointer;
            typedef ModelBasedRegistrationKernelInterface::ParametersType ParametersType;

			virtual String getModelName() const;


			/*! gets the parameters
			  @eguarantee strong
			  @return a ParametersType containing the parameters
			 */
			virtual ParametersType getParameters() const;

			/*! transforms a point
			@eguarantee strong
			@param inPoint pointer to a MovingPointType
			@return pointer to a TargetPointType
			@pre transform model must be set and not null.
			*/
			virtual OutputPointType transformPoint(const InputPointType& inPoint) const;

			/*! transforms a vector
			@eguarantee strong
			@param inVector pointer to a InputVectorType
			@return pointer to a OutputVectorType
			@pre transform model must be set and not null.
			*/
			virtual OutputVectorType transformVector(const InputVectorType& inVector) const;

			/*! Returns pointer to the transform model used by the kernel
			@eguarantee no fail
			@return pointer to the tranform model
			*/
			const TransformType* getTransformModel() const;

			/*! sets the transform model used by the kernel
			@eguarantee no fail
			@param pTransform Pointer to the transform model
			*/
			void setTransformModel(TransformType* pTransform);

			/*! @brief gets the largest possible representation descriptor. The descriptor defines
			 * the space the kernel guarantees to map.
			 * @return Smart pointer to the descriptor (may be generated dynamicaly)
			 * @retval NULL there is no descriptor. If hasLimitedRepresentation returns false, the kernel
			 * has no mapping limitations and covers the total input space.
			  @eguarantee strong
			 */
			virtual RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const;

			virtual void precomputeKernel();


		protected:
			ModelBasedRegistrationKernel();
			~ModelBasedRegistrationKernel();

			typedef typename TransformType::ConstPointer TransformConstPointer;
			TransformConstPointer _spTransformModel;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const;

		private:

			//No copy constructor allowed
			ModelBasedRegistrationKernel(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapModelBasedRegistrationKernel.tpp"
#endif

#endif
