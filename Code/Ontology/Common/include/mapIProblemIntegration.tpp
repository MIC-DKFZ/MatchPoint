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





#ifndef __MAP_I_PROBLEM_INTEGRATION_TPP
#define __MAP_I_PROBLEM_INTEGRATION_TPP

#include "mapIProblemIntegration.h"

namespace iro
{
  namespace core
  {

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    Result<typename IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::ConstProblemStatementPointer>
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    defineProblemStatement(ProblemStatementInferencePointer pNewStatement)
    {
      assert(_pProblemInferenceInterface);

      if (!pNewStatement)
      {
        throw exceptions::InvalidArgument("Cannot define problem statement. Passed statement pointer is NULL.");
      }

      return doDefineProblemStatement(pNewStatement);
    };

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    Result<typename IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::ConstProblemStatementPointer>
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    storeProblemStatement(ProblemStatementInferencePointer pStatement)
      {
        if (!pStatement)
        {
          throw exceptions::InvalidArgument("Cannot store problem statement. Passed statement pointer is NULL.");
        }

        return doStoreProblemStatement(pStatement);
      };

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    typename IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::StatementDeleteReturnType
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    deleteProblemStatement(ProblemStatementInferencePointer pStatement)
    {
        if (!pStatement)
        {
          throw exceptions::InvalidArgument("Cannot store problem statement. Passed statement pointer is NULL.");
        }

        return doDeleteProblemStatement(pStatement);
    };

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    Result<typename IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::ConstProblemModelPointer>
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    defineProblemModel(ProblemModelInferencePointer pNewModel)
    {
      assert(_pProblemInferenceInterface);

      if (!pNewModel)
      {
        throw exceptions::InvalidArgument("Cannot define problem model. Passed model pointer is NULL.");
      }

      return doDefineProblemModel(pNewModel);
    };

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    Result<typename IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::ConstProblemModelPointer>
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    storeProblemModel(ProblemModelInferencePointer pModel)
      {
        if (!pModel)
        {
          throw exceptions::InvalidArgument("Cannot store problem model. Passed model pointer is NULL.");
        }

        return doStoreProblemModel(pModel);
      };

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    typename IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::ModelDeleteReturnType
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    deleteProblemModel(ProblemModelInferencePointer pModel)
    {
        if (!pModel)
        {
          throw exceptions::InvalidArgument("Cannot store problem model. Passed model pointer is NULL.");
        }

        return doDeleteProblemModel(pModel);
    };

    template <typename TPMTraits, typename TPInference, typename TPSDReturnType, typename TPMDReturnType>
    void
    IProblemIntegration<TPMTraits, TPInference, TPSDReturnType, TPMDReturnType>::
    setProblemInferenceInterface(const ProblemInferenceInterface* pInterface)
    {
      _pProblemInferenceInterface = pInterface;
    };

  } // end namespace core
} // end namespace iro

#endif
