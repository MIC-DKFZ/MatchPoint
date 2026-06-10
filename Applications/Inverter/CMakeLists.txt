MESSAGE (STATUS "generating App: invertR - MatchPoint generic registration inversion tool")

IF(MSVC)
     add_compile_options(/bigobj)
ENDIF()

MAP_CREATE_APPLICATION(invertR DEPENDS MAPCore MAPIO MAPUtilities)
MAP_CREATE_APPLICATION_TESTS(invertR PACKAGE_DEPENDS Litmus)
