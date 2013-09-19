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


#ifndef __MAP_VOLUME_TPP
#define __MAP_VOLUME_TPP

#include "mapVolume.h"
#include <assert.h>

namespace map
{
	namespace core
	{
		namespace continuous
		{

			template <unsigned int VDimensions>
			Volume<VDimensions>::
			Volume()
			{
			};

			template <unsigned int VDimensions>
			Volume<VDimensions>::
			~Volume()
			{};

			template <unsigned int VDimensions>
			Volume<VDimensions>::
			Volume(const Self& volume): _origin(volume._origin), _size(volume._size)
			{};

			template <unsigned int VDimensions>
			Volume<VDimensions>::
			Volume(const OriginType& origin, const SizeType& size): _origin(origin), _size(size)
			{
				assert(size.isPositive()); //size must be positive
			};

			template <unsigned int VDimensions>
			Volume<VDimensions>::
			Volume(const SizeType& size): _size(size)
			{
				assert(size.isPositive()); //size must be positive
				_origin.Fill(0);
			} ;

			template <unsigned int VDimensions>
			void
			Volume<VDimensions>::
			operator=(const Self& volume)
			{
				_origin = volume._origin;
				_size = volume._size;
			};

			template <unsigned int VDimensions>
			void
			Volume<VDimensions>::
			setOrigin(const OriginType& origin)
			{
				_origin = origin;
			};

			template <unsigned int VDimensions>
			const typename Volume<VDimensions>::OriginType&
			Volume<VDimensions>::
			getOrigin() const
			{
				return _origin;
			};

			template <unsigned int VDimensions>
			void
			Volume<VDimensions>::
			setSize(const SizeType& size)
			{
				assert(size.isPositive()); //size must be positive
				_size = size;
			};

			template <unsigned int VDimensions>
			const typename Volume<VDimensions>::SizeType&
			Volume<VDimensions>::
			getSize() const
			{
				return _size;
			}

			template <unsigned int VDimensions>
			void
			Volume<VDimensions>::
			setSize(unsigned long i, SizeValueType sze)
			{
				assert(i < VDimensions); //index for setting may not be out of bound
				assert(sze >= 0); //size must be positive
				_size[i] = sze;
			}

			template <unsigned int VDimensions>
			typename Volume<VDimensions>::SizeValueType
			Volume<VDimensions>::
			getSize(unsigned long i) const
			{
				assert(i < VDimensions); //index for getting may not be out of bound
				return _size[i];
			}

			template <unsigned int VDimensions>
			void
			Volume<VDimensions>::
			setOrigin(unsigned long i, OriginValueType sze)
			{
				assert(i < VDimensions); //index for getting may not be out of bound
				_origin[i] = sze;
			}

			template <unsigned int VDimensions>
			typename Volume<VDimensions>::OriginValueType
			Volume<VDimensions>::
			getOrigin(unsigned long i) const
			{
				assert(i < VDimensions); //index for getting may not be out of bound
				return _origin[i];
			}

			template <unsigned int VDimensions>
			bool
			Volume<VDimensions>::
			operator==(const Self& volume) const
			{
				bool same = 1;
				same = (_origin == volume._origin);
				same = same && (_size == volume._size);
				return same;
			}

			template <unsigned int VDimensions>
			bool
			Volume<VDimensions>::
			operator!=(const Self& volume) const
			{
				bool same = 1;
				same = (_origin == _origin);
				same = same && (_size == _size);
				return !same;
			}

			template <unsigned int VDimensions>
			bool
			Volume<VDimensions>::
			isInside(const PointType& point) const
			{
				for (unsigned int i = 0; i < VolumeDimension; ++i)
				{
					if (point[i] < _origin[i])
					{
						return false;
					}

					if (point[i] >= _origin[i] + _size[i])
					{
						return false;
					}
				}

				return true;
			}

			template <unsigned int VDimensions>
			bool
			Volume<VDimensions>::
			isInside(const Self& volume) const
			{
				OriginType beginCorner = volume.GetIndex();

				if (! this->isInside(beginCorner))
				{
					return false;
				}

				OriginType endCorner;
				SizeType  size = volume.GetSize();

				for (unsigned int i = 0; i < VDimensions; i++)
				{
					endCorner[i] = beginCorner[i] + size[i] - 1;
				}

				if (! this->IsInside(endCorner))
				{
					return false;
				}

				return true;
			}

