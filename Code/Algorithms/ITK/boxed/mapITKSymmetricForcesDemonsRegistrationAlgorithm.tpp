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


#ifndef __ITK_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_TPP
#define __ITK_SYMMETRIC_FORCES_DEMONS_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{


			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			ITKSymmetricForcesDemonsRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			~ITKSymmetricForcesDemonsRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			configureAlgorithm()
			{
				Superclass::configureAlgorithm();
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold",
								typeid(double), true, true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			typename ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::MetaPropertyPointer
			ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "IntensityDifferenceThreshold")
				{
					spResult = map::core::MetaProperty<double>::New(0.001);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKSymmetricForcesDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "IntensityDifferenceThreshold")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(value);
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
