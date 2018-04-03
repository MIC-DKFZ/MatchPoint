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


#ifndef __ITK_PDE_DEMONS_REGISTRATION_ALGORITHM_TPP
#define __ITK_PDE_DEMONS_REGISTRATION_ALGORITHM_TPP

#include "mapITKPDEDemonsRegistrationAlgorithm.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{


			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			ITKPDEDemonsRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			~ITKPDEDemonsRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			configureAlgorithm()
			{
				Superclass::configureAlgorithm();
			}

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("IntensityDifferenceThreshold",
								typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseMovingImageGradient", typeid(bool), true,
								true));
#endif
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			typename ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::MetaPropertyPointer
			ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "IntensityDifferenceThreshold")
				{
					spResult = map::core::MetaProperty<double>::New(0.001);
				}
				else if (name == "UseMovingImageGradient")
				{
					spResult = map::core::MetaProperty<bool>::New(false);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TDisplacementField>
			void
			ITKPDEDemonsRegistrationAlgorithm<TImageType, TIdentificationPolicy, TDisplacementField>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "IntensityDifferenceThreshold")
				{
					double value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetIntensityDifferenceThreshold(value);
				}
				else if (name == "UseMovingImageGradient")
				{
					bool value;
					map::core::unwrapMetaProperty(pProperty, value);
					this->getInternalRegistrationMethod().SetUseMovingImageGradient(value);
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
