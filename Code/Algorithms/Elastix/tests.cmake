SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

ADD_TEST(mapElxParameterFileRegistrationAlgorithmTest ${MODULE_TESTS} mapElxParameterFileRegistrationAlgorithmTest "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/Elastix/parameters_Translation.txt")
