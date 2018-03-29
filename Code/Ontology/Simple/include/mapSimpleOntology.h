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
      typedef SimpleOntology Self;

      typedef std::shared_ptr< Self >         Pointer;
      typedef std::shared_ptr< const Self >   ConstPointer;
      using Superclass = iro::core::OntologyAccess<SimpleOntologyAccessTraits>;

      using EntityInferenceInterface = Superclass::EntityInferenceInterface;
      using MappingInferenceInterface = Superclass::MappingInferenceInterface;
      using ProblemInferenceInterface = Superclass::ProblemInferenceInterface;
      using EntityIntegrationInterface = Superclass::EntityIntegrationInterface;
      using MappingIntegrationInterface = Superclass::MappingIntegrationInterface;

      typedef EntityInferenceInterface::InfEntityType                     InfEntityType;
      typedef EntityInferenceInterface::InfSpaceType                      InfSpaceType;
      typedef EntityInferenceInterface::CorrelationType                   CorrelationType;
      typedef EntityInferenceInterface::ConstInfEntityPointer             ConstInfEntityPointer;
      typedef EntityInferenceInterface::ConstInfSpacePointer              ConstInfSpacePointer;
      typedef EntityInferenceInterface::ConstCorrelationPointer           ConstCorrelationPointer;
      typedef EntityInferenceInterface::InfEntityInferencePointer         InfEntityInferencePointer;
      typedef EntityInferenceInterface::InfSpaceInferencePointer          InfSpaceInferencePointer;
      typedef EntityInferenceInterface::CorrelationInferencePointer       CorrelationInferencePointer;

      typedef EntityInferenceInterface::ConstInfEntityVectorType          ConstInfEntityVectorType;
      typedef EntityInferenceInterface::ConstInfSpaceVectorType           ConstInfSpaceVectorType;
      typedef EntityInferenceInterface::ConstCorrelationVectorType        ConstCorrelationVectorType;

      typedef MappingInferenceInterface::ProblemComplianceInterface       ProblemComplianceInterface;

      typedef MappingInferenceInterface::RegistrationPathType             RegistrationPathType;
      typedef MappingInferenceInterface::ConstRegistrationPathPointer     ConstRegistrationPathPointer;

      typedef MappingInferenceInterface::TransformationPathType           TransformationPathType;
      typedef MappingInferenceInterface::ConstTransformationPathPointer   ConstTransformationPathPointer;
      
      typedef MappingInferenceInterface::RegPathOptCollectionType         RegPathOptCollectionType;
      typedef MappingInferenceInterface::ConstRegPathOptColPointer        ConstRegPathOptColPointer;
      typedef MappingInferenceInterface::ConstRegPathOptColVectorType     ConstRegPathOptColVectorType;
      typedef RegPathOptCollectionType::OptionType                        RegPathOptionType;
      typedef RegPathOptCollectionType::ConstOptionPointer                ConstRegPathOptionPointer;

      typedef MappingInferenceInterface::TransPathOptCollectionType       TransPathOptCollectionType;
      typedef MappingInferenceInterface::ConstTransPathOptColPointer      ConstTransPathOptColPointer;
      typedef MappingInferenceInterface::ConstTransPathOptColVectorType   ConstTransPathOptColVectorType;
      typedef TransPathOptCollectionType::OptionType                      TransPathOptionType;
      typedef TransPathOptCollectionType::ConstOptionPointer              ConstTransPathOptionPointer;

      typedef ProblemInferenceInterface::ProblemStatementType             ProblemStatementType;
      typedef ProblemInferenceInterface::ConstProblemStatementPointer     ConstProblemStatementPointer;
      typedef ProblemInferenceInterface::ProblemStatementInferencePointer ProblemStatementInferencePointer;
      typedef ProblemInferenceInterface::ConstProblemStatementVectorType  ConstProblemStatementVectorType;

      typedef ProblemInferenceInterface::ProblemModelType                 ProblemModelType;
      typedef ProblemInferenceInterface::ConstProblemModelPointer         ConstProblemModelPointer;
      typedef ProblemInferenceInterface::ProblemModelInferencePointer     ProblemModelInferencePointer;
      typedef ProblemInferenceInterface::ConstProblemModelVectorType      ConstProblemModelVectorType;

      typedef ProblemInferenceInterface::ProblemAssociatedInterface       ProblemAssociatedInterface;

      typedef EntityIntegrationInterface::EntityDeleteReturnType          EntityDeleteReturnType;
      typedef EntityIntegrationInterface::ISDeleteReturnType              ISDeleteReturnType;
      typedef EntityIntegrationInterface::CorrelationDeleteReturnType     CorrelationDeleteReturnType;

      typedef MappingIntegrationInterface::TransInfoInferencePointer        TransInfoInferencePointer;
      typedef MappingIntegrationInterface::ConstTransformationInfoPointer   ConstTransformationInfoPointer;
      typedef MappingIntegrationInterface::TransformationDeleteReturnType   TransformationDeleteReturnType;

      /** Resets the complete ontology. Revision number will be increased and is keept consistent.*/
      void reset();

      virtual ~SimpleOntology();
      SimpleOntology();

    protected:

      ///////////////////////////////////////////////////////////////
      // Entity Inference

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getContainingIS*/
			virtual Result<ConstInfSpacePointer> doGetContainingIS(InfEntityInferencePointer pEntity) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntitiesInIS*/
			virtual Result<ConstInfEntityVectorType> doGetEntitiesInIS(InfSpaceInferencePointer pIS) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForSameIS*/
			virtual Result<bool> doCheckForSameIS(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForSameIS*/
			virtual Result<bool> doCheckForSameIS(const ConstInfEntityVectorType& entities) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntitiesWithSemanticCorrelations*/
			virtual Result<ConstInfEntityVectorType> doGetEntitiesWithSemanticCorrelations(InfEntityInferencePointer pEntity) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticallyCorrelatedEntities*/
			virtual Result<ConstInfEntityVectorType> doGetSemanticallyCorrelatedEntities(InfSpaceInferencePointer pSourceIS, InfSpaceInferencePointer pCorrelatedIS) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfSpaceInferencePointer pIS1, InfSpaceInferencePointer pIS2) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pIs) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations(InfEntityInferencePointer pEntity1, InfEntityInferencePointer pEntity2) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getDataRepresentationType*/
			virtual Result<DataRepresentationType> doGetDataRepresentationType(InfEntityInferencePointer pEntity) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see hasDiscreteDataRepresentation*/
			virtual Result<bool> doHasDiscreteDataRepresentation(InfEntityInferencePointer pEntity) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see hasContinuousDataRepresentation*/
			virtual Result<bool> doHasContinuousDataRepresentation(InfEntityInferencePointer pEntity) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getEntities*/
			virtual Result<ConstInfEntityVectorType> doGetEntities() const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getInformationSpaces*/
			virtual Result<ConstInfSpaceVectorType> doGetInformationSpaces() const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getSemanticCorrelations*/
			virtual Result<ConstCorrelationVectorType> doGetSemanticCorrelations() const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstInfEntityPointer> doActualize(InfEntityInferencePointer pEntity) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstInfSpacePointer> doActualize(InfSpaceInferencePointer pIS) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstCorrelationPointer> doActualize(CorrelationInferencePointer corr) const;

      ///////////////////////////////////////////////////////////////
      // Entity Integration

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineEntity*/
      virtual Result<ConstInfEntityPointer> doDefineEntity(InfEntityInferencePointer pNewEntity, InfSpaceInferencePointer pContainingIS);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeEntity*/
      virtual Result<ConstInfEntityPointer> doStoreEntity(InfEntityInferencePointer pEntity);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see convertTransformationToRegistrationPath*/
      virtual EntityDeleteReturnType doDeleteEntity(InfEntityInferencePointer pEntity);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineInformationSpace*/
      virtual Result<ConstInfSpacePointer> doDefineInformationSpace(InfSpaceInferencePointer pNewIS);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeInformationSpace*/
      virtual Result<ConstInfSpacePointer> doStoreInformationSpace(InfSpaceInferencePointer pIS);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteInformationSpace*/
      virtual ISDeleteReturnType doDeleteInformationSpace(InfSpaceInferencePointer pIS);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see switchInformationSpace*/
      virtual void doSwitchInformationSpace(InfEntityInferencePointer pEntity, InfSpaceInferencePointer pNewIS);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineSemanticCorrelation*/
      virtual Result<ConstCorrelationPointer> doDefineSemanticCorrelation(CorrelationInferencePointer pNewCorr);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeSemanticCorrelation*/
      virtual Result<ConstCorrelationPointer> doStoreSemanticCorrelation(CorrelationInferencePointer corr);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteSemanticCorrelation*/
      virtual CorrelationDeleteReturnType doDeleteSemanticCorrelation(CorrelationInferencePointer corr);

      ///////////////////////////////////////////////////////////////
      // Mapping inference

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getRegistrationPaths*/
      virtual Result<ConstRegPathOptColPointer> doGetRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getRegistrationPaths*/
      virtual Result<ConstRegPathOptColVectorType> doGetRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getTransformationPaths*/
      virtual Result<ConstTransPathOptColPointer> doGetTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getTransformationPaths*/
      virtual Result<ConstTransPathOptColVectorType> doGetTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalRegistrationPaths*/
      virtual Result<ConstRegPathOptColPointer> doGetOptimalRegistrationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalRegistrationPaths*/
      virtual Result<ConstRegPathOptColVectorType> doGetOptimalRegistrationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const;

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalTransformationPaths*/
      virtual Result<ConstTransPathOptColPointer> doGetOptimalTransformationPaths(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getOptimalTransformationPaths*/
      virtual Result<ConstTransPathOptColVectorType> doGetOptimalTransformationPaths(const ConstInfEntityVectorType& movingEntities, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL, const TransPathMetricInterface* pMetric = NULL) const;

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getMappableInformationSpaces*/
      virtual Result<ConstInfSpaceVectorType> doGetMappableInformationSpaces(InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL, const RegPathMetricInterface* pMetric = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, InfSpaceInferencePointer pFixedIS, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfSpaceInferencePointer pMovingIS, InfSpaceInferencePointer pFixedIS, DataRepresentationSupport::Type requiredDataSupport = DataRepresentationSupport::All, const ProblemComplianceInterface* pProblemCompliance = NULL) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstRegistrationPathPointer pPath) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see checkForMappingFailureReason*/
      virtual Result<MappingErrorType> doCheckForMappingFailureReason(InfEntityInferencePointer pMovingEntity, ConstTransformationPathPointer pPath) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see convertTransformationToRegistrationPath*/
      virtual Result<ConstRegistrationPathPointer> doConvertTransformationToRegistrationPath(ConstTransformationPathPointer pPath) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
      virtual Result<ConstTransformationInfoPointer> doActualize(TransformationInfoInferencePointer pTI) const;

      ///////////////////////////////////////////////////////////////
      // Mapping Integration

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineTransformation*/
      virtual Result<ConstTransformationInfoPointer> doDefineTransformation(TransInfoInferencePointer newTransformation);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeTransformation*/
      virtual Result<ConstTransformationInfoPointer> doStoreTransformation(TransInfoInferencePointer transformation);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteTransformation*/
      virtual TransformationDeleteReturnType doDeleteTransformation(TransInfoInferencePointer transformation);

      ///////////////////////////////////////////////////////////////
      // Problem Inference

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getAssociatedProblemModels*/
			virtual Result<ConstProblemModelVectorType> doGetAssociatedProblemModels(ProblemStatementInferencePointer ps) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see geProblemModels*/
			virtual Result<ConstProblemModelVectorType> doGetProblemModels() const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see getProblemStatements*/
			virtual Result<ConstProblemStatementVectorType> doGetProblemStatements() const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstProblemStatementPointer> doActualize(ProblemStatementInferencePointer ps) const;

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see actualize*/
			virtual Result<ConstProblemModelPointer> doActualize(ProblemModelInferencePointer pm) const;

      ///////////////////////////////////////////////////////////////
      // Problem Integration

      /*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineProblemStatement*/
      virtual Result<ConstProblemStatementPointer> doDefineProblemStatement(ProblemStatementInferencePointer pNewStatement);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeProblemStatement*/
      virtual Result<ConstProblemStatementPointer> doStoreProblemStatement(ProblemStatementInferencePointer pStatement);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteProblemStatement*/
      virtual StatementDeleteReturnType doDeleteProblemStatement(ProblemStatementInferencePointer pStatement);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see defineProblemModel*/
      virtual Result<ConstProblemModelPointer> doDefineProblemModel(ProblemModelInferencePointer pNewModel);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see storeProblemModel*/
      virtual Result<ConstProblemModelPointer> doStoreProblemModel(ProblemModelInferencePointer pModel);

			/*! virtual abstract part of the NVI idiom. See public member for more information.
      *@see deleteProblemModel*/
      virtual ModelDeleteReturnType doDeleteProblemModel(ProblemModelInferencePointer pModel);

      ///////////////////////////////////////////////////////////////
      // internals
      using OntologyCoreType = SimpleOntologyCore<SimpleOntologyAccessTraits>;
      std::shared_ptr< OntologyCoreType > _spCore;

    private:
      SimpleOntology(const Self&); //not implemented by purpose
      Self& operator=(const Self&); //not implemented by purpose
    };

  } // end namespace scenario

} // end namespace iro

#endif
