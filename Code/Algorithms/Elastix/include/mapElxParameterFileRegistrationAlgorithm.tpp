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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Elastix/include/mapElxParameterFileRegistrationAlgorithm.tpp $
*/


#ifndef __MAP_ELX_PARAMETERFILE_REGISTRATION_ALGORITHM_TPP
#define __MAP_ELX_PARAMETERFILE_REGISTRATION_ALGORITHM_TPP

//Elastix
#include "itkParameterFileParser.h"

namespace map
{
	namespace algorithm
	{
		namespace elastix
		{

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			ParameterFileRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			~ParameterFileRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			configureAlgorithm()
			{
				if (this->isFirstConfiguration())
				{
					Superclass::configureAlgorithm();
					_parameterFilePath = "";
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			compileInfos(MetaPropertyVectorType &infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("ParameterFilePath", typeid(map::core::String), true, true));
#endif
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::MetaPropertyPointer
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetProperty(const MetaPropertyNameType &name) const
			{
				MetaPropertyPointer spResult;

				if (name == "ParameterFilePath")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_parameterFilePath);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
			{
				if (name == "ParameterFilePath")
				{
					core::String path;
					map::core::unwrapMetaProperty(pProperty, path);
					this->_parameterFilePath = path;
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepParameterMaps()
			{
				itk::ParameterFileParser::Pointer spParser = itk::ParameterFileParser::New();
				spParser->SetParameterFileName(this->_parameterFilePath);
				spParser->ReadParameterFile();
				ParameterMapType map = spParser->GetParameterMap();
				this->_parameterMaps.clear();
				this->_parameterMaps.push_back(map);
			}

		} // end namespace elastix
	} // end namespace algorithm
} // end namespace map

#endif
