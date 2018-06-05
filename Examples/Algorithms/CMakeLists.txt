MESSAGE (STATUS "processing MatchPoint algorithm examples")

IF(BUILD_TESTING)
	SET(DEPENDS "MAPCore" "MAPIO" "MAPAlgorithmsITK")
	SET(DEPENDS_BEFORE "not initialized")
	SET(PACKAGE_DEPENDS "Litmus")
	MAP_USE_MODULE(${DEPENDS})

	INCLUDE_DIRECTORIES(. ${ALL_INCLUDE_DIRECTORIES})
	LINK_DIRECTORIES(${ALL_LIBRARY_DIRS})


	# Adding examples
	ADD_EXECUTABLE(demoITKImageRegistration mapDemoITKImageRegistration.cpp mapDemoHelper.h mapDemoHelper.cpp)
	ADD_EXECUTABLE(demoFixedITKImageRegistration mapDemoFixedITKImageRegistration.cpp mapDemoHelper.h mapDemoHelper.cpp)
	ADD_EXECUTABLE(demoITKMultiResImageRegistration mapDemoITKMultiResImageRegistration.cpp mapDemoHelper.h mapDemoHelper.cpp)
	ADD_EXECUTABLE(demoAutoSealedAlgorithm mapDemoAutoSealedAlgorithm.cpp)
	ADD_EXECUTABLE(demoHelloWorldRegistration1 mapDemoHelloWorldRegistration1.cpp mapDemoHelloWorldRegistration1Helper.h mapDemoHelloWorldRegistration1Helper.cpp)
	ADD_EXECUTABLE(demoHelloWorldRegistration2 mapDemoHelloWorldRegistration2.cpp mapDemoHelloWorldRegistration1Helper.h mapDemoHelloWorldRegistration1Helper.cpp mapDemoRegistrationAlgorithmTemplate.h)
	ADD_EXECUTABLE(demoHelloWorldRegistration3 mapDemoHelloWorldRegistration3.cpp mapDemoHelper.h mapDemoHelper.cpp mapDemoRegistrationAlgorithmTemplate.h)


	TARGET_LINK_LIBRARIES(demoITKImageRegistration MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)
	TARGET_LINK_LIBRARIES(demoFixedITKImageRegistration MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)
	TARGET_LINK_LIBRARIES(demoITKMultiResImageRegistration MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)
	TARGET_LINK_LIBRARIES(demoAutoSealedAlgorithm MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)

	TARGET_LINK_LIBRARIES(demoHelloWorldRegistration1 MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)
	TARGET_LINK_LIBRARIES(demoHelloWorldRegistration2 MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)
	TARGET_LINK_LIBRARIES(demoHelloWorldRegistration3 MAPCore MAPAlgorithms MAPAlgorithmsITK MAPIO LitmusCommon LitmusITK)

	ADD_DEPENDENCIES(demoITKImageRegistration Litmus)
	ADD_DEPENDENCIES(demoFixedITKImageRegistration Litmus)
	ADD_DEPENDENCIES(demoITKMultiResImageRegistration Litmus)
	ADD_DEPENDENCIES(demoAutoSealedAlgorithm Litmus)
	ADD_DEPENDENCIES(demoHelloWorldRegistration1 Litmus)
	ADD_DEPENDENCIES(demoHelloWorldRegistration2 Litmus)
	ADD_DEPENDENCIES(demoHelloWorldRegistration3 Litmus)

	#-----------------------------------------------------------------------------
	# Install

	IF(NOT MatchPoint_INSTALL_NO_EXAMPLES)

		INSTALL(TARGETS demoITKImageRegistration
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)
		INSTALL(TARGETS demoITKMultiResImageRegistration
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)
		INSTALL(TARGETS demoFixedITKImageRegistration
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)
		INSTALL(TARGETS demoAutoSealedAlgorithm
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)
		INSTALL(TARGETS demoHelloWorldRegistration1
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)
		INSTALL(TARGETS demoHelloWorldRegistration2
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)
		INSTALL(TARGETS demoHelloWorldRegistration3
			RUNTIME DESTINATION ${MatchPoint_INSTALL_EXAMPLE_DIR} COMPONENT RuntimeLibraries)

	ENDIF(NOT MatchPoint_INSTALL_NO_EXAMPLES)

	#-----------------------------------------------------------------------------
	# Tests
	IF( NOT MAP_DISABLE_CXX_TESTING )

	  SET(TEST_DATA_ROOT ${MatchPointTesting_SOURCE_DIR}/Data)

	  SET(TEMP ${MatchPointTesting_BINARY_DIR}/Temporary)

	  #-----------------------------------------------------------------------------
	  ADD_TEST(demoITKImageRegistrationTest ${CXX_TEST_PATH}/demoITKImageRegistration "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceShifted13x17y.txt" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceBorder20.txt" 1 0.05 demoITKImageRegistrationTest)
	  ADD_TEST(demoITKMultiResRegistrationTest ${CXX_TEST_PATH}/demoITKMultiResImageRegistration "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceShifted13x17y.txt" -test "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceBorder20.txt" 6.1 0.05 demoMultiResITKImageRegistrationTest)
	  ADD_TEST(demoFixedITKImageRegistrationTest ${CXX_TEST_PATH}/demoFixedITKImageRegistration "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceShifted13x17y.txt" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceBorder20.txt" 1 0.05 demoFixedITKImageRegistrationTest)
	  ADD_TEST(demoAutoSealedAlgorithmTest ${CXX_TEST_PATH}/demoAutoSealedAlgorithm)
	  ADD_TEST(demoHelloWorldRegistration1Test ${CXX_TEST_PATH}/demoHelloWorldRegistration1 "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" 1 0.05 demoHelloWorldRegistration1Test)
	  ADD_TEST(demoHelloWorldRegistration2Test ${CXX_TEST_PATH}/demoHelloWorldRegistration2 "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" 1 0.05 demoHelloWorldRegistration2Test)
	  ADD_TEST(demoHelloWorldRegistration3Test ${CXX_TEST_PATH}/demoHelloWorldRegistration3 "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceShifted13x17y.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceShifted13x17y.txt" -test "${TEST_DATA_ROOT}/Algorithms/BrainProtonDensitySliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/BrainT1SliceBorder20.png" "${TEST_DATA_ROOT}/Algorithms/Landmarks_BrainProtonDensitySliceBorder20.txt" 1 0.05 demoHelloWorldRegistration3Test)

	ENDIF( NOT MAP_DISABLE_CXX_TESTING )
ELSE(BUILD_TESTING)
  MESSAGE(STATUS "To build examples, activate BUILD_TESTING")
ENDIF(BUILD_TESTING)
