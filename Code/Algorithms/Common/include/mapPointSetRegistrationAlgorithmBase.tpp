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


#ifndef __POINT_SET_REGISTRATION_ALGORITHM_INTERFACE_TPP
#define __POINT_SET_REGISTRATION_ALGORITHM_INTERFACE_TPP

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************
		template<class TMovingPointSet, class TTargetPointSet>
		typename PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::MovingPointSetConstPointer
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		getMovingPointSet() const
		{
			return _spMovingPointSet;
		}

		template<class TMovingPointSet, class TTargetPointSet>
		typename PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::TargetPointSetConstPointer
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		getTargetPointSet() const
		{
			return _spTargetPointSet;
		}


		template<class TMovingPointSet, class TTargetPointSet>
		void
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		setMovingPointSet(const MovingPointSetType* pMovingPointSet)
		{
			_spMovingPointSet = pMovingPointSet;
			this->_movingPSMTime.setWatchedObject(pMovingPointSet);
		}

		template<class TMovingPointSet, class TTargetPointSet>
		void
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		setTargetPointSet(const TargetPointSetType* pTargetPointSet)
		{
			_spTargetPointSet = pTargetPointSet;
			this->_targetPSMTime.setWatchedObject(pTargetPointSet);
		}

		template<class TMovingPointSet, class TTargetPointSet>
		unsigned long
		map::algorithm::PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::getMovingPointSetMTime()
		const
		{
			return _movingPSMTime.getMTime();
		}

		template<class TMovingPointSet, class TTargetPointSet>
		unsigned long
		map::algorithm::PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::getTargetPointSetMTime()
		const
		{
			return _targetPSMTime.getMTime();
		}

		// **** protected methods ****
		// ***************************

		template<class TMovingPointSet, class TTargetPointSet>
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		~PointSetRegistrationAlgorithmBase() {}

		template<class TMovingPointSet, class TTargetPointSet>
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		PointSetRegistrationAlgorithmBase() {}

		template<class TMovingPointSet, class TTargetPointSet>
		void
		PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			os << indent << "Moving point set: " << _spMovingPointSet.GetPointer() << std::endl;
			os << indent << "Target point set: " << _spTargetPointSet.GetPointer() << std::endl;
		}

	} // end namespace algorithms
} // end namespace map

#endif
