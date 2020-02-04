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


#ifndef __MAP_ELX_PARAMETERFILE_REGISTRATION_ALGORITHM_TPP
#define __MAP_ELX_PARAMETERFILE_REGISTRATION_ALGORITHM_TPP

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
          _parameterFilePath2 = "";
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("ParameterFilePath",
								typeid(map::core::String), true, true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("ParameterFilePath_2",
          typeid(map::core::String), true, true));
#endif
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::MetaPropertyPointer
			ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "ParameterFilePath")
				{
					spResult = map::core::MetaProperty<map::core::String>::New(this->_parameterFilePath);
				}
        else if (name == "ParameterFilePath_2")
        {
          spResult = map::core::MetaProperty<map::core::String>::New(this->_parameterFilePath2);
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
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "ParameterFilePath")
				{
					core::String path;
					map::core::unwrapMetaProperty(pProperty, path);
					this->_parameterFilePath = path;
				}
        if (name == "ParameterFilePath_2")
        {
          core::String path;
          map::core::unwrapMetaProperty(pProperty, path);
          this->_parameterFilePath2 = path;
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
				this->_parameterMaps.clear();

        if (!this->_parameterFilePath.empty())
        {
          ParameterMapType map = readParameterMapFromFile(this->_parameterFilePath);
          this->_parameterMaps.push_back(map);
        }

        if (!this->_parameterFilePath2.empty())
        {
          ParameterMapType map = readParameterMapFromFile(this->_parameterFilePath2);
          this->_parameterMaps.push_back(map);
        }
			}

		} // end namespace elastix
	} // end namespace algorithm
} // end namespace map

#endif
