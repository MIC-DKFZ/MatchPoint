// -----------------------------------------------------------------------
// RAP - Registration Algoritm Portfolio
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See rapCopyright.txt and/or notes within this file
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision: 4933 $ (last changed revision)
// @date    $Date: 2013-09-05 17:19:45 +0200 (Do, 05 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/RAP/trunk/Algorithms/Diffusion/difRigid_MattesMI.cpp $
*/



#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapITKRigid3DMattesMIBoundingBoxRegistrationAlgorithmTemplate.h"
#include "mapConfigure.h"

#include "itkRegionOfInterestImageFilter.h"
#include "itkBinaryErodeImageFilter.h"
#include "itkFlatStructuringElement.h"
#include "itkImageMaskSpatialObject.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm() : _ActivateBoundingBox(false), _ActivateMargin(false)
  		{
			};

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      ~ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm()
			{
			};

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      void
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      configureAlgorithm()
			{
				Superclass::configureAlgorithm();

				this->setResolutionLevels(3);
				this->_preInitialize = true;
				this->_useCenterOfGravity = false;
        this->_ActivateBoundingBox = false;
        this->_ActivateMargin = false;
				this->_margins.Fill(0.0);

				//optimizer
        ScalesType scales(6);
        scales[0] = 10.0;
        scales[1] = 10.0;
        scales[2] = 10.0;
        scales[3] = 1.0 / 10000;
        scales[4] = 1.0 / 10000;
        scales[5] = 1.0 / 10000;

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
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			doInterLevelSetup()
			{
				Superclass::doInterLevelSetup();

				if (this->getCurrentLevel() != 0)
				{
					this->getConcreteMetricControl()->getConcreteMetric()->SetUseAllPixels(false);

					ScalesType scales(6);
					scales[0] = 1.0;
					scales[1] = 1.0;
					scales[2] = 1.0;
					scales[3] = 1.0 / 1000;
					scales[4] = 1.0 / 1000;
					scales[5] = 1.0 / 1000;

					this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);

					unsigned int nrOfSmpl = ::itk::Math::Round<unsigned int, double>
											(this->getMovingImage()->GetLargestPossibleRegion().GetNumberOfPixels() * 0.15);

					this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfSpatialSamples(nrOfSmpl);
				}
			};

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      void
        ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
        prepPerpareInternalInputData()
      {
        ::map::core::OStringStream os;
        ::map::core::OStringStream os2;

        if (this->_ActivateMargin)
        {
          using TargetImageSOType = ::itk::ImageSpatialObject<TargetImageType::ImageDimension>;

          auto targetMask = this->getInternalTargetMask();
          auto targetImageMask = dynamic_cast<const TargetImageSOType*>(targetMask.GetPointer());

          if (targetImageMask)
          {
            //we have a mask -> add margin
            using TargetImageMaskImageType = typename TargetImageSOType::ImageType;

            auto spacing = this->getInternalTargetImage()->GetSpacing();

            using StructuringElementType = ::itk::FlatStructuringElement<TargetImageType::ImageDimension>;
            typename StructuringElementType::RadiusType radius;

            for (unsigned int i = 0; i < spacing.Size(); ++i)
            {
              radius[i] = ::itk::Math::Round<typename StructuringElementType::RadiusType::SizeValueType, double>(_margins[i] / spacing[i]);
            }

            StructuringElementType structuringElement = StructuringElementType::Ball(radius);

            //We don't know the mask lables, but we know that background is always 0. Therefore we erode
            //the background.
            using BinaryErodeImageFilterType = ::itk::BinaryErodeImageFilter<TargetImageMaskImageType, TargetImageMaskImageType, StructuringElementType>;

            typename BinaryErodeImageFilterType::Pointer erodeFilter = BinaryErodeImageFilterType::New();
            erodeFilter->SetInput(targetImageMask->GetImage());
            erodeFilter->SetKernel(structuringElement);
            erodeFilter->SetErodeValue(0);
            erodeFilter->SetBackgroundValue(::itk::NumericTraits<typename TargetImageMaskImageType::PixelType>::max());
            erodeFilter->Update();

            auto dilatedImage = erodeFilter->GetOutput();
            using TargetImageMaskSOType = ::itk::ImageMaskSpatialObject< TargetImageType::ImageDimension >;
            typename TargetImageMaskSOType::Pointer newMask = TargetImageMaskSOType::New();
            newMask->SetImage(dilatedImage);
            this->setInternalTargetMask(newMask);
            os << "Target mask: add margin with size (in mm): " << _margins << " (pixels: "<< radius<<")";
            
          }
          else
          {
            os << "Target mask: is not image based. No margins added.";
          }

          this->InvokeEvent(::map::events::AlgorithmEvent(this, os.str()));

          using MovingImageSOType = ::itk::ImageSpatialObject<MovingImageType::ImageDimension>;

          auto movingMask = this->getInternalMovingMask();
          auto movingImageMask = dynamic_cast<const MovingImageSOType*>(movingMask.GetPointer());

          if (movingImageMask)
          {
            //we have a mask -> add margin
            using MovingImageMaskImageType = typename MovingImageSOType::ImageType;

            auto spacing = this->getInternalMovingImage()->GetSpacing();

            using StructuringElementType = ::itk::FlatStructuringElement<MovingImageType::ImageDimension>;
            typename StructuringElementType::RadiusType radius;

            for (unsigned int i = 0; i < spacing.Size(); ++i)
            {
              radius[i] = ::itk::Math::Round<typename StructuringElementType::RadiusType::SizeValueType, double>(_margins[i] / spacing[i]);
            }

            StructuringElementType structuringElement = StructuringElementType::Ball(radius);

            //We don't know the mask lables, but we know that background is always 0. Therefore we erode
            //the background.
            using BinaryErodeImageFilterType = ::itk::BinaryErodeImageFilter<MovingImageMaskImageType, MovingImageMaskImageType, StructuringElementType>;

            typename BinaryErodeImageFilterType::Pointer erodeFilter = BinaryErodeImageFilterType::New();
            erodeFilter->SetInput(movingImageMask->GetImage());
            erodeFilter->SetKernel(structuringElement);
            erodeFilter->SetErodeValue(0);
            erodeFilter->SetBackgroundValue(::itk::NumericTraits<typename MovingImageMaskImageType::PixelType>::max());
            erodeFilter->Update();

            auto dilatedImage = erodeFilter->GetOutput();
            using MovingImageMaskSOType = ::itk::ImageMaskSpatialObject< MovingImageType::ImageDimension >;
            typename MovingImageMaskSOType::Pointer newMask = MovingImageMaskSOType::New();
            newMask->SetImage(dilatedImage);
            this->setInternalMovingMask(newMask);
            os << "Moving mask: add margin with size (in mm): " << _margins << " (pixels: " << radius << ")";

          }
          else
          {
            os << "Moving mask: is not image based. No margins added.";
          }

          this->InvokeEvent(::map::events::AlgorithmEvent(this, os2.str()));

        }


        if (this->_ActivateBoundingBox)
        {
          this->_ActivateBoundingBox = true;
        }
        Superclass::prepPerpareInternalInputData();
      }

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      void
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      prepSetInternalInputData()
			{
				Superclass::prepSetInternalInputData();

				if (this->_ActivateBoundingBox)
				{
          //the internal moving and target images have already cropped to the bpunding box. This we only
          //have to deactivate the use of the mask.
          this->InvokeEvent(events::AlgorithmEvent(this, "Deactivate masks -> use bounding box instead."));
          typename MovingMaskBaseType::Pointer nullMMask;
          typename TargetMaskBaseType::Pointer nullTMask;

          this->getMetricInternal()->getImageToImageMetric()->SetMovingImageMask(nullMMask);
          this->getMetricInternal()->getImageToImageMetric()->SetFixedImageMask(nullTMask);
				}
			}

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      void
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
        infos.push_back(map::algorithm::MetaPropertyInfo::New("ActivateBoundingBox", typeid(bool), true, true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("ActivateMargins", typeid(bool), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Margin_X", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Margin_Y", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Margin_Z", typeid(double), true, true));
#endif
			}

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      typename ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::MetaPropertyPointer
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

        if (name == "ActivateBoundingBox")
        {
          spResult = map::core::MetaProperty<bool>::New(this->_ActivateBoundingBox);
        }
				else if (name == "ActivateMargins")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_ActivateMargin);
				}
				else if (name == "Margin_X")
				{
					spResult = map::core::MetaProperty<double>::New(this->_margins[0]);
				}
				else if (name == "Margin_Y")
				{
					spResult = map::core::MetaProperty<double>::New(this->_margins[1]);
				}
				else if (name == "Margin_Z")
				{
					spResult = map::core::MetaProperty<double>::New(this->_margins[2]);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;

			};

      template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
      void
      ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
      doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
        if (name == "ActivateBoundingBox")
        {
          bool activate;
          map::core::unwrapMetaProperty(pProperty, activate);
          this->_ActivateBoundingBox = activate;

          if (activate)
          {
            this->_CropInputImagesByMask = true;
          }
        }
        else if (name == "ActivateMargins")
				{
					bool activate;
					map::core::unwrapMetaProperty(pProperty, activate);
					this->_ActivateMargin = activate;
				}
				else if (name == "Margin_X")
				{
					double margin;
					map::core::unwrapMetaProperty(pProperty, margin);
					this->_margins[0] = margin;
				}
				else if (name == "Margin_Y")
				{
					double margin;
					map::core::unwrapMetaProperty(pProperty, margin);
					this->_margins[1] = margin;
				}
				else if (name == "Margin_Z")
				{
					double margin;
					map::core::unwrapMetaProperty(pProperty, margin);
					this->_margins[2] = margin;
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}

			};

		}
	}
}
