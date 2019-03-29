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




#ifndef __MAP_SIMPLE_ONTOLOGY_H
#define __MAP_SIMPLE_ONTOLOGY_H

#include "mapOntologyAccess.h"
#include "mapSimpleRegPathOptionCollection.h"
#include "mapSimpleTransPathOptionCollection.h"
#include "mapSimpleAlgorithmExecutionInfo.h"
#include "mapSimpleProblemModel.h"
#include "mapSimpleSemanticCorrelation.h"

#include "mapMAPOntologySimpleExports.h"

namespace iro
{
  namespace scenario
  {


    struct SimpleOntologyAccessTraits : public iro::core::OntologyAccessTraits < SimpleRegistrationPathTraits, SimpleRegPathOptionCollectionTraits,
      SimpleTransPathOptionCollectionTraits, SimpleSemanticCorrelationTraits,
      SimpleProblemModelTraits>
    {};

    template <typename TOATraits>
    class SimpleOntologyCore;

    /*! @class SimpleOntology
     * @brief Simple specific implementation of the ontology
     * @ingroup Simple*/
    class MAPOntologySimple_EXPORT SimpleOntology : public iro::core::OntologyAccess<SimpleOntologyAccessTraits>
    {
    public:
      using Self = SimpleOntology;

      using Pointer = std::shared_ptr<Self>;
      using ConstPointer = std::shared_ptr<const Self>;
      using Superclass = iro::core::OntologyAccess<SimpleOntologyAccessTraits>;

      using EntityInferenceInterface = Superclass::EntityInferenceInterface;
      using MappingInferenceInterface = Superclass::MappingInferenceInterface;
      using ProblemInferenceInterface = Superclass::ProblemInferenceInterface;
      using EntityIntegrationInterface = Superclass::EntityIntegrationInterface;
      using MappingIntegrationInterface = Superclass::MappingIntegrationInterface;

      using InfEntityType = EntityInferenceInterface::InfEntityType;
      using InfSpaceType = EntityInferenceInterface::InfSpaceType;
      using CorrelationType = EntityInferenceInterface::CorrelationType;
      using ConstInfEntityPointer = EntityInferenceInterface::ConstInfEntityPointer;
      using ConstInfSpacePointer = EntityInferenceInterface::ConstInfSpacePointer;
      using ConstCorrelationPointer = EntityInferenceInterface::ConstCorrelationPointer;
      using InfEntityInferencePointer = EntityInferenceInterface::InfEntityInferencePointer;
      using InfSpaceInferencePointer = EntityInferenceInterface::InfSpaceInferencePointer;
      using CorrelationInferencePointer = EntityInferenceInterface::CorrelationInferencePointer;

      using ConstInfEntityVectorType = EntityInferenceInterface::ConstInfEntityVectorType;
      using ConstInfSpaceVectorType = EntityInferenceInterface::ConstInfSpaceVectorType;
      using ConstCorrelationVectorType = EntityInferenceInterface::ConstCorrelationVectorType;

      using ProblemComplianceInterface = MappingInferenceInterface::ProblemComplianceInterface;

      using RegistrationPathType = MappingInferenceInterface::RegistrationPathType;
      using ConstRegistrationPathPointer = MappingInferenceInterface::ConstRegistrationPathPointer;

      using TransformationPathType = MappingInferenceInterface::TransformationPathType;
      using ConstTransformationPathPointer = MappingInferenceInterface::ConstTransformationPathPointer;
      
      using RegPathOptCollectionType = MappingInferenceInterface::RegPathOptCollectionType;
      using ConstRegPathOptColPointer = MappingInferenceInterface::ConstRegPathOptColPointer;
      using ConstRegPathOptColVectorType = MappingInferenceInterface::ConstRegPathOptColVectorType;
      using RegPathOptionType = RegPathOptCollectionType::OptionType;
      using ConstRegPathOptionPointer = RegPathOptCollectionType::ConstOptionPointer;

      using TransPathOptCollectionType = MappingInferenceInterface::TransPathOptCollectionType;
      using ConstTransPathOptColPointer = MappingInferenceInterface::ConstTransPathOptColPointer;
      using ConstTransPathOptColVectorType = MappingInferenceInterface::ConstTransPathOptColVectorType;
      using TransPathOptionType = TransPathOptCollectionType::OptionType;
      using ConstTransPathOptionPointer = TransPathOptCollectionType::ConstOptionPointer;

