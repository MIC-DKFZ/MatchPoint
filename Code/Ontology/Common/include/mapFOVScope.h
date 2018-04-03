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





#ifndef __MAP_FOV_SCOPE_H
#define __MAP_FOV_SCOPE_H

namespace iro
{

/*! @struct FOVScope
* Indication the supported scope of the field of view of a transformation.
*
* Possible values:
* - Global
* - Local
*/
  struct FOVScope
  {
    enum Type {
      Global = 0,
      Local = 1
    };
  };

} // end namespace iro

#endif
