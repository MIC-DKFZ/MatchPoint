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


#ifndef __MAP_FIELD_BY_FIELD_INVERSION_FUNCTOR_H
#define __MAP_FIELD_BY_FIELD_INVERSION_FUNCTOR_H

#include "mapTransformGenerationFunctor.h"
#include "mapRegistrationKernel.h"
#include "mapRegistrationTopology.h"

namespace map
{
    namespace core
    {
        namespace functors
        {

            /*! @class FieldByFieldInversionFunctor
            * @brief Functors generates a field by inverting an other field nummerically
            *
            * This field functors generates a field by inverting an other field. For the inversion the
            * itk::IterativeInverseDisplacementFieldImageFilter will be used by the functor.\n
            * This functor needs the input field representation to be set, other wise it wouldn't
            * be clear how to generate the field (size, spacing).
            * The output field representation is not used by this functor.
            *
            * @todo Im moment benutzt der itk filter defacto die OutputRepresentation, da er die geometry des Ausgabebildes
            * an dem Eingabefeld orientiert -> entweder die itk:komponente muss modifiziert werden, so dass man die outputgeometrie mitgeben kann,
            * oder man porbiert doch auch mal den itk::InverseDisplacementFieldImageFilter aus, der hat das feature schon.
            * @ingroup RegFunctors
            * @tparam VInputDimensions Dimensions of the input space the field should map from.
            * @tparam VOutputDimensions Dimensions of the output space the field should map into.
            */
            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            class FieldByFieldInversionFunctor : public
                TransformGenerationFunctor < VInputDimensions, VOutputDimensions >
            {
            public:
                /*! Standard class typedefs. */
                typedef FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>  Self;
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
                typedef RegistrationKernel < VOutputDimensions, VInputDimensions > SourceFieldKernelType;
                typedef typename RegistrationTopology < VInputDimensions,
                    VOutputDimensions >::InverseFieldType                       SourceFieldType;
                typedef typename SourceFieldType::ConstPointer                  SourceFieldConstPointer;
                typedef typename SourceFieldKernelType::ConstPointer            SourceFieldKernelConstPointer;

                itkTypeMacro(FieldByFieldInversionFunctor, TransformGenerationFunctor);

                /*! Generates the field an returns the result as a smart pointer.
                * @eguarantee should be strong
                * @return Smart pointer to the generated field.
                */
                virtual TransformPointer generateTransform() const override;

                /*! Returns a const pointer to the source field that will be inverted in order
                 * to generate the field.
                 * @eguarantee no fail
                 * @return Pointer to the source field.
                 * @post Return value is guaranteed not to be NULL.
                 */
                const SourceFieldKernelType* getSourceFieldKernel(void) const;

                /*! Static methods that creates the functor.
                 * Thus it is a specialized version of the itkNewMacro()
                 * @eguarantee strong
                 * @param [in] sourceFieldKernel Reference to the field kernel offering the field that should be used as inversion source.
                 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
                 * may not be null for this functor.
                 * @return Smart pointer to the new functor
                 * @pre sourceFieldKernel musst be set, may not be NULL
                 * @pre pInFieldRepresentation musst be set, may not be NULL*/
                static Pointer New(const SourceFieldKernelType* sourceFieldKernel,
                    const InFieldRepresentationType* pInFieldRepresentation);

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
                 * @param [in] sourceFieldKernel Reference to the field kernel offering the field that should be used as inversion source.
                 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
                 * may not be null for this functor.
                 * @pre sourceFieldKernel musst be set, may not be NULL
                 * @pre pInFieldRepresentation musst be set, may not be NULL*/
                FieldByFieldInversionFunctor(const SourceFieldKernelType* sourceFieldKernel,
                    const InFieldRepresentationType* pInFieldRepresentation);

                virtual ~FieldByFieldInversionFunctor();

                /*! The source field. Its inversion will be used to generate the result field.*/
                SourceFieldKernelConstPointer _spSourceFieldKernel;

                /*! Methods invoked by itk::LightObject::Print().  */
                virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

                unsigned long _nrOfIterations;

                double _stopValue;

            private:
                FieldByFieldInversionFunctor(const Self&);  //purposely not implemented
                void operator=(const Self&);  //purposely not implemented
            };

        } // end namespace functors
    } // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldByFieldInversionFunctor.tpp"
#endif

#endif
