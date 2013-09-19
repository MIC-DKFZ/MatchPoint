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


#ifndef __MAP_PM_VOLUME_H
#define __MAP_PM_VOLUME_H

#include <vector>
#include <iostream>

#include "mapContinuous.h"
#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		namespace continuous
		{

			/*! @class PMVolume
			* @brief Represents a continuouse volume by a bounding box.
			*
			* Serves as continuouse analogy for the discrete image region.
			* The difference between the class Volume and PMVolume is that
			* PMVolume isn't templated by the dimension number, thus it
			* is somehow a variant container for normal volume information
			* that can be treated polymorphically. Therefore the prefix
			* PM stands for poly morphic.
			* @sa Volume
			* @sa ImageRegion
			*
			* @ingroup Continuous
			*/
			class MAPCore_EXPORT PMVolume
			{
			public:
				/*! Standard class typedefs. */
				typedef PMVolume  Self;

				/*! Dimension of the volume available at run time. */
				unsigned int getVolumeDimension()  const;

				/*! Point typedef support.*/
				typedef ScalarType									 PointValueType;
				typedef std::vector<PointValueType>  PointType;
				typedef PointValueType							 OriginValueType;
				typedef PointType										 OriginType;

				/*! Size typedef support. A size is used to define volume bounds. */
				typedef ScalarType SizeValueType;
				typedef std::vector<SizeValueType>   SizeType;

				/*! Constructor. PMVolume is a lightweight object that is not reference
				* counted, so the constructor is public.
				*
				* @eguarantee strong */
				PMVolume();

				/*! Destructor. PMVolume is a lightweight object that is not reference
				* counted and not supposed to be a base object, so the destructor is non virtual public.
				* @eguarantee none throw*/
				~PMVolume();

				/*! Copy constructor. PMVolume is a lightweight object that is not
				* reference counted, so the copy constructor is public.
				* @eguarantee strong */
				PMVolume(const Self& volume);

				/*! Constructor that takes an origin and size. PMVolume is a lightweight
				* object that is not reference counted, so this constructor is public.
				* @eguarantee strong
				* @param [in] origin Values of the volume origin.
				* @param [in] size Values of the volume size.
				* @pre Origin and size must have the same vector size.*/
				PMVolume(const OriginType& origin, const SizeType& size);

				/*! Constructor that takes a size and assumes an origin of zero. PMVolume
				* is lightweight object that is not reference counted so this constructor
				* is public.
				* @eguarantee strong */
				PMVolume(const SizeType& size);

				/*! operator=. PMVolume is a lightweight object that is not reference
				* counted, so operator= is public.
				* @eguarantee basic */
				void operator=(const Self& volume);

				/*! operator==. Checks if two PMVolume instance define the same volume.
				* @eguarantee basic */
				bool operator==(const Self& volume) const;

				/*! Set the origin defining the corner of the region.
				* @eguarantee strong */
				void setOrigin(const OriginType& origin);

				/*! Get the point defining the origin of the volume.
				* @eguarantee strong */
				const OriginType& getOrigin() const;

				/*! Set the size of the volume. This plus the origin determines the
				* rectangular shape, or extent, of the volume.
				* @eguarantee strong */
				void setSize(const SizeType& size);

				/*! Get the size of the volume.
				* @eguarantee strong */
				const SizeType& getSize() const;

				/*! Convenience methods to set the size of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..getVolumeDimension()-1).
				* @pre see parameters*/
				void setSize(unsigned long i, SizeValueType sze);

				/*! Convenience methods to get the size of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..getVolumeDimension()-1).
				* @pre see parameters*/
				SizeValueType getSize(unsigned long i) const;

				/*! Convenience methods to set the origin value of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..getVolumeDimension()-1).
				* @pre see parameters*/
				void setOrigin(unsigned long i, OriginValueType sze);

				/*! Convenience methods to get the origin value of the particular dimension i.
				* @param [in] i Index of the particular dimension; must be within the range
				* of the volume dimensions (0..getVolumeDimension()-1).
				* @pre see parameters*/
				OriginValueType getOrigin(unsigned long i) const;

			protected:
				OriginType _origin;
				SizeType   _size;
			};

			MAPCore_EXPORT std::ostream& operator<<(std::ostream& os, const PMVolume& volume);

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#endif
