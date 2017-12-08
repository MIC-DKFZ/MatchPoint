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





#ifndef __MAP_I_PROBLEM_INFERENCE_TPP
#define __MAP_I_PROBLEM_INFERENCE_TPP

#include "mapIProblemInference.h"
#include "mapOntologyExceptions.h"

namespace iro
{
	namespace core
	{

    template <typename TPMTraits>
    Result< typename IProblemInference<TPMTraits>::ConstProblemModelVectorType>
    IProblemInference<TPMTraits>::
		 getAssociatedProblemModels(const ProblemAssociatedInterface* pAssociated) const
    {
      if (!pAssociated)
      {
        throw exceptions::InvalidArgument("Cannot get associated problem models. Passed pointer of associated instance is NULL.");
      }

      return getAssociatedProblemModels(pAssociated->getAssociatedProblemStatement());
    };

    template <typename TPMTraits>
    Result< typename IProblemInference<TPMTraits>::ConstProblemModelVectorType>
    IProblemInference<TPMTraits>::
		 getAssociatedProblemModels(ProblemStatementInferencePointer ps) const
    {
      if (!ps)
      {
        throw exceptions::InvalidArgument("Cannot get associated problem models. Passed proplem statement pointer is NULL.");
      }

      ConstProblemStatementPointer spCurrentPS = actualize(ps);

      if (!spCurrentPS)
      {
        throw exceptions::UndefinedElement("Cannot get associated problem models. Passed problem statement is not defined in the ontology.");
      }

      return doGetAssociatedProblemModels(spCurrentPS);
    };

    template <typename TPMTraits>
    Result< typename IProblemInference<TPMTraits>::ConstProblemModelVectorType>
    IProblemInference<TPMTraits>::
		 getProblemModels() const
    {
      return doGetProblemModels();
    };      

    template <typename TPMTraits>
    Result< typename IProblemInference<TPMTraits>::ConstProblemStatementVectorType>
    IProblemInference<TPMTraits>::
		 getProblemStatements() const
    {
      return doGetProblemStatements();
    };      

    template <typename TPMTraits>
    Result< typename IProblemInference<TPMTraits>::ConstProblemStatementPointer>
    IProblemInference<TPMTraits>::
			actualize(ProblemStatementInferencePointer ps) const
    {
      if (!ps)
      {
        throw exceptions::InvalidArgument("Cannot actualize problem statement. Passed pointer is NULL.");
      }

      return doActualize(ps);
    };      

    template <typename TPMTraits>
    Result< typename IProblemInference<TPMTraits>::ConstProblemModelPointer>
    IProblemInference<TPMTraits>::
			actualize(ProblemModelInferencePointer pm) const
    {
      if (!pm)
      {
        throw exceptions::InvalidArgument("Cannot actualize problem model. Passed pointer is NULL.");
      }

      return doActualize(pm);
    };      
 

	} // end namespace core
} // end namespace iro

#endif
