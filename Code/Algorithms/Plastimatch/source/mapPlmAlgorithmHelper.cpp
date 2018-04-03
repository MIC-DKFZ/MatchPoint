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



#include <itksys/SystemTools.hxx>

//MatchPoint
#include "mapPlmAlgorithmHelper.h"
#include "mapString.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace plastimatch
		{


			void saveConfigurationToFile(const ConfigurationType& config, const map::core::String& fileName)
			{
				if (config.size() < 2)
				{
					mapDefaultExceptionStaticMacro( <<
													"Cannot save configuration. Config seems to be invalid, containing less then two parts (GLOBAL and one STAGE is mandatory). File path: "
													<< fileName);
				}

				std::ofstream file;

				std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
				file.open(fileName.c_str(), iOpenFlag);

				if (!file.is_open())
				{
					mapDefaultExceptionStaticMacro( << "Cannot open or create parameter map file to save. File path: "
													<< fileName);
				}

				for (ConfigurationType::const_iterator stagePos = config.begin(); stagePos != config.end();
					 ++stagePos)
				{
					if (stagePos == config.begin())
					{
						file << "[GLOBAL]" << std::endl;
					}
					else
					{
						file << "[STAGE]" << std::endl;
					}

					for (ParameterStageType::const_iterator pos = stagePos->begin(); pos != stagePos->end(); ++pos)
					{
						file << pos->first << "=";

						for (ParameterValuesType::const_iterator posValues = pos->second.begin();
							 posValues != pos->second.end(); ++posValues)
						{
							if (posValues != pos->second.begin())
							{
								file << " ";
							}

							file << *posValues;
						}

						file << std::endl;
					}
				}

				file.close();
			};

			ConfigurationType loadConfigurationFromFile(const map::core::String& fileName)
			{
				ConfigurationType result;
				ParameterStageType stage;

				std::ifstream parameterFile;

				parameterFile.open(fileName.c_str(), std::fstream::in);

				if (!parameterFile.is_open())
				{
					mapDefaultExceptionStaticMacro( << "ERROR: could not open " << fileName	<< " for reading.");
				}

				::map::core::String line = "";

				while (parameterFile.good())
				{
					/** Extract a line. */
					if (itksys::SystemTools::GetLineFromStream(parameterFile, line))
					{
						if (line.find("[STAGE]") != core::String::npos)
						{
							//change the stage
							result.push_back(stage);
							stage.clear();
						}
						else
						{
							std::vector<itksys::String> valueTemp = itksys::SystemTools::SplitString(line.c_str(), '=');

							if (valueTemp.size() > 1)
							{
								// ok we have a parameter line, so don't ignore. Everything else would/should be an empty line, comment or [GLOBAL]
								if (valueTemp.size() != 2)
								{
									// there only should be two lines, everything else means more then one '=' thus is strange
									mapDefaultExceptionStaticMacro( <<
																	"ERROR: invalid configuration file. Seems to be more then one '=' per line. Invalid line" << line);
								}

								ParameterNameType name = valueTemp[0];
								valueTemp = itksys::SystemTools::SplitString(valueTemp[1].c_str(), ' ');
								ParameterValuesType values;

								for (std::vector<itksys::String>::iterator pos = valueTemp.begin(); pos != valueTemp.end(); ++pos)
								{
									values.push_back(*pos);
								}

								stage.insert(std::make_pair(name, values));
							}
						}
					}
				}

				result.push_back(stage); //add the last active stage

				parameterFile.close();

				return result;
			};

			ParamGenerator::ParamGenerator()
			{
			}

			ParamGenerator::~ParamGenerator()
			{
			}

			ParamGenerator::
			operator ParameterValuesType()
			{
				return this->_values;
			}

		}
	}
}
