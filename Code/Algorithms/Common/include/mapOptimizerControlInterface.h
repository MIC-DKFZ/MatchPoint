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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapOptimizerControlInterface.h $
*/




#ifndef __OPTIMIZER_CONTROL_INTERFACE_H
#define __OPTIMIZER_CONTROL_INTERFACE_H

#include <vector>

#include "itkArray.h"

#include "mapMacros.h"
#include "mapString.h"
#include "mapMAPAlgorithmsExports.h"

namespace map
{
	namespace algorithm
	{

		/*! @class OptimizerControlInterface
		@brief Interface for controller classes that form a virtual wrapper around optimizers
		that are used in iterative registration algorithms.
		This wrapper is used to offer abstract and general access to basic information and methods
		independent from the concrete optimizer implementation.
		*/
		class MAPAlgorithms_EXPORT OptimizerControlInterface
		{
		public:
			typedef OptimizerControlInterface Self;

			typedef unsigned long IterationCountType;

			typedef ::std::vector<double> OptimizerMeasureType;
			typedef ::itk::Array<double> OptimizerPositionType;
			typedef ::itk::Array<double> OptimizerScalesType;

			/*! is this optimizer stoppable?
			@eguarantee no fail
			@return stoppability as a boolean value
			*/
			virtual bool isStoppable() const = 0;

			/*! stop the optimizer
			@eguarantee strong
			@return success of operation. If optimizer cannot be stopped by the user, return is always false
			*/
			bool stop();

			/*! has the optimizer an iteration count?
			@eguarantee no fail
			@return Indicates if the optimizer can determin its current iteration count
			*/
			virtual bool hasIterationCount() const = 0;

			/*! return the current number of iterations.
			@eguarantee strong
			@return Iteration count. If the optimizer has no iteration count, return is always 0
			*/
			IterationCountType getCurrentIteration() const;

			/*! has the optimizer an maximum iteration count?
			@eguarantee no fail
			@return Indicates if the algorithm can determin its maximum iteration count
			*/
			virtual bool hasMaxIterationCount() const = 0;

			/*! @brief gets the maximum number of the optimizers's iterations
			@eguarantee strong
			@return returns the optimizers's maximum iterations count
			*/
			virtual IterationCountType getMaxIterations() const;

			/*! @brief Indicates if the optimizer is able to minimize a cost function
			@eguarantee strong
			*/
			virtual bool canMinimize() const = 0;

			/*! @brief Indicates if the optimizer is able to maximize a cost function
			@eguarantee strong
			*/
			virtual bool canMaximize() const = 0;

			/*! @brief Indicates if the optimizer is currently in minimization mode.
			@eguarantee strong
			*/
			virtual bool getMinimize() const = 0;

			/*! @brief Indicates if the optimizer is currently in maximization mode.
			@eguarantee strong
			*/
			virtual bool getMaximize() const = 0;

			/*! @brief Changes the optimizer into minimization mode. May raise exception if this isn't possible.
			To avoid the exception check with canMinimize()/canMaximize() before hand.
			@eguarantee strong
			*/
			virtual void setMinimize(bool minimize) = 0;

			/*! @brief Changes the optimizer into maximization mode. May raise exception if this isn't possible.
			To avoid the exception check with canMinimize()/canMaximize() before hand.
			@eguarantee strong
			*/
			virtual void setMaximize(bool maximize) = 0;

			/*! This function indicates of the optimizer of the iterative registration algorithm is
			* able to return its current metric/optimizer value(s)?
			@eguarantee no fail
			@return Indicates if the algorithm can determin its curent value.
			*/
			virtual bool hasCurrentValue() const = 0;

			/*! @brief gets the current value/cost of the optimizer iteration of the registration algorithm
			@eguarantee strong
			@return returns the optimizers current value/cost if optimizer cannot return current values (hasCurrentValue == false)
			an empty vector will be returned.
			*/
			OptimizerMeasureType getCurrentValue() const;

			/*! This function indicates of the optimizer of the iterative registration algorithm is
			* able to return its current optimizer position in search space.
			@eguarantee no fail
			@return Indicates if the algorithm can determin its current position.
			*/
			virtual bool hasCurrentPosition() const = 0;

			/*! @brief gets the current position of the optimizer iteration of the registration algorithm
			@eguarantee strong
			@return returns the optimizers current position if optimizer cannot return current values (hasCurrentValue == false)
			an empty vector will be returned.
			*/
			OptimizerPositionType getCurrentPosition() const;

			/*! This function indicates of the optimizer of the iterative registration algorithm uses
			* parameter scaling to normalize different dynamic ranges of its search space.
			@eguarantee no fail
			@return Indicates if the algorithm can determin its current position.
			*/
			virtual bool hasScales() const = 0;

			/*! @brief gets the scaling of the search parameters of the optimizer of the registration algorithm
			@eguarantee strong
			@return returns the scaling of parameters of optimizer. An empty array will be returned.
			*/
			OptimizerScalesType getScales() const;

			/** Get the reason for last termination of the optimizer.
			 * If the return value is an empty string the optimizer hasn't terminated yet or
			 * does not support this method to indicate the termination reason.*/
			virtual const core::String getStopConditionDescription() const = 0;

		protected:
			/*! stop the optimizer
			Will be called by stop() if isStopable() returns true.
			@eguarantee strong
			@return success of operation. If optimizer cannot be stopped by the user, return is always false
			*/
			virtual bool doStop() = 0;

			/*! return the current number of iterations.
			Will be called by getCurrentIteration() if hasIterationCount() returns true.
			@eguarantee strong
			@return Iteration count
			*/
			virtual IterationCountType doGetCurrentIteration() const = 0;

			/*! return the maximum number of iterations.
			Will be called by getMaxIterations() if hasMaxIterationCount() returns true.
			@eguarantee strong
			@return Maximum iteration count
			*/
			virtual IterationCountType doGetMaxIterations() const = 0;

			/*! Will  be called to get the current value/cost of the optimizer iteration
			@eguarantee strong
			@return returns the optimizers current value/cost
			*/
			virtual OptimizerMeasureType doGetCurrentValue() const = 0;

			/*! Will  be called to get the current position of the optimizer iteration
			@eguarantee strong
			@return returns the optimizers current position
			*/
			virtual OptimizerPositionType doGetCurrentPosition() const = 0;

			/*! Will be called to get the scales of the optimizer
			@eguarantee strong
			@return returns the scales
			*/
			virtual OptimizerScalesType doGetScales() const = 0;

			OptimizerControlInterface();
			virtual ~OptimizerControlInterface();

		private:
			//No copy constructor allowed
			OptimizerControlInterface(const Self &source);
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#endif
