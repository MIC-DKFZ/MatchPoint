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
#include "mapConvert.h"

namespace map
{

  namespace algorithm
  {
    namespace profile
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

      const structuredData::Element::Pointer extractCharacteristicsFromProfile(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer result;

        if(profileRoot)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(profileRoot->getSubElementBegin(),profileRoot->getSubElementEnd(),tags::AlgorithmCharacteristics);
          if (pos != profileRoot->getSubElementEnd())
          {
            result = *pos;
          }
        }

        return result;
      }

      ValueListType getValues(const structuredData::Element* node, const map::core::String& tag)
      {
        ValueListType result;
        if(node)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(node->getSubElementBegin(),node->getSubElementEnd(),tag);
          while (pos != node->getSubElementEnd())
          {
            result.push_back((*pos)->getValue());
            pos = ::map::structuredData::findNextSubElement(++pos,node->getSubElementEnd(),tag);
          }
        }
        return result;
      }

      MAPAlgorithms_EXPORT const ::map::core::String getDescription(const structuredData::Element* profileRoot)
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

      MAPAlgorithms_EXPORT const ::map::core::String getDescription(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getDescription(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getContact(const structuredData::Element* profileRoot)
      {
        ValueListType result = getValues(profileRoot,tags::AlgorithmContact);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getContact(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getContact(profile);
      }

      MAPAlgorithms_EXPORT bool getTerms(const structuredData::Element* profileRoot, map::core::String& terms)
      {
        bool result = false;
        if(profileRoot)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(profileRoot->getSubElementBegin(),profileRoot->getSubElementEnd(),tags::AlgorithmTerms);
          if(pos != profileRoot->getSubElementEnd())
          {
            terms = (*pos)->getValue();
            result = true;
          }
        }
        return result;
      }

      MAPAlgorithms_EXPORT bool getTerms(const core::String& profileStr, map::core::String& terms)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getTerms(profile, terms);
      }

      MAPAlgorithms_EXPORT ValueListType getCitation(const structuredData::Element* profileRoot)
      {
        ValueListType result = getValues(profileRoot,tags::AlgorithmCitation);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getCitation(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getCitation(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getDataType(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmDataType);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getDataType(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getDataType(profile);
      }

      MAPAlgorithms_EXPORT bool getComputationStyle(const structuredData::Element* profileRoot, map::core::String& stlye)
      {
        bool result = false;
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        if(chars)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(chars->getSubElementBegin(),chars->getSubElementEnd(),tags::AlgorithmComputationStyle);
          if(pos != chars->getSubElementEnd())
          {
            stlye = (*pos)->getValue();
            result = true;
          }
        }
        return result;
      }

      MAPAlgorithms_EXPORT bool getComputationStyle(const core::String& profileStr, map::core::String& stlye)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getComputationStyle(profile, stlye);
      }

      MAPAlgorithms_EXPORT bool getMovingDimensions(const structuredData::Element* profileRoot, unsigned int& dims)
      {
        bool result = false;
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        if(chars)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(chars->getSubElementBegin(),chars->getSubElementEnd(),tags::AlgorithmDimMoving);
          if(pos != chars->getSubElementEnd())
          {
            dims = map::core::convert::toUInt((*pos)->getValue());
            result = true;
          }
        }
        return result;
      }

      MAPAlgorithms_EXPORT bool getMovingDimensions(const core::String& profileStr, unsigned int& dims)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getMovingDimensions(profile, dims);
      }

      MAPAlgorithms_EXPORT ValueListType getMovingModality(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmModalityMoving);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getMovingModality(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getMovingModality(profile);
      }

      MAPAlgorithms_EXPORT bool getTargetDimensions(const structuredData::Element* profileRoot, unsigned int& dims)
      {
        bool result = false;
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        if(chars)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(chars->getSubElementBegin(),chars->getSubElementEnd(),tags::AlgorithmDimTarget);
          if(pos != chars->getSubElementEnd())
          {
            dims = map::core::convert::toUInt((*pos)->getValue());
            result = true;
          }
        }
        return result;
      }

      MAPAlgorithms_EXPORT bool getTargetDimensions(const core::String& profileStr, unsigned int& dims)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getTargetDimensions(profile, dims);
      }

      MAPAlgorithms_EXPORT ValueListType getTargetModality(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmModalityTarget);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getTargetModality(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getTargetModality(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getObject(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmObject);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getObject(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getObject(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getSubject(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmSubject);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getSubject(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getSubject(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getTransformModel(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmTransformModel);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getTransformModel(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getTransformModel(profile);
      }


      MAPAlgorithms_EXPORT ValueListType getMetric(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmMetric);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getMetric(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getMetric(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getOptimization(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmOptimization);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getOptimization(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getOptimization(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getInteraction(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        ValueListType result = getValues(chars,tags::AlgorithmInteraction);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getInteraction(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getInteraction(profile);
      }

      MAPAlgorithms_EXPORT ValueListType getKeywords(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer keywords;
        if(profileRoot)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(profileRoot->getSubElementBegin(),profileRoot->getSubElementEnd(),tags::AlgorithmKeywords);
          if (pos != profileRoot->getSubElementEnd())
          {
            keywords = *pos;
          }
        }

        ValueListType result = getValues(keywords,tags::AlgorithmKeyword);
        return result;
      }

      MAPAlgorithms_EXPORT ValueListType getKeywords(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return getKeywords(profile);
      }

      MAPAlgorithms_EXPORT bool isDeterministic(const structuredData::Element* profileRoot)
      {
        structuredData::Element::Pointer chars = extractCharacteristicsFromProfile(profileRoot);
        bool result = false;

        if(chars)
        {
          ::map::structuredData::Element::ConstSubElementIteratorType pos = ::map::structuredData::findNextSubElement(chars->getSubElementBegin(),chars->getSubElementEnd(),tags::AlgorithmDeterministic);
          result = pos != chars->getSubElementEnd();
        }

        return result;
      }

      MAPAlgorithms_EXPORT bool isDeterministic(const core::String& profileStr)
      {
        structuredData::Element::Pointer profile = parseProfileString(profileStr);
        return isDeterministic(profile);
      }

    }
  }
}
