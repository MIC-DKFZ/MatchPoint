MESSAGE (STATUS "generating App: matchR - MatchPoint generic light weight image registration tool")

IF(MSVC)
     ADD_DEFINITIONS(/bigobj)
ENDIF()

MAP_CREATE_APPLICATION(matchR DEPENDS MAPCore MAPAlgorithms MAPDeployment MAPAlgorithmsITK MAPIO MAPUtilities)
MAP_CREATE_APPLICATION_TESTS(matchR PACKAGE_DEPENDS Litmus)

IF(NOT WIN32)
	target_compile_features(matchR PRIVATE cxx_auto_type cxx_nullptr cxx_override)
	set(CMAKE_CXX_FLAGS "-fpermissive")
ENDIF()
