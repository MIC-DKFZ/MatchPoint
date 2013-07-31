SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

ADD_TEST(mapPlmParameterFileRegistrationAlgorithmTest ${MODULE_TESTS} mapPlmParameterFileRegistrationAlgorithmTest "${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd" "${TEST_DATA_ROOT}/Algorithms/MatchPointLogoShifted10x-16y-5z.mhd" "${TEST_DATA_ROOT}/Algorithms/Plastimatch/parameters_Translation.txt")
