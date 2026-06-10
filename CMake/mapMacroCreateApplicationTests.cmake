##################################################################
#
# MAP_CREATE_APPLICATION_TESTS 
#
#! Creates tests for a APP.
#!
#! USAGE:
#!
#! \code
#! MAP_CREATE_APPLICATION_TESTS( <APPName>
#!     [INCLUDE_DIRS <include directories>]
#!     [DEPENDS <additional modules we need>]
#!     [PACKAGE_DEPENDS <packages we need, like ITK, Litmus>]
#! \endcode
#!
#! \param APP_NAME_IN The name for the new APP
#
##################################################################

MACRO(MAP_CREATE_APPLICATION_TESTS APP_NAME_IN)
  cmake_parse_arguments(APP
                        "HEADER_TESTS"
                        ""
                        "INCLUDE_DIRS;DEPENDS;PACKAGE_DEPENDS;ADDITIONAL_LIBS"
                        ${ARGN})
                        
  SET(APP_NAME "test${APP_NAME_IN}")

  IF(BUILD_TESTING)
    MESSAGE(STATUS "configuring Tests ${APP_NAME}...") 
    # first of all we check for the dependencies
    MAP_CHECK_MODULE(_MISSING_DEP ${APP_DEPENDS})
    IF(_MISSING_DEP)
      MESSAGE("APP ${APP_NAME} won't be built, missing dependency: ${_MISSING_DEP}") 
      SET(APP_IS_ENABLED 0)
    ELSE(_MISSING_DEP)
      SET(APP_IS_ENABLED 1)
      # now check for every package if it is enabled. This overlaps a bit with
      # MAP_CHECK_MODULE ... 
      FOREACH(_package ${APP_PACKAGE_DEPENDS})
        IF((DEFINED MAP_USE_${_package}) AND NOT (MAP_USE_${_package}))
          MESSAGE("APP ${APP_NAME} won't be built. Turn on MAP_USE_${_package} if you want to use it.")
		  SET(APP_IS_ENABLED 0)
	    ENDIF()  
      ENDFOREACH()

	  SET(DEPENDS "${APP_DEPENDS}") 
	  SET(DEPENDS_BEFORE "not initialized")
	  SET(PACKAGE_DEPENDS "${APP_PACKAGE_DEPENDS}")
	  MAP_USE_MODULE("${APP_DEPENDS}") 
	
	  # ok, now create the APP itself
	  INCLUDE(files.cmake)
	  
      SET(APP_TESTS ${CXX_TEST_PATH}/${APP_NAME})
	  
	  INCLUDE(tests.cmake)
	
	  ORGANIZE_SOURCES(SOURCE ${TEST_CPP_FILES})

	   ADD_EXECUTABLE(${APP_NAME} ${TEST_CPP_FILES})

       target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${MatchPoint_BINARY_DIR} ${ALL_INCLUDE_DIRECTORIES})
       if(ALL_LIBRARY_DIRS)
         target_link_directories(${APP_NAME} PRIVATE ${ALL_LIBRARY_DIRS})
       endif()
       if(ALL_LIBRARIES)
         target_link_libraries(${APP_NAME} PRIVATE ${ALL_LIBRARIES})
       endif()
	   	    
    ENDIF(_MISSING_DEP)
  ENDIF(BUILD_TESTING)
ENDMACRO(MAP_CREATE_APPLICATION_TESTS)