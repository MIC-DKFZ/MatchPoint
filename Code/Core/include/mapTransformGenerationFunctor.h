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


#ifndef __MAP_TRANSFORM_GENERATION_FUNCTOR_H
#define __MAP_TRANSFORM_GENERATION_FUNCTOR_H

#include "mapFieldRepresentationDescriptor.h"
#include "mapRegistrationTopology.h"
#include "mapClassMacros.h"

#include "itkObject.h"

namespace map
{
    namespace core
    {
        namespace functors
        {

            /*! @class TransformGenerationFunctor
            * @brief Base class for functors that gernerate transform instances
            *
            * The field functors are used in conjunction with special service providers
            * to realize the "lazy" generation of transforms that are used in a mapping
            * kernel of a registration. The "lazy" generation of the transform is prefered
            * if/because the representation of a mapping direction may consume memory without
            * really being needed to register a certain data type. E.g. To register
            * point data you only need a direct mapping. The inverse mapping will only be
            * created (by a functor), if an image should also be registered.
            * Typical candidates for such a lazy generation are itk::DiscplacementFieldTransform
            * based instances.
            *
            * @ingroup RegFunctors
            * @tparam VInputDimensions Dimensions of the input space the transform should map from.
            * @tparam VOutputDimensions Dimensions of the output space the transform should map into.
            */
            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            class TransformGenerationFunctor : public itk::Object
            {
            public:
                /*! Standard class typedefs. */
                typedef TransformGenerationFunctor<VInputDimensions, VOutputDimensions>  Self;
                using Superclass = itk::Object;
                using Pointer = itk::SmartPointer<Self>;
                using ConstPointer = itk::SmartPointer<const Self>;

                itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
                itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

                using InFieldRepresentationType = FieldRepresentationDescriptor<VInputDimensions>;
                using InFieldRepresentationConstPointer = typename InFieldRepresentationType::ConstPointer;
                using OutFieldRepresentationType = FieldRepresentationDescriptor<VOutputDimensions>;
                using OutFieldRepresentationConstPointer = typename OutFieldRepresentationType::ConstPointer;
                typedef typename RegistrationTopology < VInputDimensions,
                    VOutputDimensions >::DirectTransformType TransformType;
                using TransformPointer = typename TransformType::Pointer;

                typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::TargetPointType
                    NullPointType;

                itkTypeMacro(TransformGenerationFunctor, itk::Object);

                /*! Generates the field an returns the result as a smart pointer.
                 * @eguarantee should be strong
                 * @return Smart pointer to the generated field.
                 */
                virtual TransformPointer generateTransform() const = 0;

                /*! Returns a const pointer to the input field representation descriptor.
                 * @eguarantee no fail
                 * @return Pointer to the input field representation descriptor, if set. May be NULL if no special
                 * representation is declared.
                 * @retval NULL There is no explicit field representation descriptor for the input space.
                 */
                const InFieldRepresentationType* getInFieldRepresentation() const;

                mapSetVarMacro(NullPoint, NullPointType, _nullPoint);
                mapGetConstVarMacro(NullPoint, NullPointType, _nullPoint);
                mapSetVarMacro(NullPointUsage, bool, _useNullPoint);
                mapGetConstVarMacro(NullPointUsage, bool, _useNullPoint);

            protected:
                TransformGenerationFunctor(const InFieldRepresentationType* pInFieldRepresentation);
                ~TransformGenerationFunctor() override;

                InFieldRepresentationConstPointer _spInFieldRepresentation;

                NullPointType _nullPoint;
                bool _useNullPoint;


                /*! Methods invoked by itk::LightObject::Print().  */
                void PrintSelf(std::ostream& os, itk::Indent indent) const override;

            private:
                TransformGenerationFunctor(const Self&);  //purposely not implemented
                void operator=(const Self&);  //purposely not implemented
            };

        } // end namespace functors
    } // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapTransformGenerationFunctor.tpp"
#endif

#endif
