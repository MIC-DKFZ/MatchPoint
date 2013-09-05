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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKEuler3DMattesMIRegistrationAlgorithmTemplate.h $
*/


#ifndef __MAP_ITK_EULER3D_MATTES_MI_REGISTRATION_ALGORITHM_TEMPLATE_H
#define __MAP_ITK_EULER3D_MATTES_MI_REGISTRATION_ALGORITHM_TEMPLATE_H

#include "mapITKImageRegistrationAlgorithm.h"

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

			mapGenerateAlgorithmUIDPolicyMacro(DefaultEuler3DMattesMIRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint", "Euler3DMattesMIRegistrationAlgorithm.default", "1.0.0", "");

			/** @brief Boxing of a simple rigid mattes based image registration algorithm
			@ingroup Boxed
			*/
			template < class TMovingImage, class TTargetImage = TMovingImage,
			         typename TUIDPolicy = DefaultEuler3DMattesMIRegistrationAlgorithmUIDPolicy,
			         class TInterpolatorPolicy = SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType> > >
			class ITKEuler3DMattesMIRegistrationAlgorithm :
				public algorithm::itk::ITKImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
				TInterpolatorPolicy,
				SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
				SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform<map::core::continuous::ScalarType> > >
			{
			public:
				typedef ITKEuler3DMattesMIRegistrationAlgorithm<TMovingImage, TTargetImage, TUIDPolicy, TInterpolatorPolicy> Self;

				typedef typename algorithm::itk::ITKImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
				        TInterpolatorPolicy,
				        SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
				        SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
				        SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform<map::core::continuous::ScalarType> > >  Superclass;

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

				virtual void compileInfos(MetaPropertyVectorType &infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType &name) const;

				virtual void doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty);

				/*! Calls the super class version. Afterwards it preinitializes the transform of
				* the algorithm as setup (no init, init by geometry or init by center of gravity).
				@eguarantee strong
				*/
				virtual void prepInitializeTransformation();

				/*! Indicates if the transform should be pre initialized */
				bool _preInitialize;
				/*! Indicates if for a pre initialization the center of gravity (true) or the image geometry center (false)
				* should be used.*/
				bool _useCenterOfGravity;

			private:

				ITKEuler3DMattesMIRegistrationAlgorithm(const Self &source);  //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKEuler3DMattesMIRegistrationAlgorithmTemplate.tpp"
#endif

#endif
