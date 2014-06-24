SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)
SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(combineRBasicUsageTest ${APP_TESTS} combineRBasicUsageTest ${TEST_DATA_ROOT} ${TEMP})