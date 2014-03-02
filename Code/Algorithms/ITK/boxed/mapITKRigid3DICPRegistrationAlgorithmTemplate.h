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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19. Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKRigid3DICPRegistrationAlgorithmTemplate.h $
*/


#ifndef __MAP_RIGID_3D_ICP_REGISTRATION_ALGORITHM_H
#define __MAP_RIGID_3D_ICP_REGISTRATION_ALGORITHM_H

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
			const char* const DefaultITKRigid3DICPRegistrationAlgorithm_profile =
				"<Profile><Description>Simple 3D rigid (translation and euler angles) registration algorithm using point sets and a ICP solution.</Description><Contact>Ralf Floca; sbr@dkfz-heidelberg.de</Contact><Characteristics><DataType>Points</DataType><DimMoving>2</DimMoving><DimTarget>2</DimTarget><TransformModel>rigid</TransformModel><TransformDomain>global</TransformDomain><Optimization>ICP<Optimization/></Characteristics><Keywords><Keyword>basic</Keyword></Keywords></Profile>";
			mapGenerateAlgorithmUIDPolicyMacro(DefaultITKRigid3DICPRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "ITKRigid3DICPRegistrationAlgorithm.default", "1.0.0",
											   DefaultITKRigid3DICPRegistrationAlgorithm_profile);

			/** @brief Boxing of a simple rigid point set registration algorithm using Rigid3D transform
			@ingroup Boxed
			*/
			template < class TMovingPointSet, class TTargetPointSet = TMovingPointSet,
					 class TIdentificationPolicy = DefaultITKRigid3DICPRegistrationAlgorithmUIDPolicy,
					 class TDistanceMap = typename
					 map::core::discrete::Elements<TMovingPointSet::PointDimension>::InternalImageType >
			class ITKRigid3DICPRegistrationAlgorithm: public
				map::algorithm::itk::ITKPointSetRegistrationAlgorithm < TMovingPointSet,
				TTargetPointSet,
				TIdentificationPolicy,
				SealedFixedPointSetToPointSetMetricPolicyMacro< ::itk::EuclideanDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >,
				SealedFixedMVNLOptimizerPolicyMacro< ::itk::LevenbergMarquardtOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform< map::core::continuous::ScalarType> > >
			{
			public:
				//optional
				typedef ::itk::EuclideanDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap>
				MetricType;
				typedef ::itk::LevenbergMarquardtOptimizer OptimizerType;
				typedef ::itk::Euler3DTransform< map::core::continuous::ScalarType> TransformType;

				typedef SealedFixedPointSetToPointSetMetricPolicyMacro<MetricType> MetricPolicyType;
				typedef SealedFixedMVNLOptimizerPolicyMacro<OptimizerType> OptimizerPolicyType;
				typedef SealedFixedTransformPolicyMacro<TransformType> TransformPolicyType;

				typedef ITKRigid3DICPRegistrationAlgorithm Self;

				typedef map::algorithm::itk::ITKPointSetRegistrationAlgorithm < TMovingPointSet,
						TTargetPointSet,
						TIdentificationPolicy,
						SealedFixedPointSetToPointSetMetricPolicyMacro< ::itk::EuclideanDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >,
						SealedFixedMVNLOptimizerPolicyMacro< ::itk::LevenbergMarquardtOptimizer>,
						SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform< map::core::continuous::ScalarType> > >
						Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(ITKRigid3DICPRegistrationAlgorithm, ITKPointSetRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

			protected:
				ITKRigid3DICPRegistrationAlgorithm()
				{
				};

				virtual ~ITKRigid3DICPRegistrationAlgorithm()
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
					this->getConcreteITKOptimizer()->SetNumberOfIterations(2000);
					this->getConcreteITKOptimizer()->SetUseCostFunctionGradient(false);
				}

			private:

				ITKRigid3DICPRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}


#endif
