// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright c German Cancer Research Center DKFZ,
// Software development for Integrated Diagnostics and Therapy SIDT.
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------




#ifndef __MAP_SIMPLE_REG_PATH_CHECK_POLICY_TPP
#define __MAP_SIMPLE_REG_PATH_CHECK_POLICY_TPP

#include "mapFOVScope.h"
#include "mapSimpleRegPathCheckPolicy.h"

namespace iro
{

  template <typename TPathTraits>
  bool
    SimpleRegPathCheckPolicy<TPathTraits>::
    checkPathSupportOfEntity(ConstPathPointer path, ConstEntityPointer entity)
  {
    return checkForFailureReason(path,entity) == MappingError::NoFailure;
  };

  template <typename TPathTraits>
  MappingError::Type
    SimpleRegPathCheckPolicy<TPathTraits>::
    checkForFailureReason(ConstPathPointer path, ConstEntityPointer entity)
  {
    MappingError::Type result = MappingError::NoFailure;

    for (typename PathType::ConstPathElementIterator pos = path->getBegin(); pos!=path->getEnd(); ++pos)
    {
      typename TPathTraits::TransformationInfoTraitsType::ConstPointer relevantInfo = (*pos)->getContinuousTransformation();
      if (entity->getDataRepresentation()==DataRepresentation::Discrete)
      {
        relevantInfo = (*pos)->getDiscreteTransformation();
      }

      if (!relevantInfo)
      {
        result = MappingError::NoDataSupport;
        break;
      }
      else
      {
        if (relevantInfo->getFOVScope()!=FOVScope::Global)
        {
          result = MappingError::NoMappingGuarantee;
        }
      }
    }

    return result;
  };

} // end namespace iro

#endif