      using ProblemStatementType = ProblemInferenceInterface::ProblemStatementType;
      using ConstProblemStatementPointer = ProblemInferenceInterface::ConstProblemStatementPointer;
      using ProblemStatementInferencePointer = ProblemInferenceInterface::ProblemStatementInferencePointer;
      using ConstProblemStatementVectorType = ProblemInferenceInterface::ConstProblemStatementVectorType;

      using ProblemModelType = ProblemInferenceInterface::ProblemModelType;
      using ConstProblemModelPointer = ProblemInferenceInterface::ConstProblemModelPointer;
      using ProblemModelInferencePointer = ProblemInferenceInterface::ProblemModelInferencePointer;
      using ConstProblemModelVectorType = ProblemInferenceInterface::ConstProblemModelVectorType;

      using ProblemAssociatedInterface = ProblemInferenceInterface::ProblemAssociatedInterface;

      using EntityDeleteReturnType = EntityIntegrationInterface::EntityDeleteReturnType;
      using ISDeleteReturnType = EntityIntegrationInterface::ISDeleteReturnType;
      using CorrelationDeleteReturnType = EntityIntegrationInterface::CorrelationDeleteReturnType;

      using TransInfoInferencePointer = MappingIntegrationInterface::TransInfoInferencePointer;
      using ConstTransformationInfoPointer = MappingIntegrationInterface::ConstTransformationInfoPointer;
      using TransformationDeleteReturnType = MappingIntegrationInterface::TransformationDeleteReturnType;

      /** Resets the complete ontology. Revision number will be increased and is keept consistent.*/
      void reset();

      ~SimpleOntology() override;
      SimpleOntology();

    protected:

      ///////////////////////////////////////////////////////////////
      // Entity Inference

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getContainingIS*/
			Result<ConstInfSpacePointer> doGetContainingIS(InfEntityInferencePointer pEntity) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntitiesInIS*/
			Result<ConstInfEntityVectorType> doGetEntitiesInIS(InfSpaceInferencePointer pIS) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForSameIS*/
			Result<bool> doCheckForSameIS(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForSameIS*/
			Result<bool> doCheckForSameIS(const ConstInfEntityVectorType& entities) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntitiesWithSemanticCorrelations*/
			Result<ConstInfEntityVectorType> doGetEntitiesWithSemanticCorrelations(InfEntityInferencePointer pEntity) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticallyCorrelatedEntities*/
			Result<ConstInfEntityVectorType> doGetSemanticallyCorrelatedEntities(InfSpaceInferencePointer pSourceIS, InfSpaceInferencePointer pCorrelatedIS) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfSpaceInferencePointer pIS1, InfSpaceInferencePointer pIS2) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pIs) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getDataRepresentationType*/
			Result<DataRepresentationType> doGetDataRepresentationType(InfEntityInferencePointer pEntity) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see hasDiscreteDataRepresentation*/
			Result<bool> doHasDiscreteDataRepresentation(InfEntityInferencePointer pEntity) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see hasContinuousDataRepresentation*/
			Result<bool> doHasContinuousDataRepresentation(InfEntityInferencePointer pEntity) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntities*/
			Result<ConstInfEntityVectorType> doGetEntities() const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getInformationSpaces*/
			Result<ConstInfSpaceVectorType> doGetInformationSpaces() const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			Result<ConstCorrelationVectorType> doGetSemanticCorrelations() const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			Result<ConstInfEntityPointer> doActualize(InfEntityInferencePointer pEntity) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			Result<ConstInfSpacePointer> doActualize(InfSpaceInferencePointer pIS) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			Result<ConstCorrelationPointer> doActualize(CorrelationInferencePointer corr) const override;

      ///////////////////////////////////////////////////////////////
      // Entity Integration

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineEntity*/
      Result<ConstInfEntityPointer> doDefineEntity(InfEntityInferencePointer pNewEntity, InfSpaceInferencePointer pContainingIS) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeEntity*/
      Result<ConstInfEntityPointer> doStoreEntity(InfEntityInferencePointer pEntity) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see convertTransformationToRegistrationPath*/
      EntityDeleteReturnType doDeleteEntity(InfEntityInferencePointer pEntity) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineInformationSpace*/
      Result<ConstInfSpacePointer> doDefineInformationSpace(InfSpaceInferencePointer pNewIS) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeInformationSpace*/
      Result<ConstInfSpacePointer> doStoreInformationSpace(InfSpaceInferencePointer pIS) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteInformationSpace*/
      ISDeleteReturnType doDeleteInformationSpace(InfSpaceInferencePointer pIS) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see switchInformationSpace*/
      void doSwitchInformationSpace(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pNewIS) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineSemanticCorrelation*/
      Result<ConstCorrelationPointer> doDefineSemanticCorrelation(CorrelationInferencePointer pNewCorr) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeSemanticCorrelation*/
      Result<ConstCorrelationPointer> doStoreSemanticCorrelation(CorrelationInferencePointer corr) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteSemanticCorrelation*/
      CorrelationDeleteReturnType doDeleteSemanticCorrelation(CorrelationInferencePointer corr) override;

