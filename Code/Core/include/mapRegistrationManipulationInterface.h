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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapRegistrationManipulationInterface.h $
*/

#ifndef __REGISTRATION_MANIPULATION_INTERFACE_H
#define __REGISTRATION_MANIPULATION_INTERFACE_H

#include "mapFieldRepresentationDescriptor.h"
#include "mapRegistrationKernelBase.h"
#include "mapRegistrationBase.h"

namespace map
{
	namespace core
	{

		//forward decleration
		class RegistrationBaseManipulator;

		/*! @class RegistrationManipulationInterface
		@brief Interface for the manipulation of a registration

		This class is the interface allowing for the manipulation of a registration base.
		*/
		class RegistrationBaseManipulationInterface
		{
		public:
			friend class RegistrationBaseManipulator;

			typedef RegistrationBaseManipulationInterface Self;

		protected:
			RegistrationBaseManipulationInterface() {};
			virtual ~RegistrationBaseManipulationInterface() {};

			typedef RegistrationBase::TagMapType TagMapType;

			/*! @brief sets the tags of a registration
			@eguarantee strong
			*/
			virtual void setTagValues(const TagMapType &tags) = 0;

			/*! @brief allows non const access to the registration tags.
			@eguarantee no fail
			*/
			virtual TagMapType &getTagValues() = 0;

		private:
			//No copy constructor allowed
			RegistrationBaseManipulationInterface(const Self &source);
			void operator=(const Self &); //purposely not implemented

		};

		//forward decleration
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		class RegistrationManipulator;

		/*! @class RegistrationManipulationInterface
		@brief Interface for the manipulation of a registration

		This class is the interface allowing for the manipulation of a registration.
		*/
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		class RegistrationManipulationInterface: public RegistrationBaseManipulationInterface
		{
		public:
			friend class RegistrationManipulator<VMovingDimensions, VTargetDimensions>;

			typedef RegistrationManipulationInterface Self;

		protected:
			RegistrationManipulationInterface() {};
			virtual ~RegistrationManipulationInterface() {};

			typedef RegistrationKernelBase<VMovingDimensions, VTargetDimensions> DirectMappingType;
			typedef RegistrationKernelBase<VTargetDimensions, VMovingDimensions> InverseMappingType;

			typedef typename DirectMappingType::RepresentationDescriptorType  DirectFieldRepresentationType;
			typedef typename InverseMappingType::RepresentationDescriptorType InverseFieldRepresentationType;

			/*! sets the DirectMapping kernel
			@param pKernel the kernel for direct mapping
			@eguarantee no fail
			*/
			virtual void setDirectMapping(DirectMappingType *pKernel) = 0;

			/*! sets the InverseMapping kernel
			@param pKernel the kernel for inverse mapping
			@eguarantee no fail
			*/
			virtual void setInverseMapping(InverseMappingType *pKernel) = 0;

		private:
			//No copy constructor allowed
			RegistrationManipulationInterface(const Self &source);
			void operator=(const Self &); //purposely not implemented

		};

	}
}

#endif
