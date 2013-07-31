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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Elastix/source/mapElxAlgorithmHelper.cpp $
*/



//MatchPoint
#include "mapElxAlgorithmHelper.h"
#include "mapString.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace elastix
		{

			void saveParameterMapToFile(const ParameterMapType &parameterMap, const map::core::String &filePath)
			{
				std::ofstream file;

				std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
				file.open(filePath.c_str(), iOpenFlag);

				if (!file.is_open())
				{
					mapDefaultExceptionStaticMacro( << "Cannot open or create parameter map file to save. File path: " << filePath);
				}

				for (ParameterMapType::const_iterator pos = parameterMap.begin(); pos != parameterMap.end(); ++pos)
				{
					file << "(" << pos->first;

					for (ParameterValuesType::const_iterator valPos = pos->second.begin(); valPos != pos->second.end(); ++valPos)
					{
						file << " " << *valPos;
					}

					file << ")\n";
				}

				file.close();
			};

			ParamGenerator::ParamGenerator()
			{
			}

			ParamGenerator::~ParamGenerator()
			{
			}

			ParamGenerator &
			ParamGenerator::
			addStr(const core::String &value)
			{
				this->_values.push_back("\"" + value + "\"");
				return *this;
			}

			ParamGenerator::
			operator ParameterValuesType()
			{
				return this->_values;
			}

		}
	}
}
