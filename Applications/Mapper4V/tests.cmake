SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(mapRBasicUsageTest ${CXX_TEST_PATH}/mapRTests mapRBasicUsageTest ${TEST_DATA_ROOT} ${TEMP})
ADD_TEST(mapRSimpleMappingTest ${CXX_TEST_PATH}/mapRTests mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/Shift10x-16y-5z.mapr ${TEMP}/mapRTestResult_10x-16y-5z.mhd ${TEST_DATA_ROOT}/Algorithms/MatchPointLogoShifted10x-16y-5z.mhd)
ADD_TEST(mapRSimpleMappingTestPadding ${CXX_TEST_PATH}/mapRTests mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/Shift10x-16y-5z.mapr ${TEMP}/mapRTestResult_10x-16y-5z.mhd ${TEST_DATA_ROOT}/Applications/mapRTestResult_10x-16y-5z_padding200.mhd "-p" "200")