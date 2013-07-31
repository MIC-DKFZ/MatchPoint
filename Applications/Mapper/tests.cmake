SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(mapRBasicUsageTest ${APP_TESTS} mapRBasicUsageTest ${TEST_DATA_ROOT} ${TEMP})