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





#ifndef __MAP_I_ENTITY_INTEGRATION_TPP
#define __MAP_I_ENTITY_INTEGRATION_TPP

#include <assert.h>
#include "mapIEntityIntegration.h"

namespace iro
{
  namespace core
  {

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    Result<typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ConstInfEntityPointer>
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    defineEntity(InfEntityInferencePointer pNewEntity, InfSpaceInferencePointer pContainingIS)
    {
      assert(_pEntityInferenceInterface);

      if (!pNewEntity)
      {
        throw exceptions::InvalidArgument("Cannot define entity. Passed entity pointer is NULL.");
      }

      if (!pContainingIS)
      {
        throw exceptions::InvalidArgument("Cannot define entity. Passed IS pointer is NULL.");
      }

      ConstInfSpacePointer spContainingIS = _pEntityInferenceInterface->actualize(pContainingIS);

      if (!spContainingIS)
      {
        throw exceptions::UndefinedElement("Cannot define entity. Passed IS is not defined in the ontology.");
      }

      return doDefineEntity(pNewEntity, spContainingIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    Result<typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ConstInfEntityPointer>
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    storeEntity(InfEntityInferencePointer pEntity)
      {
        if (!pEntity)
        {
          throw exceptions::InvalidArgument("Cannot store entity. Passed entity pointer is NULL.");
        }

        return doStoreEntity(pEntity);
      };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::EntityDeleteReturnType
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    deleteEntity(InfEntityInferencePointer pEntity)
    {
        if (!pEntity)
        {
          throw exceptions::InvalidArgument("Cannot store entity. Passed entity pointer is NULL.");
        }

        return doDeleteEntity(pEntity);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    Result<typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ConstInfSpacePointer>
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    defineInformationSpace(InfSpaceInferencePointer pNewIS)
    {
        if (!pNewIS)
        {
          throw exceptions::InvalidArgument("Cannot define IS. Passed IS pointer is NULL.");
        }

        return doDefineInformationSpace(pNewIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    Result<typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ConstInfSpacePointer>
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    storeInformationSpace(InfSpaceInferencePointer pIS)
    {
        if (!pIS)
        {
          throw exceptions::InvalidArgument("Cannot store IS. Passed IS pointer is NULL.");
        }

        return doStoreInformationSpace(pIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ISDeleteReturnType
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    deleteInformationSpace(InfSpaceInferencePointer pIS)
    {
        if (!pIS)
        {
          throw exceptions::InvalidArgument("Cannot delete IS. Passed IS pointer is NULL.");
        }

        return doDeleteInformationSpace(pIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    void
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    switchInformationSpace(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pNewIS)
    {
      assert(_pEntityInferenceInterface);

      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot define entity. Passed entity pointer is NULL.");
      }

      if (!pNewIS)
      {
        throw exceptions::InvalidArgument("Cannot define entity. Passed IS pointer is NULL.");
      }

      ConstInfEntityPointer spEntity = _pEntityInferenceInterface->actualize(pEntity);

      if (!spEntity)
      {
        throw exceptions::UndefinedElement("Cannot switch entity. Passed entity is not defined in the ontology.");
      }

      ConstInfSpacePointer spNewIS = _pEntityInferenceInterface->actualize(pNewIS);

      if (!spNewIS)
      {
        throw exceptions::UndefinedElement("Cannot switch entity. Passed IS is not defined in the ontology.");
      }

      doSwitchInformationSpace(spEntity, spNewIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    Result<typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ConstCorrelationPointer>
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    defineSemanticCorrelation(CorrelationInferencePointer pNewCorr)
    {
        if (!pNewCorr)
        {
          throw exceptions::InvalidArgument("Cannot define correlation. Passed correlation pointer is NULL.");
        }

        return doDefineSemanticCorrelation(pNewCorr);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    Result<typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::ConstCorrelationPointer>
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    storeSemanticCorrelation(CorrelationInferencePointer corr)
    {
        if (!corr)
        {
          throw exceptions::InvalidArgument("Cannot store correlation. Passed correlation pointer is NULL.");
        }

        return doStoreSemanticCorrelation(corr);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    typename IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::CorrelationDeleteReturnType
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    deleteSemanticCorrelation(CorrelationInferencePointer corr)
    {
        if (!corr)
        {
          throw exceptions::InvalidArgument("Cannot delete correlation. Passed correlation pointer is NULL.");
        }

        return doDeleteSemanticCorrelation(corr);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType, typename TISDReturnType, typename TCDReturnType>
    void
    IEntityIntegration<TIETraits, TISTraits, TSCTraits, TIEInference, TEDReturnType, TISDReturnType, TCDReturnType>::
    setEntityInferenceInterface(const EntityInferenceInterface* pInterface)
    {
      _pEntityInferenceInterface = pInterface;
    };

  } // end namespace core
} // end namespace iro

#endif
