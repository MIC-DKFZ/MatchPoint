MESSAGE (STATUS "generating App: mapR - MatchPoint generic image mapping tool")

IF(MSVC)
     ADD_DEFINITIONS(/bigobj)
ENDIF()

MAP_CREATE_APPLICATION(mapR DEPENDS MAPCore MAPIO MAPUtilities)
MAP_CREATE_APPLICATION_TESTS(mapR PACKAGE_DEPENDS Litmus)
