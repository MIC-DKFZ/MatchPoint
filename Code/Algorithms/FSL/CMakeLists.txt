MAP_CREATE_MODULE(MAPAlgorithmsFSL DEPENDS MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO MAPUtilities)
MAP_CREATE_MODULE_TESTS(MAPAlgorithmsFSL PACKAGE_DEPENDS Litmus HEADER_TESTS)

IF (BUILD_TESTING)
	ADD_EXECUTABLE(mapDummyFlirt "test/mapDummyFlirt.cpp")
	SET_TARGET_PROPERTIES(mapDummyFlirt PROPERTIES OUTPUT_NAME "flirt")
	TARGET_LINK_LIBRARIES(mapDummyFlirt MAPCore)
ENDIF (BUILD_TESTING)


MAP_DEFINE_DEPLOYED_ALGORITHM(FSL2DRegistration PROFILE "deployed/FSL2DRegistration.profile" FILES "deployed/mapFSL2DRegistration.cpp" MODULE_DEPENDS MAPCore MAPAlgorithms MAPDeployment MAPAlgorithmsFSL MAPUtilities)
MAP_DEFINE_DEPLOYED_ALGORITHM(FSL3DRegistration PROFILE "deployed/FSL3DRegistration.profile" FILES "deployed/mapFSL3DRegistration.cpp" MODULE_DEPENDS MAPCore MAPAlgorithms MAPDeployment MAPAlgorithmsFSL MAPUtilities)
