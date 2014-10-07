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


#ifndef __ITK_FAST_SYMMETRIC_FORCES_DEMONS_MULTI_RES_REGISTRATION_ALGORITHM_TPP
#define __ITK_FAST_SYMMETRIC_FORCES_DEMONS_MULTI_RES_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			~ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			configureAlgorithm()
			{
				Superclass::configureAlgorithm();
				this->setResolutionLevels(4);

				_lvlIntensityDifferenceThreshold.SetSize(4);
				_lvlIntensityDifferenceThreshold[0] = 0.01;
				_lvlIntensityDifferenceThreshold[1] = 0.01;
				_lvlIntensityDifferenceThreshold[2] = 0.001;
				_lvlIntensityDifferenceThreshold[3] = 0.001;
				_lvlMaximumUpdateStepLength.SetSize(4);
				_lvlMaximumUpdateStepLength[0] = 10;
				_lvlMaximumUpdateStepLength[1] = 3;
				_lvlMaximumUpdateStepLength[2] = 1;
				_lvlMaximumUpdateStepLength[3] = 0.5;
				_lvlUseGradientType.SetSize(4);
				_lvlUseGradientType[0] = 0;
				_lvlUseGradientType[1] = 0;
				_lvlUseGradientType[2] = 0;
				_lvlUseGradientType[3] = 0;
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.1",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumUpdateStepLength.1", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseGradientType.1",
								typeid(int), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.2",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumUpdateStepLength.2", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseGradientType.2",
								typeid(int), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.3",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumUpdateStepLength.3", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseGradientType.3",
								typeid(int), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold.4",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumUpdateStepLength.4", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseGradientType.4",
								typeid(int), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			typename ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::MetaPropertyPointer
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "IntensityDifferenceThreshold.1")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[0]);
				}
				else if (name == "MaximumUpdateStepLength.1")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlMaximumUpdateStepLength[0]);
				}
				else if (name == "UseGradientType.1")
				{
					spResult = map::core::MetaProperty<int>::New(_lvlUseGradientType[0]);
				}
				else if (name == "IntensityDifferenceThreshold.2")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[1]);
				}
				else if (name == "MaximumUpdateStepLength.2")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlMaximumUpdateStepLength[1]);
				}
				else if (name == "UseGradientType.2")
				{
					spResult = map::core::MetaProperty<int>::New(_lvlUseGradientType[1]);
				}
				else if (name == "IntensityDifferenceThreshold.3")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[2]);
				}
				else if (name == "MaximumUpdateStepLength.3")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlMaximumUpdateStepLength[2]);
				}
				else if (name == "UseGradientType.3")
				{
					spResult = map::core::MetaProperty<int>::New(_lvlUseGradientType[2]);
				}
				else if (name == "IntensityDifferenceThreshold.4")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlIntensityDifferenceThreshold[3]);
				}
				else if (name == "MaximumUpdateStepLength.4")
				{
					spResult = map::core::MetaProperty<double>::New(_lvlMaximumUpdateStepLength[3]);
				}
				else if (name == "UseGradientType.4")
				{
					spResult = map::core::MetaProperty<int>::New(_lvlUseGradientType[3]);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "IntensityDifferenceThreshold.1")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(value);
					this->_lvlIntensityDifferenceThreshold[0] = value;
				}
				else if (name == "MaximumUpdateStepLength.1")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetMaximumUpdateStepLength(value);
					this->_lvlMaximumUpdateStepLength[0] = value;
				}
				else if (name == "UseGradientType.1")
				{
					int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetUseGradientType(static_cast<typename Superclass::InternalRegistrationMethodType::GradientType>(value));
					this->_lvlUseGradientType[0] = value;
				}
				else if (name == "IntensityDifferenceThreshold.2")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlIntensityDifferenceThreshold[1] = value;
				}
				else if (name == "MaximumUpdateStepLength.2")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlMaximumUpdateStepLength[1] = value;
				}
				else if (name == "UseGradientType.2")
				{
					int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlUseGradientType[1] = value;
				}
				else if (name == "IntensityDifferenceThreshold.3")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlIntensityDifferenceThreshold[2] = value;
				}
				else if (name == "MaximumUpdateStepLength.3")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlMaximumUpdateStepLength[2] = value;
				}
				else if (name == "UseGradientType.3")
				{
					int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlUseGradientType[2] = value;
				}
				else if (name == "IntensityDifferenceThreshold.4")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlIntensityDifferenceThreshold[3] = value;
				}
				else if (name == "MaximumUpdateStepLength.4")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlMaximumUpdateStepLength[3] = value;
				}
				else if (name == "UseGradientType.4")
				{
					int value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->_lvlUseGradientType[3] = value;
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField, class TPyramideInitializationPolicy>
			void
			ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy >::
			doInterLevelSetup()
			{
				Superclass::doInterLevelSetup();

				if (this->getCurrentLevel() > 0)
				{
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(
						this->_lvlIntensityDifferenceThreshold[this->getCurrentLevel()]);
					this->getInternalRegistrationMethod().SetMaximumUpdateStepLength(this->_lvlMaximumUpdateStepLength[this->getCurrentLevel()]);
					this->getInternalRegistrationMethod().SetUseGradientType( static_cast<typename Superclass::InternalRegistrationMethodType::GradientType>(this->_lvlUseGradientType[this->getCurrentLevel()]));
				}
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
