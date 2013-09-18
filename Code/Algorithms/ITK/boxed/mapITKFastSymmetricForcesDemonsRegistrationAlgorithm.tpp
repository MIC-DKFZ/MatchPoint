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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKFastSymmetricForcesDemonsRegistrationAlgorithm.tpp $
*/


#ifndef __ITK_FAST_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_TPP
#define __ITK_FAST_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_TPP

#include <itkHistogramMatchingImageFilter.h>

#include "mapAlgorithmException.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
      

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			~ITKFastSymmetricForcesDemonsRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			configureAlgorithm()
			{
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			compileInfos(MetaPropertyVectorType &infos) const
			{
        Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumUpdateStepLength", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseGradientType", typeid(int), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			typename ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::MetaPropertyPointer
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doGetProperty(const MetaPropertyNameType &name) const
			{
				MetaPropertyPointer spResult;

				if (name == "IntensityDifferenceThreshold")
				{
					spResult = map::core::MetaProperty<double>::New(0.001);
				}
        else if (name == "MaximumUpdateStepLength")
				{
					spResult = map::core::MetaProperty<double>::New(0.5);
				}
				else if (name == "UseGradientType")
				{
					spResult = map::core::MetaProperty<int>::New(0);
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
			{
				if (name == "IntensityDifferenceThreshold")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(value);
				}
        else if (name == "MaximumUpdateStepLength")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetMaximumUpdateStepLength(value);
				}
				else if (name == "UseGradientType")
				{
					int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetUseGradientType(static_cast<Superclass::InternalRegistrationMethodType::GradientType>(value));
				}
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
