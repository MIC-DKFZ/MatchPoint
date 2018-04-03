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




#ifndef __SEALED_IMAGE_TO_IMAGE_METRIC_POLICY_H
#define __SEALED_IMAGE_TO_IMAGE_METRIC_POLICY_H

#include "mapITKMetricControl.h"
#include "mapITKImageToImageMetricControlInterface.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class SealedImageToImageMetricPolicy
			    @brief class for SealedImageToImageMetricPolicy.

			    This class is a SealedImageToImageMetricPolicy. It is used if an ITKImageRegistrationAlgorithm
			    should have one specific metric type. With this policy the interpolator is never to be changed and sealed, so
			    that the instance and its setting aren't public.
			    @sa FixedImageToImageMetricPolicy
			    @sa ArbitraryImageToImageMetricPolicy
			    @ingroup ITKPolicies
			 */

			template<class TConcreteMetric>
			class SealedImageToImageMetricPolicy
			{
			public:
				typedef SealedImageToImageMetricPolicy<TConcreteMetric>      Self;

				typedef TConcreteMetric ConcreteMetricType;
				typedef ITKMetricControl<ConcreteMetricType> ConcreteMetricControlType;
				typedef typename ConcreteMetricControlType::Pointer ConcreteMetricControlPointer;
				typedef ITKImageToImageMetricControlInterface<typename ConcreteMetricType::MovingImageType, typename ConcreteMetricType::FixedImageType>
				MetricControlType;

			protected:
				SealedImageToImageMetricPolicy();
				~SealedImageToImageMetricPolicy();

				/*! This is a command slot that can be used by any class derivering from this policy
				 * to get informed if the component instances is changed.
				 * @remark In the case of fixed policy (they don't allow the change of the instance, like this policy)
				 * the command will invoke no event. The command is present because it is part of a general policy API that
				 * allows policy using classes to interact in the same way with fixed and arbitrary policies.
				 */
				::itk::Command::Pointer _spOnChange;


				/*! gets the internal metric
				  @eguarantee strong
				  @return a pointer to a metric type
				*/
				MetricControlType* getMetricInternal();
				const MetricControlType* getMetricInternal() const;

				/*! gets the concrete interpolator
				  @eguarantee strong
				  @return a pointer to a ConcreteInterpolatorType object
				*/
				virtual const ConcreteMetricControlType* getConcreteMetricControl() const;
				/*! gets the concrete metric
				 * @eguarantee strong
				 * @return a pointer to a ConcreteMetricControlType object
				*/
				virtual ConcreteMetricControlType* getConcreteMetricControl();

				/*! initializes the metric
				  @eguarantee strong
				*/
				virtual void prepareMetric();

				/*! initializes the metric
				 * after it was integrated in a controlling structur (e.g. registration algorithm)
				@eguarantee strong
				*/
				virtual void prepareMetricAfterAssembly();

				/*! Returns the modification time of the policy (and its controlled component).
				 * In this case the modification time is a pass through of the internal component.
				@eguarantee strong
				@return the modification time
				*/
				virtual unsigned long GetMTime() const;

				/*! This method can be used to indicate modification of the policy.
				*/
				void indicateModification() const;

			private:
				ConcreteMetricControlPointer _spMetric;

				/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
				 * because the initialization is going to change the intern object (e.g. prepareMetric() will change the settings of the metric)*/
				mutable ::itk::TimeStamp _mTime;

				//No copy constructor allowed
				SealedImageToImageMetricPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}


#ifndef MatchPoint_MANUAL_TPP
#include "mapSealedImageToImageMetricPolicy.tpp"
#endif

#endif
