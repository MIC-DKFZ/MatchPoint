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


#ifndef __MAP_ITK_EULER3D_MATTES_MI_REGISTRATION_ALGORITHM_TEMPLATE_H
#define __MAP_ITK_EULER3D_MATTES_MI_REGISTRATION_ALGORITHM_TEMPLATE_H

#include "mapITKInitializedImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
#include "mapITKEuler3DTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

#include "mapFixedImageToImageMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedSVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"


namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			mapGenerateAlgorithmUIDPolicyMacro(DefaultEuler3DMattesMIRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "Euler3DMattesMIRegistrationAlgorithm.default", "1.0.1", "");

			/** @brief Boxing of a simple rigid mattes based image registration algorithm
			@ingroup Boxed
			*/
			template < class TMovingImage, class TTargetImage = TMovingImage,
					 typename TUIDPolicy = DefaultEuler3DMattesMIRegistrationAlgorithmUIDPolicy,
					 class TInterpolatorPolicy =
					 SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType> >
					 >
			class ITKEuler3DMattesMIRegistrationAlgorithm :
				public algorithm::boxed::ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
				TInterpolatorPolicy,
				SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
				SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform<map::core::continuous::ScalarType> > >
			{
			public:
				typedef ITKEuler3DMattesMIRegistrationAlgorithm<TMovingImage, TTargetImage, TUIDPolicy, TInterpolatorPolicy>
				Self;

				typedef typename algorithm::boxed::ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage,
						TUIDPolicy,
						TInterpolatorPolicy,
						SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
						SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
						SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform<map::core::continuous::ScalarType> > >
						Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(ITKEuler3DMattesMIRegistrationAlgorithm, ITKImageRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef ::itk::Array<double> ParametersType;

				typedef typename Superclass::MetaPropertyType MetaPropertyType;
				typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
				typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
				typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				ITKEuler3DMattesMIRegistrationAlgorithm();
				virtual ~ITKEuler3DMattesMIRegistrationAlgorithm();

				virtual void configureAlgorithm();

				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

			private:

				ITKEuler3DMattesMIRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKEuler3DMattesMIRegistrationAlgorithmTemplate.tpp"
#endif

#endif
