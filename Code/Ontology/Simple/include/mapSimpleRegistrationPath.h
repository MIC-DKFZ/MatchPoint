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




#ifndef __MAP_SIMPLE_REGISTRATION_PATH_H
#define __MAP_SIMPLE_REGISTRATION_PATH_H

#include "mapRegistrationPathBase.h"
#include "mapRegistrationPathTraits.h"
#include "mapSimpleTransformationPath.h"
#include "mapSimpleRegistrationInfo.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleRegistrationPath
    * @brief Registration path in the Simple scenario.
    * @ingroup Simple
    */
    using SimpleRegistrationPath = ::iro::RegistrationPathBase< SimpleRegistrationInfoTraits, SimpleTransformationPathTraits >;
    using SimpleRegistrationPathTraits = ::iro::RegistrationPathTraits<SimpleRegistrationPath, SimpleRegistrationInfoTraits, SimpleTransformationPathTraits>;
  } // end namespace scenario

} // end namespace iro

#endif
