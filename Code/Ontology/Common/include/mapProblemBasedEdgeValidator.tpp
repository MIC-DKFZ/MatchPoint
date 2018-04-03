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




#include "mapProblemBasedEdgeValidator.h"

namespace iro
{

  template<typename TRegistrationGraphType, typename TProblemComplianceInterface>
  bool
    ProblemBasedEdgeValidator<TRegistrationGraphType, TProblemComplianceInterface>::
      isValid(EdgeDescriptorType edge, const GraphType& graph, DataRepresentationSupport::Type dataRep,
      const ProblemComplianceInterface* pProblemCompliance, bool& currentCTrail, bool& currentDTrail) const
    {
      if (currentCTrail) currentCTrail = graph[edge].direct != nullptr;
      if (currentDTrail) currentDTrail = graph[edge].inverse != nullptr;

      if (!currentCTrail && (dataRep == DataRepresentationSupport::All || dataRep == DataRepresentationSupport::Continuous))
      { //direct transform is not set but needed
        return false;
      }

      if (!currentDTrail && (dataRep == DataRepresentationSupport::All || dataRep == DataRepresentationSupport::Discrete))
      { //inverse transform is not set but needed
        return false;
      }

      if (pProblemCompliance)
      {
        if (currentCTrail && (dataRep == DataRepresentationSupport::All || dataRep == DataRepresentationSupport::Continuous))
        { //direct transform is set and needed ->check problem compliance
          if (!(pProblemCompliance->checkComplianceOfStatement( graph[edge].direct->getAssociatedProblemStatement().get())))
          {
            return false;
          }
        }
        if (currentDTrail && (dataRep == DataRepresentationSupport::All || dataRep == DataRepresentationSupport::Discrete))
        { //inverse transform is set and needed ->check problem compliance
          if (!(pProblemCompliance->checkComplianceOfStatement( graph[edge].direct->getAssociatedProblemStatement().get())))
          {
            return false;
          }
        }
      }

      return true;
    };

} // end namespace iro
