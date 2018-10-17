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


#ifndef __ITK_RIGID_3D_MATTESMI_SLABBEDHEAD_REGISTRATION_ALGORITHM_TPP
#define __ITK_RIGID_3D_MATTESMI_SLABBEDHEAD_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      MultiModalRigidSlabbedHeadRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
        MultiModalRigidSlabbedHeadRegistrationAlgorithm()
			{
			}

			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      MultiModalRigidSlabbedHeadRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			~MultiModalRigidSlabbedHeadRegistrationAlgorithm()
			{
			}

			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			void
        MultiModalRigidSlabbedHeadRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			configureAlgorithm()
			{
        Superclass::configureAlgorithm();

        this->setResolutionLevels(3);
        this->_preInitialize = true;
        this->_useCenterOfGravity = false;

        //optimizer
        ConcreteOptimizerType::ScalesType scales(6);
        scales[0] = 10.0;
        scales[1] = 10.0;
        scales[2] = 10.0;
        scales[3] = 1.0 / 10000;
        scales[4] = 1.0 / 10000;
        scales[5] = 1.0 / 10000;

        this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);
        this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(3.00);
        this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(0.5);
        this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetNumberOfIterations(200);
        this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetRelaxationFactor(0.8);
        this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetGradientMagnitudeTolerance(1e-4);

        //metric
        this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfHistogramBins(30);
        this->getConcreteMetricControl()->getConcreteMetric()->SetUseAllPixels(true);
        this->getConcreteMetricControl()->getConcreteMetric()->ReinitializeSeed();
        this->getConcreteMetricControl()->getConcreteMetric()->UseExplicitPDFDerivativesOn();
			}
			
			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			void
        MultiModalRigidSlabbedHeadRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			doInterLevelSetup(){
        Superclass::doInterLevelSetup();

        if (this->getCurrentLevel() != 0)
        {
          getConcreteMetricControl()->getConcreteMetric()->SetUseAllPixels(false);

          OptimizerBaseType::SVNLOptimizerBaseType::ScalesType scales(6);
          scales[0] = 1.0;
          scales[1] = 1.0;
          scales[2] = 1.0;
          scales[3] = 1.0 / 1000;
          scales[4] = 1.0 / 1000;
          scales[5] = 1.0 / 1000;

          getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);

          unsigned int nrOfSmpl = ::itk::Math::Round<unsigned int, double>
            (this->getMovingImage()->GetLargestPossibleRegion().GetNumberOfPixels() * 0.15);

          getConcreteMetricControl()->getConcreteMetric()->SetNumberOfSpatialSamples(nrOfSmpl);

          //optimizer adjustment
          getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(
            getConcreteOptimizerControl()->getConcreteOptimizer()->GetCurrentStepLength() * 2.0);
          getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(
            getConcreteOptimizerControl()->getConcreteOptimizer()->GetMinimumStepLength() * 0.5);

        }
			}

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
