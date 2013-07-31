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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapVolumeSize.tpp $
*/

#ifndef __MAP_VOLUME_SIZE_TPP
#define __MAP_VOLUME_SIZE_TPP

#include "mapVolumeSize.tpp"
#include <assert.h>

namespace map
{
	namespace core
	{
		namespace continuous
		{

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::Self
			VolumeSize<VDimensions>::
			operator+(const Self &vec) const
			{
				Self result;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					result[i] = _size[i] + vec._size[i];
				}

				return result;
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::Self &
			VolumeSize<VDimensions>::
			operator+=(const Self &vec)
			{
				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					_size[i] += vec._size[i];
				}

				return *this;
			}

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::Self
			VolumeSize<VDimensions>::
			operator-(const Self &vec) const
			{
				Self result;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					result[i] = _size[i] - vec._size[i];
				}

				return result;
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::Self &
			VolumeSize<VDimensions>::
			operator-=(const Self &vec)
			{
				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					_size[i] -= vec._size[i];
				}

				return *this;
			}

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::Self
			VolumeSize<VDimensions>::
			operator*(const Self &vec) const
			{
				Self result;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					result[i] = _size[i] * vec._size[i];
				}

				return result;
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::Self &
			VolumeSize<VDimensions>::
			operator*=(const Self &vec)
			{
				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					_size[i] *= vec._size[i];
				}

				return *this;
			}

			template<unsigned int VDimensions>
			bool
			VolumeSize<VDimensions>::
			operator==(const Self &vec) const
			{
				bool same = true;

				for (unsigned int i = 0; i < VDimensions && same; ++i)
				{
					same = (_size[i] == vec._size[i]);
				}

				return same;
			}

			template<unsigned int VDimensions>
			bool
			VolumeSize<VDimensions>::
			operator!=(const Self &vec) const
			{
				bool same = true;

				for (unsigned int i = 0; i < VDimensions && same; ++i)
				{
					same = (_size[i] == vec._size[i]);
				}

				return !same;
			}

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::SizeValueType &
			VolumeSize<VDimensions>::
			operator[](unsigned int dim)
			{
				assert(dim < VDimensions); //check if index dim is out of bound
				return _size[dim];
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::SizeValueType
			VolumeSize<VDimensions>::
			operator[](unsigned int dim) const
			{
				assert(dim < VDimensions); //check if index dim is out of bound
				return _size[dim];
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::SizeValueType *
			VolumeSize<VDimensions>::
			getVolumeSize() const
			{
				return _size;
			};

			template<unsigned int VDimensions>
			void
			VolumeSize<VDimensions>::
			setVolumeSize(const SizeValueType val[VDimensions])
			{
				memcpy(_size, val, sizeof(SizeValueType)*VDimensions);
			}

			template<unsigned int VDimensions>
			void
			VolumeSize<VDimensions>::
			setElement(unsigned long element, SizeValueType val)
			{
				_size[ element ] = val;
			}

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::SizeValueType
			VolumeSize<VDimensions>::
			getElement(unsigned long element) const
			{
				assert(element < VDimensions); //check if index element is out of bound
				return _size[ element ];
			}

			template<unsigned int VDimensions>
			void
			VolumeSize<VDimensions>::
			fill(SizeValueType value)
			{
				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					_size[i] = value;
				}
			}

			template<unsigned int VDimensions>
			bool
			VolumeSize<VDimensions>::
			isPositive() const
			{
				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					if (_size[i] < 0)
					{
						return false;
					}
				}

				return true;
			};


			template<unsigned int VDimensions>
			std::ostream &operator<<(std::ostream &os, const VolumeSize<VDimensions> &size)
			{
				os << "[";

				for (unsigned int i = 0; i + 1 < VDimensions; ++i)
				{
					os << size[i] << ", ";
				}

				if (VDimensions >= 1)
				{
					os << size[VDimensions - 1];
				}

				os << "]";
				return os;
			}

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#endif
