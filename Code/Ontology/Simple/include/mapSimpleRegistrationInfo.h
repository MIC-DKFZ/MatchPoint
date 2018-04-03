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




#ifndef __MAP_SIMPLE_REGISTRATION_INFO_H
#define __MAP_SIMPLE_REGISTRATION_INFO_H

#include "mapRegistrationInfo.h"
#include "mapRegistrationInfoTraits.h"
#include "mapSimpleTransformationInfo.h"

namespace iro
{
  namespace scenario
  {
    /*! @class SimpleRegistrationInfo
    * @brief Definition for registration infos in the Simple context.
    * @ingroup Simple
    */
    using SimpleRegistrationInfo = ::iro::RegistrationInfo< SimpleInformationSpaceTraits, SimpleProblemStatementTraits, SimpleTransformationInfoTraits>;
  
    using SimpleRegistrationInfoTraits = ::iro::RegistrationInfoTraits<SimpleRegistrationInfo, SimpleInformationSpaceTraits, SimpleProblemStatementTraits, SimpleTransformationInfoTraits>;
  } // end namespace scenario

} // end namespace iro

#endif
