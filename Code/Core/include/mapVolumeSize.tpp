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

#ifndef __MAP_VOLUME_SIZE_TPP
#define __MAP_VOLUME_SIZE_TPP

#include <cassert>

#include "mapVolumeSize.tpp"
#include "mapConvert.h"
#include "mapSDITKStreamingHelper.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace core
	{
		namespace continuous
		{

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::Self
			VolumeSize<VDimensions>::
			operator+(const Self& vec) const
			{
				Self result;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					result[i] = _size[i] + vec._size[i];
				}

				return result;
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::Self&
			VolumeSize<VDimensions>::
			operator+=(const Self& vec)
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
			operator-(const Self& vec) const
			{
				Self result;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					result[i] = _size[i] - vec._size[i];
				}

				return result;
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::Self&
			VolumeSize<VDimensions>::
			operator-=(const Self& vec)
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
			operator*(const Self& vec) const
			{
				Self result;

				for (unsigned int i = 0; i < VDimensions; ++i)
				{
					result[i] = _size[i] * vec._size[i];
				}

				return result;
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::Self&
			VolumeSize<VDimensions>::
			operator*=(const Self& vec)
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
			operator==(const Self& vec) const
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
			operator!=(const Self& vec) const
			{
				bool same = true;

				for (unsigned int i = 0; i < VDimensions && same; ++i)
				{
					same = (_size[i] == vec._size[i]);
				}

				return !same;
			}

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::SizeValueType&
			VolumeSize<VDimensions>::
			operator[](unsigned int dim)
			{
				assert(dim < VDimensions); //check if index dim is out of bound
				return _size[dim];
			}

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::SizeValueType
			VolumeSize<VDimensions>::
			operator[](unsigned int dim) const
			{
				assert(dim < VDimensions); //check if index dim is out of bound
				return _size[dim];
			}

			template<unsigned int VDimensions>
			const typename VolumeSize<VDimensions>::SizeValueType*
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
			::map::structuredData::StreamingInterface::ElementPointer
			VolumeSize<VDimensions>::
			streamToStructuredData(const Self& vs)
			{
				structuredData::Element::Pointer spElement = structuredData::Element::New();
				spElement->setTag("VolumeSize");

				for (unsigned int rowID = 0; rowID < VDimensions; ++rowID)
				{
					structuredData::Element::Pointer spValueElement = structuredData::Element::New();
					spValueElement->setTag(tags::Value);
					spValueElement->setValue(convert::toStr(vs._size[rowID]));
					spValueElement->setAttribute(tags::Row, convert::toStr(rowID));
					spElement->addSubElement(spValueElement);
				}

				return spElement;
			};

			template<unsigned int VDimensions>
			typename VolumeSize<VDimensions>::Self
			VolumeSize<VDimensions>::
			streamFromStructuredData(const structuredData::Element* pElement)
			{
				if (pElement == nullptr)
				{
					mapDefaultExceptionStaticMacro( <<
					                                "Error: convert structured data into VolumeSize. Reason: passed structured element point to NULL.");
				}

				if (pElement->getSubElementsCount() != VDimensions)
				{
					mapDefaultExceptionStaticMacro( <<
					                                "Error: convert structured data into VolumeSize. Reason: Wrong number of sub elements. Expected: "
					                                <<
					                                VDimensions << "; found: " << pElement->getSubElementsCount());
				}

				Self vs;

				for (auto pos = pElement->getSubElementBegin();
				     pos != pElement->getSubElementEnd(); ++pos)
				{
					unsigned int rowID = core::convert::toUInt((*pos)->getAttribute(tags::Row));

					vs._size[rowID] = core::convert::toValueGeneric<SizeValueType>((*pos)->getValue());
				}

				return vs;
			};


			template<unsigned int VDimensions>
			std::ostream& operator<<(std::ostream& os, const VolumeSize<VDimensions>& size)
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
