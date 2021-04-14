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




#ifndef __ARBITRARY_POINT_SET_TO_POINT_SET_METRIC_POLICY_H
#define __ARBITRARY_POINT_SET_TO_POINT_SET_METRIC_POLICY_H

#include "mapITKPointSetToPointSetMetricSetterInterface.h"
#include "mapITKPointSetToPointSetMetricGetterInterface.h"
#include "mapITKPointSetToPointSetMetricControlInterface.h"
#include "mapModificationTimeValidator.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ArbitraryPointSetToPointSetMetricPolicy
			@brief class for ArbitraryPointSetToPointSetMetricPolicy.

			This class is a ArbitraryPointSetToPointSetMetricPolicy. It is used if an ITKPointSetRegistrationAlgorithm
			should use an arbitrary metric that is to be set by the user (in contrary to FixedPointSetToPointSetMetricPolicy).
			@sa FixedPointSetToPointSetMetricPolicy
			@ingroup ITKPolicies
			*/

			template<class TMovingPointSet, class TTargetPointSet>
			class ArbitraryPointSetToPointSetMetricPolicy : public
				facet::ITKPointSetToPointSetMetricSetterInterface<TMovingPointSet, TTargetPointSet>,
			public facet::ITKPointSetToPointSetMetricGetterInterface<TMovingPointSet, TTargetPointSet>
			{
			public:
				typedef ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>      Self;
				typedef facet::ITKPointSetToPointSetMetricSetterInterface<TMovingPointSet, TTargetPointSet>
				Superclass;
                itkTypeMacroNoParent(ArbitraryPointSetToPointSetMetricPolicy);

				typedef ITKPointSetToPointSetMetricControlInterface<TMovingPointSet, TTargetPointSet>
				MetricControlType;

				/*! gets the metric controll
				@eguarantee strong
				@param pMetric the metric instance
				*/
				virtual const MetricControlType* getMetricControl() const;
				virtual MetricControlType* getMetricControl();

				/*! sets the metric
				@eguarantee strong
				@param pMetric the metric instance
				*/
				virtual void setMetricControl(MetricControlType* pMetric);

				/*! Returns the modification time of the policy (and its controlled component).
				 * In this case the modification time is a pass through of the internal component.
				@eguarantee strong
				@return the modification time
				*/
				virtual ::itk::ModifiedTimeType GetMTime() const;

			protected:
				ArbitraryPointSetToPointSetMetricPolicy();
				~ArbitraryPointSetToPointSetMetricPolicy();

				/*! This is a command slot that can be used by any class derivering from this policy
				 * to get informed if the component instances is changed. \n
				 * Two events will be invoked with this command: \n
				 * - UnregisterAlgorithmComponentEvent
				 * - RegisterAlgorithmComponentEvent
				 * .
				 * The first one is used when the current metric is going to be replaced (by setMetricControl). The event data in this case
				 * is a void pointer to the current (soon outdated) object. The second event will be called when the new metric was set
				 * (by setMetricControl). In this case the event data is a pointer to the new metric.*/
				::itk::Command::Pointer _spOnChange;

				/*! gets the internal metric
				  @eguarantee strong
				  @return a pointer to a metric type
				*/
				virtual MetricControlType* getMetricInternal();
				virtual const MetricControlType* getMetricInternal() const;

				/*! initializes the metric
				  @eguarantee strong
				*/
				void prepareMetric();

				/*! initializes the metric
				 * after it was integrated in a controlling structur (e.g. registration algorithm)
				@eguarantee strong
				*/
				void prepareMetricAfterAssembly();

			private:
				typename MetricControlType::Pointer _spMetric;

				/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
				 * because the controlled object has changed.*/
				mutable core::ModificationTimeValidator _mTime;

				//No copy constructor allowed
				ArbitraryPointSetToPointSetMetricPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapArbitraryPointSetToPointSetMetricPolicy.tpp"
#endif

#endif
