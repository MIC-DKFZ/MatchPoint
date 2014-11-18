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

#ifndef __FIELD_REPRESENTATION_DESCRIPTOR_TPP
#define __FIELD_REPRESENTATION_DESCRIPTOR_TPP

#include "itkImageTransformHelper.h"

#include "mapFieldRepresentationDescriptor.h"
#include "mapExceptionObject.h"
#include "mapConvert.h"
#include "mapSDITKStreamingHelper.h"

namespace map
{
	namespace core
	{

		// **** public methods ****
		// ************************

		template<unsigned int VDimensions>
		inline const typename FieldRepresentationDescriptor<VDimensions>::SizeType
		FieldRepresentationDescriptor<VDimensions>::
		getSize() const
		{
			return *_pFieldSize;
		}

		template<unsigned int VDimensions>
		void
		FieldRepresentationDescriptor<VDimensions>::
		setSize(const SizeType& value)
		{
			SizeType* pNewSize = new SizeType(value);
			delete _pFieldSize;
			_pFieldSize = pNewSize;
		}


		template<unsigned int VDimensions>
		inline const typename FieldRepresentationDescriptor<VDimensions>::PointType
		FieldRepresentationDescriptor<VDimensions>::
		getOrigin() const
		{
			return *_pFieldOrigin;
		}


		template<unsigned int VDimensions>
		void
		FieldRepresentationDescriptor<VDimensions>::
		setOrigin(const PointType& value)
		{
			PointType* pNewPoint = new PointType(value);
			delete _pFieldOrigin;
			_pFieldOrigin = pNewPoint;
		}


		template<unsigned int VDimensions>
		inline const typename FieldRepresentationDescriptor<VDimensions>::SpacingType
		FieldRepresentationDescriptor<VDimensions>::
		getSpacing() const
		{
			return *_pFieldSpacing;
		}


		template<unsigned int VDimensions>
		void
		FieldRepresentationDescriptor<VDimensions>::
		setSpacing(const SpacingType& value)
		{
			SpacingType* pNewSpacing = new SpacingType(value);
			delete _pFieldSpacing;
			_pFieldSpacing = pNewSpacing;
		}


		template<unsigned int VDimensions>
		inline const typename FieldRepresentationDescriptor<VDimensions>::DirectionType
		FieldRepresentationDescriptor<VDimensions>::
		getDirection() const
		{
			return *_pFieldDirection;
		}


		template<unsigned int VDimensions>
		void
		FieldRepresentationDescriptor<VDimensions>::
		setDirection(const DirectionType& value)
		{
			DirectionType* pNewDirection = new DirectionType(value);
			delete _pFieldDirection;
			_pFieldDirection = pNewDirection;
		}

		template<unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::ImageRegionType
		FieldRepresentationDescriptor<VDimensions>::
		getRepresentedLocalImageRegion(const PointType& imageOrigin,
		                               const DirectionType& imageDirection) const
		{
			if (!(imageDirection == this->getDirection()))
			{
				mapDefaultExceptionMacro( <<
				                          "Directions of field representation and image are not the same. Cannot determin image region. Field direction: "
				                          << this->getDirection() << "; image direction: " << imageDirection);
			}

			typename ImageRegionType::SizeType regionSize;
			typename ImageRegionType::IndexType regionIndex;

			DirectionType pointToIndexMatrix = computePhysicalPointToIndexMatrix();

			::itk::ImageTransformHelper < VDimensions, VDimensions - 1,
			VDimensions - 1 >::TransformPhysicalPointToIndex(pointToIndexMatrix, imageOrigin, this->getOrigin(),
			        regionIndex);

			for (unsigned long i = 0; i < VDimensions; ++i)
			{
				regionSize[i] = static_cast<typename ImageRegionType::SizeType::SizeValueType>(floor((
				                    *_pFieldSize)[i] / (*_pFieldSpacing)[i]));
			}

			return ImageRegionType(regionIndex, regionSize);
		}

		template<unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::ImageRegionType
		FieldRepresentationDescriptor<VDimensions>::
		getRepresentedLocalImageRegion() const
		{
			return getRepresentedLocalImageRegion(this->getOrigin(), this->getDirection());
		}

		template<unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::DirectionType
		FieldRepresentationDescriptor<VDimensions>::
		computePhysicalPointToIndexMatrix() const
		{
			DirectionType scale;
			DirectionType result;

			for (unsigned int i = 0; i < VDimensions; i++)
			{
				scale[i][i] = (*_pFieldSpacing)[i];
			}

			if (vnl_determinant(_pFieldDirection->GetVnlMatrix()) == 0.0)
			{
				itkExceptionMacro( << "Bad direction, determinant is 0. Direction is " << *_pFieldDirection);
			}

			result = (*_pFieldDirection) * scale;
			result = result.GetInverse();

			return result;
		}

		template<unsigned int VDimensions>
		inline const typename FieldRepresentationDescriptor<VDimensions>::VolumeType
		FieldRepresentationDescriptor<VDimensions>::
		getRepresentedVolume() const
		{
			return VolumeType(*_pFieldOrigin, *_pFieldSize);
		}

