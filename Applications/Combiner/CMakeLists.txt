MESSAGE (STATUS "generating App: combineR - MatchPoint registration combination tool")

IF(MSVC)
     ADD_DEFINITIONS(/bigobj)
ENDIF()

MAP_CREATE_APPLICATION(combineR DEPENDS MAPCore MAPAlgorithmITK MAPIO MAPUtilities)
MAP_CREATE_APPLICATION_TESTS(combineR PACKAGE_DEPENDS Litmus)
