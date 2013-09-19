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

#ifndef __TEST_META_PROPERTY_ALGORITHM_H
#define __TEST_META_PROPERTY_ALGORITHM_H

#include "litValueRecorder.h"
#include "mapMetaPropertyAlgorithmBase.h"


namespace map
{
	namespace testing
	{
		class TestMetaPropertyAlgorithm : public map::algorithm::MetaPropertyAlgorithmBase
		{
		public:
			TestMetaPropertyAlgorithm()
			{
				_size = 2;
				_count = 100;
				_secret = 0.42;
				_text = "Dummy";
				_pHole = NULL;
			};


			enum FncCallID
			{
				compileInfosID = 0,
				doGetPropertyID = 1,
				doSetPropertyID = 2,
			};

			mutable ::lit::ValueRecorder<FncCallID> recorder;

			int _size;
			int _count;
			float _secret;
			std::string _text;
			void* _pHole;

			using map::algorithm::MetaPropertyAlgorithmBase::configureAlgorithmByMetaProperties;
			using map::algorithm::MetaPropertyAlgorithmBase::GetMTime;

		protected:

			virtual void compileInfos(MetaPropertyVectorType& infos) const
			{
				recorder.recordValue(compileInfosID);
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Size", typeid(int), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Count", typeid(int), true, false));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Text", typeid(std::string), true, false));
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("SecretIngredient", typeid(float), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("BlackHole", typeid(void*), false, true));
#endif
			};

			virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const
			{
				recorder.recordValue(doGetPropertyID);

				MetaPropertyPointer spResult;

				if (name == "Size")
				{
					spResult = map::core::MetaProperty<int>::New(_size);
				}
				else if (name == "Count")
				{
					spResult = map::core::MetaProperty<int>::New(_count);
				}
				else if (name == "Text")
				{
					spResult = map::core::MetaProperty<std::string>::New(_text);
				}
				else if (name == "SecretIngredient")
				{
					spResult = map::core::MetaProperty<float>::New(_secret);
				}

				return spResult;
			};

			virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				recorder.recordValue(doSetPropertyID);

				if (name == "Size")
				{
					map::core::unwrapMetaProperty(pProperty, _size);
				}
				else if (name == "SecretIngredient")
				{
					map::core::unwrapMetaProperty(pProperty, _secret);
				}
				else if (name == "BlackHole")
				{
					map::core::unwrapMetaProperty(pProperty, _pHole);
				}
			};
		};
	}
}
#endif