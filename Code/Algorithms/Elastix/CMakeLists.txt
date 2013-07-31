MAP_CREATE_MODULE(MAPAlgorithmsElastix DEPENDS MAPAlgorithms MAPUtilities MAPIO PACKAGE_DEPENDS Elastix)
MAP_CREATE_MODULE_TESTS(MAPAlgorithmsElastix PACKAGE_DEPENDS Litmus HEADER_TESTS)

IF (BUILD_TESTING)
	ADD_EXECUTABLE(mapDummyElastix "test/mapDummyElastix.cpp")
	SET_TARGET_PROPERTIES(mapDummyElastix PROPERTIES OUTPUT_NAME "elastix")
	TARGET_LINK_LIBRARIES(mapDummyElastix MAPCore)

	ADD_EXECUTABLE(mapDummyTransformix "test/mapDummyTransformix.cpp")
	SET_TARGET_PROPERTIES(mapDummyTransformix PROPERTIES OUTPUT_NAME "transformix")
	TARGET_LINK_LIBRARIES(mapDummyTransformix MAPCore)
ENDIF (BUILD_TESTING)

MAP_DEFINE_DEPLOYED_ALGORITHM(ElxParameterFileCLI2DRegistration FILES "deployed/mapElxParameterFileCLI2DRegistration.cpp" DEPENDS MAPAlgorithmsElastix MAPDeployment)
MAP_DEFINE_DEPLOYED_ALGORITHM(ElxParameterFileCLI3DRegistration FILES "deployed/mapElxParameterFileCLI3DRegistration.cpp" DEPENDS MAPAlgorithmsElastix MAPDeployment)
MAP_DEFINE_DEPLOYED_ALGORITHM(ElxBSplineCLI2DRegistration FILES "deployed/mapElxBSplineCLI2DRegistration.cpp" DEPENDS MAPAlgorithmsElastix MAPDeployment)
MAP_DEFINE_DEPLOYED_ALGORITHM(ElxBSplineCLI3DRegistration FILES "deployed/mapElxBSplineCLI3DRegistration.cpp" DEPENDS MAPAlgorithmsElastix MAPDeployment)
