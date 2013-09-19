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


#ifndef __MAP_REGISTRATION_TOPOLOGY_H
#define __MAP_REGISTRATION_TOPOLOGY_H

#include "mapContinuousElements.h"
#include "mapDiscreteElements.h"


namespace map
{
	namespace core
	{

		/*! @class RegistrationTopology
		 * @brief RegistrationTopology defines the very basic data containers needed in the context of registration
		 *
		 * Type of vectors, fields, points and other data depends on the dimensions of the moving
		 * and the target space. The mapping style depends on the nature of the data: continuous
		 * (direct mapping) and discrete (inverse mapping). This is a helper class only containing typedefs
		 * that specify the correct vector fields for both mapping styles depending on the dimensions given
		 * as template parameter.
		 * @remarks This class is not ment to be constructed an is therfore abstract with no constructors of any kind.
		 * @ingroup Registration
		 */
		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		struct RegistrationTopology
		{
		public:
			//direct mapping
			itkStaticConstMacro(DirectInputDimension, unsigned int, VMovingDimensions);
			itkStaticConstMacro(DirectOutputDimension, unsigned int, VTargetDimensions);

			typedef typename continuous::Elements< DirectOutputDimension >::VectorType DirectMappingVectorType;
			typedef itk::Image< DirectMappingVectorType, DirectInputDimension> DirectFieldType;
			typedef typename DirectFieldType::Pointer DirectFieldPointer;
			typedef typename DirectFieldType::RegionType DirectFieldRegionType;

			//inverse mapping
			itkStaticConstMacro(InverseInputDimension, unsigned int, VTargetDimensions);
			itkStaticConstMacro(InverseOutputDimension, unsigned int, VMovingDimensions);

			typedef typename continuous::Elements< InverseOutputDimension >::VectorType
			InverseMappingVectorType;
			typedef itk::Image< InverseMappingVectorType, InverseInputDimension > InverseFieldType;
			typedef typename InverseFieldType::Pointer InverseFieldPointer;
			typedef typename InverseFieldType::RegionType InverseFieldRegionType;

		private:
			typedef RegistrationTopology<VMovingDimensions, VTargetDimensions> Self;

			//purposely not implemented
			RegistrationTopology();
			//purposely not implemented
			RegistrationTopology(const Self& source);
			//purposely not implemented
			virtual Self& operator = (const Self& source) = 0;
		};

	} // end namespace core
} // end namespace map

#endif
