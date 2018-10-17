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


#ifndef __JOM_PLM_BSPLINE_CLI_REGISTRATION_ALGORITHM_TPP
#define __JOM_PLM_BSPLINE_CLI_REGISTRATION_ALGORITHM_TPP

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			JOMPlmBSplineCLIRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			~JOMPlmBSplineCLIRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			void
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			configureAlgorithm()
			{
        Superclass::configureAlgorithm();
				if (this->isFirstConfiguration())
				{
          _alignCenter = true;
          _s1_maxIterations = 30;
          _s1_subsampling = "4 4 2";
          _s2_maxIterations = 50;
          _s2_subsampling = "4 4 4";
          _s2_gridSpacing = "35 35 35";
          _s2_regularization = 0.005;
          _doStage3 = true;
          _s3_maxIterations = 100;
          _s3_subsampling = "2 2 2";
          _s3_gridSpacing = "11 11 11";
          _s3_regularization = 0.005;
				}
			};

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			void
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			compileInfos(MetaPropertyVectorType& infos) const
      {
        Superclass::compileInfos(infos);

#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("EnableStage_0", typeid(bool), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage1.MaxIterations", typeid(unsigned int), true,
								true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage1.SubsamplingFactor", typeid(map::core::String),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage2.MaxIterations", typeid(unsigned int), true,
								true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage2.SubsamplingFactor", typeid(map::core::String),
								true, true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage2.GridSpacing", typeid(map::core::String),
								true, true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage2.RegularizationLambda", typeid(double),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("EnableStage_3", typeid(bool), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage3.MaxIterations", typeid(unsigned int), true,
								true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage3.SubsamplingFactor", typeid(map::core::String),
								true, true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage3.GridSpacing", typeid(map::core::String),
								true, true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("Stage3.RegularizationLambda", typeid(double),
								true, true));
