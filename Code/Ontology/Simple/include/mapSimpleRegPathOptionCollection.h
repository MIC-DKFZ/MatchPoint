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




#ifndef __MAP_SIMPLE_REG_PATH_OPTION_COLLECTION_PATH_H
#define __MAP_SIMPLE_REG_PATH_OPTION_COLLECTION_PATH_H

#include "mapPathOptionCollection.h"
#include "mapPathOptionCollectionTraits.h"
#include "mapSimpleRegPathOption.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleRegPathOptionCollection
    * @brief Registration path option collection in the Simple scenario.
    * @ingroup Simple*/
    using SimpleRegPathOptionCollection = ::iro::PathOptionCollection<::iro::scenario::SimpleRegPathOption>;
    using SimpleRegPathOptionCollectionTraits = ::iro::PathOptionCollectionTraits<SimpleRegPathOptionCollection, SimpleRegPathOptionTraits>;
  
  } // end namespace scenario

} // end namespace iro

#endif
