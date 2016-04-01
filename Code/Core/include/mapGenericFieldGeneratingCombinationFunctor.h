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

#ifndef __MAP_GENERIC_FIELD_GENERATING_COMBINATION_FUNCTOR_H
#define __MAP_GENERIC_FIELD_GENERATING_COMBINATION_FUNCTOR_H

#include "mapTransformGenerationFunctor.h"
#include "mapCombinationFunctorInterface.h"
#include "mapRegistrationKernel.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			/*! @class GenericFieldGeneratingCombinationFunctor
			* @brief Functors generates a transform field by combining two kernels
			*
			* This functors generates a transform (displacement field) by combining two kernels.
			* This functor needs the input field representation to be set, other wise it wouldn't
			* be clear how to generate the field (size, spacing).
      * The functor makes a mapping for each point of the input field representation through
      * both kernels and computes the resulting combined transform factor in order to store
      * it in the displacement field.
			* The output field representation is not used by this functor.
			*
			* @ingroup RegFunctors
			* @tparam VInputDimensions Dimensions of the input space the field should map from.
			* @tparam VInterimDimensions Dimensions of the interim space into which the transformation maps.
			* @tparam VOutputDimensions Dimensions of the output space the field should map into.
			*/
			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			class GenericFieldGeneratingCombinationFunctor: public
				TransformGenerationFunctor<VInputDimensions, VOutputDimensions>,
			public CombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
			{
			public:
				/*! Standard class typedefs. */
				typedef GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>
				Self;
				typedef TransformGenerationFunctor<VInputDimensions, VOutputDimensions>  Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;
				typedef CombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>
				CombinationInterface;

				typedef typename Superclass::InFieldRepresentationType            InFieldRepresentationType;
				typedef typename Superclass::InFieldRepresentationConstPointer    InFieldRepresentationConstPointer;
				typedef typename Superclass::OutFieldRepresentationType           OutFieldRepresentationType;
				typedef typename Superclass::OutFieldRepresentationConstPointer
				OutFieldRepresentationConstPointer;
        typedef typename RegistrationTopology < VInputDimensions,
            VOutputDimensions >::DirectFieldType                          FieldType;
        typedef typename Superclass::TransformType                      TransformType;
        typedef typename Superclass::TransformPointer                   TransformPointer;
				typedef typename CombinationInterface::SourceKernel1BaseType SourceKernel1BaseType;
				typedef typename CombinationInterface::SourceKernel2BaseType SourceKernel2BaseType;

        itkTypeMacro(GenericFieldGeneratingCombinationFunctor, TransformGenerationFunctor);

				/*! Generates the field an returns the result as a smart pointer.
				 * @eguarantee should be strong
				 * @return Smart pointer to the generated field.
				 */
        virtual TransformPointer generateTransform() const override;

				/*! Returns a const pointer to the first source kernel base (source field kernel)
				* that will be used in order to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				virtual const SourceKernel1BaseType* get1stSourceKernelBase(void) const override;

				/*! Returns a const pointer to the second source kernel base (source model kernel)
				* that will be used in order to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the source field kernel.
				 * @post Return value is guaranteed not to be NULL.
				 */
				virtual const SourceKernel2BaseType* get2ndSourceKernelBase(void) const override;

				/*! Static methods that creates the functor.
				 * Thus it is a specialized version of the itkNewMacro()
				 * @eguarantee strong
				 * @param [in] kernel1 Pointer to the 1st source kernel that should be used.
				 * @param [in] kernel2 Pointer to the 2nd source kernel that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @return Smart pointer to the new functor
				 * @pre kernel1 must be set, may not be NULL
         * @pre kernel2 must be set, may not be NULL
         * @pre pInFieldRepresentation must be set, may not be NULL*/
        static Pointer New(const SourceKernel1BaseType* kernel1,
            const SourceKernel2BaseType* kernel2,
								   const InFieldRepresentationType* pInFieldRepresentation);

				/*! Creates a functor via New and returns it as a itk::LightObject smart pointer.
				 * @eguarantee strong
				 * @return Smart pointer to the new functor as itk::LightObject*/
				virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			protected:
				/*! Protected constructor used by New.
				 * @eguarantee strong
         * @param [in] kernel1 Pointer to the 1st source kernel that should be used.
				 * @param [in] kernel2 Pointer to the 2nd source kernel that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @return Smart pointer to the new functor
				 * @pre kernel1 must be set, may not be NULL
         * @pre kernel2 must be set, may not be NULL
         * @pre pInFieldRepresentation must be set, may not be NULL*/
          GenericFieldGeneratingCombinationFunctor(const SourceKernel1BaseType* kernel1,
              const SourceKernel2BaseType* kernel2,
              const InFieldRepresentationType* pInFieldRepresentation);

				virtual ~GenericFieldGeneratingCombinationFunctor();

				/*! The source field kernel.*/
        SourceKernel1BaseType _spSourceKernel1;

				/*! The transformation model.*/
        SourceKernel2BaseType _spSourceKernel2;

				/*! Methods invoked by itk::LightObject::Print().  */
				virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			private:
				GenericFieldGeneratingCombinationFunctor(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace functors
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
 #include "mapGenericFieldGeneratingCombinationFunctor.tpp"
#endif

#endif