			template <unsigned int VDimensions>
			bool
			Volume<VDimensions>::
			crop(const Self& region)
			{
				double crop;
				unsigned int i;
				bool cropPossible = true;

				// Can we crop?
				for (i = 0; i < VDimensions && cropPossible; i++)
				{
					// Is left edge of current region to the right of the right edge
					// of the region to crop with? (if so, we cannot crop)
					if (_origin[i] >= region.GetIndex()[i]
						+ static_cast<double>(region.GetSize()[i]))
					{
						cropPossible = false;
					}

					// If right edge of the current region to the left of the left
					// edge of the region to crop with? (if so, we cannot crop)
					if (_origin[i] + static_cast<double>(_size[i]) <= region.GetIndex()[i])
					{
						cropPossible = false;
					}
				}

				// if we cannot crop, return without changing anythin
				if (!cropPossible)
				{
					return cropPossible;
				}

				// we can crop, so crop
				for (i = 0; i < VDimensions; i++)
				{
					// first check the start index
					if (_origin[i] < region.GetIndex()[i])
					{
						// how much do we need to adjust
						crop = region.GetIndex()[i] - _origin[i];

						// adjust the start index and the size of the current region
						_origin[i] += crop;
						_size[i] -= static_cast<double>(crop);
					}

					// now check the final size
					if (_origin[i] + static_cast<double>(_size[i])
						> region.GetIndex()[i] + static_cast<double>(region.GetSize()[i]))
					{
						// how much do we need to adjust
						crop = _origin[i] + static_cast<double>(_size[i])
							   - region.GetIndex()[i] - static_cast<double>(region.GetSize()[i]);

						// adjust the size
						_size[i] -= static_cast<double>(crop);
					}
				}

				return cropPossible;

			};

			template <unsigned int VDimensions>
			typename Volume<VDimensions>::Self
			Volume<VDimensions>::
			expand(const PointType& point) const
			{
				OriginType origin = this->getOrigin();
				SizeType size = this->getSize();

				for (unsigned int i = 0; i < VolumeDimension; ++i)
				{
					if (point[i] < origin[i])
					{
						size[i] += origin[i] - point[i];
						origin[i] = point[i];
					}
					else if (point[i] >= origin[i] + size[i])
					{
						size[i] = point[i] - origin[i];
					}
				}

				return Self(origin, size);
			};

			template <unsigned int VDimensions>
			typename Volume<VDimensions>::Self
			Volume<VDimensions>::
			expand(const Self& volume2) const
			{
				const OriginType& origin = this->getOrigin();
				const SizeType& size = this->getSize();
				const OriginType& origin2 = volume2.getOrigin();
				const SizeType& size2 = volume2.getSize();
				OriginType blP(origin); //bottom left point
				OriginType trP;  //top right point
				SizeType resultSize;

				//compute outer points
				for (unsigned int i = 0; i < VolumeDimension; ++i)
				{
					if (origin2[i] < origin[i])
					{
						blP[i] = origin2[i];
					}

					if (origin2[i] + size2[i] > origin[i] + size[i])
					{
						trP[i] = origin2[i] + size2[i];
					}
					else
					{
						trP[i] = origin[i] + size[i];
					}

					resultSize[i] = trP[i] - blP[i];
				}

				return Self(blP, resultSize);
			};

			template<unsigned int VDimensions>
			std::ostream& operator<<(std::ostream& os, const Volume<VDimensions>& volume)
			{
				os << "Dimension: " << volume.getVolumeDimension() << std::endl;
				os << "Origin: " << volume.getOrigin() << std::endl;
				os << "Size: " << volume.getSize() << std::endl;;
				return os;
			}

			template<unsigned int VDimensions>
			Volume<VDimensions> convertToVolume(const PMVolume& pmVolume)
			{
				assert(pmVolume.getVolumeDimension() ==
					   VDimensions); //PMVolume must have the same dimension to be convertible
				typedef Volume<VDimensions> VolumeType;
				typename VolumeType::OriginType origin;
				typename VolumeType::SizeType size;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					origin[i] = pmVolume.getOrigin()[i];
					size[i] = pmVolume.getSize()[i];
				}

				return VolumeType(origin, size);
			};

			template<unsigned int VDimensions>
			PMVolume convertToPMVolume(const Volume<VDimensions>& volume)
			{
				typedef Volume<VDimensions> VolumeType;
				PMVolume::OriginType origin;
				PMVolume::SizeType size;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					origin[i] = volume.getOrigin(i);
					size[i] = volume.getSize(i);
				}

				return PMVolume(origin, size);
			};

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#endif
