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


#ifndef __MAP_BOOST_UID_POLICY_H
#define __MAP_BOOST_UID_POLICY_H

#include "mapMAPOntologySimpleExports.h"

#include "boost/uuid/uuid.hpp"

namespace iro
{
    /*! @struct BoostUIDPolicy
    * @brief Policy for using boost::uuid as UID in MatchPoint ontologies.
    * 
    * @ingroup UIDPolicy
    */
    struct MAPOntologySimple_EXPORT BoostUIDPolicy
    {
      typedef boost::uuids::uuid  UIDType;

      static UIDType generateUID();
    };

} // end namespace iro

#endif
