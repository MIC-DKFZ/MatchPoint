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




#ifndef __MAP_PLM_ALGORITHM_HELPER_H
#define __MAP_PLM_ALGORITHM_HELPER_H


//MatchPoint
#include "mapContinuous.h"
#include "mapString.h"
#include "mapConvert.h"
#include "mapMAPAlgorithmsPlastimatchExports.h"

namespace map
{
	namespace algorithm
	{
		namespace plastimatch
		{

			typedef core::String ParameterValueType;
			typedef core::String ParameterNameType;
			typedef std::vector<ParameterValueType> ParameterValuesType;
			typedef std::map<ParameterNameType, ParameterValuesType> ParameterStageType;
			typedef std::vector<ParameterStageType> ConfigurationType;

			/**! Helper function that stores the passed configuration to the given file path.
			  If the file already exists it is overwritten. The configuration is stored
				in the plastimatch format: "<ParameterName>=<Value1> [<Value2> [...]]).\n
				It is assumed that the first element of the configuration is the global configuration.
				All other elements are the stages settings.
				@pre param config must have at least to elements (global and stage 1).*/
			MAPAlgorithmsPlastimatch_EXPORT void saveConfigurationToFile(const ConfigurationType& config,
					const map::core::String& fileName);

			/**! Helper function that loads a configuration from a given file path.*/
			MAPAlgorithmsPlastimatch_EXPORT ConfigurationType loadConfigurationFromFile(
				const map::core::String& fileName);


			class MAPAlgorithmsPlastimatch_EXPORT ParamGenerator
			{
			public:
				ParamGenerator();
				~ParamGenerator();

				template <typename TElement>
				ParamGenerator& add(const TElement& value)
				{
					this->_values.push_back(::map::core::convert::toStrGeneric(value));
					return *this;
				};

				operator ParameterValuesType();

			protected:
				ParameterValuesType _values;
			};
		}
	}
}

#endif
