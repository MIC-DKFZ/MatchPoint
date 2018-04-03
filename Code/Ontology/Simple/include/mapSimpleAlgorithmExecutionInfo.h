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




#ifndef __MAP_SIMPLE_ALGORITHM_EXECUTION_INFO_H
#define __MAP_SIMPLE_ALGORITHM_EXECUTION_INFO_H

#include "mapAlgorithmExecutionInfo.h"
#include "mapAlgorithmExecutionInfoTraits.h"
#include "mapSimpleInformationSpace.h"
#include "mapSimpleInformationEntity.h"

namespace iro
{
  namespace scenario
  {

    /*! @class SimpleAlgorithmExecutionInfo
     * @brief Algorithm execution info in the Simple scenario.
     * @ingroup Simple
     * 
     */
    typedef ::iro::AlgorithmExecutionInfo< SimpleInformationSpaceTraits, SimpleInformationEntityTraits > SimpleAlgorithmExecutionInfo;
  
    using SimpleAlgorithmExecutionInfoTraits = AlgorithmExecutionInfoTraits<SimpleAlgorithmExecutionInfo>;

  } // end namespace scenario

} // end namespace iro

#endif
