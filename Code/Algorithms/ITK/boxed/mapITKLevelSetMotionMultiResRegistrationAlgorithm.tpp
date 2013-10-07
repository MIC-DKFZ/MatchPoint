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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKLevelSetMotionMultiResRegistrationAlgorithm.tpp $
*/


#ifndef __ITK_LEVEL_SET_MOTION_MULTI_RES_REGISTRATION_ALGORITHM_TPP
#define __ITK_LEVEL_SET_MOTION_MULTI_RES_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
      
			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			ITKLevelSetMotionMultiResRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			~ITKLevelSetMotionMultiResRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			configureAlgorithm()
			{
			    Superclass::configureAlgorithm();
  				this->setResolutionLevels(4);
				
					_lvlIntensityDifferenceThreshold.SetSize(4);
					_lvlIntensityDifferenceThreshold[0] = 0.01;
					_lvlIntensityDifferenceThreshold[1] = 0.01;
					_lvlIntensityDifferenceThreshold[2] = 0.001;
					_lvlIntensityDifferenceThreshold[3] = 0.001;
				  _lvlAlpha.SetSize(4);
					_lvlAlpha[0] = 1;
					_lvlAlpha[1] = 0.1;
					_lvlAlpha[2] = 0.01;
					_lvlAlpha[3] = 0.001;
				  _lvlGradientMagnitudeThreshold.SetSize(4);
					_lvlGradientMagnitudeThreshold[0] = 1e-6;
					_lvlGradientMagnitudeThreshold[1] = 1e-7;
					_lvlGradientMagnitudeThreshold[2] = 1e-8;
					_lvlGradientMagnitudeThreshold[3] = 1e-9;
				  _lvlGradientSmoothingStandardDeviations.SetSize(4);
					_lvlGradientSmoothingStandardDeviations[0] = 1;
					_lvlGradientSmoothingStandardDeviations[1] = 1;
					_lvlGradientSmoothingStandardDeviations[2] = 1;
					_lvlGradientSmoothingStandardDeviations[3] = 1;
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			compileInfos(MetaPropertyVectorType &infos) const
			{
        Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.1", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Alpha.1", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeThreshold.1", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientSmoothingStandardDeviations.1", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.2", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Alpha.2", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeThreshold.2", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientSmoothingStandardDeviations.2", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.3", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Alpha.3", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeThreshold.3", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientSmoothingStandardDeviations.3", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.4", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Alpha.4", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeThreshold.4", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientSmoothingStandardDeviations.4", typeid(double), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			typename ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::MetaPropertyPointer
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			doGetProperty(const MetaPropertyNameType &name) const
			{
				MetaPropertyPointer spResult;

				if (name == "IntensityDifferenceThreshold.1")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[0]);
				}
        else if (name == "Alpha.1")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlAlpha[0]);
				}
				else if (name == "GradientMagnitudeThreshold.1")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientMagnitudeThreshold[0]);
				}
				else if (name == "GradientSmoothingStandardDeviations.1")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientSmoothingStandardDeviations[0]);
				}
				else if (name == "IntensityDifferenceThreshold.2")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[1]);
				}
        else if (name == "Alpha.2")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlAlpha[1]);
				}
				else if (name == "GradientMagnitudeThreshold.2")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientMagnitudeThreshold[1]);
				}
				else if (name == "GradientSmoothingStandardDeviations.2")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientSmoothingStandardDeviations[1]);
				}
				else if (name == "IntensityDifferenceThreshold.3")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[2]);
				}
        else if (name == "Alpha.3")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlAlpha[2]);
				}
				else if (name == "GradientMagnitudeThreshold.3")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientMagnitudeThreshold[2]);
				}
				else if (name == "GradientSmoothingStandardDeviations.3")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientSmoothingStandardDeviations[2]);
				}
				else if (name == "IntensityDifferenceThreshold.4")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[3]);
				}
        else if (name == "Alpha.4")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlAlpha[3]);
				}
				else if (name == "GradientMagnitudeThreshold.4")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientMagnitudeThreshold[3]);
				}
				else if (name == "GradientSmoothingStandardDeviations.4")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlGradientSmoothingStandardDeviations[3]);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
			{
				if (name == "IntensityDifferenceThreshold.1")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(value);
					this->_lvlIntensityDifferenceThreshold[0] = value;
				}
        else if (name == "Alpha.1")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetAlpha(value);
					this->_lvlAlpha[0] = value;
				}
				else if (name == "GradientMagnitudeThreshold.1")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetGradientMagnitudeThreshold(value);
					this->_lvlGradientMagnitudeThreshold[0] = value;
				}
				else if (name == "GradientSmoothingStandardDeviations.1")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetGradientSmoothingStandardDeviations(value);
					this->_lvlGradientSmoothingStandardDeviations[0] = value;
				}
				else if (name == "IntensityDifferenceThreshold.2")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlIntensityDifferenceThreshold[1] = value;
				}
        else if (name == "Alpha.2")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlAlpha[1] = value;
				}
				else if (name == "GradientMagnitudeThreshold.2")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlGradientMagnitudeThreshold[1] = value;
				}
				else if (name == "GradientSmoothingStandardDeviations.2")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlGradientSmoothingStandardDeviations[1] = value;
				}
				else if (name == "IntensityDifferenceThreshold.3")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlIntensityDifferenceThreshold[2] = value;
				}
        else if (name == "Alpha.3")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlAlpha[2] = value;
				}
				else if (name == "GradientMagnitudeThreshold.3")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlGradientMagnitudeThreshold[2] = value;
				}
				else if (name == "GradientSmoothingStandardDeviations.3")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlGradientSmoothingStandardDeviations[2] = value;
				}
				else if (name == "IntensityDifferenceThreshold.4")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlIntensityDifferenceThreshold[3] = value;
				}
        else if (name == "Alpha.4")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlAlpha[3] = value;
				}
				else if (name == "GradientMagnitudeThreshold.4")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlGradientMagnitudeThreshold[3] = value;
				}
				else if (name == "GradientSmoothingStandardDeviations.4")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlGradientSmoothingStandardDeviations[3] = value;
				}
        else
        {
          Superclass::doSetProperty(name, pProperty);
        }
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKLevelSetMotionMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			doInterLevelSetup()
			{
        Superclass::doInterLevelSetup();

				if (this->getCurrentLevel() > 0)
				{
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(this->_lvlIntensityDifferenceThreshold[this->getCurrentLevel()]);
					this->getInternalRegistrationMethod().SetAlpha(this->_lvlAlpha[this->getCurrentLevel()]);
					this->getInternalRegistrationMethod().SetGradientMagnitudeThreshold(this->_lvlGradientMagnitudeThreshold[this->getCurrentLevel()]);
					this->getInternalRegistrationMethod().SetGradientSmoothingStandardDeviations(this->_lvlGradientSmoothingStandardDeviations[this->getCurrentLevel()]);
				}
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
