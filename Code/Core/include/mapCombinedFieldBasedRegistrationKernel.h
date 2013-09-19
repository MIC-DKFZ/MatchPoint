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

#ifndef __COMBINED_FIELD_BASED_REGISTRATION_KERNEL_H
#define __COMBINED_FIELD_BASED_REGISTRATION_KERNEL_H

#include "mapConcreteFieldBasedRegistrationKernel.h"
#include "mapLazyFieldPolicy.h"
#include "mapFieldCombinationFunctorInterface.h"


/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
	namespace core
	{

		/*!@brief  CombinedFieldBasedRegistrationKernel is a special implementation of a lazy field based registration kernel.
		 * This implementation uses a combination functor to generate its field. In contrast to the normal field based kernel
		 * implementation, this kernel maps points directly by using its functor given source kernels. Thus no field will generated
		 * just for mapping points. The field must be generated explicitly by calling gernerateField().
		 * @ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class CombinedFieldBasedRegistrationKernel : public
			ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, LazyFieldPolicy>
		{
		public:
			typedef CombinedFieldBasedRegistrationKernel<VInputDimensions, VInterimDimensions, VOutputDimensions>
			Self;
			typedef ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, ::map::core::LazyFieldPolicy>
			Superclass; //an error in the VS2005 name lookup forces to define the policy explicitly with full namespace information
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;
			// typedef typename Superclass::FieldPolicyType FieldPolicyType;

			itkTypeMacro(CombinedFieldBasedRegistrationKernel, ConcreteFieldBasedRegistrationKernel);
			itkNewMacro(Self);

			typedef typename Superclass::FieldType FieldType;
			typedef typename Superclass::FieldRegionType FieldRegionType;
			typedef typename Superclass::RepresentationDescriptorType RepresentationDescriptorType;
			typedef typename Superclass::RepresentationDescriptorPointer RepresentationDescriptorPointer;
			typedef typename Superclass::RepresentationDescriptorConstPointer
			RepresentationDescriptorConstPointer;
			typedef typename Superclass::FieldPolicyType FieldPolicyType;
			typedef typename FieldPolicyType::FieldGenerationFunctorType FieldGenerationFunctorType;
			typedef typename Superclass::InputPointType  InputPointType;
			typedef typename Superclass::OutputPointType OutputPointType;

			/*! sets the field's functor
			  @eguarantee no fail
			  @param functor Reference to the functor that is responsible for generating the field
			  @pre Functor must have implemented FieldCombinationFunctorInterface
			*/
			virtual void setFieldFunctor(const FieldGenerationFunctorType& functor);

		protected:
			typedef functors::FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
			FieldCombinationFunctorInterfaceType;
			typedef typename FieldCombinationFunctorInterfaceType::SourceKernel1BaseType SourceKernel1BaseType;
			typedef typename FieldCombinationFunctorInterfaceType::SourceKernel2BaseType SourceKernel2BaseType;

			const FieldCombinationFunctorInterfaceType* _pCombinationInterface;

			/*! maps a given point by using both source kernel. In contrast to other ConcreteFieldBasedRegistrationKernel classes,
			 * calling this methos will not trigger the generation of the kernel field.
			  @eguarantee no fail
			  @param functor Reference to the functor that is responsible for generating the field
			  @pre Functor must have implemented FieldCombinationFunctorInterface
			*/
			virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const;

			CombinedFieldBasedRegistrationKernel();
			virtual ~CombinedFieldBasedRegistrationKernel();


			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:

			//No copy constructor allowed
			CombinedFieldBasedRegistrationKernel(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapCombinedFieldBasedRegistrationKernel.tpp"
#endif

#endif
