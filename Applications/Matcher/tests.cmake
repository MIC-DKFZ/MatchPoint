SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(matchRBasicUsageTest ${CXX_TEST_PATH}/testmatchR matchRBasicUsageTest ${TEST_DATA_ROOT} ${TEMP})

#TODO Implement test correctly and reactivate
#ADD_TEST(matchRSimpleRegTest ${CXX_TEST_PATH}/testmatchR matchRSimpleRegTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogoShifted10x-16y-5z.mhd ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEMP}/matchRTestResult_10x-16y-5z.mapR ${TEST_DATA_ROOT}/Applications/Shift10x-16y-5z.mapR)