#endif
      };

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			typename JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::MetaPropertyPointer
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
      {
				MetaPropertyPointer spResult;

				if (name == "EnableStage_0")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_alignCenter);
				}
				else if (name == "Stage1.MaxIterations")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(this->_s1_maxIterations);
				}
				else if (name == "Stage1.SubsamplingFactor")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_s1_subsampling);
				}
				else if (name == "Stage2.MaxIterations")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(this->_s2_maxIterations);
				}
				else if (name == "Stage2.SubsamplingFactor")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_s2_subsampling);
				}
				else if (name == "Stage2.GridSpacing")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_s2_gridSpacing);
				}
				else if (name == "Stage2.RegularizationLambda")
				{
					spResult = map::core::MetaProperty<double>::New(this->_s2_regularization);
				}
				else if (name == "EnableStage_3")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_doStage3);
				}
				else if (name == "Stage3.MaxIterations")
				{
					spResult = map::core::MetaProperty<unsigned int>::New(this->_s3_maxIterations);
				}
				else if (name == "Stage3.SubsamplingFactor")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_s3_subsampling);
				}
				else if (name == "Stage3.GridSpacing")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_s3_gridSpacing);
				}
				else if (name == "Stage3.RegularizationLambda")
				{
					spResult = map::core::MetaProperty<double>::New(this->_s3_regularization);
				}
        else
				{
					spResult = Superclass::doGetProperty(name);
        }

				return spResult;
      };

			template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			void
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
      doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
      {
				if (name == "EnableStage_0")
				{
					bool enable;
					map::core::unwrapMetaProperty(pProperty, enable);
					this->_alignCenter = enable;
				}
				else if (name == "Stage1.MaxIterations")
				{
					unsigned int iterations;
					map::core::unwrapMetaProperty(pProperty, iterations);
					this->_s1_maxIterations = iterations;
				}
				else if (name == "Stage1.SubsamplingFactor")
				{
					core::String factorStr;
					map::core::unwrapMetaProperty(pProperty, factorStr);
					this->_s1_subsampling = factorStr;
				}
				else if (name == "Stage2.MaxIterations")
				{
					unsigned int iterations;
					map::core::unwrapMetaProperty(pProperty, iterations);
					this->_s2_maxIterations = iterations;
				}
				else if (name == "Stage2.SubsamplingFactor")
				{
					core::String factorStr;
					map::core::unwrapMetaProperty(pProperty, factorStr);
					this->_s2_subsampling = factorStr;
				}
				else if (name == "Stage2.GridSpacing")
				{
					core::String gridStr;
					map::core::unwrapMetaProperty(pProperty, gridStr);
					this->_s2_gridSpacing = gridStr;
				}
				else if (name == "Stage2.RegularizationLambda")
				{
					double lambda;
					map::core::unwrapMetaProperty(pProperty, lambda);
					this->_s2_regularization = lambda;
				}
				else if (name == "EnableStage_3")
				{
					bool enable;
					map::core::unwrapMetaProperty(pProperty, enable);
					this->_doStage3 = enable;
				}
				else if (name == "Stage3.MaxIterations")
				{
					unsigned int iterations;
					map::core::unwrapMetaProperty(pProperty, iterations);
					this->_s2_maxIterations = iterations;
				}
				else if (name == "Stage3.SubsamplingFactor")
				{
					core::String factorStr;
					map::core::unwrapMetaProperty(pProperty, factorStr);
					this->_s3_subsampling = factorStr;
				}
				else if (name == "Stage3.GridSpacing")
				{
					core::String gridStr;
					map::core::unwrapMetaProperty(pProperty, gridStr);
					this->_s3_gridSpacing = gridStr;
				}
				else if (name == "Stage3.RegularizationLambda")
				{
					double lambda;
					map::core::unwrapMetaProperty(pProperty, lambda);
					this->_s3_regularization = lambda;
				}
        else
				{
					Superclass::doSetProperty(name,pProperty);
				}
      }

      template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
			void
			JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>::
			prepConfigurationPLM()
			{
				this->_configurationPLM.clear();
				this->_configurationPLM.push_back(
					algorithm::plastimatch::ParameterStageType()); //add global section, will be filled by base class

				algorithm::plastimatch::ParameterStageType map;
				/////////////////////////////////
				//Setup Stage 0: align center
				/////////////////////////////////
        if (this->_alignCenter)
        {
				  map["xform"] = plastimatch::ParamGenerator().add("align_center");
				  this->_configurationPLM.push_back(map);
        }
        /////////////////////////////////
				//Setup Stage 1: rigid
				/////////////////////////////////
				map.clear();
				map["metric"] = plastimatch::ParamGenerator().add("mse");
				map["xform"] = plastimatch::ParamGenerator().add("rigid");
				map["optim"] = plastimatch::ParamGenerator().add("versor");
				map["impl"] = plastimatch::ParamGenerator().add("itk");
        map["max_its"] = plastimatch::ParamGenerator().add(this->_s1_maxIterations);
				map["res"] = plastimatch::ParamGenerator().add(this->_s1_subsampling);
				this->_configurationPLM.push_back(map);

				/////////////////////////////////
				//Setup Stage 2: BSpline
				/////////////////////////////////
				map.clear();
				map["xform"] = plastimatch::ParamGenerator().add("bspline");
				map["optim"] = plastimatch::ParamGenerator().add("lbfgsb");
				map["impl"] = plastimatch::ParamGenerator().add("plastimatch");
				map["threading"] = plastimatch::ParamGenerator().add("openmp");
				map["metric"] = plastimatch::ParamGenerator().add("mse");
        map["max_its"] = plastimatch::ParamGenerator().add(this->_s2_maxIterations);
        map["regularization_lambda"] = plastimatch::ParamGenerator().add(this->_s2_regularization);
				map["res"] = plastimatch::ParamGenerator().add(this->_s2_subsampling);
				map["grid_spac"] = plastimatch::ParamGenerator().add(this->_s2_gridSpacing);
				this->_configurationPLM.push_back(map);

				/////////////////////////////////
				//Setup Stage 3: BSpline 2
				/////////////////////////////////
        if(this->_doStage3)
        {
				  map.clear();
          map["max_its"] = plastimatch::ParamGenerator().add(this->_s3_maxIterations);
          map["regularization_lambda"] = plastimatch::ParamGenerator().add(this->_s3_regularization);
				  map["res"] = plastimatch::ParamGenerator().add(this->_s3_subsampling);
				  map["grid_spac"] = plastimatch::ParamGenerator().add(this->_s3_gridSpacing);
				  this->_configurationPLM.push_back(map);
        }
			}

		} // end namespace boxed
	} // end namespace algorithm
} // end namespace map

#endif
