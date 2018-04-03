SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(mapDeploymentDLLHelperTest ${MODULE_TESTS} mapDeploymentDLLHelperTest)
ADD_TEST(mapDeploymentDLLInfoTest ${MODULE_TESTS} mapDeploymentDLLInfoTest)
ADD_TEST(mapDeploymentDLLHandleTest ${MODULE_TESTS} mapDeploymentDLLHandleTest)
ADD_TEST(mapDeploymentDLLAccessTest ${MODULE_TESTS} mapDeploymentDLLAccessTest)
ADD_TEST(mapDeploymentDLLBrowserTest ${MODULE_TESTS} mapDeploymentDLLBrowserTest)
ADD_TEST(mapDeploymentDLLConfigTest ${MODULE_TESTS} mapDeploymentDLLConfigTest ${TEMP})
