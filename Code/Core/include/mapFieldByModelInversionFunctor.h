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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldByModelInversionFunctor.h $
*/

#ifndef __MAP_FIELD_BY_MODEL_INVERSION_FUNCTOR_H
#define __MAP_FIELD_BY_MODEL_INVERSION_FUNCTOR_H

#include "mapFieldGenerationFunctor.h"
#include "mapTransformModelBase.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			/*! @class FieldByModelInversionFunctor
			* @brief Functors generates a field by sampling a transformation model after inverting it nummerically
			*
			* This field functors generates a field by sampling the inversion of a transformation which is
			* assumed to model the inverse mapping direction. The inversion of the model will be done nummerically,
			* thus if the model can be inverted analytically, you should invert the transform and use the inverted
			* one in combination with FieldByModelFunctor.\n
			* This functor needs the input field representation to be set, other wise it wouldn't
			* be clear how to generate the field (size, spacing).
			* The output field representation is not used by this functor.
			*
			* @todo Tatsächliche qualität der Iterative Inversion methode feststellen. in Kombination mit der
			* scale transform (faktor 3) gabe es bei 40x40x40 bildern starke abweicheichungen. Ist das auch
			* be anderen transformationen so? vielleicht auf die fixed point methode umsteigen?
			* @todo Wenn TransformModel wrapper realisiert sind, dann erst prüfen ob analytisch invertierbar -> dann weitergeben an FieldByModelFunctor
			* @ingroup RegFunctors
			* @sa FieldByModelFunctor
			* @tparam VInputDimensions Dimensions of the input space the field should map from.
			* @tparam VOutputDimensions Dimensions of the output space the field should map into.
			*/
			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			class FieldByModelInversionFunctor: public FieldGenerationFunctor<VInputDimensions, VOutputDimensions>
			{
			public:
				/*! Standard class typedefs. */
				typedef FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>  Self;
				typedef FieldGenerationFunctor<VInputDimensions, VOutputDimensions>  Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;

				itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
				itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

				typedef typename Superclass::InFieldRepresentationType          InFieldRepresentationType;
				typedef typename Superclass::InFieldRepresentationConstPointer  InFieldRepresentationConstPointer;
				typedef typename Superclass::OutFieldRepresentationType         OutFieldRepresentationType;
				typedef typename Superclass::OutFieldRepresentationConstPointer OutFieldRepresentationConstPointer;
				typedef typename Superclass::FieldType                          FieldType;
				typedef typename Superclass::FieldPointer                       FieldPointer;
				typedef TransformModelBase < map::core::continuous::ScalarType,
				        VOutputDimensions, VInputDimensions >  TransformModelType;
				typedef typename TransformModelType::ConstPointer               TransformModelConstPointer;

				itkTypeMacro(FieldByModelInversionFunctor, FieldGenerationFunctor);

				/*! Generates the field an returns the result as a smart pointer.
				 * @eguarantee should be strong
				 * @return Smart pointer to the generated field.
				 */
				virtual FieldPointer generateField() const;

				/*! Returns a const pointer to the transform model that will be inverted in order
				 * to generate the field.
				 * @eguarantee no fail
				 * @return Pointer to the transform model.
				 * @post Return value is guaranteed not to be NULL.
				 */
				const TransformModelType *getTransformModel(void) const;

				/*! Static methods that creates the functor.
				 * Thus it is a specialized version of the itkNewMacro()
				 * @eguarantee strong
				 * @param [in] model Reference to the transform model that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @return Smart pointer to the new functor
				 * @pre pInFieldRepresentation musst be set, may not be NULL*/
				static Pointer New(const TransformModelType &model,
				                   const InFieldRepresentationType *pInFieldRepresentation);

				/*! Creates a functor via New and returns it as a itk::LightObject smart pointer.
				 * @eguarantee strong
				 * @return Smart pointer to the new functor as itk::LightObject*/
				virtual ::itk::LightObject::Pointer CreateAnother(void) const;

				/*! gets the number of iterations that has been set for the numeric inversion
				* @return the number of iterations
				 * @eguarantee no fail */
				unsigned long getNumberOfIterations() const;

				/*! Sets the number of iterations for the numeric inversion
				* @param [in] nrOfIterations the number of iterations
				 * @eguarantee no fail */
				void setNumberOfIterations(unsigned long nrOfIterations);

				/*! gets the stop value (exactness delta) that has been set for the numeric inversion
				 * @return the stop value
						 * @eguarantee no fail */
				double getStopValue() const;

				/*! Sets the stop value for the numeric inversion (exactness)
				 * @param [in] nrOfIterations the number of iterations
						 * @eguarantee no fail */
				void setStopValue(double stopValue);


			protected:
				/*! Protected constructor used by New.
				 * @eguarantee strong
				 * @param [in] model Reference to the transform model that should be used.
				 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
				 * may not be null for this functor.
				 * @param [in] pOutFieldRepresentation Pointer to the field representation in the output space,
				 * may be NULL if no representation is defined.
				 * @pre pInFieldRepresentation musst be set, may not be NULL*/
				FieldByModelInversionFunctor(const TransformModelType &model,
				                             const InFieldRepresentationType *pInFieldRepresentation);

				virtual ~FieldByModelInversionFunctor();

				TransformModelConstPointer _spTransformModel;

				unsigned long _nrOfIterations;

				double _stopValue;

				/*! Methods invoked by itk::LightObject::Print().  */
				virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

			private:
				FieldByModelInversionFunctor(const Self &); //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};

		} // end namespace functors
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldByModelInversionFunctor.tpp"
#endif

#endif
