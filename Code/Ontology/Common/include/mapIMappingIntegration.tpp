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





#ifndef __MAP_I_MAPPING_INTEGRATION_TPP
#define __MAP_I_MAPPING_INTEGRATION_TPP

#include "mapIMappingIntegration.h"

namespace iro
{
  namespace core
  {

    template <typename TTITraits, typename TIEInference, typename TPInference, typename TTDReturnType>
    Result<typename IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::ConstTransformationInfoPointer>
      IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::
      defineTransformation(TransInfoInferencePointer newTransformation)
    {
      assert(_pEntityInferenceInterface);
      assert(_pProblemInferenceInterface);

      if (!newTransformation)
      {
        throw exceptions::InvalidArgument("Cannot define transformation info. Passed transformation info pointer is NULL.");
      }

      typedef typename InformationSpaceTraitsType::ConstPointer ConstInfSpacePointer;
      ConstInfSpacePointer movingIS = _pEntityInferenceInterface->actualize(newTransformation->getMovingIS());

      if (!movingIS)
      {
        throw exceptions::UndefinedElement("Cannot define transformation info. Referenced moving IS is not defined in the ontology.");
      }

      ConstInfSpacePointer targetIS = _pEntityInferenceInterface->actualize(newTransformation->getTargetIS());

      if (!targetIS)
      {
        throw exceptions::UndefinedElement("Cannot define transformation info. Referenced target IS is not defined in the ontology.");
      }

      if (newTransformation->getAssociatedProblemStatement())
      {
        typedef typename ProblemStatementTraitsType::ConstPointer ConstStatPointer;
        ConstStatPointer stat = _pProblemInferenceInterface->actualize(newTransformation->getAssociatedProblemStatement());

        if (!stat)
        {
          throw exceptions::UndefinedElement("Cannot define transformation info. Referenced problem statement is not defined in the ontology.");
        }
      }

      return doDefineTransformation(newTransformation);
    };

    template <typename TTITraits, typename TIEInference, typename TPInference, typename TTDReturnType>
    Result<typename IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::ConstTransformationInfoPointer>
      IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::
      storeTransformation(TransInfoInferencePointer transformation)
    {
      assert(_pEntityInferenceInterface);
      assert(_pProblemInferenceInterface);

      if (!transformation)
      {
        throw exceptions::InvalidArgument("Cannot store transformation info. Passed transformation info pointer is NULL.");
      }

      typedef typename InformationSpaceTraitsType::ConstPointer ConstInfSpacePointer;
      ConstInfSpacePointer movingIS = _pEntityInferenceInterface->actualize(transformation->getMovingIS());

      if (!movingIS)
      {
        throw exceptions::UndefinedElement("Cannot store transformation info. Referenced moving IS is not defined in the ontology.");
      }

      ConstInfSpacePointer targetIS = _pEntityInferenceInterface->actualize(transformation->getTargetIS());

      if (!targetIS)
      {
        throw exceptions::UndefinedElement("Cannot store transformation info. Referenced target IS is not defined in the ontology.");
      }

      if (transformation->GetAssociatedProblemStatement())
      {
        typedef typename ProblemStatementTraitsType::ConstPointer ConstStatPointer;
        ConstStatPointer stat = _pProblemInferenceInterface->actualize(transformation->GetAssociatedProblemStatement());

        if (!stat)
        {
          throw exceptions::UndefinedElement("Cannot store transformation info. Referenced problem statement is not defined in the ontology.");
        }
      }

      return doStoreTransformation(transformation);
    };

    template <typename TTITraits, typename TIEInference, typename TPInference, typename TTDReturnType>
    typename IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::TransformationDeleteReturnType
      IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::
      deleteTransformation(TransInfoInferencePointer transformation)
    {
      if (!transformation)
      {
        throw exceptions::InvalidArgument("Cannot delete transformation. Passed entity pointer is NULL.");
      }

      return doDeleteTransformation(transformation);
    };


    template <typename TTITraits, typename TIEInference, typename TPInference, typename TTDReturnType>
    void
      IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::
      setEntityInferenceInterface(const EntityInferenceInterface* pInterface)
    {
      _pEntityInferenceInterface = pInterface;
    };


    template <typename TTITraits, typename TIEInference, typename TPInference, typename TTDReturnType>
    void
      IMappingIntegration<TTITraits, TIEInference, TPInference, TTDReturnType>::
      setProblemInferenceInterface(const ProblemInferenceInterface* pInterface)
    {
      _pProblemInferenceInterface = pInterface;
    };

  } // end namespace core
} // end namespace iro

#endif
