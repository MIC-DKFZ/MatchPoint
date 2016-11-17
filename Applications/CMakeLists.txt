MESSAGE (STATUS "processing MatchPoint applications/tools code")

ADD_SUBDIRECTORY (Mapper)
ADD_SUBDIRECTORY (Combiner)
ADD_SUBDIRECTORY (Inverter)

OPTION(MAP_BUILD_VIRTUOS_SUPPORT "Enable application support for virtuos files. Activate to build a special mapR version (mapR4V) that handles also virtuos files." OFF)
MARK_AS_ADVANCED(MAP_BUILD_VIRTUOS_SUPPORT)

IF (MAP_BUILD_VIRTUOS_SUPPORT)
  ADD_SUBDIRECTORY (Mapper4V)
ENDIF (MAP_BUILD_VIRTUOS_SUPPORT)