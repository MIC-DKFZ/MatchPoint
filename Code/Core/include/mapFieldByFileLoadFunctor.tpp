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

#ifndef __MAP_FIELD_BY_FILE_LOAD_FUNCTOR_TPP
#define __MAP_FIELD_BY_FILE_LOAD_FUNCTOR_TPP

#include "mapFieldByFileLoadFunctor.h"
#include "mapLogbookMacros.h"
#include "mapRepresentationException.h"
#include "mapGenericVectorFieldTransform.h"

#include "itkImageFileReader.h"
#include "itkImageIOFactory.h"

#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"

namespace map
{
    namespace core
    {
        namespace functors
        {

            /*! Helper class for a workaround.
            * right now we only support symmetric inversion. Must be implemented later on.
            * Template specialization allows the compiling of the code even in unsupported
            * cases.
            * @todo: Implement suitable solutions for unsymmetric cases (like VectorCombinationPolicy)
            */
            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            class FieldByFileLoadFunctorHelper
            {
            public:
                typedef typename ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> TransformType;
                using TransformPointer = typename TransformType::Pointer;
                typedef typename
                    FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType
                    InFieldRepresentationType;

                static inline TransformPointer generate(const ::map::core::String& filePath,
                    const InFieldRepresentationType* pInFieldRepresentation)
                {
                    mapExceptionStaticMacro(ExceptionObject,
                        << "Error unsymmetric field inversion not implemented yet.");
                    return nullptr;
                }
            };

            template <unsigned int VDimensions>
            class FieldByFileLoadFunctorHelper < VDimensions, VDimensions >
            {
            public:
                typedef typename FieldByFileLoadFunctor<VDimensions, VDimensions>::FieldType FieldType;
                typedef typename ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VDimensions, VDimensions> TransformType;
                using TransformPointer = typename TransformType::Pointer;
                typedef typename FieldByFileLoadFunctor<VDimensions, VDimensions>::InFieldRepresentationType
                    InFieldRepresentationType;


