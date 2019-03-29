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




#ifndef __INTERIM_REGISTRATION_RESULT_ACCESS_INTERFACE_H
#define __INTERIM_REGISTRATION_RESULT_ACCESS_INTERFACE_H

#include "mapFieldRepresentationDescriptor.h"
#include "mapRegistration.h"
#include "mapOptimizerControlInterface.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class InterimRegistrationResultAccessInterface
			@brief This is the interface that allows to access the interim results of an registration algorithm
			@ingroup AlgorithmFacets
			*/
			template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
			class InterimRegistrationResultAccessInterface
			{
			public:

				typedef InterimRegistrationResultAccessInterface<VMovingDimensions, VTargetDimensions> Self;

				typedef core::Registration<VMovingDimensions, VTargetDimensions> InterimRegistrationType;
				using InterimRegistrationPointer = typename InterimRegistrationType::Pointer;

				using MovingRepresentationDescriptorType = core::FieldRepresentationDescriptor<VMovingDimensions>;
				using TargetRepresentationDescriptorType = core::FieldRepresentationDescriptor<VTargetDimensions>;

				using OptimizerMeasureType = OptimizerControlInterface::OptimizerMeasureType;

				/*! @brief gets the registration result that has been computed in the last iteration.
				This interim registration may have other representation descriptors, passed as function
				arguments. Calls determineInterimRegistration to generate the registration.
				@param [in] pMovingRepresentation Pointer to the interim moving space representation descriptor.
				If pointer is NULL the default descriptor of the algorithm will be used.
				@param [in] pTargetRepresentation Pointer to the interim target space representation descriptor.
				If pointer is NULL the default descriptor of the algorithm will be used.
				@eguarantee strong
				@return the interim registration result as smart pointer. If the algorithm is not able to determine
				an interim registration, the smart pointer will point to NULL.
				@retval a Registration object
				@sa Registration
				*/
				virtual InterimRegistrationPointer getInterimRegistration(const MovingRepresentationDescriptorType*
						pMovingRepresentation = NULL,
						const TargetRepresentationDescriptorType* pTargetRepresentation = NULL) const = 0;


				/*! This function indicates of the optimizer of the iterative registration algorithm is
				* able to return its current metric/optimizer value(s)?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its curent value.
				*/
				virtual bool hasCurrentOptimizerValue() const = 0;

				/*! @brief gets the current value/cost of the optimizer iteration of the registration algorithm
				@eguarantee strong
				@return returns the optimizers current value/cost
				*/
				virtual OptimizerMeasureType getCurrentOptimizerValue() const = 0;

			protected:
				InterimRegistrationResultAccessInterface() {};
				virtual ~InterimRegistrationResultAccessInterface() {};

			private:
				//No copy constructor allowed
				InterimRegistrationResultAccessInterface(const Self& source); //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};
		}  // namespace facet
	}  // namespace algorithm
}  // namespace map

#endif
