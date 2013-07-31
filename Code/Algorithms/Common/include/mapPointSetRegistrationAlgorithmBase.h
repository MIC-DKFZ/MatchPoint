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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapPointSetRegistrationAlgorithmBase.h $
*/




#ifndef __POINT_SET_REGISTRATION_ALGORITHM_BASE_H
#define __POINT_SET_REGISTRATION_ALGORITHM_BASE_H

#include "mapModificationTimeValidator.h"
#include "itkIndent.h"

#include "mapPointSetRegistrationAlgorithmInterface.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{

		/*! @class PointSetRegistrationAlgorithmBase
		@brief This is the default implementation of the interface for point set based registration algorithms

		@ingroup AlgorithmFacets
		@template TMovingPointSet Type of the moving point set
		@template TTargetPointSet Type of the target point set
		*/
		template<class TMovingPointSet, class TTargetPointSet>
		class PointSetRegistrationAlgorithmBase : public facet::PointSetRegistrationAlgorithmInterface<TMovingPointSet, TTargetPointSet>

		{
		public:
			typedef PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet> Self;

			typedef TMovingPointSet MovingPointSetType;
			typedef TTargetPointSet TargetPointSetType;

			typedef typename MovingPointSetType::ConstPointer MovingPointSetConstPointer;
			typedef typename TargetPointSetType::ConstPointer TargetPointSetConstPointer;

			/*! @brief gets a const pointer to the moving point set
			@eguarantee strong
			@return a const pointer to the moving point set
			*/
			virtual MovingPointSetConstPointer getMovingPointSet() const;

			/*! @brief gets a const pointer to the target point set
			@eguarantee strong
			@return a const pointer to the target point set
			*/
			virtual TargetPointSetConstPointer getTargetPointSet() const;

			/*! @brief sets the moving point set
			@eguarantee strong
			@param pMovingPointSet a pointer to the moving point set
			*/
			virtual void setMovingPointSet(const MovingPointSetType *pMovingPointSet);

			/*! @brief sets the target point set
			@eguarantee strong
			@param pTargetPointSet a pointer to the moving point set
			*/
			virtual void setTargetPointSet(const TargetPointSetType *pTargetPointSet);

			/*! returns the modification time of the target point set.
			*/
			virtual unsigned long getTargetPointSetMTime() const;

			/*! returns the modification time of the moving point set.
			*/
			virtual unsigned long getMovingPointSetMTime() const;

		protected:
			/*! @brief virtual destructor
			*/
			virtual ~PointSetRegistrationAlgorithmBase();

			PointSetRegistrationAlgorithmBase();

			/*! Methods invoked by derivated classes.  */
			virtual void PrintSelf(std::ostream &os, ::itk::Indent indent) const;

		private:

			core::ModificationTimeValidator _targetPSMTime;
			core::ModificationTimeValidator _movingPSMTime;

			MovingPointSetConstPointer _spMovingPointSet;

			TargetPointSetConstPointer _spTargetPointSet;

			//No copy constructor allowed
			PointSetRegistrationAlgorithmBase(const Self &source);
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapPointSetRegistrationAlgorithmBase.tpp"
#endif


#endif
