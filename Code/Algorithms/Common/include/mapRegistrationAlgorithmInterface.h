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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapRegistrationAlgorithmInterface.h $
*/




#ifndef __REGISTRATION_ALGORITHM_INTERFACE_H
#define __REGISTRATION_ALGORITHM_INTERFACE_H

#include "mapRegistration.h"
#include "mapFieldRepresentationDescriptor.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class RegistrationAlgorithmInterface
			    @brief Basic interface for registration algorithms.
			    It has input and output dimensions.
			    @ingroup AlgorithmFacets
			 */
			template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
			class RegistrationAlgorithmInterface
			{
			public:
				typedef RegistrationAlgorithmInterface<VMovingDimensions, VTargetDimensions> Self;

				/** Dimension of the algorithm */
				itkStaticConstMacro(MovingDimensions, unsigned int, VMovingDimensions);
				itkStaticConstMacro(TargetDimensions, unsigned int, VTargetDimensions);

				typedef ::map::core::Registration<VMovingDimensions, VTargetDimensions>  RegistrationType;
				typedef typename RegistrationType::Pointer                             RegistrationPointer;
				typedef typename RegistrationType::ConstPointer                        ConstRegistrationPointer;

				/*! Checks if the registration is uptodate. If not the registration becomes (re)computed
				 * the valid registration will be returned.
				  @eguarantee strong
				  @return Smart pointer to the registration instance. May be null if no registration could be
				  computed (determineRegistration returned false).
				  @retval an ITK smart pointer on a specific RegistrationType object
				 */
				virtual RegistrationPointer getRegistration() = 0;

				typedef core::FieldRepresentationDescriptor<VMovingDimensions> MovingRepresentationDescriptorType;
				typedef core::FieldRepresentationDescriptor<VTargetDimensions> TargetRepresentationDescriptorType;


				/*! @brief Defines the state the algorithm is in
				*/
				struct FieldRepRequirement
				{
					enum Type
					{
					    No = 0     /*!< the field representation is not required by the algorithm. */,
					    Unkown = 1 /*!< it is not known or can not be determined if a field representation is required. Should, if not sure, be treated like "Yes".*/,
					    Yes = 2    /*!< the field representation is required by the algorithm. */,
					};
				};

				virtual const MovingRepresentationDescriptorType *getMovingRepresentation() const = 0;
				virtual void setMovingRepresentation(const MovingRepresentationDescriptorType *pDescriptor) = 0;

				/*! The field representation indicates the support region in the moving space
				    required by the algorithm user. In addition some algorithm need this information
				    to determine valid registrations (e.g. if a field kernel must be generated for point registrations.)
				    This method allows to deduce if the algorithm needs the representation for the moving space to be defined by the user.*/
				virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const = 0;

				virtual const TargetRepresentationDescriptorType *getTargetRepresentation() const = 0;
				virtual void setTargetRepresentation(const TargetRepresentationDescriptorType *pDescriptor) = 0;

				/*! The field representation indicates the support region in the moving space
				    required by the algorithm user. In addition some algorithm need this information
				    to determine valid registrations (e.g. if a field kernel must be generated for point registrations.)
				    This method allows to deduce if the algorithm needs the representation for the target space to be defined by the user.*/
				virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const = 0;

				///*! @brief Returns if the algorithm is supports the probeAlgorithmResult()
				//* method.
				//@eguarantee strong
				//@retval true if the algorithm allows to probe the nature of the registration result.
				//@retval false if the algorithm does not support the probing of the nature of the registration result.
				//*/
				//virtual bool isAbleToProbeAlgorithmResult() const = 0;

				///*! @brief Returns a representative result (in terms of used type and configuration).
				//* This method returns an instance of a registration object, whose configuration and used kernel types
				//* are representative with the result that will be produced by the registration algorithm if
				//* you call getRegistration().
				//* @remark The result of this method is not supposed to be used for any (!) mapping and it does not guarantee
				//* sensible results. Its purpose is to offer the possibility to depict the nature of the produced results
				//* before the determination process is started. E.g. for the usage in host application that
				//* change there GUI according to the type of result (matrix or vector field).
				//@eguarantee strong
				//@return Pointer to an instance that is representative for the type of result the algorithms produces. It may be null, if the algorithm
				//* does not support this method.
				//*/
				//virtual RegistrationPointer probeAlgorithmResult() const = 0;

			protected:

				RegistrationAlgorithmInterface() {};
				virtual ~RegistrationAlgorithmInterface() {};

			private:
				RegistrationAlgorithmInterface(const Self &source);  //purposely not implemented
				void operator=(const Self &); //purposely not implemented

			};

		}
	}
}

#endif