		template<unsigned int VDimensions>
		bool
		FieldRepresentationDescriptor<VDimensions>::
		operator == (const Self& frd) const
		{
			bool result = this->getSize() == frd.getSize();

			if (result)
			{
				result = this->getOrigin() == frd.getOrigin();
			}

			if (result)
			{
				result = this->getSpacing() == frd.getSpacing();
			}

			if (result)
			{
				result = this->getDirection() == frd.getDirection();
			}

			return result;
		};


		// **** protected methods ****
		// ***************************

		template<unsigned int VDimensions>
		FieldRepresentationDescriptor<VDimensions>::
		FieldRepresentationDescriptor()
		{
			_pFieldSize = new SizeType();
			_pFieldSize->fill(0);
			_pFieldOrigin = new PointType();
			_pFieldOrigin->Fill(0);
			_pFieldSpacing = new SpacingType();
			_pFieldSpacing->Fill(0);
			_pFieldDirection = new DirectionType();
			_pFieldDirection->SetIdentity();
		}


		template<unsigned int VDimensions>
		FieldRepresentationDescriptor<VDimensions>::
		~FieldRepresentationDescriptor()
		{
			delete _pFieldSize;
			delete _pFieldOrigin;
			delete _pFieldSpacing;
			delete _pFieldDirection;
		}


		template<unsigned int VDimensions>
		void
		FieldRepresentationDescriptor<VDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			unsigned int i = 0;
			Superclass::PrintSelf(os, indent);
			// print field size
			os << indent << "field size: (";

			for (i = 0; i < VDimensions; i++)
			{
				os << (*_pFieldSize)[i] << " ";
			}

			os << ")\n";

			// print field origin
			os << indent << "field origin: (";

			for (i = 0; i < VDimensions; i++)
			{
				os << (*_pFieldOrigin)[i] << " ";
			}

			os << ")\n";

			// print field spacing
			os << indent << "field spacing: (";

			for (i = 0; i < VDimensions; i++)
			{
				os << (*_pFieldSpacing)[i] << " ";
			}

			os << ")\n" << std::endl;

			// print field direction
			os << indent << "field direction: (";
			os << *_pFieldSpacing;
			os << ")\n" << std::endl;

		}

		template<unsigned int VDimensions>
		::map::structuredData::StreamingInterface::ElementPointer
		FieldRepresentationDescriptor<VDimensions>::
		streamToSDInternal() const
		{
			structuredData::Element::Pointer spNewSD = structuredData::Element::New();

			spNewSD->setTag("FieldRepresentationDescriptor");

			//save attributes
			spNewSD->setAttribute("Dimensions", convert::toStr(VDimensions));

			//save size
			structuredData::Element::Pointer spSizeElement = SizeType::streamToStructuredData(this->getSize());
			spSizeElement->setTag("Size");
			spNewSD->addSubElement(spSizeElement);
			structuredData::Element::Pointer spOriginElement = structuredData::streamITKFixedArrayToSD(
			            this->getOrigin());
			spOriginElement->setTag("Origin");
			spNewSD->addSubElement(spOriginElement);
			structuredData::Element::Pointer spSpacingElement = structuredData::streamITKFixedArrayToSD(
			            this->getSpacing());
			spSpacingElement->setTag("Spacing");
			spNewSD->addSubElement(spSpacingElement);
			structuredData::Element::Pointer spDirectionElement = structuredData::streamITKMatrixToSD(
			            this->getDirection());
			spDirectionElement->setTag("Direction");
			spNewSD->addSubElement(spDirectionElement);

			return spNewSD;
		};

		template<unsigned int VDimensions>
		void
		FieldRepresentationDescriptor<VDimensions>::
		streamFromSDInternal(const structuredData::Element* pElement)
		{
			SizeType newSize;
			PointType newOrigin;
			SpacingType newSpacing;
			DirectionType newDirection;

			structuredData::Element::ConstSubElementIteratorType subPos = structuredData::findNextSubElement(
			            pElement->getSubElementBegin(), pElement->getSubElementEnd(), "Size");

			if (subPos == pElement->getSubElementEnd())
			{
				mapDefaultExceptionMacro( <<
				                          "Error: cannot stream from structured data. Reason: sub element \"Size\" is missing.");
			}

			newSize = SizeType::streamFromStructuredData(*subPos);

			subPos = structuredData::findNextSubElement(
			             pElement->getSubElementBegin(), pElement->getSubElementEnd(), "Origin");

			if (subPos == pElement->getSubElementEnd())
			{
				mapDefaultExceptionMacro( <<
				                          "Error: cannot stream from structured data. Reason: sub element \"Origin\" is missing.");
			}

			newOrigin = structuredData::streamSDToITKFixedArray<PointType>(*subPos);

			subPos = structuredData::findNextSubElement(
			             pElement->getSubElementBegin(), pElement->getSubElementEnd(), "Spacing");

			if (subPos == pElement->getSubElementEnd())
			{
				mapDefaultExceptionMacro( <<
				                          "Error: cannot stream from structured data. Reason: sub element \"Spacing\" is missing.");
			}

			newSpacing = structuredData::streamSDToITKFixedArray<SpacingType>(*subPos);

			subPos = structuredData::findNextSubElement(
			             pElement->getSubElementBegin(), pElement->getSubElementEnd(), "Direction");

			if (subPos == pElement->getSubElementEnd())
			{
				mapDefaultExceptionMacro( <<
				                          "Error: cannot stream from structured data. Reason: sub element \"Direction\" is missing.");
			}

			newDirection = structuredData::streamSDToITKMatrix<DirectionType>(*subPos);

			this->setSize(newSize);
			this->setOrigin(newOrigin);
			this->setSpacing(newSpacing);
			this->setDirection(newDirection);
		};

