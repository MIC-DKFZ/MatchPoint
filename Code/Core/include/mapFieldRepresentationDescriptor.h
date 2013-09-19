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


#ifndef __FIELD_REPRESENTATION_DESCRIPTOR_H
#define __FIELD_REPRESENTATION_DESCRIPTOR_H

#include "mapContinuousElements.h"
#include "mapVolume.h"
#include "mapDiscreteElements.h"

#include "itkLightObject.h"
#include "itkImageRegion.h"
#include "itkMatrix.h"


/*! @namespace map The namespace map::core is for the library of MatchPoint
*/
namespace map
{
	namespace core
	{

		/*! @class FieldRepresentationDescriptor
		@brief class for FieldRepresentationDescriptor.

		This class is used as descriptor for a continous or discrete volume of finite size.
		It is always used by MatchPoint if there is the need to define the field of view
		or of support (e.g. which area of the target space is to be supported by the registration
		determined by an algorithm in the case that the registration must be defined by
		a vector field, hence it will only have limited coverage).
			@ingroup Registration
		*/
		template<unsigned int VDimensions>
		class FieldRepresentationDescriptor : public itk::LightObject
		{
		public:
			typedef FieldRepresentationDescriptor<VDimensions> Self;
			typedef itk::LightObject Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(FieldRepresentationDescriptor, itk::LightObject);
			itkNewMacro(Self);

			typedef typename discrete::Elements<VDimensions>::ImageRegionType  ImageRegionType;
			typedef typename continuous::Volume<VDimensions>                   VolumeType;

			/** Spacing typedef support.  Spacing holds the size of a pixel. The
			 * spacing is the geometric distance between descriptor samples.
			 * @remark ITK only supports positive spacing value: negative values may cause
			 * undesirable results.  */
			typedef typename continuous::Elements<VDimensions>::SpacingType    SpacingType;
			/** Origin typedef support.  The origin is the geometric coordinates
			 * of the index (0,0). */
			typedef typename continuous::Elements<VDimensions>::PointType      PointType;
			/** Size typedef support. A size is used to define the bounds
			 * of the field representation.
			 * @remark In contrast to the itk::ImageRegion this size is the continuous
			 * size (therefor size of the image and not the number of voxels). */
			typedef typename continuous::Elements<VDimensions>::VolumeSizeType SizeType;

			/** Direction typedef support.  The Direction is a matrix of
			 * direction cosines that specify the direction between samples.
			 * */
			typedef itk::Matrix<double, VDimensions, VDimensions>   DirectionType;

			/*! gets the field size
			@eguarantee strong
			@return a const SizeType value
			*/
			inline const SizeType getSize() const;


			/*! sets the field size
			@eguarantee strong
			@param value a value for the SizeType
			*/
			void setSize(const SizeType& value);


			/*! gets the field origin
			@eguarantee strong
			@return a const PointType value
			*/
			inline const PointType getOrigin() const;

			/*! sets the field origin
			@eguarantee strong
			@param value a value for the PointType
			*/
			void setOrigin(const PointType& value);


			/*! gets the field spacing
			@eguarantee strong
			@return a const SpacingType value
			*/
			inline const SpacingType getSpacing() const;

			/*! sets the field spacing
			@eguarantee strong
			@param value a value for the SpacingType
			*/
			void setSpacing(const SpacingType& value);

			/*! gets the field direction
			@eguarantee strong
			@return a const DirectionType value
			*/
			inline const DirectionType getDirection() const;

			/*! sets the field direction
			* The direction cosines are vectors that point from one pixel to the next.
			*
			* One row of the matrix indicates the direction cosines of the unit vector
			* that is parallel to the lines of the image grid corresponding to that
			* dimension. For example, and image with Direction matrix
			*
			*    0.866   0.500
			*   -0.500   0.866
			*
			* has an image grid were the fastest changing index (dimension[0]) walks
			* over a line that in Physical space is oriented parallel to the vector
			* (0.866,0.5). The second fastest changing index (dimension[1]) walks along
			* a line that in Physical space is oriented parallel to the vector
			* (-0.5,0.866)
			*
			* The vectors whose direction cosines are stored in the Direction matrix,
			* are expected to be orthogonal to each other, and they are expected to form
			* a right handed coordinate system, but this is not checked nor enforced here
			* or in the the itk::ImageBase.
			*
			* For details, please see:
			*
			* http://www.itk.org/Wiki/Proposals:Orientation#Some_notes_on_the_DICOM_convention_and_current_ITK_usage
			@eguarantee strong
			@param value a value for the SpacingType
			*/
			void setDirection(const DirectionType& value);

