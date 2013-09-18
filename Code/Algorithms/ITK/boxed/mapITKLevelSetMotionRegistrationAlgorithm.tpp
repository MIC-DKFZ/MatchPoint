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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKLevelSetMotionRegistrationAlgorithm.tpp $
*/


#ifndef __ITK_LEVEL_SET_MOTION_REGISTRATION_ALGORITHM_TPP
#define __ITK_LEVEL_SET_MOTION_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
      

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			ITKLevelSetMotionRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			~ITKLevelSetMotionRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			configureAlgorithm()
			{
			    Superclass::configureAlgorithm();
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			compileInfos(MetaPropertyVectorType &infos) const
			{
        Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Alpha", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeThreshold", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientSmoothingStandardDeviations", typeid(double), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			typename ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::MetaPropertyPointer
			ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doGetProperty(const MetaPropertyNameType &name) const
			{
				MetaPropertyPointer spResult;

				if (name == "IntensityDifferenceThreshold")
				{
					spResult = map::core::MetaProperty<double>::New(0.001);
				}
        else if (name == "Alpha")
				{
					spResult = map::core::MetaProperty<double>::New(0.001);
				}
				else if (name == "GradientMagnitudeThreshold")
				{
					spResult = map::core::MetaProperty<double>::New(1e-9);
				}
				else if (name == "GradientSmoothingStandardDeviations")
				{
					spResult = map::core::MetaProperty<double>::New(1.0);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKLevelSetMotionRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
			{
				if (name == "IntensityDifferenceThreshold")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(value);
				}
        else if (name == "Alpha")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetAlpha(value);
				}
				else if (name == "GradientMagnitudeThreshold")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetGradientMagnitudeThreshold(value);
				}
				else if (name == "GradientSmoothingStandardDeviations")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetGradientSmoothingStandardDeviations(value);
				}
        else
        {
          Superclass::doSetProperty(name, pProperty);
        }
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
