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




#ifndef __POINT_SET_REGISTRATION_ALGORITHM_INTERFACE_H
#define __POINT_SET_REGISTRATION_ALGORITHM_INTERFACE_H

#include "mapModificationTimeValidator.h"
#include "itkIndent.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class PointSetRegistrationAlgorithmInterface
			@brief This is the interface for point set based registration algorithms

			@ingroup AlgorithmFacets
			@template TMovingPointSet Type of the moving point set
			@template TTargetPointSet Type of the target point set
			*/
			template<class TMovingPointSet, class TTargetPointSet>
			class PointSetRegistrationAlgorithmInterface
			{
			public:
				typedef PointSetRegistrationAlgorithmInterface<TMovingPointSet, TTargetPointSet> Self;

				using MovingPointSetType = TMovingPointSet;
				using TargetPointSetType = TTargetPointSet;

				using MovingPointSetConstPointer = typename MovingPointSetType::ConstPointer;
				using TargetPointSetConstPointer = typename TargetPointSetType::ConstPointer;

				/*! @brief gets a const pointer to the moving point set
				@eguarantee strong
				@return a const pointer to the moving point set
				*/
				virtual MovingPointSetConstPointer getMovingPointSet() const = 0;

				/*! @brief gets a const pointer to the target point set
				@eguarantee strong
				@return a const pointer to the target point set
				*/
				virtual TargetPointSetConstPointer getTargetPointSet() const = 0;

				/*! @brief sets the moving point set
				@eguarantee strong
				@param pMovingPointSet a pointer to the moving point set
				*/
				virtual void setMovingPointSet(const MovingPointSetType* pMovingPointSet) = 0;

				/*! @brief sets the target point set
				@eguarantee strong
				@param pTargetPointSet a pointer to the moving point set
				*/
				virtual void setTargetPointSet(const TargetPointSetType* pTargetPointSet) = 0;

				/*! returns the modification time of the target point set.
				*/
				virtual ::itk::ModifiedTimeType getTargetPointSetMTime() const = 0;

				/*! returns the modification time of the moving point set.
				*/
				virtual ::itk::ModifiedTimeType getMovingPointSetMTime() const = 0;

			protected:
				/*! @brief virtual destructor
				*/
				virtual ~PointSetRegistrationAlgorithmInterface() {};

				PointSetRegistrationAlgorithmInterface() {};

			private:

				//No copy constructor allowed
				PointSetRegistrationAlgorithmInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}  // namespace facet
	}  // namespace algorithm
}  // namespace map

#endif
