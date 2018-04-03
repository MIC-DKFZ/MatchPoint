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

#ifndef __REGISTRATION_TPP
#define __REGISTRATION_TPP

#include "mapRegistration.h"

namespace map
{
	namespace core
	{
		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		bool
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		mapPoint(const MovingPointType& inPoint, TargetPointType& outPoint) const
		{
			assert(_spDirectMapping.IsNotNull());
			return _spDirectMapping->mapPoint(inPoint, outPoint);
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		bool
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		mapPointInverse(const TargetPointType& inPoint, MovingPointType& outPoint) const
		{
			assert(_spInverseMapping.IsNotNull());
			return _spInverseMapping->mapPoint(inPoint, outPoint);
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		const typename
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::InverseMappingType&

		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		getInverseMapping() const
		{
			assert(_spInverseMapping.IsNotNull());
			return *(_spInverseMapping.GetPointer());
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		const typename
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::DirectMappingType&
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		getDirectMapping() const
		{
			assert(_spDirectMapping.IsNotNull());
			return *(_spDirectMapping.GetPointer());
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		typename Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::DirectFieldRepresentationConstPointer
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		getDirectFieldRepresentation() const
		{
			assert(_spDirectMapping.IsNotNull());
			return _spDirectMapping->getLargestPossibleRepresentation();
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		typename Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::InverseFieldRepresentationConstPointer
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		getInverseFieldRepresentation() const
		{
			assert(_spInverseMapping.IsNotNull());
			return _spInverseMapping->getLargestPossibleRepresentation();
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		void
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		precomputeDirectMapping()
		{
			assert(_spDirectMapping.IsNotNull());
			return _spDirectMapping->precomputeKernel();
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		void
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		precomputeInverseMapping()
		{
			assert(_spInverseMapping.IsNotNull());
			return _spInverseMapping->precomputeKernel();
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		Registration()
		{
			_spDirectMapping = NULL;
			_spInverseMapping = NULL;
		}


		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		~Registration()
		{
		}

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		void
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		setDirectMapping(DirectMappingType* pKernel)
		{
			_spDirectMapping = pKernel;
			this->Modified();
		};

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		void
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		setInverseMapping(InverseMappingType* pKernel)
		{
			_spInverseMapping = pKernel;
			this->Modified();
		};

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		unsigned int
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		getMovingDimensions() const
		{
			return VMovingDimensions;
		};

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		unsigned int
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		getTargetDimensions() const
		{
			return VTargetDimensions;
		};

		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		bool
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		hasLimitedTargetRepresentation() const
		{
			assert(_spInverseMapping.IsNotNull());
			return _spInverseMapping->hasLimitedRepresentation();
		}


		template < unsigned int VMovingDimensions, unsigned int VTargetDimensions,
				 template <unsigned int, unsigned int> class TRegistrationTopologyPolicy >
		bool
		Registration<VMovingDimensions, VTargetDimensions, TRegistrationTopologyPolicy>::
		hasLimitedMovingRepresentation() const
		{
			assert(_spDirectMapping.IsNotNull());
			return _spDirectMapping->hasLimitedRepresentation();
		}

	} // end namespace core
} // end namespace map

#endif
