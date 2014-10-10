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


#ifndef __ITK_FAST_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_TPP
#define __ITK_FAST_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_TPP

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
				Superclass::configureAlgorithm();
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumUpdateStepLength", typeid(double),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseGradientType", typeid(int), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			typename ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::MetaPropertyPointer
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doGetProperty(const MetaPropertyNameType& name) const
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
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKFastSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
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
					this->getInternalRegistrationMethod().SetUseGradientType(
						static_cast<typename Superclass::InternalRegistrationMethodType::GradientType>(value));
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
