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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKEuler3DICPRegistrationAlgorithmTemplate.h $
*/


#ifndef __MAP_EULER_3D_ICP_REGISTRATION_ALGORITHM_H
#define __MAP_EULER_3D_ICP_REGISTRATION_ALGORITHM_H

#include "mapITKPointSetRegistrationAlgorithm.h"

#include "mapITKLevenbergMarquardtOptimizer.h"
#include "mapITKEuclideanDistancePointMetric.h"
#include "mapITKEuler3DTransform.h"

#include "mapFixedPointSetToPointSetMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedMVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"


namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
      const char *const DefaultITKEuler3DICPRegistrationAlgorithm_profile = "<Profile><Description>Simple 3D rigid (translation and euler angles) registration algorithm using point sets pairs and a ICP solution.</Description><Contact>Ralf Floca; sbr@dkfz-heidelberg.de</Contact><Characteristics><DataType>Points</DataType><DimMoving>3</DimMoving><DimTarget>3</DimTarget><TransformModel>rigid</TransformModel><TransformDomain>global</TransformDomain><Optimization>ICP<Optimization/></Characteristics><Keywords><Keyword>basic</Keyword></Keywords></Profile>";

			mapGenerateAlgorithmUIDPolicyMacro(DefaultITKEuler3DICPRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint", "ITKEuler3DICPRegistrationAlgorithm.default", "1.0.0", DefaultITKEuler3DICPRegistrationAlgorithm_profile);

			/** @brief Boxing of a simple rigid point set registration algorithm using Euler3D transform
			@ingroup Boxed
			*/
			template < class TMovingPointSet, class TTargetPointSet = TMovingPointSet,
			         class TIdentificationPolicy = DefaultITKEuler3DICPRegistrationAlgorithmUIDPolicy,
			         class TDistanceMap = typename map::core::discrete::Elements<TMovingPointSet::PointDimension>::InternalImageType >
			class ITKEuler3DICPRegistrationAlgorithm: public map::algorithm::itk::ITKPointSetRegistrationAlgorithm < TMovingPointSet,
				TTargetPointSet,
				TIdentificationPolicy,
				SealedFixedPointSetToPointSetMetricPolicyMacro< ::itk::EuclideanDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >,
				SealedFixedMVNLOptimizerPolicyMacro< ::itk::LevenbergMarquardtOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform< map::core::continuous::ScalarType> > >
			{
			public:
				//optional
				typedef ::itk::EuclideanDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> MetricType;
				typedef ::itk::LevenbergMarquardtOptimizer OptimizerType;
				typedef ::itk::Euler3DTransform< map::core::continuous::ScalarType> TransformType;

				typedef SealedFixedPointSetToPointSetMetricPolicyMacro<MetricType> MetricPolicyType;
				typedef SealedFixedMVNLOptimizerPolicyMacro<OptimizerType> OptimizerPolicyType;
				typedef SealedFixedTransformPolicyMacro<TransformType> TransformPolicyType;

				typedef ITKEuler3DICPRegistrationAlgorithm Self;

				typedef map::algorithm::itk::ITKPointSetRegistrationAlgorithm < TMovingPointSet,
				        TTargetPointSet,
				        TIdentificationPolicy,
				        SealedFixedPointSetToPointSetMetricPolicyMacro< ::itk::EuclideanDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >,
				        SealedFixedMVNLOptimizerPolicyMacro< ::itk::LevenbergMarquardtOptimizer>,
				        SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform< map::core::continuous::ScalarType> > >  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(ITKEuler3DICPRegistrationAlgorithm, ITKPointSetRegistrationAlgorithme);
				mapNewAlgorithmMacro(Self);

			protected:
				ITKEuler3DICPRegistrationAlgorithm()
				{
				};

				void configureAlgorithm()
				{
					OptimizerType::ScalesType scales(6);
					scales[0] = 1.0;
					scales[1] = 1.0;
					scales[2] = 1.0;
					scales[3] = 1.0 / 1000;
					scales[4] = 1.0 / 1000;
					scales[5] = 1.0 / 1000;

					this->getConcreteTransformModel()->getConcreteTransform()->SetIdentity();
					this->getConcreteITKOptimizer()->SetScales(scales);
					this->getConcreteITKOptimizer()->SetValueTolerance(1e-5);
					this->getConcreteITKOptimizer()->SetGradientTolerance(1e-5);
					this->getConcreteITKOptimizer()->SetEpsilonFunction(1e-6);
					this->getConcreteITKOptimizer()->SetNumberOfIterations(20000);
					this->getConcreteITKOptimizer()->SetUseCostFunctionGradient(false);
				}

				virtual ~ITKEuler3DICPRegistrationAlgorithm()
				{
				};

			private:

				ITKEuler3DICPRegistrationAlgorithm(const Self &source);  //purposely not implemented
				void operator=(const Self &); //purposely not implemented

			};

		}
	}
}


#endif
