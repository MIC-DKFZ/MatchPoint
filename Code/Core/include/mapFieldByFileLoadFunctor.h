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

#ifndef __MAP_FIELD_BY_FILE_LOAD_FUNCTOR_H
#define __MAP_FIELD_BY_FILE_LOAD_FUNCTOR_H

#include "mapTransformGenerationFunctor.h"
#include "mapMacros.h"

namespace map
{
    namespace core
    {
        namespace functors
        {

            /*! @class FieldByFileLoadFunctor
            * @brief Functors generates a field by loading it from a specified file
            *
            * This field functors loads the field from a specified file when the field is
            * requested.\n
            * This functor does not need the input field repesantation to be set. If it is not set,
            * it will assume that the repesantation equals the size of the stored field.
            * If it is set and the representation is not a subset of the loaded field, an exception
            * will be raised.
            *
            * @ingroup RegFunctors
            * @tparam VInputDimensions Dimensions of the input space the field should map from.
            * @tparam VOutputDimensions Dimensions of the output space the field should map into.
            */
            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            class FieldByFileLoadFunctor : public TransformGenerationFunctor < VInputDimensions, VOutputDimensions >
            {
            public:
                /*! Standard class typedefs. */
                typedef FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>  Self;
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

                itkTypeMacro(FieldByFileLoadFunctor, TransformGenerationFunctor);

                /*! Generates the field an returns the result as a smart pointer.
                * @eguarantee should be strong
                * @return Smart pointer to the generated field.
                */
                virtual TransformPointer generateTransform() const override;

                /*! Returns the file path from where the field will be/was loaded.
                 * @eguarantee no fail
                 * @return reference to the specified path.
                 */
                const String& getFieldFilePath(void) const;

                /*! Static methods that creates the functor.
                 * Thus it is a specialized version of the itkNewMacro()
                 * @eguarantee strong
                 * @param [in] model Reference to the transform model that should be used.
                 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
                 * may be null for this functor (meaning that the loaded field defines the representation).
                 * @return Smart pointer to the new functor*/
                static Pointer New(const String& filepath,
                    const InFieldRepresentationType* pInFieldRepresentation = NULL);

                /*! Creates a functor via New and returns it as a itk::LightObject smart pointer.
                 * @eguarantee strong
                 * @return Smart pointer to the new functor as itk::LightObject*/
                virtual ::itk::LightObject::Pointer CreateAnother(void) const;

            protected:
                /*! Protected constructor used by New.
                 * @eguarantee strong
                 * @param [in] model Reference to the transform model that should be used.
                 * @param [in] pInFieldRepresentation Pointer to the field representation in the input space,
                 * may be null for this functor (meaning that the loaded field defines the representation).*/
                FieldByFileLoadFunctor(const String& filepath,
                    const InFieldRepresentationType* pInFieldRepresentation);

                virtual ~FieldByFileLoadFunctor();

                String _filePath;

                /*! Methods invoked by itk::LightObject::Print().  */
                virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

            private:
                FieldByFileLoadFunctor(const Self&);  //purposely not implemented
                void operator=(const Self&);  //purposely not implemented
            };

        } // end namespace functors

        /*! creates a field representation descriptor from the meta header file of a meta image
        @eguarantee strong
        @param filePath Path to the header file of the meta image
        @return FieldRepresentationDescriptor that describes the meta image
        @pre filePath must point to a valid file
        @pre The meta image specified in the file must have the correct dimension.
        @exception DimRepresentationException Thrown if the meta image stored in the file has not the correct dimension.
        @exception itk::ImageFileReaderException Thrown if filePath does not exist or is an incorrect file.
        */
        template <unsigned int VDimensions>
        typename FieldRepresentationDescriptor<VDimensions>::Pointer
            createFieldRepresentationOfMetaImageFile(const String& filePath);

    } // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldByFileLoadFunctor.tpp"
#endif

#endif
