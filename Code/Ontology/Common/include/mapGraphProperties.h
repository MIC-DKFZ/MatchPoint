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





#ifndef __IRO_I_GRAPH_PROPERTIES_H
#define __IRO_I_GRAPH_PROPERTIES_H

#include "mapInformationSpaceTraits.h"
#include "mapTransformationInfoTraits.h"

namespace iro
{
  namespace core
  {
    /*! @class ISGraphInfo
    * @brief Property struct used for the vertices of the internal InformationSpace-Registration-Graph.
    * This is used for the representation of the information spaces modeled in
    * a boost graph.
    */
    template <typename TISTraits>
    struct ISGraphInfo
    {
      using InfSpaceType = typename TISTraits::Type;
      using ConstInfSpacePointer = typename TISTraits::ConstPointer;

      ConstInfSpacePointer infSpace;
    };

    /*! @class RegistrationISGraphInfo
    * @brief Property struct used for the edges of the internal InformationSpace-Registration-Graph.
    * This is used for the representation of the registration between to information spaces modeled in
    * a boost graph.
    */
    template <typename TTITraits>
    struct RegistrationISGraphInfo
    {
      using InfoType = typename TTITraits::Type;
      using InfoPointer = typename TTITraits::Pointer;

      /* Pointer to the transformation with direct mapping support*/
      InfoPointer direct;
      /* Pointer to the transformation with inverse mapping support*/
      InfoPointer inverse;
    };


  } // end namespace core
} // end namespace iro

#endif
