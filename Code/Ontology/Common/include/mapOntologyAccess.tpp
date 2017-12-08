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





#ifndef __IRO_ONTOLOGY_ACCESS_TPP
#define __IRO_ONTOLOGY_ACCESS_TPP

#include "mapOntologyAccess.h"

namespace iro
{
  namespace core
  {

    template <typename TOATraits>
    OntologyAccess<TOATraits>::
    ~OntologyAccess()
    {
    };

    template <typename TOATraits>
    OntologyAccess<TOATraits>::
    OntologyAccess()
    {
      MappingInferenceInterface::setEntityInferenceInterface(this);
      EntityIntegrationInterface::setEntityInferenceInterface(this);
      ProblemIntegrationInterface::setProblemInferenceInterface(this);
      MappingIntegrationInterface::setEntityInferenceInterface(this);
      MappingIntegrationInterface::setProblemInferenceInterface(this);
    };

  } // end namespace core
} // end namespace iro

#endif
