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


#ifndef __MAP_ELX_BSPLINE_CLI_REGISTRATION_ALGORITHM_TPP
#define __MAP_ELX_BSPLINE_CLI_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			ElxBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			ElxBSplineCLIRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			ElxBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			~ElxBSplineCLIRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ElxBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepParameterMaps()
			{
				this->_parameterMaps.clear();
				elastix::ParameterMapType map;
				/////////////////////////////////
				//Setup Stage 1: rigid
				/////////////////////////////////
				map["FixedInternalImagePixelType"] = elastix::ParamGenerator().addStr("float");
				map["MovingInternalImagePixelType"] = elastix::ParamGenerator().addStr("float");

				map["UseDirectionCosines"] = elastix::ParamGenerator().addStr("true");

				// **************** Main Components **************************
				map["Registration"] = elastix::ParamGenerator().addStr("MultiResolutionRegistration");
				map["Interpolator"] = elastix::ParamGenerator().addStr("BSplineInterpolator");
				map["ResampleInterpolator"] = elastix::ParamGenerator().addStr("FinalBSplineInterpolator");
				map["Resampler"] = elastix::ParamGenerator().addStr("DefaultResampler");

				map["FixedImagePyramid"] = elastix::ParamGenerator().addStr("FixedRecursiveImagePyramid");
				map["MovingImagePyramid"] = elastix::ParamGenerator().addStr("MovingRecursiveImagePyramid");

				map["Optimizer"] = elastix::ParamGenerator().addStr("AdaptiveStochasticGradientDescent");
				map["Transform"] = elastix::ParamGenerator().addStr("EulerTransform");
				map["Metric"] = elastix::ParamGenerator().addStr("AdvancedMattesMutualInformation");

				// ***************** Transformation **************************

				// Scales the rotations compared to the translations, to make
				// sure they are in the same range. In general, it's best to
				// use automatic scales estimation:
				map["AutomaticScalesEstimation"] = elastix::ParamGenerator().addStr("true");

				// Automatically guess an initial translation by aligning the
				// geometric centers of the fixed and moving.
				map["AutomaticTransformInitialization"] = elastix::ParamGenerator().addStr("true");

				// Whether transforms are combined by composition or by addition.
				// In generally, Compose is the best option in most cases.
				// It does not influence the results very much.
				map["HowToCombineTransforms"] = elastix::ParamGenerator().addStr("Compose");

				// ******************* Similarity measure *********************

				// Number of grey level bins in each resolution level,
				// for the mutual information. 16 or 32 usually works fine.
				// You could also employ a hierarchical strategy:
				//(NumberOfHistogramBins 16 32 64)
				map["NumberOfHistogramBins"] = elastix::ParamGenerator().add(32);

				// If you use a mask, this option is important.
				// If the mask serves as region of interest, set it to false.
				// If the mask indicates which pixels are valid, then set it to true.
				// If you do not use a mask, the option doesn't matter.
				map["ErodeMask"] = elastix::ParamGenerator().addStr("false");

				// ******************** Multiresolution **********************

				// The number of resolutions. 1 Is only enough if the expected
				// deformations are small. 3 or 4 mostly works fine. For large
				// images and large deformations, 5 or 6 may even be useful.
				map["NumberOfResolutions"] = elastix::ParamGenerator().add(4);

				// ******************* Optimizer ****************************

				// Maximum number of iterations in each resolution level:
				// 200-500 works usually fine for rigid registration.
				// For more robustness, you may increase this to 1000-2000.
				map["MaximumNumberOfIterations"] = elastix::ParamGenerator().add(250);

				// The step size of the optimizer, in mm. By default the voxel size is used.
				// which usually works well. In case of unusual high-resolution images
				// (eg histology) it is necessary to increase this value a bit, to the size
				// of the "smallest visible structure" in the image:
				//(MaximumStepLength 1.0)

				// **************** Image sampling **********************

				// Number of spatial samples used to compute the mutual
				// information (and its derivative) in each iteration.
				// With an AdaptiveStochasticGradientDescent optimizer,
				// in combination with the two options below, around 2000
				// samples may already suffice.
				map["NumberOfSpatialSamples"] = elastix::ParamGenerator().add(2048);

				// Refresh these spatial samples in every iteration, and select
				// them randomly. See the manual for information on other sampling
				// strategies.
				map["NewSamplesEveryIteration"] = elastix::ParamGenerator().addStr("true");
				map["ImageSampler"] = elastix::ParamGenerator().addStr("Random");

				// ************* Interpolation and Resampling ****************

				map["BSplineInterpolationOrder"] = elastix::ParamGenerator().add(1);
				map["FinalBSplineInterpolationOrder"] = elastix::ParamGenerator().add(3);

				map["DefaultPixelValue"] = elastix::ParamGenerator().add(0);

				map["WriteResultImage"] = elastix::ParamGenerator().addStr("false");

				this->_parameterMaps.push_back(map);

				/////////////////////////////////
				//Setup Stage 2: BSpline
				/////////////////////////////////
				map.clear();

				map["FixedInternalImagePixelType"] = elastix::ParamGenerator().addStr("float");
				map["MovingInternalImagePixelType"] = elastix::ParamGenerator().addStr("float");

				map["UseDirectionCosines"] = elastix::ParamGenerator().addStr("true");

				// **************** Main Components **************************

				map["Registration"] = elastix::ParamGenerator().addStr("MultiResolutionRegistration");
				map["Interpolator"] = elastix::ParamGenerator().addStr("BSplineInterpolator");
				map["ResampleInterpolator"] = elastix::ParamGenerator().addStr("FinalBSplineInterpolator");
				map["Resampler"] = elastix::ParamGenerator().addStr("DefaultResampler");

				map["FixedImagePyramid"] = elastix::ParamGenerator().addStr("FixedRecursiveImagePyramid");
				map["MovingImagePyramid"] = elastix::ParamGenerator().addStr("MovingRecursiveImagePyramid");

				map["Optimizer"] = elastix::ParamGenerator().addStr("AdaptiveStochasticGradientDescent");
				map["Transform"] = elastix::ParamGenerator().addStr("BSplineTransform");
				map["Metric"] = elastix::ParamGenerator().addStr("AdvancedMattesMutualInformation");

				// ***************** Transformation **************************

				// The control point spacing of the bspline transformation in
				// the finest resolution level. Can be specified for each
				// dimension differently. Unit: mm.
				// The lower this value, the more flexible the deformation.
				// Low values may improve the accuracy, but may also cause
				// unrealistic deformations. This is a very important setting!
				// We recommend tuning it for every specific application. It is
				// difficult to come up with a good 'default' value.
				map["FinalGridSpacingInPhysicalUnits"] = elastix::ParamGenerator().add(16);

				map["HowToCombineTransforms"] = elastix::ParamGenerator().addStr("Compose");

				// ******************* Similarity measure *********************

				map["NumberOfHistogramBins"] = elastix::ParamGenerator().add(32);

				map["ErodeMask"] = elastix::ParamGenerator().addStr("false");

				// ******************** Multiresolution **********************

				// The number of resolutions. 1 Is only enough if the expected
				// deformations are small. 3 or 4 mostly works fine. For large
				// images and large deformations, 5 or 6 may even be useful.
				map["NumberOfResolutions"] = elastix::ParamGenerator().add(4);

				// ******************* Optimizer ****************************

				// Maximum number of iterations in each resolution level:
				// 200-2000 works usually fine for nonrigid registration.
				// The more, the better, but the longer computation time.
				// This is an important parameter!
				map["MaximumNumberOfIterations"] = elastix::ParamGenerator().add(500);

				// **************** Image sampling **********************

				// Number of spatial samples used to compute the mutual
				// information (and its derivative) in each iteration.
				// With an AdaptiveStochasticGradientDescent optimizer,
				// in combination with the two options below, around 2000
				// samples may already suffice.
				map["NumberOfSpatialSamples"] = elastix::ParamGenerator().add(2048);

				// Refresh these spatial samples in every iteration, and select
				// them randomly. See the manual for information on other sampling
				// strategies.
				map["NewSamplesEveryIteration"] = elastix::ParamGenerator().addStr("true");
				map["ImageSampler"] = elastix::ParamGenerator().addStr("Random");

				// ************* Interpolation and Resampling ****************

				map["BSplineInterpolationOrder"] = elastix::ParamGenerator().add(1);
				map["FinalBSplineInterpolationOrder"] = elastix::ParamGenerator().add(3);

				map["DefaultPixelValue"] = elastix::ParamGenerator().add(0);
				map["WriteResultImage"] = elastix::ParamGenerator().addStr("true");

				// The pixel type and format of the resulting deformed moving image
				map["ResultImagePixelType"] = elastix::ParamGenerator().addStr("short");
				map["ResultImageFormat"] = elastix::ParamGenerator().addStr("mhd");

				this->_parameterMaps.push_back(map);
			}

		} // end namespace boxed
	} // end namespace algorithm
} // end namespace map

#endif
