MESSAGE (STATUS "generating App: mapR for Virtuos - MatchPoint generic image mapping tool with RT support")

IF(MSVC)
     ADD_DEFINITIONS(/bigobj)
ENDIF()

MAP_CREATE_APPLICATION(mapR4V DEPENDS MAPCore MAPIO MAPUtilities PACKAGE_DEPENDS VII VirtuosIOCore)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Applications/Mapper/include ${CMAKE_SOURCE_DIR}/Applications/Mapper/source)