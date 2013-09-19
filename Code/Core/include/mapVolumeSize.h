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

#ifndef __MAP_VOLUME_SIZE_H
#define __MAP_VOLUME_SIZE_H

#include "mapContinuous.h"
#include <iostream>

namespace map
{
	namespace core
	{
		namespace continuous
		{

			/*! @class Size
			* @brief Represent the size (bounds) of a n-dimensional volume.
			*
			* Size is a class to represent multi-dimensional volume bounds,
			* templated over the dimension.
			*
			* For the sake of efficiency, Size does not define a default constructor, a
			* copy constructor, or an operator=. We rely on the compiler to provide
			* efficient bitwise copies.
			*
			* Size is an "aggregate" class.  Its data is public (_size)
			* allowing for fast and convenient instantiations/assignments.
			*
			* The following syntax for assigning a size is allowed/suggested:
			*    VolumeSize<3> size = {256, 256, 20};
			*
			* @ingroup Continuous
			*/
			template<unsigned int VDimensions = 2>
			class VolumeSize
			{
			public:
				/** Standard class typedefs. */
				typedef VolumeSize<VDimensions>  Self;

				/** Compatible Size and value typedef */
				typedef   VolumeSize<VDimensions>  SizeType;
				typedef   ScalarType              SizeValueType;

				/** Get the dimension of the size object. */
				static unsigned int getVolumeSizeDimension(void)
				{
					return VDimensions;
				}

				/** Add two sizes.  */
				Self operator+(const Self& vec) const;

				/** Increment size by a size.  */
				const Self& operator+=(const Self& vec);

				/** Subtract two sizes.  */
				Self operator-(const Self& vec) const;

				/** Decrement size by a size.  */
				const Self& operator-=(const Self& vec);

				/** Multiply two sizes (elementwise product).  */
				Self operator*(const Self& vec) const;

				/** Multiply two sizes (elementwise product).  */
				const Self& operator*=(const Self& vec);

				/** Compare two sizes. */
				bool operator==(const Self& vec) const;

				/** Compare two sizes. */
				bool operator!=(const Self& vec) const;

				/** Access an element of the size. Elements are numbered
				* 0, ..., VDimension-1. No bounds checking is performed. */
				SizeValueType& operator[](unsigned int dim);

				/** Access an element of the size. Elements are numbered
				* 0, ..., VDimension-1. This version can only be an rvalue.
				* No bounds checking is performed. */
				const SizeValueType operator[](unsigned int dim) const;

				/** Get the value array of VolumeSize. This provides a read only reference to the size.
				* @sa SetSize */
				const SizeValueType* getVolumeSize() const;

				/** Set the value array of VolumeSize.
				 * Try to prototype this function so that val has to point to a block of
				 * memory that is the appropriate size. @sa GetSize */
				void setVolumeSize(const SizeValueType val[VDimensions]);

				/** Set an element of the Size.
				 * sets the value of one of the elements in the Size
				 * This method is mainly intended to facilitate the access to elements
				 * from Tcl and Python where C++ notation is not very convenient.
				 * @warning No bound checking is performed.
				 * @sa SetSize() @sa GetElement() */
				void setElement(unsigned long element, SizeValueType val);

				/** Get an element of the Size.
				* gets the value of one of the elements in the size
				* This method is mainly intended to facilitate the access to elements
				* from Tcl and Python where C++ notation is not very convenient.
				* @warning No bound checking is performed
				* @sa GetSize() @sa SetElement() */
				SizeValueType getElement(unsigned long element) const;

				/** Set one value for the index in all dimensions.  Useful for initializing
				* an offset to zero. */
				void fill(SizeValueType value);

				/** Checks if the volume is positive. */
				bool isPositive() const;

				/** Size is an "aggregate" class.  Its data is public (m_Size)
				* allowing for fast and convenient instantiations/assignments.
				*
				* The following syntax for assigning a size is allowed/suggested:
				*
				* Size<3> size = {{256, 256, 20}};
				*
				* The doubled braces {{ and }} are required to prevent `gcc -Wall'
				* (and perhaps other compilers) from complaining about a partly
				* bracketed initializer. */
				SizeValueType _size[VDimensions];
			};


			template<unsigned int VDimensions>
			std::ostream& operator<<(std::ostream& os, const VolumeSize<VDimensions>& size);

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapVolumeSize.tpp"
#endif

#endif
