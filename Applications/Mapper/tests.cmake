SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(mapRBasicUsageTest ${CXX_TEST_PATH}/testmapR mapRBasicUsageTest ${TEST_DATA_ROOT} ${TEMP})
ADD_TEST(mapRSimpleMappingTest ${CXX_TEST_PATH}/testmapR mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/Shift10x-16y-5z.mapr ${TEMP}/mapRTestResult_10x-16y-5z.mhd ${TEST_DATA_ROOT}/Algorithms/MatchPointLogoShifted10x-16y-5z.mhd)
ADD_TEST(mapRSimpleMappingTestPadding ${CXX_TEST_PATH}/testmapR mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/Shift10x-16y-5z.mapr ${TEMP}/mapRTestResult_10x-16y-5z.mhd ${TEST_DATA_ROOT}/Applications/mapRTestResult_10x-16y-5z_padding200.mhd "-p" "200")
ADD_TEST(mapRSimpleMappingTestLinearInterpolation1 ${CXX_TEST_PATH}/testmapR mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/r10.mapr ${TEMP}/mapRTestResult_r10_linear1.mhd ${TEST_DATA_ROOT}/Applications/mapRTestResult_r10_linear_interpolator.mhd)
ADD_TEST(mapRSimpleMappingTestLinearInterpolation2 ${CXX_TEST_PATH}/testmapR mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/r10.mapr ${TEMP}/mapRTestResult_r10_linear2.mhd ${TEST_DATA_ROOT}/Applications/mapRTestResult_r10_linear_interpolator.mhd -i linear)
ADD_TEST(mapRSimpleMappingTestNNInterpolation ${CXX_TEST_PATH}/testmapR mapRSimpleMappingTest ${TEST_DATA_ROOT}/Algorithms/MatchPointLogo.mhd ${TEST_DATA_ROOT}/Applications/r10.mapr ${TEMP}/mapRTestResult_r10_nn.mhd ${TEST_DATA_ROOT}/Applications/mapRTestResult_r10_nn_interpolator.mhd -i nn)