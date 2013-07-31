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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldByFieldFieldCombinationFunctor.h $
*/


#ifndef __MAP_FIELD_BY_FIELD_FIELD_COMBINATION_FUNCTOR_H
#define __MAP_FIELD_BY_FIELD_FIELD_COMBINATION_FUNCTOR_H

#include "mapFieldGenerationFunctor.h"
#include "mapFieldCombinationFunctorInterface.h"
#include "mapFieldBasedRegistrationKernel.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			/*! @class FieldByFieldFieldCombinationFunctor
			* @brief Functors generates a field by combining two mappings (field + field)
			*
			* This field functors generates a field by combining two mappings (field 1, field 2).
			* The functor assumes that the 1st field kernel maps from input into interim space
			* and that the 2nd field kernel maps from interim space into output space.\n
			* This functor needs the input field representation to be set, other wise it wouldn't
			* be clear how to generate the field (size, spacing).
			* The output field representation is not used by this functor.
			*
			* @ingroup RegFunctors
			* @tparam VInputDimensions Dimensions of the input space the field should map from.
			* @tparam VInterimDimensions Dimensions of the interim space into which the transformation maps.
			* @tparam VOutputDimensions Dimensions of the output space the field should map into.
			*/
			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			class FieldByFieldFieldCombinationFunctor: public FieldGenerationFunctor<VInputDimensions, VOutputDimensions>,
				public FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
			{
			public:
				/*! Standard class typedefs. */
				typedef FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>  Self;
				typedef FieldGenerationFunctor<VInputDimensions, VOutputDimensions>  Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;
				typedef FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>  CombinationInterface;

				itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
				itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

				typedef typename Superclass::InFieldRepresentationType            InFieldRepresentationType;
				typedef typename Superclass::InFieldRepresentationConstPointer    InFieldRepresentationConstPointer;
				typedef typename Superclass::OutFieldRepresentationType           OutFieldRepresentationType;
				typedef typename Superclass::OutFieldRepresentationConstPointer   OutFieldRepresentationConstPointer;
				typedef typename Superclass::FieldType                            FieldType;
				typedef typename Superclass::FieldPointer                         FieldPointer;
				typedef FieldBasedRegistrationKernel < VInputDimensions,
				        VInterimDimensions >          SourceFieldKernel1Type;
				typedef typename SourceFieldKernel1Type::ConstPointer             SourceFieldKernel1ConstPointer;
				typedef FieldBasedRegistrationKernel < VInterimDimensions,
				        VOutputDimensions >           SourceFieldKernel2Type;
				typedef typename SourceFieldKernel2Type::ConstPointer             SourceFieldKernel2ConstPointer;
				typedef typename CombinationInterface::SourceKernel1BaseType SourceKernel1BaseType;
				typedef typename CombinationInterface::SourceKernel2BaseType SourceKernel2BaseType;

				itkTypeMacro(FieldByFieldModelCombinationFunctor, FieldGenerationFunctor);

				/*! Generates the field an returns the result as a smart pointer.
				 * @eguarantee should be strong
				 * @return Smart pointer to the generated field.
				 */
				virtual FieldPointer generateField() const;

				/*! Returns a const pointer to the source field kernel that will be used in order
				 * to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				const SourceFieldKernel1Type *get1stSourceFieldKernel(void) const;

				/*! Returns a const pointer to the source field kernel that will be used in order
				 * to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				const SourceFieldKernel2Type *get2ndSourceFieldKernel(void) const;

				/*! Returns a const pointer to the first source kernel base that will be used in order
				 * to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				virtual const SourceKernel1BaseType *get1stSourceKernelBase(void) const;

				/*! Returns a const pointer to the second source kernel base that will be used in order
				 * to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				virtual const SourceKernel2BaseType *get2ndSourceKernelBase(void) const;

				/*! Static methods that creates the functor.
				 * Thus it is a specialized version of the itkNewMacro()
				 * @eguarantee strong
				 * @param [in] fieldKernel1 Reference to the 1st source field kernel that should be used.
				 * @param [in] fieldKernel2 Reference to the 2nd source field kernel that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @return Smart pointer to the new functor
				 * @pre pInFieldRepresentation musst be set, may not be NULL*/
				static Pointer New(const SourceFieldKernel1Type &fieldKernel1,
				                   const SourceFieldKernel2Type &fieldKernel2,
				                   const InFieldRepresentationType *pInFieldRepresentation);

				/*! Creates a functor via New and returns it as a itk::LightObject smart pointer.
				 * @eguarantee strong
				 * @return Smart pointer to the new functor as itk::LightObject*/
				virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			protected:
				/*! Protected constructor used by New.
				 * @eguarantee strong
				 * @param [in] fieldKernel1 Reference to the 1st source field kernel that should be used.
				 * @param [in] fieldKernel2 Reference to the 2nd source field kernel that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @pre pInFieldRepresentation musst be set, may not be NULL*/
				FieldByFieldFieldCombinationFunctor(const SourceFieldKernel1Type &fieldKernel1,
				                                    const SourceFieldKernel2Type &fieldKernel2,
				                                    const InFieldRepresentationType *pInFieldRepresentation);

				virtual ~FieldByFieldFieldCombinationFunctor();

				/*! The 1st source field kernel.*/
				SourceFieldKernel1ConstPointer _sp1stSourceFieldKernel;

				/*! The 2nd source field kernel.*/
				SourceFieldKernel2ConstPointer _sp2ndSourceFieldKernel;

				/*! Methods invoked by itk::LightObject::Print().  */
				virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

			private:
				FieldByFieldFieldCombinationFunctor(const Self &); //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};

		} // end namespace functors
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldByFieldFieldCombinationFunctor.tpp"
#endif

#endif
