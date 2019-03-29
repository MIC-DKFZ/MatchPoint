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


#include "mapPMVolume.h"
#include <cassert>
#include <algorithm>
#include <utility>

namespace map
{
	namespace core
	{
		namespace continuous
		{
			unsigned int
			PMVolume::
			getVolumeDimension()  const
			{
				//origin and _size must always have the same size.
				return _size.size();
			};

			PMVolume::
			PMVolume()
			= default;

			PMVolume::
			~PMVolume()
			= default;

			PMVolume::
			PMVolume(const Self& volume)
			{
				_size = volume._size;
				_origin = volume._origin;
			};

			PMVolume::
			PMVolume(const OriginType& origin, const SizeType& size): _origin(origin), _size(size)
			{
				assert(origin.size() == size.size());
			};

			PMVolume::
			PMVolume(SizeType  size): _size(std::move(size))
			{
				_origin.resize(_size.size(), 0.0);
			};

			void
			PMVolume::
			operator=(const Self& volume)
			{
				if (this != &volume)
				{
					_origin = volume._origin;
					_size = volume._size;
				}
			};

			bool
			PMVolume::
			operator==(const Self& volume) const
			{
				bool result = true;

				if (_size.size() != volume._size.size())
				{
					result = false;
				}

				if (_origin.size() != volume._origin.size())
				{
					result = false;
				}

				if (result)
				{
					result = std::equal(_size.begin(), _size.end(), volume._size.begin());
				}

				if (result)
				{
					result = std::equal(_origin.begin(), _origin.end(), volume._origin.begin());
				}

				return result;
			};

			void
			PMVolume::
			setOrigin(const OriginType& origin)
			{
				_origin = origin;
			};

			const PMVolume::OriginType&
			PMVolume::
			getOrigin() const
			{
				return _origin;
			};

			void
			PMVolume::
			setSize(const SizeType& size)
			{
				_size = size;
			};

			const PMVolume::SizeType&
			PMVolume::
			getSize() const
			{
				return _size;
			};

			void
			PMVolume::
			setSize(unsigned long i, SizeValueType sze)
			{
				assert(i < _size.size());
				_size[i] = sze;
			};

			PMVolume::SizeValueType
			PMVolume::
			getSize(unsigned long i) const
			{
				assert(i < _size.size());
				return _size[i];
			};

			void
			PMVolume::
			setOrigin(unsigned long i, OriginValueType sze)
			{
				assert(i < _origin.size());
				_origin[i] = sze;
			};

			PMVolume::OriginValueType
			PMVolume::
			getOrigin(unsigned long i) const
			{
				assert(i < _origin.size());
				return _origin[i];
			};

			std::ostream& operator<<(std::ostream& os, const PMVolume& volume)
			{
				os << "PMVolume[origin[";

				PMVolume::OriginType origin = volume.getOrigin();

				for (PMVolume::OriginType::const_iterator pos = origin.begin(); pos != origin.end(); ++pos)
				{
					os << *pos;

					if (pos + 1 != origin.end())
					{
						os << ";";
					}
				};

				os << "] size[";

				PMVolume::SizeType size = volume.getSize();

				for (PMVolume::SizeType::const_iterator pos = size.begin(); pos != size.end(); ++pos)
				{
					os << *pos;

					if (pos + 1 != size.end())
					{
						os << ";";
					}
				};

				os << "]]";

				return os;
			};

		} // end namespace continuous
	} // end namespace core
} // end namespace map