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




#ifndef __MAP_SIMPLE_TRANS_PATH_OPTION_COLLECTION_PATH_H
#define __MAP_SIMPLE_TRANS_PATH_OPTION_COLLECTION_PATH_H

#include "mapPathOptionCollection.h"
#include "mapPathOptionCollectionTraits.h"
#include "mapSimpleTransPathOption.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleTransPathOptionCollection
    * @brief Transformation path option collection in the Simple scenario.
    * @ingroup Simple*/
    using SimpleTransPathOptionCollection = ::iro::PathOptionCollection<::iro::scenario::SimpleTransPathOption>;
    using SimpleTransPathOptionCollectionTraits = ::iro::PathOptionCollectionTraits<SimpleTransPathOptionCollection, SimpleTransPathOptionTraits>;
  } // end namespace scenario

} // end namespace iro

#endif
