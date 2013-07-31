SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)

SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
IF(NOT UNIX)
	ADD_TEST(mapFSL3DRegistrationAlgorithmTest ${MODULE_TESTS} mapFSL3DRegistrationAlgorithmTest "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png")
ENDIF(NOT UNIX)