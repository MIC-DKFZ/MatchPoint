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




#ifndef __FIXED_IMAGE_TO_IMAGE_METRIC_POLICY_H
#define __FIXED_IMAGE_TO_IMAGE_METRIC_POLICY_H

#include "mapSealedImageToImageMetricPolicy.h"
#include "mapITKImageToImageMetricGetterInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class FixedImageToImageMetricPolicy
			    @brief class for FixedImageToImageMetricPolicy.

			    This class is a FixedImageToImageMetricPolicy. It is used if an ITKImageRegistrationAlgorithm
			    should have one specific metric type and it is never to be changed.
			    @sa SealedImageToImageMetricPolicy
			    @sa ArbitraryImageToImageMetricPolicy
			    @ingroup ITKPolicies
			 */

			template<class TConcreteMetric>
			class FixedImageToImageMetricPolicy : public SealedImageToImageMetricPolicy<TConcreteMetric>,
				public facet::ITKImageToImageMetricGetterInterface < typename TConcreteMetric::MovingImageType,
				typename TConcreteMetric::FixedImageType >
			{
			public:
				typedef FixedImageToImageMetricPolicy<TConcreteMetric>     Self;
				typedef SealedImageToImageMetricPolicy<TConcreteMetric>    Superclass;

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

				FixedImageToImageMetricPolicy();
				~FixedImageToImageMetricPolicy();

			private:

				//No copy constructor allowed
				FixedImageToImageMetricPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#ifdef MAP_SEAL_ALGORITHMS
#define SealedFixedImageToImageMetricPolicyMacro ::map::algorithm::itk::SealedImageToImageMetricPolicy
#else
#define SealedFixedImageToImageMetricPolicyMacro ::map::algorithm::itk::FixedImageToImageMetricPolicy
#endif

#ifndef MatchPoint_MANUAL_TPP
#include "mapFixedImageToImageMetricPolicy.tpp"
#endif

#endif
