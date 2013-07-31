SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)

SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(mapRegistrationAlgorithmBaseTest ${MODULE_TESTS} mapRegistrationAlgorithmBaseTest)
ADD_TEST(mapRegistrationAlgorithmTest ${MODULE_TESTS} mapRegistrationAlgorithmTest)
ADD_TEST(mapIterativeAlgorithmBaseTest ${MODULE_TESTS} mapIterativeAlgorithmBaseTest)
ADD_TEST(mapIterativeRegistrationAlgorithmTest ${MODULE_TESTS} mapIterativeRegistrationAlgorithmTest)
ADD_TEST(mapImageRegistrationAlgorithmBaseTest ${MODULE_TESTS} mapImageRegistrationAlgorithmBaseTest)
ADD_TEST(mapMaskedRegistrationAlgorithmBaseTest ${MODULE_TESTS} mapMaskedRegistrationAlgorithmBaseTest)
ADD_TEST(mapOptimizerControlInterfaceTest ${MODULE_TESTS} mapOptimizerControlInterfaceTest)
ADD_TEST(mapMetaPropertyInfoTest ${MODULE_TESTS} mapMetaPropertyInfoTest)
ADD_TEST(mapMetaPropertyAlgorithmBaseTest ${MODULE_TESTS} mapMetaPropertyAlgorithmBaseTest)
ADD_TEST(mapUIDTest ${MODULE_TESTS} mapUIDTest)
ADD_TEST(mapAlgorithmIdentificationBaseTest ${MODULE_TESTS} mapAlgorithmIdentificationBaseTest)
ADD_TEST(mapArbitraryImagePyramidesPolicyTest ${MODULE_TESTS} mapArbitraryImagePyramidesPolicyTest)
ADD_TEST(mapMultiResImageRegistrationAlgorithmBaseTest ${MODULE_TESTS} mapMultiResImageRegistrationAlgorithmBaseTest)