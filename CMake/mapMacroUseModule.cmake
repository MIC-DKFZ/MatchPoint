##################################################################
#
# MAP_USE_MODULE
#
# Usage: MAP_USE_MODULE([dependencies ...] )
# loads module config files of all dependencies specified as input
# values.
#
##################################################################

MACRO(MAP_USE_MODULE)
  SET(DEPENDS "")
  SET(DEPENDS_BEFORE "not initialized")
  
  # check for each parameter if it is a package (3rd party)
  FOREACH(package ${ARGN})
    SET(is_package)
    FOREACH(dir ${MODULES_PACKAGE_DEPENDS_DIRS})
      IF(EXISTS "${dir}/MAP_${package}_Config.cmake") 
        LIST(APPEND PACKAGE_DEPENDS ${package})
        SET(is_package 1)
        BREAK()
      ENDIF()
    ENDFOREACH()
    IF(NOT is_package)
      LIST(APPEND DEPENDS ${package}) 
    ENDIF()
  ENDFOREACH(package)
  
  # go through all module dependencies and get there dependencies for modules and packages
  WHILE(NOT "${DEPENDS}" STREQUAL "${DEPENDS_BEFORE}")
    SET(DEPENDS_BEFORE ${DEPENDS})
    FOREACH(dependency ${DEPENDS})
      INCLUDE(${MAP_MODULES_CONF_DIR}/${dependency}Config.cmake)
      LIST(APPEND DEPENDS ${${dependency}_DEPENDS})
      LIST(APPEND PACKAGE_DEPENDS ${${dependency}_PACKAGE_DEPENDS})
    ENDFOREACH(dependency) 
    IF(DEPENDS)
      LIST(REMOVE_DUPLICATES DEPENDS)
      LIST(SORT DEPENDS)
    ENDIF(DEPENDS)
    IF(PACKAGE_DEPENDS)
      LIST(REMOVE_DUPLICATES PACKAGE_DEPENDS)
      LIST(SORT PACKAGE_DEPENDS)
    ENDIF(PACKAGE_DEPENDS)
  ENDWHILE()
  
  # now go through all module dependencies and get dirs and libraries
  FOREACH(dependency ${DEPENDS} ${MODULE_DEPENDS_INTERNAL})
    INCLUDE(${MAP_MODULES_CONF_DIR}/${dependency}Config.cmake)
    SET(ALL_INCLUDE_DIRECTORIES ${ALL_INCLUDE_DIRECTORIES} ${${dependency}_INCLUDE_DIRS})
    SET(ALL_LIBRARIES ${ALL_LIBRARIES} ${${dependency}_PROVIDES})
    SET(ALL_LIBRARY_DIRS ${ALL_LIBRARY_DIRS} ${${dependency}_LIBRARY_DIRS})
  ENDFOREACH(dependency)

  # now go through all package dependencies and include there config file
  FOREACH(package ${PACKAGE_DEPENDS})
    FOREACH(dir ${MODULES_PACKAGE_DEPENDS_DIRS})
      IF(EXISTS "${dir}/MAP_${package}_Config.cmake")
        INCLUDE("${dir}/MAP_${package}_Config.cmake")
        BREAK()
      ENDIF()
    ENDFOREACH()
  ENDFOREACH(package)

  SET(ALL_LIBRARIES ${ALL_LIBRARIES} ${MODULE_ADDITIONAL_LIBS})
  SET(ALL_INCLUDE_DIRECTORIES ${ALL_INCLUDE_DIRECTORIES} ${MODULE_INCLUDE_DIRS} ${MODULE_INTERNAL_INCLUDE_DIRS} ${MAP_MODULES_CONF_DIR})

  IF(ALL_LIBRARY_DIRS)
    LIST(REMOVE_DUPLICATES ALL_LIBRARY_DIRS)
  ENDIF(ALL_LIBRARY_DIRS)

ENDMACRO(MAP_USE_MODULE)
