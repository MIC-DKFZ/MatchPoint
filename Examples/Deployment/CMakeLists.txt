MESSAGE (STATUS "processing MatchPoint deployment examples")

SET(DEPENDS "MAPCore" "MAPIO" "MAPDeployment" "MAPAlgorithmsITK") 
SET(DEPENDS_BEFORE "not initialized")
SET(PACKAGE_DEPENDS "Litmus")
MAP_USE_MODULE(${DEPENDS}) 
	
INCLUDE_DIRECTORIES(. ${ALL_INCLUDE_DIRECTORIES})
LINK_DIRECTORIES(${ALL_LIBRARY_DIRS})

ADD_EXECUTABLE(demoHelloWorldDeployment1 mapDemoHelloWorldDeployment1.cpp ../Algorithms/mapDemoHelloWorldRegistration1Helper.h ../Algorithms/mapDemoHelloWorldRegistration1Helper.cpp ../Algorithms/mapDemoRegistrationAlgorithmTemplate.h)

ADD_EXECUTABLE(demoHelloWorldDeployment2 mapDemoHelloWorldDeployment2.cpp)

ADD_EXECUTABLE(demoDeploymentDLLDirectoryBrowser mapDemoDeploymentDLLDirectoryBrowser.cpp)

ADD_EXECUTABLE(demoDeploymentPropertiedAlgorithm mapDemoDeploymentPropertiedAlgorithm.cpp ../Algorithms/mapDemoHelloWorldRegistration1Helper.h ../Algorithms/mapDemoHelloWorldRegistration1Helper.cpp)

ADD_LIBRARY(demoRegistrationAlgorithm2D SHARED mapDemoRegistrationAlgorithm2DDLL.cpp)

ADD_LIBRARY(demoPropertiedAlgorithm2D SHARED mapDemoPropertiedAlgorithm2DDLL.cpp)

IF(MAP_LIBRARY_PROPERTIES)
  SET_TARGET_PROPERTIES(demoRegistrationAlgorithm2D PROPERTIES ${MAP_LIBRARY_PROPERTIES})
  SET_TARGET_PROPERTIES(demoPropertiedAlgorithm2D PROPERTIES ${MAP_LIBRARY_PROPERTIES})
ENDIF(MAP_LIBRARY_PROPERTIES)

TARGET_LINK_LIBRARIES(demoHelloWorldDeployment1 MAPCore MAPAlgorithms MAPAlgorithmsITK MAPDeployment LitmusCommon LitmusITK ${ITK_LIBRARIES})
TARGET_LINK_LIBRARIES(demoHelloWorldDeployment2 MAPCore MAPAlgorithms MAPDeployment LitmusCommon)
TARGET_LINK_LIBRARIES(demoDeploymentDLLDirectoryBrowser MAPCore MAPDeployment LitmusCommon LitmusITK ${ITK_LIBRARIES})
TARGET_LINK_LIBRARIES(demoDeploymentPropertiedAlgorithm MAPCore MAPAlgorithms MAPAlgorithmsITK MAPDeployment LitmusCommon LitmusITK ${ITK_LIBRARIES})

TARGET_LINK_LIBRARIES(demoRegistrationAlgorithm2D MAPCore MAPAlgorithms MAPAlgorithmsITK MAPDeployment ${ITK_LIBRARIES})
TARGET_LINK_LIBRARIES(demoPropertiedAlgorithm2D MAPCore MAPAlgorithms MAPAlgorithmsITK MAPDeployment ${ITK_LIBRARIES})



#-----------------------------------------------------------------------------
# Install

IF(NOT MatchPoint_INSTALL_NO_EXAMPLES)

	INSTALL(TARGETS demoHelloWorldDeployment1
	    RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)

ENDIF(NOT MatchPoint_INSTALL_NO_EXAMPLES)

#-----------------------------------------------------------------------------
# Tests
IF( BUILD_TESTING )
IF( NOT MAP_DISABLE_CXX_TESTING )

  SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)

  #-----------------------------------------------------------------------------
  ADD_TEST(demoHelloWorldDeployment1Test ${CXX_TEST_PATH}/demoHelloWorldDeployment1 "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" 1 0.05 demoHelloWorldDeployment1Test)

  ADD_TEST(demoHelloWorldDeployment2Test ${CXX_TEST_PATH}/demoHelloWorldDeployment2)

  ADD_TEST(demoDeploymentPropertiedAlgorithmTest ${CXX_TEST_PATH}/demoDeploymentPropertiedAlgorithm "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" 1 0.05 demoHelloWorldDeployment1Test)

ENDIF( NOT MAP_DISABLE_CXX_TESTING )
ENDIF( BUILD_TESTING )