      ///////////////////////////////////////////////////////////////
      // Mapping inference

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getRegistrationPaths*/
      Result<ConstRegPathOptColPointer> doGetRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getRegistrationPaths*/
      Result<ConstRegPathOptColVectorType> doGetRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getTransformationPaths*/
      Result<ConstTransPathOptColPointer> doGetTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getTransformationPaths*/
      Result<ConstTransPathOptColVectorType> doGetTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalRegistrationPaths*/
      Result<ConstRegPathOptColPointer> doGetOptimalRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance = nullptr, const RegPathMetricInterface* pMetric = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalRegistrationPaths*/
      Result<ConstRegPathOptColVectorType> doGetOptimalRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr, const RegPathMetricInterface* pMetric = nullptr) const override;

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalTransformationPaths*/
      Result<ConstTransPathOptColPointer> doGetOptimalTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr, const TransPathMetricInterface* pMetric = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalTransformationPaths*/
      Result<ConstTransPathOptColVectorType> doGetOptimalTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr, const TransPathMetricInterface* pMetric = nullptr) const override;

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getMappableInformationSpaces*/
      Result<ConstInfSpaceVectorType> doGetMappableInformationSpaces(InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = nullptr, const RegPathMetricInterface* pMetric = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      Result<MappingErrorType> doCheckForMappingFailureReason(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = nullptr) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstRegistrationPathPointer pPath) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstTransformationPathPointer pPath) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see convertTransformationToRegistrationPath*/
      Result<ConstRegistrationPathPointer> doConvertTransformationToRegistrationPath(ConstTransformationPathPointer pPath) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
      Result<ConstTransformationInfoPointer> doActualize(TransformationInfoInferencePointer pTI) const override;

      ///////////////////////////////////////////////////////////////
      // Mapping Integration

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineTransformation*/
      Result<ConstTransformationInfoPointer> doDefineTransformation(TransInfoInferencePointer newTransformation) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeTransformation*/
      Result<ConstTransformationInfoPointer> doStoreTransformation(TransInfoInferencePointer transformation) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteTransformation*/
      TransformationDeleteReturnType doDeleteTransformation(TransInfoInferencePointer transformation) override;

      ///////////////////////////////////////////////////////////////
      // Problem Inference

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getAssociatedProblemModels*/
			Result<ConstProblemModelVectorType> doGetAssociatedProblemModels(ProblemStatementInferencePointer ps) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see geProblemModels*/
			Result<ConstProblemModelVectorType> doGetProblemModels() const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getProblemStatements*/
			Result<ConstProblemStatementVectorType> doGetProblemStatements() const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			Result<ConstProblemStatementPointer> doActualize(ProblemStatementInferencePointer ps) const override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			Result<ConstProblemModelPointer> doActualize(ProblemModelInferencePointer pm) const override;

      ///////////////////////////////////////////////////////////////
      // Problem Integration

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineProblemStatement*/
      Result<ConstProblemStatementPointer> doDefineProblemStatement(ProblemStatementInferencePointer pNewStatement) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeProblemStatement*/
      Result<ConstProblemStatementPointer> doStoreProblemStatement(ProblemStatementInferencePointer pStatement) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteProblemStatement*/
      StatementDeleteReturnType doDeleteProblemStatement(ProblemStatementInferencePointer pStatement) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineProblemModel*/
      Result<ConstProblemModelPointer> doDefineProblemModel(ProblemModelInferencePointer pNewModel) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeProblemModel*/
      Result<ConstProblemModelPointer> doStoreProblemModel(ProblemModelInferencePointer pModel) override;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteProblemModel*/
      ModelDeleteReturnType doDeleteProblemModel(ProblemModelInferencePointer pModel) override;

      ///////////////////////////////////////////////////////////////
      // internals
      using OntologyCoreType = SimpleOntologyCore<SimpleOntologyAccessTraits>;
      std::shared_ptr< OntologyCoreType > _spCore;

    private:
      SimpleOntology(const Self&) = delete; //not implemented by purpose
      Self& operator=(const Self&) = delete; //not implemented by purpose
    };

  } // end namespace scenario

} // end namespace iro

#endif
