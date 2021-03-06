SET(CPP_FILES
source/mapBijectivCorrelation.cpp
source/mapDataRepresentation.cpp
source/mapOntologyExceptions.cpp
source/mapInjectivCorrelation.cpp
source/mapISemanticCorrelationType.cpp
source/mapUnkownBijectivCorrelation.cpp
source/mapUnkownInjectivCorrelation.cpp
)

SET(H_FILES 
include/mapAlgorithmExecutionInfo.h
include/mapAlgorithmExecutionInfoTraits.h
include/mapBijectivCorrelation.h
include/mapDataRepresentation.h
include/mapFOVScope.h
include/mapGraphProperties.h
include/mapIEntityInference.h
include/mapIEntityIntegration.h
include/mapIInformationSpaceConnector.h
include/mapIMappingInference.h
include/mapIMappingIntegration.h
include/mapInformationEntityTraits.h
include/mapInformationSpaceTraits.h
include/mapInjectivCorrelation.h
include/mapIPathMetric.h
include/mapIProblemComplianceChecker.h
include/mapIProblemComplianceDefinition.h
include/mapIProblemInference.h
include/mapIProblemIntegration.h
include/mapIProblemStatementAssociated.h
include/mapISCacheKey.h
include/mapISConnectorPathBase.h
include/mapISemanticCorrelationType.h
include/mapMappingError.h
include/mapOntologyAccess.h
include/mapOntologyExceptions.h
include/mapOntologyResult.h
include/mapOntologyString.h
include/mapPathOption.h
include/mapPathOptionCollection.h
include/mapPathOptionCollectionTraits.h
include/mapPathOptionTraits.h
include/mapProblemBasedEdgeValidator.h
include/mapProblemModelBase.h
include/mapProblemModelTraits.h
include/mapProblemStatementBase.h
include/mapProblemStatementTraits.h
include/mapRegistrationInfo.h
include/mapRegistrationInfoTraits.h
include/mapRegistrationPathBase.h
include/mapRegistrationPathTraits.h
include/mapSemanticCorrelation.h
include/mapSemanticCorrelationTraits.h
include/mapTransformationInfoTraits.h
include/mapTransformationPathBase.h
include/mapTransformationPathTraits.h
include/mapUnkownBijectivCorrelation.h
include/mapUnkownInjectivCorrelation.h
include/mapValidityIndicator.h
)

SET(TPP_FILES
include/mapAlgorithmExecutionInfo.tpp
include/mapIEntityInference.tpp
include/mapIEntityIntegration.tpp
include/mapIMappingInference.tpp
include/mapIMappingIntegration.tpp
include/mapIProblemInference.tpp
include/mapIProblemIntegration.tpp
include/mapISCacheKey.tpp
include/mapISConnectorPathBase.tpp
include/mapOntologyAccess.tpp
include/mapOntologyResult.tpp
include/mapPathOption.tpp
include/mapPathOptionCollection.tpp
include/mapProblemBasedEdgeValidator.tpp
include/mapProblemModelBase.tpp
include/mapProblemStatementBase.tpp
include/mapRegistrationInfo.tpp
include/mapRegistrationPathBase.tpp
include/mapSemanticCorrelation.tpp
include/mapTransformationPathBase.tpp
)

SET(TEST_CPP_FILES
test/mapOntologyResultTest.cpp
test/mapCommonTests.cpp
)