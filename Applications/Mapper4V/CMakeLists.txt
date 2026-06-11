MESSAGE (STATUS "generating App: mapR for Virtuos - MatchPoint generic image mapping tool with RT support")

IF(MSVC)
     add_compile_options(/bigobj)
ENDIF()

MAP_CREATE_APPLICATION(mapR4V DEPENDS MAPCore MAPIO MAPUtilities PACKAGE_DEPENDS VII VirtuosIOCore)
target_include_directories(mapR4V PRIVATE ${MatchPoint_SOURCE_DIR}/Applications/Mapper/include ${MatchPoint_SOURCE_DIR}/Applications/Mapper/source)