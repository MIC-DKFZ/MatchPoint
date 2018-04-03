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




#ifndef __MAP_SIMPLE_REG_PATH_OPTION_PATH_H
#define __MAP_SIMPLE_REG_PATH_OPTION_PATH_H

#include "mapPathOption.h"
#include "mapPathOptionTraits.h"
#include "mapSimpleRegPathCheckPolicy.h"
#include "mapSimpleRegistrationPath.h"

#include "mapSimpleInformationSpace.h"
#include "mapSimpleRegistrationInfo.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleRegPathOption
    * @brief Registration path option in the Simple scenario.
    * @ingroup Simple*/
    using SimpleRegPathOption = ::iro::PathOption< SimpleRegistrationPathTraits, SimpleRegPathCheckPolicy< SimpleRegistrationPathTraits > >;

    using SimpleRegPathOptionTraits = ::iro::PathOptionTraits<SimpleRegPathOption>;
   
  } // end namespace scenario

} // end namespace iro

#endif
