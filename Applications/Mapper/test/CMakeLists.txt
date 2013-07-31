#-----------------------------------------------------------------------------
# Setup the system information test.  Write out some basic failsafe
# information in case the test doesn't run.
#-----------------------------------------------------------------------------

IF( NOT MAP_DISABLE_CXX_TESTING )


SET(APP_TESTS ${CXX_TEST_PATH}/mapDeploymentTests)
SET(APP_HEADER_TEST ${CXX_TEST_PATH}/mapDeploymentHeaderTest)

SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)

SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

#-----------------------------------------------------------------------------
ADD_TEST(mapRBasicUsageTest ${CXX_TEST_PATH}/mapRTests mapRBasicUsageTest ${TEST_DATA_ROOT} ${TEMP})

SET(mapRTests_SRCS
  mapRBasicUsageTest.cpp
)

INCLUDE_DIRECTORIES("${MatchPointTesting_BINARY_DIR}")

ADD_EXECUTABLE(mapRTests mapRTests.cpp ${mapRTests_SRCS})

TARGET_LINK_LIBRARIES(mapRTests MAPCore MAPAlgorithms MAPAlgorithmsITK MAPDeployment MAPUtilities LitmusCommon LitmusITK)

#-----------------------------------------------------------------------------

IF(MatchPoint_BINARY_DIR)
  SET(MatchPoint_SYSTEM_INFORMATION_DIR ${MatchPoint_BINARY_DIR})
ELSE(MatchPoint_BINARY_DIR)
  SET(MatchPoint_SYSTEM_INFORMATION_DIR ${MatchPointTesting_BINARY_DIR})
ENDIF(MatchPoint_BINARY_DIR)

WRITE_FILE(
  "${MatchPoint_SYSTEM_INFORMATION_DIR}/testing/HTML/TestingResults/Sites/${SITE}/${BUILDNAME}/BuildNameNotes.xml"

  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<Site BuildName=\"CMakeCache\" Name=\"crd\">\n"
  "<BuildNameNotes>\n"
  "<Note>\n"
  "<DateTime>Wed Oct 24 1:00:00 EST</DateTime>\n"
  "<Text>\n"
  "Here is some basic information:\n"
  "MatchPoint_SOURCE_DIR = ${MatchPoint_SOURCE_DIR}\n"
  "MatchPoint_BINARY_DIR = ${MatchPoint_BINARY_DIR}\n"
  "MatchPointTesting_SOURCE_DIR = ${MatchPointTesting_SOURCE_DIR}\n"
  "MatchPointTesting_BINARY_DIR = ${MatchPointTesting_BINARY_DIR}\n"
  "CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}\n"
  "CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}\n"
  "CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}\n"
  "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}\n"
  "CMAKE_SYSTEM = ${CMAKE_SYSTEM}\n"
  "CMAKE_MAKE_PROGRAM = ${CMAKE_MAKE_PROGRAM}\n"
  "</Text>\n"
  "</Note>\n"
  "</BuildNameNotes>\n"
  "</Site>\n"
)


ENDIF( NOT MAP_DISABLE_CXX_TESTING )

