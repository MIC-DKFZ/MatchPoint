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

#ifndef __DEFAULT_REGISTRATION_TOPOLOGY_POLICY_H
#define __DEFAULT_REGISTRATION_TOPOLOGY_POLICY_H

#include "mapRegistrationTopology.h"
#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace core
	{

		/*! @class DefaultRegistrationTopologyPolicy
		This is a Policy that defines the type of registration fields images and their pixels.
		It can be used to exchange the vector field style that represents a registration in
		a discrete way.
		*/
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		struct DefaultRegistrationTopologyPolicy
		{
		public:
			typedef DefaultRegistrationTopologyPolicy<VMovingDimensions, VTargetDimensions> Self;
			typedef RegistrationTopology<VMovingDimensions, VTargetDimensions> RegistrationTopologyType;

			//direct mapping
			itkStaticConstMacro(DirectInputDimensions, unsigned int, VMovingDimensions);
			itkStaticConstMacro(DirectOutputDimensions, unsigned int, VTargetDimensions);

			using DirectMappingVectorType = typename RegistrationTopologyType::DirectMappingVectorType;
			using DirectFieldType = typename RegistrationTopologyType::DirectFieldType;
			using DirectFieldPointer = typename RegistrationTopologyType::DirectFieldPointer;
			using DirectFieldRegionType = typename RegistrationTopologyType::DirectFieldRegionType;

			//inverse mapping
			itkStaticConstMacro(InverseInputDimensions, unsigned int, VTargetDimensions);
			itkStaticConstMacro(InverseOutputDimensions, unsigned int, VMovingDimensions);

			using InverseMappingVectorType = typename RegistrationTopologyType::InverseMappingVectorType;
			using InverseFieldType = typename RegistrationTopologyType::InverseFieldType;
			using InverseFieldPointer = typename RegistrationTopologyType::InverseFieldPointer;
			using InverseFieldRegionType = typename RegistrationTopologyType::InverseFieldRegionType;

			typedef RegistrationKernelBase<DirectInputDimensions, DirectOutputDimensions> DirectMappingType;
			typedef RegistrationKernelBase<InverseInputDimensions, InverseOutputDimensions> InverseMappingType;

      //general
      using MovingPointType = typename RegistrationTopologyType::MovingPointType;
      using TargetPointType = typename RegistrationTopologyType::TargetPointType;
		};

	}  // namespace core
}  // namespace map

#endif
