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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/include/mapRHelper.h $
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
