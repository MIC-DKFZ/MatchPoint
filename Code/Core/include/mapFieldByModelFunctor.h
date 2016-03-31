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

#ifndef __MAP_FIELD_BY_MODEL_FUNCTOR_H
#define __MAP_FIELD_BY_MODEL_FUNCTOR_H

#include <itkTransform.h>

#include "mapTransformGenerationFunctor.h"
#include "mapRegistrationKernel.h"
#include "mapRegistrationTopology.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			/*! @class FieldByModelFunctor
			* @brief Functors generates a field by sampling a transformation model
			*
			* This field functors generates a field by sampling a transformation which is
			* assumed to model the same mapping direction.\n
			* This functor needs the input field representation to be set, other wise it wouldn't
			* be clear how to generate the field (size, spacing).
			* The output field representation is not used by this functor.
			*
			* @ingroup RegFunctors
			* @tparam VInputDimensions Dimensions of the input space the field should map from.
			* @tparam VOutputDimensions Dimensions of the output space the field should map into.
			*/
			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			class FieldByModelFunctor: public TransformGenerationFunctor<VInputDimensions, VOutputDimensions>
			{
			public:
				/*! Standard class typedefs. */
				typedef FieldByModelFunctor<VInputDimensions, VOutputDimensions>  Self;
				typedef TransformGenerationFunctor<VInputDimensions, VOutputDimensions>  Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;

				itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
				itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

				typedef typename Superclass::InFieldRepresentationType          InFieldRepresentationType;
				typedef typename Superclass::InFieldRepresentationConstPointer  InFieldRepresentationConstPointer;
				typedef typename Superclass::OutFieldRepresentationType         OutFieldRepresentationType;
				typedef typename Superclass::OutFieldRepresentationConstPointer OutFieldRepresentationConstPointer;
        typedef typename RegistrationTopology < VInputDimensions,
            VOutputDimensions >::DirectFieldType                          FieldType;
        typedef typename Superclass::TransformType                      TransformType;
        typedef typename Superclass::TransformPointer                   TransformPointer;
        typedef typename RegistrationTopology < VInputDimensions,
            VOutputDimensions >::DirectTransformType SourceTransformModelType;
        typedef typename SourceTransformModelType::ConstPointer               SourceTransformModelConstPointer;

				itkTypeMacro(FieldByModelFunctor, TransformGenerationFunctor);

        /*! Generates the field an returns the result as a smart pointer.
        * @eguarantee should be strong
        * @return Smart pointer to the generated field.
        */
        virtual TransformPointer generateTransform() const override;

        /*! Returns a const pointer to the transform model that will be inverted in order
        * to generate the field.
        * @eguarantee no fail
        * @return Pointer to the transform model.
        * @post Return value is guaranteed not to be NULL.
        */
        const SourceTransformModelType* getSourceTransformModel(void) const;

        /*! Static methods that creates the functor.
        * Thus it is a specialized version of the itkNewMacro()
        * @eguarantee strong
        * @param [in] model Pointer to the transform model that should be used.
        * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
        * may not be null for this functor.
        * @return Smart pointer to the new functor
        * @pre pInFieldRepresentation musst be set, may not be NULL
        * @pre model musst be set, may not be NULL */
        static Pointer New(const SourceTransformModelType* model,
            const InFieldRepresentationType* pInFieldRepresentation);

				/*! Creates a functor via New and returns it as a itk::LightObject smart pointer.
				 * @eguarantee strong
				 * @return Smart pointer to the new functor as itk::LightObject*/
				virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			protected:
				/*! Protected constructor used by New.
				 * @eguarantee strong
				 * @param [in] model Reference to the transform model that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
         * @pre pInFieldRepresentation musst be set, may not be NULL
         * @pre model musst be set, may not be NULL */
          FieldByModelFunctor(const SourceTransformModelType* model,
									const InFieldRepresentationType* pInFieldRepresentation);

				virtual ~FieldByModelFunctor();

        SourceTransformModelConstPointer _spTransformModel;

				/*! Methods invoked by itk::LightObject::Print().  */
				virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			private:
				FieldByModelFunctor(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace functors
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldByModelFunctor.tpp"
#endif

#endif
