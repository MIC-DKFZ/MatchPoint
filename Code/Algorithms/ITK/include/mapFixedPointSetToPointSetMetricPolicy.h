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




#ifndef __FIXED_POINT_SET_METRIC_POLICY_H
#define __FIXED_POINT_SET_METRIC_POLICY_H

#include "mapSealedPointSetToPointSetMetricPolicy.h"
#include "mapITKPointSetToPointSetMetricGetterInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class FixedPointSetToPointSetMetricPolicy
			    @brief class for FixedPointSetToPointSetMetricPolicy.

			    This class is a FixedPointSetToPointSetMetricPolicy. It is used if an ITKPointSetRegistrationAlgorithm
			    should have one specific metric type and it is never to be changed.
			    @sa SealedPointSetToPointSetMetricPolicy
			    @sa ArbitraryPointSetToPointSetMetricPolicy
			    @ingroup ITKPolicies
			 */

			template<class TConcreteMetric>
			class FixedPointSetToPointSetMetricPolicy : public
				SealedPointSetToPointSetMetricPolicy<TConcreteMetric>,
			public facet::ITKPointSetToPointSetMetricGetterInterface < typename
				TConcreteMetric::MovingPointSetType,
				typename TConcreteMetric::FixedPointSetType >
			{
			public:
				typedef FixedPointSetToPointSetMetricPolicy<TConcreteMetric>     Self;
				typedef SealedPointSetToPointSetMetricPolicy<TConcreteMetric>    Superclass;

				typedef typename Superclass::ConcreteMetricType             ConcreteMetricType;
				typedef typename Superclass::ConcreteMetricControlType      ConcreteMetricControlType;
				typedef typename Superclass::ConcreteMetricControlPointer   ConcreteMetricControlPointer;
				typedef typename Superclass::MetricControlType              MetricControlType;

				/*! gets the metric controll
				@eguarantee strong
				@param pMetric the metric instance
				*/
				virtual const MetricControlType* getMetricControl() const;
				virtual MetricControlType* getMetricControl();

				using Superclass::getConcreteMetricControl;

			protected:

				FixedPointSetToPointSetMetricPolicy();
				~FixedPointSetToPointSetMetricPolicy();

			private:

				//No copy constructor allowed
				FixedPointSetToPointSetMetricPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#ifdef MAP_SEAL_ALGORITHMS
#define SealedFixedPointSetToPointSetMetricPolicyMacro ::map::algorithm::itk::SealedPointSetToPointSetMetricPolicy
#else
#define SealedFixedPointSetToPointSetMetricPolicyMacro ::map::algorithm::itk::FixedPointSetToPointSetMetricPolicy
#endif

#ifndef MatchPoint_MANUAL_TPP
#include "mapFixedPointSetToPointSetMetricPolicy.tpp"
#endif

#endif
