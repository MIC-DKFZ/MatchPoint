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


//Elastix
#include "ParameterFileParser\itkParameterFileParser.h"

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

			void saveParameterMapToFile(const ParameterMapType& parameterMap, const map::core::String& filePath)
			{
				std::ofstream file;

				std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
				file.open(filePath.c_str(), iOpenFlag);

				if (!file.is_open())
				{
					mapDefaultExceptionStaticMacro( << "Cannot open or create parameter map file to save. File path: "
													<< filePath);
				}

				for (const auto & pos : parameterMap)
				{
					file << "(" << pos.first;

					for (auto valPos = pos.second.begin(); valPos != pos.second.end();
						 ++valPos)
					{
						file << " " << *valPos;
					}

					file << ")\n";
				}

				file.close();
			};


      ParameterMapType readParameterMapFromFile(const map::core::String& fileName)
      {
        itk::ParameterFileParser::Pointer spParser = itk::ParameterFileParser::New();
        spParser->SetParameterFileName(fileName);
        spParser->ReadParameterFile();
        return spParser->GetParameterMap();
      };

			ParamGenerator::ParamGenerator()
			= default;

			ParamGenerator::~ParamGenerator()
			= default;

			ParamGenerator&
			ParamGenerator::
			addStr(const core::String& value)
			{
				this->_values.push_back("\"" + value + "\"");
				return *this;
			}

			ParamGenerator::
			operator ParameterValuesType()
			{
				return this->_values;
			}

		}  // namespace elastix
	}  // namespace algorithm
}  // namespace map
