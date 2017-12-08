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




#ifndef __IRO_PROPBLEM_BASED_EDGE_VALIDATOR_H
#define __IRO_PROPBLEM_BASED_EDGE_VALIDATOR_H

#include "mapDataRepresentation.h"

namespace iro
{
   /** Simple edge validator based on problem compliance and data representation.
    valid edges are all edges that fulfill the following requirements:
    - Fulfilling the passed problem compliance definition.
    - Supporting the passed data representation.
    @tparam TRegistrationGraphType type that boost graph that represents the registration graph.
    @tparam TProblemComplianceInterface Type of the problem compliance definition interface
   */
    template<typename TRegistrationGraphType, typename TProblemComplianceInterface>
    class ProblemBasedEdgeValidator
    {
    public:

      typedef TRegistrationGraphType GraphType;
      typedef typename GraphType::edge_descriptor EdgeDescriptorType;
      typedef TProblemComplianceInterface ProblemComplianceInterface;

      bool isValid(EdgeDescriptorType edge, const GraphType& graph, DataRepresentationSupport::Type dataRep, const ProblemComplianceInterface* pProblemCompliance, bool& currentCTrail, bool& currentDTrail) const;
    };

} // end namespace iro

#include "mapProblemBasedEdgeValidator.tpp"

#endif
