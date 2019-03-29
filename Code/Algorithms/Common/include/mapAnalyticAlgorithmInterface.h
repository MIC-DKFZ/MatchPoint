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




#ifndef __ANALYTIC_ALGORITHM_INTERFACE_H
#define __ANALYTIC_ALGORITHM_INTERFACE_H

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class AnalyticAlgorithmInterface
			@brief This is the interface for analytic algorithms (not iterative)
			@ingroup AlgorithmFacets
			*/
			class AnalyticAlgorithmInterface
			{
			public:
				using Self = AnalyticAlgorithmInterface;



			protected:
				AnalyticAlgorithmInterface() = default;
				virtual ~AnalyticAlgorithmInterface() = default;

			private:
				//No copy constructor allowed
				AnalyticAlgorithmInterface(const Self& source) = delete;
				void operator=(const Self&) = delete;  //purposely not implemented

			};
		}  // namespace facet
	}  // namespace algorithm
}  // namespace map

#endif
