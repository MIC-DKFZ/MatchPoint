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




#ifndef __ITERATIVE_ALGORITHM_BASE_H
#define __ITERATIVE_ALGORITHM_BASE_H

#include "mapIterativeAlgorithmInterface.h"
#include "mapMAPAlgorithmsExports.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
	namespace algorithm
	{

		/*! @class IterativeAlgorithmBase
		    @brief This default implementation for the IterativeAlgorithmInterface
		    @ingroup Algorithms
		    @remark Algorithms that want to support iteration events and
		    implement this interface should use the AlgorithmIterationEvent
		    to indicate the beginning of the next iteration
		    @see map::events::AlgorithmIterationEvent
		 */
		class MAPAlgorithms_EXPORT IterativeAlgorithmBase : public facet::IterativeAlgorithmInterface
		{
		public:
			using Self = IterativeAlgorithmBase;

			/*! @brief gets the number of the algorithm's current iteration
			  @eguarantee strong
			  @return returns the algorithm's current iteration. If the optimizer has no iteration count (hasIterationCount()==false), return is always 0.
			  @retval an IterationCountType specifying the current iteration
			  @sa IterationCountType
			 */
			IterationCountType getCurrentIteration() const override;

			/*! @brief gets the maximum number of the algorithm's iterations
			  @eguarantee strong
			  @return returns the algorithm's maximum iterations count. If the optimizer has no iteration count (hasMaxIterationCount()==false), return is always 0.
			 */
			IterationCountType getMaxIterations() const override;

		protected:
			IterativeAlgorithmBase();
			~IterativeAlgorithmBase() override;

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

		private:

			//No copy constructor allowed
			IterativeAlgorithmBase(const Self& source) = delete; //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};

	}  // namespace algorithm
}  // namespace map

#endif
