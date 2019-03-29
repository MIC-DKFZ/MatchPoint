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





#ifndef __MAP_I_ENTITY_INTEGRATION_H
#define __MAP_I_ENTITY_INTEGRATION_H

#include "mapIEntityInference.h"

namespace iro
{
  namespace core
  {
    /*! @class IEntityIntegration
    * @brief Interface of the registration ontology decorator used for integration queries in the context of entities or entity
    * related information that is independent from registration/transformation.
    *
    * As integration interface it is analog to a pure setter interface.
    * Getting will be done be inference interfaces (IEntityInference).
    * This interface is implemented regarding the NVI paradigm.
    *
    * @tparam TIETraits type that define the traits of information entities.
    * @tparam TISTraits type that define the traits of information spaces.
    * @tparam TSCTraits type that define the traits of semantic correlations.
    * @tparam TIEInference type of the information entity inference interface that should be used.
    * @tparam TEDReturnType type that is returned by entity delete operations.
    * @tparam TISDReturnType type that is returned by information space delete operations.
    * @tparam TCDReturnType type that is returned by correlation delete operations.
    * @sa IProblemIntegration
    * @sa IMappingIntegration
    * @sa IEntityInference
    * @ingroup Integration
    */
    template <typename TIETraits, typename TISTraits, typename TSCTraits, typename TIEInference, typename TEDReturnType = bool, typename TISDReturnType = bool, typename TCDReturnType = bool>
    class IEntityIntegration
    {
    public:
      using InfEntityType = typename TIETraits::Type;
      using InfSpaceType = typename TISTraits::Type;
      using CorrelationType = typename TSCTraits::Type;
      using ConstInfEntityPointer = typename TIETraits::ConstPointer;
      using ConstInfSpacePointer = typename TISTraits::ConstPointer;
      using ConstCorrelationPointer = typename TSCTraits::ConstPointer;
      using InfEntityInferencePointer = typename TIETraits::InferencePointer;
      using InfSpaceInferencePointer = typename TISTraits::InferencePointer;
      using CorrelationInferencePointer = typename TSCTraits::InferencePointer;

      using EntityDeleteReturnType = TEDReturnType;
      using ISDeleteReturnType = TISDReturnType;
      using CorrelationDeleteReturnType = TCDReturnType;

      /*! Defines and stores the copy of the passed entity and associates it with the passed information space
      * after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleExistenceOnEntityDef
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] pNewEntity Pointer to the entity that should be added as definition to the ontology.
      * @param [in] pContainingIS Pointer to the information space the entity sof the searched paths.
      * @return Returns the entity after the insertion of the definition into the ontology.
      * @pre pNewEntity must point to a valid instance.
      * @pre pContainingIS must point to a valid instance.
      * @pre pContainingIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pNewEntity or pContainingIS pointer is null.
      * @exception ::iro::exceptions::UndefinedElement : pContainingIS is not defined in the ontology.
      */
      Result<ConstInfEntityPointer> defineEntity(InfEntityInferencePointer pNewEntity, InfSpaceInferencePointer pContainingIS);

      /*! Stores the copy of the passed entity or commits the changes between the passed version of the entity and the
      * one stored in the ontology after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnEntityStore
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pEntity Pointer to the entity whose changes should be commited to the ontology.
      * @return Returns the entity after the changes are commited to the ontology.
      * @pre pEntity must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pEntity is null.
      */
      Result<ConstInfEntityPointer> storeEntity(InfEntityInferencePointer pEntity);

      /*! Deletes the passed entity after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnEntityDel
      * - handleDependentsOnEntityDel
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pEntity Pointer to the entity that should be deleted.
      * @return The return type depends on the used scenario the the scenario and its interface realization for more information.
      * @pre pEntity must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pEntity pointer is null.
      */
      EntityDeleteReturnType deleteEntity(InfEntityInferencePointer pEntity);

      /*! Defines and stores the copy of the passed IS after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleExistenceOnISDef
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] pNewEntity Pointer to the entity that should be added as definition to the ontology.
      * @param [in] pContainingIS Pointer to the information space the entity sof the searched paths.
      * @return Returns the IS after the definition was added to the ontology.
      * @pre pNewIS must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pNewIS pointer is null.
      */
      Result<ConstInfSpacePointer> defineInformationSpace(InfSpaceInferencePointer pNewIS);

      /*! Stores the copy of the passed IS or commits the changes between the passed version of the IS and the
      * one stored in the ontology after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnISStore
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pIS Pointer to the IS whose changes should be commited to the ontology.
      * @return Returns the IS after the changes are commited to the ontology.
      * @pre pIS must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pIS is null.
      */
      Result<ConstInfSpacePointer> storeInformationSpace(InfSpaceInferencePointer pIS);

