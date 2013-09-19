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




#ifndef __MAP_ELX_ALGORITHM_HELPER_H
#define __MAP_ELX_ALGORITHM_HELPER_H

//Elastix
#include "itkParameterFileParser.h"

//MatchPoint
#include "mapContinuous.h"
#include "mapString.h"
#include "mapConvert.h"
#include "mapMAPAlgorithmsElastixExports.h"

namespace map
{
	namespace algorithm
	{
		namespace elastix
		{

			typedef ::itk::ParameterFileParser::ParameterMapType ParameterMapType;
			typedef ::itk::ParameterFileParser::ParameterValuesType ParameterValuesType;

			/**! Helper function that stores the passed parameter map to the given file path.
			  If the file already exists it is overwritten. The parameter map is stored
				in the elastix format: (<ParameterName> <Value1> [<Value2> [...]]).*/
			MAPAlgorithmsElastix_EXPORT void saveParameterMapToFile(const ParameterMapType& parameterMap,
					const map::core::String& fileName);

			class MAPAlgorithmsElastix_EXPORT ParamGenerator
			{
			public:
				ParamGenerator();
				~ParamGenerator();

				ParamGenerator& addStr(const core::String& value);

				template <typename TElement>
				ParamGenerator& add(const TElement& value)
				{
					this->_values.push_back(core::convert::toStrGeneric(value));
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
