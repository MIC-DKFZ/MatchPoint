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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapVolume.h $
*/


#ifndef __MAP_VOLUME_H
#define __MAP_VOLUME_H

#include "mapPMVolume.h"
#include "mapVolumeSize.h"
#include "mapContinuousElements.h"

#include "itkMacro.h"

namespace map
{
	namespace core
	{
		namespace continuous
		{

			/*! @class Volume
			* @brief Represents a continuouse volume by a bounding box.
			*
			* Serves as continuouse analogy for the discrete image region
			* @sa PMVolume
			* @sa ImageRegion
			*
			* @ingroup Continuous
			*/
			template <unsigned int VDimensions>
			class Volume
			{
			public:
				/*! Standard class typedefs. */
				typedef Volume  Self;

				/*! Dimension of the volume available at compile time. */
				itkStaticConstMacro(VolumeDimension, unsigned int, VDimensions);

				/*! Dimension of the volume available at run time. */
				static unsigned int getVolumeDimension()
				{
					return VDimensions;
				}

				/*! Point typedef support.*/
				typedef typename Elements<VDimensions>::PointType PointType;
				typedef typename Elements<VDimensions>::PointType OriginType;
				typedef typename PointType::ValueType             OriginValueType;

				/*! Size typedef support. A size is used to define volume bounds. */
				typedef VolumeSize<VDimensions>  SizeType;
				typedef typename SizeType::SizeValueType SizeValueType;

				/*! Constructor. Volume is a lightweight object that is not reference
				* counted, so the constructor is public.
				* @eguarantee strong */
				Volume();

				/*! Destructor. Volume is a lightweight object that is not reference
				* counted and not supposed to be a base object, so the destructor is non virtual public.
				* @eguarantee none throw*/
				~Volume();

				/*! Copy constructor. Volume is a lightweight object that is not
				* reference counted, so the copy constructor is public.
				* @eguarantee strong */
				Volume(const Self &volume);

				/*! Constructor that takes an origin and size. Volume is a lightweight
				* object that is not reference counted, so this constructor is public.
				* @eguarantee strong
				* @pre Parameter size must be positive. */
				Volume(const OriginType &origin, const SizeType &size);

				/*! Constructor that takes a size and assumes an origin of zero. Volume
				* is lightweight object that is not reference counted so this constructor
				* is public.
				* @eguarantee strong
				* @pre Parameter size must be positive. */
				Volume(const SizeType &size);

				/*! operator=. Volume is a lightweight object that is not reference
				* counted, so operator= is public.
				* @eguarantee basic */
				void operator=(const Self &volume);

				/*! Set the point defining the origin of the volume.
				* @eguarantee strong */
				void setOrigin(const OriginType &origin);

				/*! Get the point defining the origin of the volume.
				* @eguarantee strong */
				const OriginType &getOrigin() const;

				/*! Set the size of the volume. This plus the origin determines the
				* rectangular shape, or extent, of the volume.
				* @eguarantee strong
				* @pre Parameter size must be positive.*/
				void setSize(const SizeType &size);

				/*! Get the size of the volume.
				* @eguarantee strong */
				const SizeType &getSize() const;

				/*! Convenience methods to set the size of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..VDimensions-1).
				* @param [in] sze new size of the particular dimension; must be positive or zero.
				* @pre see parameters*/
				void setSize(unsigned long i, SizeValueType sze);

				/*! Convenience methods to get the size of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..VDimensions-1).
				* @pre see parameters*/
				SizeValueType getSize(unsigned long i) const;

				/*! Convenience methods to set the origin value of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..VDimensions-1).
				* @pre see parameters*/
				void setOrigin(unsigned long i, OriginValueType sze);

				/*! Convenience methods to get the origin value of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..VDimensions-1).
				* @pre see parameters*/
				OriginValueType getOrigin(unsigned long i) const;

				/*! Compare two volumes. */
				bool operator==(const Self &volume) const;

				/*! Compare two volumes. */
				bool operator!=(const Self &volume) const;

				/*! Test if an point is inside */
				bool isInside(const PointType &point) const;

				/*! Test if a region (the argument) is completly inside of this volume */
				bool isInside(const Self &volume) const;


				/*! Crop a region by another region. If this region is outside of the
				* crop, this method returns false and does not modify the
				* region. Otherwise, this method returns true and the region is
				* modified to reflect the crop. */
				bool crop(const Self &region);

				/*! Creates a copy of this volume and expands the copie in such a way,
				* that the new volume is a bounding box of the original volume and the point.
				* @param [in] point Point that should be contained by the new volume.
				* @return the new expanded volume.
				* @eguarantee strong */
				Self expand(const PointType &point) const;

				/*! Creates a copy of this volume and expands the copy in such a way,
				* that the new volume is a bounding box of this and the second volume.
				* @eguarantee strong
				* @param [in] volume2 The second volume that should also be contained
				* by the new volume.
				* @return the new expanded volume.
				*/
				Self expand(const Self &volume2) const;

				/*! Converts this to a poly morphical volume representation (PMVolume).
				* @eguarantee strong
				* @return PMVolume instance of the volume.*/
				PMVolume convertToPMVolume() const;

			private:
				OriginType          _origin;
				SizeType            _size;
			};

			template<unsigned int VDimensions>
			std::ostream &operator<<(std::ostream &os, const Volume<VDimensions> &region);

			template<unsigned int VDimensions>
			Volume<VDimensions> convertToVolume(const PMVolume &pmVolume);
			template<unsigned int VDimensions>
			PMVolume convertToPMVolume(const Volume<VDimensions> &volume);

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapVolume.tpp"
#endif

#endif