      /*! Deletes the passed IS from the ontology after after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnISDel
      * - handleDepTransOnISDel
      * - handleDepEntitiesOnISDel
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] pIS Pointer to the IS that should be deleted.
      * @return The return type depends on the used scenario the the scenario and its interface realization for more information.
      * @pre pIS must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pIS is null.
      */
      ISDeleteReturnType deleteInformationSpace(InfSpaceInferencePointer pIS);

      /*! Changes the information space of a given entity after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleDepTransOnEntitySwitch
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] pEntity Pointer to the entity that should be reassigned to the new IS.
      * @param [in] pNewIS Pointer to the information space the entity should be reassigned to.
      * @pre pEntity must point to a valid instance.
      * @pre pNewIS must point to a valid instance.
      * @pre pEntity must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @pre pNewIS must be defined in the ontology (use actualize() in order to check
      * this in before).
      * @exception ::iro::exceptions::InvalidArgument : pEntity or pNewIS is null.
      * @exception ::iro::exceptions::UndefinedElement : pEntity or pNewIS are not defined in the ontology.
      */
      void switchInformationSpace(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pNewIS);

      /*! Defines and stores the copy of the passed correlations
      * after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleExistenceOnCorrDef
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @param [in] pNewCorr Pointer to the correlation that should be added as definition to the ontology.
      * @return Returns the correlation after the definition was added to the ontology.
      * @pre pNewCorr must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : pNewCorr is null.
      */
      Result<ConstCorrelationPointer> defineSemanticCorrelation(CorrelationInferencePointer pNewCorr);

      /*! Stores the copy of the passed correlation or commits the changes between the passed version of the correlation and the
      * one stored in the ontology after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnCorrStore
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] corr Pointer to the correlation whose changes should be commited to the ontology.
      * @return Returns the correlation after the changes are commited to the ontology.
      * @pre corr must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : corr pointer is null.
      */
      Result<ConstCorrelationPointer> storeSemanticCorrelation(CorrelationInferencePointer corr);

      /*! Deletes the passed entity after checking all relevant integration rules.\n
      * Relevant integration rules:
      * - handleInexistenceOnCorrDel
      * .
      * See integration rule set of application scenario for information how it is handled in the used scenario.
      * @see IntegrationRuleSets
      * @param [in] corr Pointer to the correlation that should be deleted.
      * @return The return type depends on the used scenario the the scenario and its interface realization for more information.
      * @pre corr must point to a valid instance.
      * @exception ::iro::exceptions::InvalidArgument : corr is null.
      */
      CorrelationDeleteReturnType deleteSemanticCorrelation(CorrelationInferencePointer corr);

    protected:
      virtual ~IEntityIntegration() = default;
      IEntityIntegration() = default;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineEntity*/
      virtual Result<ConstInfEntityPointer> doDefineEntity(InfEntityInferencePointer pNewEntity, InfSpaceInferencePointer pContainingIS) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeEntity*/
      virtual Result<ConstInfEntityPointer> doStoreEntity(InfEntityInferencePointer pEntity) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see convertTransformationToRegistrationPath*/
      virtual EntityDeleteReturnType doDeleteEntity(InfEntityInferencePointer pEntity) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineInformationSpace*/
      virtual Result<ConstInfSpacePointer> doDefineInformationSpace(InfSpaceInferencePointer pNewIS) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeInformationSpace*/
      virtual Result<ConstInfSpacePointer> doStoreInformationSpace(InfSpaceInferencePointer pIS) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteInformationSpace*/
      virtual ISDeleteReturnType doDeleteInformationSpace(InfSpaceInferencePointer pIS) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see switchInformationSpace*/
      virtual void doSwitchInformationSpace(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pNewIS) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineSemanticCorrelation*/
      virtual Result<ConstCorrelationPointer> doDefineSemanticCorrelation(CorrelationInferencePointer pNewCorr) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeSemanticCorrelation*/
      virtual Result<ConstCorrelationPointer> doStoreSemanticCorrelation(CorrelationInferencePointer corr) = 0;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteSemanticCorrelation*/
      virtual CorrelationDeleteReturnType doDeleteSemanticCorrelation(CorrelationInferencePointer corr) = 0;

      using EntityInferenceInterface = TIEInference;
      
      /*!Sets the pointer to the interface that should be used to actualze inference elements
       * (e.g. entities or information spaces)*/
      void setEntityInferenceInterface(const EntityInferenceInterface* pInterface);

      /*!Used to actualize the passed inference elements (e.g. entities or information spaces)*/
      const EntityInferenceInterface* _pEntityInferenceInterface;

    private:
      IEntityIntegration(const IEntityIntegration&); //not implemented by purpose
      IEntityIntegration& operator=(const IEntityIntegration&); //not implemented by purpose
    };
  } // end namespace core
} // end namespace iro

#ifndef MatchPoint_MANUAL_TPP
#include "mapIEntityIntegration.tpp"
#endif

#endif
