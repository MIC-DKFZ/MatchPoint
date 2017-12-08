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




#ifndef __IRO_SIMPLE_TRANS_PATH_CHECK_POLICY_H
#define __IRO_SIMPLE_TRANS_PATH_CHECK_POLICY_H

#include "mapMappingError.h"

namespace iro
{

		/*! @class SimpleTransPathCheckPolicy
    *
    * 
    */
    template <typename TPathTraits>
    struct SimpleTransPathCheckPolicy
		{
      typedef typename TPathTraits::Type PathType;
      typedef typename TPathTraits::InformationEntityTraitsType::Type EntityType;
      typedef typename TPathTraits::ConstPointer ConstPathPointer;
      typedef typename TPathTraits::InformationEntityTraitsType::ConstPointer ConstEntityPointer;

      static bool checkPathSupportOfEntity(ConstPathPointer path, ConstEntityPointer entity);
      static MappingError::Type checkForFailureReason(ConstPathPointer path, ConstEntityPointer entity);
		};

} // end namespace iro

#ifndef IRO_MANUAL_TPP
#include "mapSimpleTransPathCheckPolicy.tpp"
#endif

#endif
