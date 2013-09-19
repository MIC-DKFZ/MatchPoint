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

#ifndef __MAP_FIELD_BY_MODEL_FIELD_COMBINATION_FUNCTOR_H
#define __MAP_FIELD_BY_MODEL_FIELD_COMBINATION_FUNCTOR_H

#include "mapFieldGenerationFunctor.h"
#include "mapFieldCombinationFunctorInterface.h"
#include "mapFieldBasedRegistrationKernel.h"
#include "mapModelBasedRegistrationKernel.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			/*! @class FieldByModelFieldCombinationFunctor
			* @brief Functors generates a field by combining two mappings (transform + field)
			*
			* This field functors generates a field by combining two mappings (transform, field).
			* The functor assumes that the transform maps from input into interim space and the
			* field kernel maps from interim space into output space.\n
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
			class FieldByModelFieldCombinationFunctor: public
				FieldGenerationFunctor<VInputDimensions, VOutputDimensions>,
			public FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
			{
			public:
				/*! Standard class typedefs. */
				typedef FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>
				Self;
				typedef FieldGenerationFunctor<VInputDimensions, VOutputDimensions>  Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;
				typedef FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
				CombinationInterface;

				itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
				itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

				typedef typename Superclass::InFieldRepresentationType            InFieldRepresentationType;
				typedef typename Superclass::InFieldRepresentationConstPointer    InFieldRepresentationConstPointer;
				typedef typename Superclass::OutFieldRepresentationType           OutFieldRepresentationType;
				typedef typename Superclass::OutFieldRepresentationConstPointer
				OutFieldRepresentationConstPointer;
				typedef typename Superclass::FieldType                            FieldType;
				typedef typename Superclass::FieldPointer                         FieldPointer;
				typedef FieldBasedRegistrationKernel < VInterimDimensions,
						VOutputDimensions >           SourceFieldKernelType;
				typedef typename SourceFieldKernelType::ConstPointer              SourceFieldKernelConstPointer;
				typedef ModelBasedRegistrationKernel < VInputDimensions,
						VInterimDimensions >          SourceModelKernelType;
				typedef typename SourceModelKernelType::ConstPointer              SourceModelKernelConstPointer;
				typedef typename CombinationInterface::SourceKernel1BaseType SourceKernel1BaseType;
				typedef typename CombinationInterface::SourceKernel2BaseType SourceKernel2BaseType;

				itkTypeMacro(FieldByModelFieldCombinationFunctor, FieldGenerationFunctor);

				/*! Generates the field an returns the result as a smart pointer.
				 * @eguarantee should be strong
				 * @return Smart pointer to the generated field.
				* @pre the souce field kernel has to have a valid transform model (not null)
				 */
				virtual FieldPointer generateField() const;

				/*! Returns a const pointer to the source field kernel that will be used in order
				 * to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				const SourceFieldKernelType* getSourceFieldKernel(void) const;

				/*! Returns a const pointer to the source transformation model kernel that will be used
				 * in order to generate the combined field.
				 * @eguarantee no fail
				 * @return Pointer to the transform model kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				const SourceModelKernelType* getSourceModelKernel(void) const;

				/*! Returns a const pointer to the first source kernel base (source model kernel)
				* that will be used in order to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				virtual const SourceKernel1BaseType* get1stSourceKernelBase(void) const;

				/*! Returns a const pointer to the second source kernel base (source field kernel)
				* that will be used in order to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				virtual const SourceKernel2BaseType* get2ndSourceKernelBase(void) const;

				/*! Static methods that creates the functor.
				 * Thus it is a specialized version of the itkNewMacro()
				 * @eguarantee strong
				 * @param [in] modelKernel Reference to the source model kernel that should be used.
				 * @param [in] fieldKernel Reference to the source field kernel that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @return Smart pointer to the new functor
				 * @pre pInFieldRepresentation musst be set, may not be NULL*/
				static Pointer New(const SourceModelKernelType& modelKernel,
								   const SourceFieldKernelType& fieldKernel,
								   const InFieldRepresentationType* pInFieldRepresentation);

				/*! Creates a functor via New and returns it as a itk::LightObject smart pointer.
				 * @eguarantee strong
				 * @return Smart pointer to the new functor as itk::LightObject*/
				virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			protected:
				/*! Protected constructor used by New.
				 * @eguarantee strong
				 * @param [in] modelKernel Reference to the source model kernel that should be used.
				 * @param [in] fieldKernel Reference to the source field kernel that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @pre pInFieldRepresentation musst be set, may not be NULL*/
				FieldByModelFieldCombinationFunctor(const SourceModelKernelType& modelKernel,
													const SourceFieldKernelType& fieldKernel,
													const InFieldRepresentationType* pInFieldRepresentation);

				virtual ~FieldByModelFieldCombinationFunctor();

				/*! The transformation model.*/
				SourceModelKernelConstPointer _spSourceModelKernel;

				/*! The source field kernel.*/
				SourceFieldKernelConstPointer _spSourceFieldKernel;

				/*! Methods invoked by itk::LightObject::Print().  */
				virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			private:
				FieldByModelFieldCombinationFunctor(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace functors
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldByModelFieldCombinationFunctor.tpp"
#endif

#endif