			/*! gets the represented image region in a local context of an image, thus the index of the image region is
			 * calculated relative to the passed imageOrigin.
			@pre Image direction and field direction must be equal
			@eguarantee strong
			@return an ImageRegionType containing the represented region
			*/
			ImageRegionType getRepresentedLocalImageRegion(const PointType& imageOrigin,
					const DirectionType& imageDirection) const;

			/*! gets the represented image region in a local context of the field representation descriptor. Thus index is zero.
			 * Has the same effect like calling getRepresentedLocalImageRegion(getOrigin()).
			@eguarantee strong
			@return an ImageRegionType containing the represented region
			*/
			ImageRegionType getRepresentedLocalImageRegion() const;

			/*! gets the represented volume
			@eguarantee strong
			@return a Volume containing the represented volume
			*/
			inline const VolumeType getRepresentedVolume() const;

			bool operator == (const Self& frd) const;

		protected:
			FieldRepresentationDescriptor();
			virtual ~FieldRepresentationDescriptor();

			/*! Helper method that computes a matrix (direction and spacing)
			  that can be used to convert points to index. It is equal to the
			  concept used in itk::ImageBase to compute the index and point matrices.
			 @eguarantee strong
			*/
			DirectionType computePhysicalPointToIndexMatrix() const;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			//using PIMPL idiom to realize strong exception guarantee
			SizeType* _pFieldSize;
			//using PIMPL idiom to realize strong exception guarantee
			PointType* _pFieldOrigin;
			//using PIMPL idiom to realize strong exception guarantee
			SpacingType* _pFieldSpacing;
			//using PIMPL idiom to realize strong exception guarantee
			DirectionType* _pFieldDirection;

		private:

			//No copy constructor allowed
			FieldRepresentationDescriptor(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

		/*! creates a field representation descriptor from an image
		@eguarantee strong
		@param image a reference to an image
		@return a FieldRepresentationDescriptor
		*/
		template <class TImage>
		typename FieldRepresentationDescriptor<TImage::ImageDimension>::Pointer
		createFieldRepresentation(const TImage& image);

		/*! creates a field representation descriptor from an image region
		@remark The direction of the representation is identity. The image origin is assumed to be 0.
		@eguarantee strong
		@param region a reference to an image region
		@param spacing spacing that should be used to convert between discrete and continuous values.
		@return a FieldRepresentationDescriptor
		*/
		template <unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::Pointer
		createFieldRepresentation(const itk::ImageRegion<VDimensions>& region,
								  const typename ::map::core::continuous::Elements<VDimensions>::SpacingType& spacing);

		/*! creates a field representation descriptor from an image region
		@eguarantee strong
		@param region a reference to an image region
		@param spacing spacing that should be used to convert between discrete and continuous values.
		@param imageOrigin Origin of the "image" the region is gathered from. It affects the computation of the origin of ther representation, because it is assumed
		 that the index of the passed region is always defined relative to the image origin.
		@param direction Direction of the field/image region.
		@return a FieldRepresentationDescriptor
		*/
		template <unsigned int VDimensions>
		typename FieldRepresentationDescriptor<VDimensions>::Pointer
		createFieldRepresentation(const itk::ImageRegion<VDimensions>& region,
								  const typename ::map::core::continuous::Elements<VDimensions>::SpacingType& spacing,
								  const typename FieldRepresentationDescriptor<VDimensions>::PointType& imageOrigin,
								  const typename FieldRepresentationDescriptor<VDimensions>::DirectionType& direction);


		/*! creates a field representation descriptor from a volume
		@eguarantee strong
		@remark The direction of the representation is identity.
		@param volume a reference to a volume
		@param spacing spacing that should be used to convert between discrete and continuous values.
		@return a FieldRepresentationDescriptor
		*/
		template <class TVolume>
		typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::Pointer
		createFieldRepresentation(const TVolume& volume,
								  const typename ::map::core::continuous::Elements<TVolume::VolumeDimension>::SpacingType& spacing);

		/*! creates a field representation descriptor from a volume
		@eguarantee strong
		@param volume a reference to a volume
		@param spacing spacing that should be used to convert between discrete and continuous values.
		@param direction Direction of the field/volume.
		@return a FieldRepresentationDescriptor
		*/
		template <class TVolume>
		typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::Pointer
		createFieldRepresentation(const TVolume& volume,
								  const typename ::map::core::continuous::Elements<TVolume::VolumeDimension>::SpacingType& spacing,
								  const typename FieldRepresentationDescriptor<TVolume::VolumeDimension>::DirectionType& direction);


	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapFieldRepresentationDescriptor.tpp"
#endif

#endif