                static inline TransformPointer generate(const ::map::core::String& filePath,
                    const InFieldRepresentationType* pInFieldRepresentation)
                {
                    typedef ::itk::ImageFileReader< FieldType > FieldReaderType;
                    typename FieldReaderType::Pointer spFieldReader = FieldReaderType::New();

                    typename FieldType::Pointer spField = nullptr;

                    try
                    {
                        spFieldReader->SetFileName(filePath.c_str());
                        spField = spFieldReader->GetOutput();
                        spFieldReader->Update();
                    }
                    catch (itk::ExceptionObject& e)
                    {
                        e.SetDescription(String("Error in FieldByFileLoadFunctor while loading field. File name: ") + filePath + String(". Description: ") +
                            e.GetDescription());
                        throw;
                    }
                    catch (const std::exception& e)
                    {
                        mapExceptionStaticMacro(ExceptionObject, << "Error in FieldByFileLoadFunctor while loading field. File name: " << filePath << ". Description: " <<
                            e.what());
                    }
                    catch (...)
                    {
                        mapExceptionStaticMacro(ExceptionObject, <<
                            "Unknown error in FieldByFileLoadFunctor while loading field. File name: " << filePath);
                    }

                    /**@TODO Have to add check of the field representation (the specified one and the one set
                    set in the functor.**/
                    //Superclass::_spInFieldRepresentation = createFieldRepresentation(*spField).GetPointer();

                    TransformPointer spResult = TransformType::New();
                    spResult->SetDisplacementField(spField);
                    return spResult.GetPointer();
                }
            };

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::TransformPointer
                FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                generateTransform() const
            {
                mapLogInfoMacro(<< "Generate field by file loading. File name: " << _filePath);

                typedef typename FieldByFileLoadFunctorHelper<VInputDimensions, VOutputDimensions>::TransformType FieldTransformType;
                typename FieldTransformType::Pointer spResult =
                    FieldByFileLoadFunctorHelper<VInputDimensions, VOutputDimensions>::generate(_filePath,
                    Superclass::_spInFieldRepresentation);

                typedef typename ::itk::map::NULLVectorAwareLinearInterpolateImageFunction < typename FieldTransformType::GenericVectorFieldType, typename FieldTransformType::ScalarType> InterpolatorType;
                typename InterpolatorType::Pointer interpolator = InterpolatorType::New();
                interpolator->SetNullVectorUsage(this->_useNullPoint);
                typename InterpolatorType::OutputType nullVector;
                typedef typename InterpolatorType::OutputType::Superclass VectorSuperclassType;
                nullVector.VectorSuperclassType::operator = (this->_nullPoint);
                interpolator->SetNullVector(nullVector);

                spResult->SetInterpolator(interpolator);
                spResult->SetUseNullPoint(this->_useNullPoint);
                spResult->SetNullPoint(this->_nullPoint);

                return spResult.GetPointer();
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            const String&
                FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                getFieldFilePath() const
            {
                return _filePath;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::Pointer
                FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                New(const String& filepath,
                const InFieldRepresentationType* pInFieldRepresentation)
            {
                Pointer spFieldByFileLoadFunctor = new Self(filepath, pInFieldRepresentation);
                spFieldByFileLoadFunctor->UnRegister();
                return spFieldByFileLoadFunctor;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename ::itk::LightObject::Pointer
                FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                CreateAnother() const
            {
                ::itk::LightObject::Pointer smartPtr;
                smartPtr = Self::New(_filePath, Superclass::_spInFieldRepresentation).GetPointer();
                return smartPtr;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                FieldByFileLoadFunctor(const String& filepath,
                const InFieldRepresentationType* pInFieldRepresentation) :
                Superclass(pInFieldRepresentation), _filePath(filepath)
            {
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                ~FieldByFileLoadFunctor() {}

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            void
                FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
                PrintSelf(std::ostream& os, itk::Indent indent) const
            {
                Superclass::PrintSelf(os, indent);
                os << indent << "File path: " << _filePath << std::endl;
            }


        } // end namespace functors

        template <unsigned int VDimensions>
        typename FieldRepresentationDescriptor<VDimensions>::Pointer
            createFieldRepresentationOfMetaImageFile(const String& filePath)
        {
            if (filePath.empty())
            {
            }

            if (!itksys::SystemTools::FileExists(filePath.c_str()))
            {
                mapExceptionStaticMacro(::itk::ImageFileReaderException,
                    << "The file doesn't exist. Cannot create field description." << std::endl << "Filename = " <<
                    filePath);
            }

            itk::ImageIOBase::Pointer spImageIO = itk::ImageIOFactory::CreateImageIO(filePath.c_str(), itk::IOFileModeEnum::ReadMode);

            if (spImageIO.IsNull())
            {
                mapExceptionStaticMacro(::itk::ImageFileReaderException,
                    << "Cannot create field description. No image io available for field file." << std::endl << "Filename = " <<
                    filePath);
            }

            spImageIO->SetFileName(filePath);
            spImageIO->ReadImageInformation();

            const unsigned int numberOfDimensionsIO = spImageIO->GetNumberOfDimensions();

            if (numberOfDimensionsIO != VDimensions)
            {
                mapExceptionStaticMacro(DimRepresentationException,
                    << "Cannot create field description. Invalid dimensionality. Dimension of meta image: " <<
                    numberOfDimensionsIO << "; expected Dimension: " << VDimensions);
            }

            typedef FieldRepresentationDescriptor<VDimensions> FRDType;

            typename FRDType::PointType origin;
            typename FRDType::SizeType fieldSize;
            typename FRDType::SpacingType fieldSpacing;
            typename FRDType::DirectionType direction;

            for (unsigned int i = 0; i < VDimensions; i++)
            {
                fieldSpacing[i] = spImageIO->GetSpacing(i);
                fieldSize[i] = static_cast<typename FRDType::SizeType::SizeValueType>(spImageIO->GetDimensions(
                    i) * fieldSpacing[i]);
                origin[i] = spImageIO->GetOrigin(i);

                // Please note: direction cosines are stored as columns of the
                // direction matrix
                std::vector<typename FRDType::DirectionType::ValueType> axis;

                axis = spImageIO->GetDirection(i);

                for (unsigned j = 0; j < VDimensions; j++)
                {
                    direction[j][i] = axis[j];
                }
            }

            typename FRDType::Pointer spFRD = FRDType::New();

            spFRD->setSpacing(fieldSpacing);
            spFRD->setSize(fieldSize);
            spFRD->setOrigin(origin);
            spFRD->setDirection(direction);

            return spFRD;
        };

    } // end namespace core
} // end namespace map

#endif
