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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm.h $
*/




#ifndef __ITK_FAST_SYMMETRIC_FORCES_DEMONS_MULTI_RES_REGISTRATION_ALGORITHM_H
#define __ITK_FAST_SYMMETRIC_FORCES_DEMONS_MULTI_RES_REGISTRATION_ALGORITHM_H

#include "itkFastSymmetricForcesDemonsRegistrationFilter.h"

#include "mapSealedImagePyramidesPolicy.h"
#include "mapITKMultiResPDEDeformableRegistrationAlgorithm.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			/*! @class ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm
			@brief The class implements an multi level approach based on ITK Fast Symmetric Forces Demons deformable registration algorithm.
			@ingroup Algorithms
			@ingroup ITK
			*/
			template < class TImageType,
					 class TIdentificationPolicy,
                     class TDisplacementField = typename core::discrete::Elements<TImageType::ImageDimension>::VectorFieldType,
					 class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy >
			class ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm :
				public itk::ITKMultiResPDEDeformableRegistrationAlgorithm < TImageType, TIdentificationPolicy,
				::itk::FastSymmetricForcesDemonsRegistrationFilter<TImageType, TImageType, TDisplacementField>,
				 TDisplacementField,
				 SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TImageType, TImageType>, ::itk::MultiResolutionPyramidImageFilter<TImageType, TImageType>, TPyramideInitializationPolicy >
				 >
			{
			public:
				typedef ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm
				< TImageType, TIdentificationPolicy, TDisplacementField, TPyramideInitializationPolicy > Self;
				typedef itk::ITKMultiResPDEDeformableRegistrationAlgorithm < TImageType, TIdentificationPolicy,
						::itk::FastSymmetricForcesDemonsRegistrationFilter<TImageType, TImageType, TDisplacementField>,
						TDisplacementField,
						SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TImageType, TImageType>, ::itk::MultiResolutionPyramidImageFilter<TImageType, TImageType>, TPyramideInitializationPolicy >
						>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm,
							 ITKMultiResPDEDeformableRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef typename
				IterativeRegistrationAlgorithm<TImageType::ImageDimension, TImageType::ImageDimension>::OptimizerMeasureType
				OptimizerMeasureType;

                typedef typename Superclass::TargetImageType TargetImageType;
                typedef typename Superclass::MovingImageType MovingImageType;
                typedef typename Superclass::MovingImageConstPointer MovingImageConstPointer;
                typedef typename Superclass::TargetImageConstPointer TargetImageConstPointer;

                typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
                typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

                typedef typename Superclass::RegistrationPointer RegistrationPointer;
                typedef typename Superclass::RegistrationType RegistrationType;
                typedef typename Superclass::FieldRepRequirement FieldRepRequirement;
                typedef typename Superclass::IterationCountType IterationCountType;

                typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
                typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
                typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;
                typedef typename Superclass::MetaPropertyType MetaPropertyType;

			protected:
				ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm();
				virtual ~ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm();

				/*! @reimplemented*/
				virtual void configureAlgorithm();

				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

				virtual void doInterLevelSetup();

				typedef ::itk::Array<double> ValueArrayType;
        typedef ::itk::Array<int> IntValueArrayType;

				ValueArrayType _lvlIntensityDifferenceThreshold;
				ValueArrayType _lvlMaximumUpdateStepLength;
				IntValueArrayType _lvlUseGradientType;

			private:
				ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm.tpp"
#endif

#endif