		// **** static methods ****
		// ************************

		template <class TImage>
		typename  FieldRepresentationDescriptor<TImage::ImageDimension>::Pointer
		createFieldRepresentation(const TImage& image)
		{
			typedef FieldRepresentationDescriptor<TImage::ImageDimension> FRDType;

			typename FRDType::Pointer spFRD = FRDType::New();

			typename FRDType::SizeType size;
			typename TImage::RegionType region = image.GetLargestPossibleRegion();
			typename TImage::SpacingType spacing = image.GetSpacing();

			for (unsigned long i = 0; i < TImage::ImageDimension; ++i)
			{
				size[i] = static_cast<typename FRDType::SizeType::SizeValueType>(region.GetSize(i) * spacing[i]);
			}

			spFRD->setSize(size);
			spFRD->setSpacing(spacing);
			spFRD->setOrigin(image.GetOrigin());
			spFRD->setDirection(image.GetDirection());

			return spFRD;
		}


		template <unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::Pointer
		createFieldRepresentation(const itk::ImageRegion<VDimensions>& region,
		                          const typename ::map::core::continuous::Elements<VDimensions>::SpacingType& spacing)
		{
			typename FieldRepresentationDescriptor<VDimensions>::DirectionType direction;
			typename FieldRepresentationDescriptor<VDimensions>::PointType origin;
			direction.SetIdentity();
			origin.Fill(0.0);

			return createFieldRepresentation(region, spacing, origin, direction);
		}

		template <unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::Pointer
		createFieldRepresentation(const itk::ImageRegion<VDimensions>& region,
		                          const typename ::map::core::continuous::Elements<VDimensions>::SpacingType& spacing,
		                          const typename FieldRepresentationDescriptor<VDimensions>::PointType& imageOrigin,
		                          const typename FieldRepresentationDescriptor<VDimensions>::DirectionType& direction)
		{
			typedef FieldRepresentationDescriptor<VDimensions> FRDType;

			typename FRDType::Pointer spFRD = FRDType::New();

			typename FRDType::DirectionType scale;
			typename FRDType::DirectionType indexToPointMatrix;

			typename FRDType::PointType origin;
			typename FRDType::SizeType size;
			typename FRDType::SpacingType fieldSpacing;

			for (unsigned long i = 0; i < VDimensions; ++i)
			{
				size[i] = static_cast<typename FRDType::SizeType::SizeValueType>(region.GetSize(i) * spacing[i]);
				fieldSpacing[i] = spacing[i];
				scale[i][i] = spacing[i];
			}

			indexToPointMatrix = direction * scale;
			::itk::ImageTransformHelper < VDimensions, VDimensions - 1,
			VDimensions - 1 >::TransformIndexToPhysicalPoint(indexToPointMatrix, imageOrigin, region.GetIndex(),
			        origin);

			spFRD->setSpacing(fieldSpacing);
			spFRD->setSize(size);
			spFRD->setOrigin(origin);
			spFRD->setDirection(direction);

			return spFRD;
		}


		template <class TVolume>
		typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::Pointer
		createFieldRepresentation(const TVolume& volume,
		                          const typename ::map::core::continuous::Elements<TVolume::VolumeDimension>::SpacingType& spacing,
		                          const typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::DirectionType& direction)
		{
			typedef FieldRepresentationDescriptor<TVolume::VolumeDimension> FRDType;

			typename FRDType::Pointer spFRD = FRDType::New();

			typename FRDType::PointType origin;
			typename FRDType::SizeType size;
			typename FRDType::SpacingType fieldSpacing;

			for (unsigned long i = 0; i < TVolume::VolumeDimension; ++i)
			{
				origin[i] = volume.getOrigin(i);
				size[i] = volume.getSize(i);
				fieldSpacing[i] = spacing[i];
			}

			spFRD->setSpacing(fieldSpacing);
			spFRD->setSize(size);
			spFRD->setOrigin(origin);
			spFRD->setDirection(direction);

			return spFRD;
		}

		template <class TVolume>
		typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::Pointer
		createFieldRepresentation(const TVolume& volume,
		                          const typename ::map::core::continuous::Elements<TVolume::VolumeDimension>::SpacingType& spacing)
		{
			typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::DirectionType direction;
			direction.SetIdentity();

			return createFieldRepresentation(volume, spacing, direction);
		}


	} // end namespace core
} // end namespace map

#endif
