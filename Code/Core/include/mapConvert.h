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


#ifndef __MAP_CONVERT_H
#define __MAP_CONVERT_H

#include <vector>

#include "mapString.h"
#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		namespace convert
		{
			MAPCore_EXPORT String toStr(const double& value, const int precision = 10);
			MAPCore_EXPORT String toStr(const float& value, const int precision = 10);
			MAPCore_EXPORT String toStr(const bool& value);
			MAPCore_EXPORT String toStr(const int& value);
			MAPCore_EXPORT String toStr(const unsigned int& value);
			MAPCore_EXPORT String toStr(const long& value);
			MAPCore_EXPORT String toStr(const unsigned long& value);

			/** This function only passes the sting through. Nothing will be changed.
			* It is needed by some template classes to handle the strings like every other
			* simple type*/
			MAPCore_EXPORT String toStr(const String& value);

			/**Helper function for types that should be converted and do not need special
			* conversion handling or are unkown when writing the code e.g. std::size_type*/
			template <typename TElement>
			String toStrGeneric(const TElement& value)
			{
				String sResult;
				OStringStream stream;

				stream << value;

				sResult = stream.str();
				return sResult;
			};

			MAPCore_EXPORT double toDouble(const String& value);
			MAPCore_EXPORT bool isADouble(const String& value);

			MAPCore_EXPORT float toFloat(const String& value);

			MAPCore_EXPORT int toInt(const String& value);
			MAPCore_EXPORT bool isAInt(const String& value);

			MAPCore_EXPORT unsigned int toUInt(const String& value);

			MAPCore_EXPORT long toLong(const String& value);
			MAPCore_EXPORT bool isALong(const String& value);

			MAPCore_EXPORT unsigned long toULong(const String& value);

			MAPCore_EXPORT bool toBool(const String& value);

			/**Helper function for types that should be converted into and do not need special
			* conversion handling or are unkown when writing the code e.g. std::size_type*/
			template <typename TElement>
			TElement toValueGeneric(const String& value)
			{
				TElement result;
				IStringStream strstrm(value);
				strstrm >> result;
				return result;
			};

			/** Converts a std::vector in any type based on itk::Array
			* @param v Reference to the data source (vector)
			* @return Array containing the values*/
			template< class TArray, typename TValue> static TArray vectorToArray(const ::std::vector<TValue>& v)
			{
				TArray newArray(v.size());

				for (typename ::std::vector<TValue>::size_type i = 0; i < v.size(); i++)
				{
					newArray[i] = v[i];
				}

				return newArray;
			};

			/** Converts any type based on itk::Array in a std::vector
			* @param v Reference to the data source (vector)
			* @return Array containing the values*/
			template< class TArray, typename TValue> static ::std::vector<TValue> vectorToArray(const TArray& a)
			{
				::std::vector<TValue> newV;

				for (unsigned int i = 0; i < a.GetSize(); ++i)
				{
					newV[i] = a[i];
				}

				return newV;
			};

			/** Loads the specified file and streams its content into a string.
			 * If the file does not exists or cannot be read, an empty string
			 * will be returned.*/
			MAPCore_EXPORT String fileContentToStr(const String& filePath);

		}
	}
} //end of namespace map
#endif
