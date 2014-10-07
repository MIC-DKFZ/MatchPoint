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
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/


#ifndef __MAP_COMBINER_HELPER_H
#define __MAP_COMBINER_HELPER_H

#include "mapRegistrationBase.h"

namespace map
{
  namespace apps
  {
    namespace combineR
    {
      map::core::RegistrationBase::Pointer invertRegistration(map::core::RegistrationBase* reg);
      map::core::RegistrationBase::Pointer combineRegistration(map::core::RegistrationBase* reg1, map::core::RegistrationBase* reg2);
      bool writeRegistration(map::core::RegistrationBase* reg, const map::core::String& fileName);
    }
  }
}

#endif
