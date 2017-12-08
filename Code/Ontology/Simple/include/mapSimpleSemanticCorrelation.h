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




#ifndef __IRO_SIMPLE_SEMANTIC_CORRELATION_H
#define __IRO_SIMPLE_SEMANTIC_CORRELATION_H

#include "mapSemanticCorrelation.h"
#include "mapBoostUIDPolicy.h"
#include "mapSimpleInformationEntity.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleSemanticCorrelation
    * @brief Transformation path option in the Simple scenario.
    * @ingroup Simple*/
    using SimpleSemanticCorrelation = ::iro::SemanticCorrelation< SimpleInformationEntityTraits, BoostUIDPolicy >;
    using SimpleSemanticCorrelationTraits = SemanticCorrelationTraits<SimpleSemanticCorrelation, SimpleInformationEntityTraits>;
  
  } // end namespace scenario

} // end namespace iro

#endif
