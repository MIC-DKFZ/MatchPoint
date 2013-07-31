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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldByFileLoadFunctor.tpp $
*/

#ifndef __MAP_FIELD_BY_FILE_LOAD_FUNCTOR_TPP
#define __MAP_FIELD_BY_FILE_LOAD_FUNCTOR_TPP

#include "mapFieldByFileLoadFunctor.h"
#include "mapLogbookMacros.h"
#include "mapRepresentationException.h"

#include "itkImageFileReader.h"
#include "itkMetaImageIO.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::FieldPointer
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			generateField() const
			{
				mapLogInfoMacro( << "Generate field by file loading. File name: " << _filePath);

				typedef ::itk::ImageFileReader< FieldType > FieldReaderType;
				typename FieldReaderType::Pointer spFieldReader  = FieldReaderType::New();

				FieldPointer spField = NULL;

				try
				{
					spFieldReader->SetFileName(_filePath.c_str());
					spField = spFieldReader->GetOutput();
					spFieldReader->Update();
				}
				catch (itk::ExceptionObject &e)
				{
					e.SetDescription(String("Error in FieldByFileLoadFunctor while loading field. Description: ") + e.GetDescription());
					throw;
				}
				catch (const std::exception &e)
				{
					mapDefaultExceptionMacro( << "Error in FieldByFileLoadFunctor while loading field. Description: " << e.what());
				}
				catch (...)
				{
					mapDefaultExceptionMacro( << "Unknown error in FieldByFileLoadFunctor while loading field. File name: " << _filePath);
				}

				/**@TODO Have to add check of the field representation (the specified one and the one set
				 set in the functor.**/
				//Superclass::_spInFieldRepresentation = createFieldRepresentation(*spField).GetPointer();

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const String &
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			getFieldFilePath(void) const
			{
				return _filePath;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::Pointer
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			New(const String &filepath,
			    const InFieldRepresentationType *pInFieldRepresentation)
			{
				Pointer spFieldByFileLoadFunctor = new Self(filepath, pInFieldRepresentation);
				spFieldByFileLoadFunctor->UnRegister();
				return spFieldByFileLoadFunctor;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename ::itk::LightObject::Pointer
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			CreateAnother(void) const
			{
				::itk::LightObject::Pointer smartPtr;
				smartPtr = Self::New(_filePath, Superclass::_spInFieldRepresentation).GetPointer();
				return smartPtr;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			FieldByFileLoadFunctor(const String &filepath,
			                       const InFieldRepresentationType *pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _filePath(filepath)
			{
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			~FieldByFileLoadFunctor() {}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions>::
			PrintSelf(std::ostream &os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "File path: " << _filePath << std::endl;
			}


		} // end namespace functors

		template <unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::Pointer
		createFieldRepresentationOfMetaImageFile(const String &filePath)
		{
			if (filePath.empty())
			{
			}

			if (! itksys::SystemTools::FileExists(filePath.c_str()))
			{
				mapExceptionStaticMacro(::itk::ImageFileReaderException, << "The file doesn't exist. Cannot create field description." << std::endl << "Filename = " << filePath);
			}

			::itk::MetaImageIO::Pointer spImageIO = ::itk::MetaImageIO::New();
			spImageIO->SetFileName(filePath);
			spImageIO->ReadImageInformation();

			const unsigned int numberOfDimensionsIO = spImageIO->GetNumberOfDimensions();

			if (numberOfDimensionsIO != VDimensions)
			{
				mapExceptionStaticMacro(DimRepresentationException, << "Cannot create field description. Invalid dimensionality. Dimension of meta image: " << numberOfDimensionsIO << "; expected Dimension: " << VDimensions);
			}

			typedef FieldRepresentationDescriptor<VDimensions> FRDType;

			typename FRDType::PointType origin;
			typename FRDType::SizeType fieldSize;
			typename FRDType::SpacingType fieldSpacing;
			typename FRDType::DirectionType direction;

			for (unsigned int i = 0; i < VDimensions; i++)
			{
				fieldSpacing[i] = spImageIO->GetSpacing(i);
				fieldSize[i] =  static_cast<typename FRDType::SizeType::SizeValueType>(spImageIO->GetDimensions(i) * fieldSpacing[i]);
				origin[i]  = spImageIO->GetOrigin(i);

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
