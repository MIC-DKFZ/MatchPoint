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




#ifndef __SEALED_INTERPOLATOR_POLICY_H
#define __SEALED_INTERPOLATOR_POLICY_H

#include "itkInterpolateImageFunction.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class SealedInterpolatorPolicy
			@brief class for SealedInterpolatorPolicy.

			This class is a SealedInterpolatorPolicy. It is used if an ITKImageRegistrationAlgorithm
			should have one specific interpolator type. With this policy the metric is never to be changed and sealed, so
			that the instance and its setting aren't public.
			@sa FixedInterpolatorPolicy
			@sa ArbitraryInterpolatorPolicy
			@ingroup ITKPolicies
			*/

			template<class TConcreteInterpolator>
			class SealedInterpolatorPolicy
			{
			public:
				using Self = SealedInterpolatorPolicy<TConcreteInterpolator>;

				using ConcreteInterpolatorType = TConcreteInterpolator;
				using ConcreteInterpolatorPointer = typename ConcreteInterpolatorType::Pointer;
				typedef ::itk::InterpolateImageFunction<typename ConcreteInterpolatorType::InputImageType, typename ConcreteInterpolatorType::CoordRepType>
				InterpolatorType;
				using CoordRepType = typename ConcreteInterpolatorType::CoordRepType;

			protected:
				SealedInterpolatorPolicy();
				~SealedInterpolatorPolicy();

				/*! Returns the modification time of the policy (and its controlled component).
				 * In this case the modification time is a pass through of the internal component.
				@eguarantee strong
				@return the modification time
				*/
				virtual unsigned long GetMTime() const;

				/*! This method can be used to indicate modification of the policy (calls _mTime.Modify()).
				*/
				void indicateModification() const;

				/*! This is a command slot that can be used by any class derivering from this policy
				 * to get informed if the component instances is changed.
				 * @remark In the case of fixed policy (they don't allow the change of the instance, like this policy)
				 * the command will invoke no event. The command is present because it is part of a general policy API that
				 * allows policy using classes to interact in the same way with fixed and arbitrary policies.
				 */
				::itk::Command::Pointer _spOnChange;

				/*! gets the internal interpolator
				@eguarantee strong
				@return a pointer to an interpolator type
				*/
				InterpolatorType* getInterpolatorInternal();
				const InterpolatorType* getInterpolatorInternal() const;

				/*! gets the concrete interpolator
				@eguarantee strong
				@return a pointer to a ConcreteInterpolatorType object
				*/
				const ConcreteInterpolatorType* getConcreteInterpolator() const;

				/*! gets the concrete interpolator
				 * @eguarantee strong
				 * @return a pointer to a ConcreteInterpolatorType object
				*/
				ConcreteInterpolatorType* getConcreteInterpolator();

				/*! initializes the interpolator
				@eguarantee strong
				*/
				virtual void prepareInterpolator();

				/*! initializes the interpolator
				* after it was integrated in a controlling structur (e.g. registration algorithm)
				@eguarantee strong
				*/
				virtual void prepareInterpolatorAfterAssembly();

			private:
				/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
				* because the initialization is going to change the intern object (e.g. prepareMetric() will change the settings of the metric)*/
				mutable ::itk::TimeStamp _mTime;

				ConcreteInterpolatorPointer _spInterpolator;

				//No copy constructor allowed
				SealedInterpolatorPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};



		}  // namespace itk
	}  // namespace algorithm
}  // namespace map


#ifndef MatchPoint_MANUAL_TPP
#include "mapSealedInterpolatorPolicy.tpp"
#endif

#endif
