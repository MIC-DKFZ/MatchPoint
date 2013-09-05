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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapAlgorithmIdentificationInterface.h $
*/


#include "mapSDXMLStrReader.h"
#include "mapAlgorithmProfileHelper.h"
#include "mapLogbookMacros.h"

namespace map
{

	namespace algorithm
	{

    MAPAlgorithms_EXPORT structuredData::Element::Pointer parseProfileString(const core::String& profileStr)
    {
      ::map::structuredData::Element::Pointer result = NULL;
      try
      {
        ::map::structuredData::XMLStrReader::Pointer reader = ::map::structuredData::XMLStrReader::New();
        ::map::structuredData::Element::Pointer spRoot = reader->read(profileStr);
        ::map::structuredData::Element::ConstSubElementIteratorType profilePos = ::map::structuredData::findNextSubElement(spRoot->getSubElementBegin(),spRoot->getSubElementEnd(),tags::AlgorithmProfile);
        if(profilePos != spRoot->getSubElementEnd())
        {
          result = *profilePos;
        }
      }
      catch (...)
      {
      	mapLogDebugStaticMacro(<<"Exception while parsing algorithm profile: Profile string: "<<profileStr);
      }

      return result;
    }

    MAPAlgorithms_EXPORT const ::map::core::String getAlgorithmDescription(const structuredData::Element* profileRoot)
    {
      ::map::core::String result = "";
      if(profileRoot)
      {
        ::map::structuredData::Element::ConstSubElementIteratorType descPos = ::map::structuredData::findNextSubElement(profileRoot->getSubElementBegin(),profileRoot->getSubElementEnd(),tags::AlgorithmDescription);
        if(descPos != profileRoot->getSubElementEnd())
        {
          result = (*descPos)->getValue();
        }
      }
      return result;
    }

  }
}
