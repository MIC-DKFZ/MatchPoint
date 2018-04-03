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


#ifndef __MAP_PLM_BSPLINE_CLI_REGISTRATION_ALGORITHM_TPP
#define __MAP_PLM_BSPLINE_CLI_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			PlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			PlmBSplineCLIRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			PlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			~PlmBSplineCLIRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			void
			PlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			prepConfigurationPLM()
			{
				this->_configurationPLM.clear();
				this->_configurationPLM.push_back(
					::map::algorithm::plastimatch::ParameterStageType()); //add global section, will be filled by base class

				::map::algorithm::plastimatch::ParameterStageType map;
				/////////////////////////////////
				//Setup Stage 1: rigid
				/////////////////////////////////
				map["metric"] = plastimatch::ParamGenerator().add("mi");
				map["xform"] = plastimatch::ParamGenerator().add("translation");
				map["optim"] = plastimatch::ParamGenerator().add("rsg");
				map["impl"] = plastimatch::ParamGenerator().add("itk");
				map["max_its"] = plastimatch::ParamGenerator().add(300);
				map["convergence_tol"] = plastimatch::ParamGenerator().add(1);
				map["grad_tol"] = plastimatch::ParamGenerator().add(1.5);
				map["res"] = plastimatch::ParamGenerator().add(4).add(4).add(4);
				this->_configurationPLM.push_back(map);

				/////////////////////////////////
				//Setup Stage 2: BSpline
				/////////////////////////////////
				map.clear();
				map["metric"] = plastimatch::ParamGenerator().add("mi");
				map["xform"] = plastimatch::ParamGenerator().add("bspline");
				map["optim"] = plastimatch::ParamGenerator().add("lbfgsb");
				map["impl"] = plastimatch::ParamGenerator().add("plastimatch");
				map["threading"] = plastimatch::ParamGenerator().add("cuda");
				map["max_its"] = plastimatch::ParamGenerator().add(300);
				map["convergence_tol"] = plastimatch::ParamGenerator().add(5);
				map["grad_tol"] = plastimatch::ParamGenerator().add(1.5);
				map["regularization_lambda"] = plastimatch::ParamGenerator().add(0.0005);
				map["res"] = plastimatch::ParamGenerator().add(2).add(2).add(2);
				map["grid_spac"] = plastimatch::ParamGenerator().add(20).add(20).add(20);
				this->_configurationPLM.push_back(map);

				/////////////////////////////////
				//Setup Stage 3: BSpline 2
				/////////////////////////////////
				map.clear();
				map["max_its"] = plastimatch::ParamGenerator().add(300);
				map["regularization_lambda"] = plastimatch::ParamGenerator().add(0.0005);
				map["res"] = plastimatch::ParamGenerator().add(1).add(1).add(1);
				map["grid_spac"] = plastimatch::ParamGenerator().add(5).add(5).add(5);
				this->_configurationPLM.push_back(map);
			}

		} // end namespace boxed
	} // end namespace algorithm
} // end namespace map

#endif
