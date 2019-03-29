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


#ifndef __MAP_ITK_INITIALIZING_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_H
#define __MAP_ITK_INITIALIZING_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_H

#include "mapITKMultiResImageRegistrationAlgorithm.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			mapGenerateAlgorithmUIDPolicyMacro(DefaultITKInitializingMultiResImageRegistrationUIDPolicy,
											   "MatchPoint.ITK", "ITKInitializedMultiResImageRegistrationAlgorithm.default", "1.0.0", "");

			template < class TMovingImage, class TTargetImage,
					 class TUIDPolicy = DefaultITKInitializingMultiResImageRegistrationUIDPolicy,
					 class TInterpolatorPolicy =
					 itk::ArbitraryInterpolatorPolicy<TMovingImage, core::continuous::ScalarType>,
					 class TMetricPolicy = itk::ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>,
					 class TOptimizerPolicy = itk::ArbitrarySVNLOptimizerPolicy,
					 class TTransformPolicy =
					 itk::ArbitraryTransformPolicy< ::map::core::continuous::ScalarType, TMovingImage::ImageDimension, TTargetImage::ImageDimension>,
					 class TPyramidesPolicy = ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> >
			class ITKInitializedMultiResImageRegistrationAlgorithm :
				public algorithm::itk::ITKMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage,
				TUIDPolicy,
				TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy >
			{
			public:
				typedef ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
						TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy > Self;

				typedef typename algorithm::itk::ITKMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage,
						TUIDPolicy,
						TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy,
						TPyramidesPolicy >  Superclass;

				using Pointer = ::itk::SmartPointer<Self>;
				using ConstPointer = ::itk::SmartPointer<const Self>;

				itkTypeMacro(ITKInitializedMultiResImageRegistrationAlgorithm,
							 ITKMultiResImageRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				using ParametersType = ::itk::Array<double>;

				using MetaPropertyType = typename Superclass::MetaPropertyType;
				using MetaPropertyPointer = typename Superclass::MetaPropertyPointer;
				using MetaPropertyNameType = typename Superclass::MetaPropertyNameType;
				using MetaPropertyVectorType = typename Superclass::MetaPropertyVectorType;

			protected:
				ITKInitializedMultiResImageRegistrationAlgorithm();
				virtual ~ITKInitializedMultiResImageRegistrationAlgorithm();

				virtual void configureAlgorithm();

				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

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

				ITKInitializedMultiResImageRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}  // namespace boxed
	}  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKInitializedMultiResImageRegistrationAlgorithm.tpp"
#endif

#endif
