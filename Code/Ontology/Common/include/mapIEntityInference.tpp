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





#ifndef __MAP_I_ENTITY_INFERENCE_TPP
#define __MAP_I_ENTITY_INFERENCE_TPP

#include "mapIEntityInference.h"
#include "mapOntologyExceptions.h"

namespace iro
{
	namespace core
	{

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfSpacePointer>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getContainingIS(InfEntityInferencePointer pEntity) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot get containing IS. Passed entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity = actualize(pEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot get containing IS. Passed entity is not defined in the ontology.");
      }

      return doGetContainingIS(spCurrentEntity);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfEntityVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getEntitiesInIS(InfSpaceInferencePointer pIS) const
    {
      if (!pIS)
      {
        throw exceptions::InvalidArgument("Cannot get enitities in IS. Passed IS pointer is NULL.");
      }

      ConstInfSpacePointer spCurrentIS = actualize(pIS);

      if (!spCurrentIS)
      {
        throw exceptions::UndefinedElement("Cannot get enitities in IS. Passed IS is not defined in the ontology.");
      }

      return doGetEntitiesInIS(spCurrentIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result<bool>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 checkForSameIS(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const
    {
      if (!pEntity1)
      {
        throw exceptions::InvalidArgument("Cannot check for mutual IS. Passed 1st entity pointer is NULL.");
      }
      if (!pEntity2)
      {
        throw exceptions::InvalidArgument("Cannot check for mutual IS. Passed 2nd entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity1 = actualize(pEntity1);
      ConstInfEntityPointer spCurrentEntity2 = actualize(pEntity2);

      if (!spCurrentEntity1)
      {
        throw exceptions::UndefinedElement("Cannot check for mutual IS. Passed onentity is not defined in the ontology.");
      }
      if (!spCurrentEntity2)
      {
        throw exceptions::UndefinedElement("Cannot check for mutual IS. Passed onentity is not defined in the ontology.");
      }

      return doCheckForSameIS(spCurrentEntity1,spCurrentEntity2);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result<bool>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 checkForSameIS(const ConstInfEntityVectorType& entities) const
    {
      ConstInfEntityVectorType currentEntities;
      for (typename ConstInfEntityVectorType::const_iterator pos = entities.begin(); pos!=entities.end(); ++pos)
      {
        if (!(*pos))
        {
          throw exceptions::InvalidArgument("Cannot check for mutual IS. At least on entity pointer in the passed vector is NULL.");
        }

        ConstInfEntityPointer spCurrentEntity = actualize(*pos);

        if (!spCurrentEntity)
        {
          throw exceptions::UndefinedElement("Cannot check for mutual IS. At least on entity in the passed vector is not defined in the ontology.");
        }

        currentEntities.push_back(spCurrentEntity);
      }


      return doCheckForSameIS(currentEntities);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfEntityVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getEntitiesWithSemanticCorrelations(InfEntityInferencePointer pEntity) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity = actualize(pEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot get containing IS. Passed entity is not defined in the ontology.");
      }

      return doGetEntitiesWithSemanticCorrelations(pEntity);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfEntityVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getSemanticallyCorrelatedEntities(InfSpaceInferencePointer pSourceIS, InfSpaceInferencePointer pCorrelatedIS) const
    {
      if (!pSourceIS)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed source IS pointer is NULL.");
      }
      if (!pCorrelatedIS)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed correlated IS pointer is NULL.");
      }

      ConstInfSpacePointer spCurrenSourceIS = actualize(pSourceIS);
      ConstInfSpacePointer spCurrentCorrelatedIS = actualize(pCorrelatedIS);

      if (!spCurrenSourceIS)
      {
        throw exceptions::UndefinedElement("Cannot query for correlations. Passed source IS is not defined in the ontology.");
      }

      if (!spCurrentCorrelatedIS)
      {
        throw exceptions::UndefinedElement("Cannot query for correlations. Passed correlated IS is not defined in the ontology.");
      }

      return doGetSemanticallyCorrelatedEntities(spCurrenSourceIS,spCurrentCorrelatedIS);
    };

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstCorrelationVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getSemanticCorrelations(InfSpaceInferencePointer pIS1, InfSpaceInferencePointer pIS2) const
    {
      if (!pIS1)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed 1st IS pointer is NULL.");
      }
      if (!pIS2)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed 2nd IS pointer is NULL.");
      }

      ConstInfSpacePointer spCurrenIS1 = actualize(pIS1);
      ConstInfSpacePointer spCurrenIS2 = actualize(pIS2);

      if (!spCurrenIS1)
      {
        throw exceptions::UndefinedElement("Cannot query for correlations. Passed 1st IS is not defined in the ontology.");
      }

      if (!spCurrenIS2)
      {
        throw exceptions::UndefinedElement("Cannot query for correlations. Passed 2nd IS is not defined in the ontology.");
      }

      return doGetSemanticCorrelations(spCurrenIS1,spCurrenIS2);
    };      
      
    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstCorrelationVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getSemanticCorrelations(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pIS) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed entity pointer is NULL.");
      }
      if (!pIS)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed IS pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity = actualize(pEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot query for correlations. Passed entity is not defined in the ontology.");
      }

      ConstInfSpacePointer spCurrentIS = actualize(pIS);

      if (!spCurrentIS)
      {
        throw exceptions::UndefinedElement("Cannot query for correlations. Passed IS is not defined in the ontology.");
      }

      return doGetSemanticCorrelations(spCurrentEntity,spCurrentIS);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstCorrelationVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getSemanticCorrelations(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const
    {
      if (!pEntity1)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed 1st entity pointer is NULL.");
      }
      if (!pEntity2)
      {
        throw exceptions::InvalidArgument("Cannot query for correlations. Passed 2nd entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity1 = actualize(pEntity1);
      ConstInfEntityPointer spCurrentEntity2 = actualize(pEntity2);

      if (!spCurrentEntity1)
      {
        throw exceptions::UndefinedElement("Cannot check for mutual IS. Passed onentity is not defined in the ontology.");
      }
      if (!spCurrentEntity2)
      {
        throw exceptions::UndefinedElement("Cannot check for mutual IS. Passed onentity is not defined in the ontology.");
      }

      return doGetSemanticCorrelations(spCurrentEntity1,spCurrentEntity2);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::DataRepresentationType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getDataRepresentationType(InfEntityInferencePointer pEntity) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot query for data representation. Passed entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity = actualize(pEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot get containing IS. Passed entity is not defined in the ontology.");
      }

      return doGetDataRepresentationType(pEntity);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result<bool>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 hasDiscreteDataRepresentation(InfEntityInferencePointer pEntity) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot query for data representation. Passed entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity = actualize(pEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot get containing IS. Passed entity is not defined in the ontology.");
      }

      return doHasDiscreteDataRepresentation(pEntity);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result<bool>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 hasContinuousDataRepresentation(InfEntityInferencePointer pEntity) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot query for data representation. Passed entity pointer is NULL.");
      }

      ConstInfEntityPointer spCurrentEntity = actualize(pEntity);

      if (!spCurrentEntity)
      {
        throw exceptions::UndefinedElement("Cannot get containing IS. Passed entity is not defined in the ontology.");
      }

      return doHasContinuousDataRepresentation(pEntity);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfEntityVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getEntities() const
    {
      return doGetEntities();
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfSpaceVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getInformationSpaces() const
    {
      return doGetInformationSpaces();
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstCorrelationVectorType>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
		 getSemanticCorrelations() const
    {
      return doGetSemanticCorrelations();
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfEntityPointer>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
			actualize(InfEntityInferencePointer pEntity) const
    {
      if (!pEntity)
      {
        throw exceptions::InvalidArgument("Cannot actualize entity. Passed entity pointer is NULL.");
      }

      return doActualize(pEntity);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstInfSpacePointer>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
			actualize(InfSpaceInferencePointer pIS) const
    {
      if (!pIS)
      {
        throw exceptions::InvalidArgument("Cannot actualize information space. Passed pointer is NULL.");
      }

      return doActualize(pIS);
    };      

    template <typename TIETraits, typename TISTraits, typename TSCTraits>
    Result< typename IEntityInference<TIETraits, TISTraits, TSCTraits>::ConstCorrelationPointer>
    IEntityInference<TIETraits, TISTraits, TSCTraits>::
			actualize(CorrelationInferencePointer corr) const
    {
      if (!corr)
      {
        throw exceptions::InvalidArgument("Cannot actualize correlation. Passed correlation pointer is NULL.");
      }

      return doActualize(corr);
    };      
    

	} // end namespace core
} // end namespace iro

#endif
