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


#ifndef __MAP_ITK_RIGID_MMI_BOUNDINGBOX_REGISTRATION_ALGORITHM_H
#define __MAP_ITK_RIGID_MMI_BOUNDINGBOX_REGISTRATION_ALGORITHM_H

#include "mapITKEuler3DMattesMIMultiResRegistrationAlgorithmTemplate.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
				/** \class ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm
				* \ingroup Data_image MetaProperty Model_rigid Det_comp_iterative Det_stochastic Det_res_multi Dim_3D_3D Mod_multi PreInit_Geo
				* Algorithm is used for special cases where a head image should be registered onto a head/neck image (target image). It skips the lower part of
					* the target image if a preinitialization (via geometric center or centroid) is used, to establish a better initialization. By default initializes via geometric centers.
				*/
      template <class TImageType, 
        class TIdentificationPolicy, 
        class TInterpolatorPolicy =
        SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TImageType, map::core::continuous::ScalarType> >,
        class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy>
				class ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm :
					public map::algorithm::boxed::ITKEuler3DMattesMIMultiResRegistrationAlgorithm<TImageType, TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>
				{
				public:
					typedef ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm Self;

          typedef ITKEuler3DMattesMIMultiResRegistrationAlgorithm<TImageType, TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy> Superclass;

					typedef ::itk::SmartPointer<Self> Pointer;
					typedef ::itk::SmartPointer<const Self> ConstPointer;

					typedef typename Superclass::MetaPropertyType MetaPropertyType;
					typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
					typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
					typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;
					typedef typename Superclass::ConcreteOptimizerType::ScalesType ScalesType;

					using MovingImageType = typename Superclass::MovingImageType;
					using TargetImageType = typename Superclass::TargetImageType;

					using MaskRegistrationAlgorithmBaseType = MaskedRegistrationAlgorithmBase<TImageType::ImageDimension, TImageType::ImageDimension>;
					using MovingMaskBaseType = typename MaskRegistrationAlgorithmBaseType::MovingMaskBaseType;
					using TargetMaskBaseType = typename MaskRegistrationAlgorithmBaseType::TargetMaskBaseType;

					itkTypeMacro(ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm,
								 ITKEuler3DMattesMIMultiResRegistrationAlgorithm);
					mapNewAlgorithmMacro(Self);

          mapSetMetaMacro(ActivateBoundingBox, bool);
          mapSetMetaMacro(ActivateMargin, bool);
          mapGetMetaMacro(ActivateBoundingBox, bool);
          mapGetMetaMacro(ActivateMargin, bool);

				protected:
					ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm();
					virtual ~ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm();

          void configureAlgorithm() override;
					void doInterLevelSetup() override;
          void prepPerpareInternalInputData() override;
          void prepSetInternalInputData() override;

          void compileInfos(MetaPropertyVectorType& infos) const override;
          MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const override;
          void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty) override;

          bool _ActivateBoundingBox;
          bool _ActivateMargin;

          /**Margins that should be used to dilate masks/bounding boxes in mm (per side). E.G. 3 mm margin in 1st dimension will make the bounding box
          bigger by 6 mm.*/
          ::itk::FixedArray<double, 3> _margins;
				private:

					ITKRigid3DMattesMIBoundingBoxRegistrationAlgorithm(const Self& source);  //purposely not implemented
					void operator=(const Self&); //purposely not implemented
				};
		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKRigid3DMattesMIBoundingBoxRegistrationAlgorithmTemplate.tpp"
#endif


#endif
