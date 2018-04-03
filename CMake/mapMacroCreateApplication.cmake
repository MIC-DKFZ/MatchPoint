##################################################################
#
# MAP_CREATE_APPLICATION
#
#! Creates an application using the automatic module dependency 
#! system within MatchPoint.
#!
#! USAGE:
#!
#! \code
#! MAP_CREATE_APPLICATION( <appName>
#!     [INCLUDE_DIRS <include directories>]
#!     [DEPENDS <modules we need>]
#!     [PACKAGE_DEPENDS <packages we need, like ITK, Litmus>]
#! \endcode
#!
#! \param APP_NAME_IN The name for the new application
#
##################################################################
MACRO(MAP_CREATE_APPLICATION APP_NAME_IN)
  MACRO_PARSE_ARGUMENTS(APP
                        "INCLUDE_DIRS;INTERNAL_INCLUDE_DIRS;DEPENDS;PROVIDES;PACKAGE_DEPENDS;EXPORT_DEFINE"
                        "FORCE_STATIC;HEADERS_ONLY"
                        ${ARGN})
                        
  SET(APP_NAME ${APP_NAME_IN})
  
    MESSAGE(STATUS "configuring Application ${APP_NAME}...") 
    # first of all we check for the dependencies
    MAP_CHECK_MODULE(_MISSING_DEP ${APP_DEPENDS})
    IF(_MISSING_DEP)
      MESSAGE("Application ${APP_NAME} won't be built, missing dependency: ${_MISSING_DEP}") 
      SET(APP_IS_ENABLED 0)
    ELSE(_MISSING_DEP)
      SET(APP_IS_ENABLED 1)
      # now check for every package if it is enabled. This overlaps a bit with
      # MAP_CHECK_MODULE ... 
      FOREACH(_package ${APP_PACKAGE_DEPENDS})
        IF((DEFINED MAP_USE_${_package}) AND NOT (MAP_USE_${_package}))
          MESSAGE("Application ${APP_NAME} won't be built. Turn on MAP_USE_${_package} if you want to use it.")
		  SET(APP_IS_ENABLED 0)
	    ENDIF()  
      ENDFOREACH()

      IF(APP_IS_ENABLED)
		SET(DEPENDS "${APP_DEPENDS}") 
		SET(DEPENDS_BEFORE "not initialized")
		SET(PACKAGE_DEPENDS "${APP_PACKAGE_DEPENDS}")
		MAP_USE_MODULE("${APP_DEPENDS}") 
		
		IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/source)
          SET(ALL_INCLUDE_DIRECTORIES ${ALL_INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/source)
        ENDIF()

        IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
          SET(ALL_INCLUDE_DIRECTORIES ${ALL_INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/include)
        ENDIF()
	
		INCLUDE_DIRECTORIES(. ${ALL_INCLUDE_DIRECTORIES})
		INCLUDE(files.cmake)
	
		ORGANIZE_SOURCES(SOURCE ${CPP_FILES}
			     HEADER ${H_FILES}
			     TPP ${TPP_FILES}
			     DOC ${DOX_FILES}
			     )

		LINK_DIRECTORIES(${ALL_LIBRARY_DIRS})
     
	    SET(coverage_sources ${CPP_FILES} ${H_FILES} ${TXX_FILES})
	    
		ADD_EXECUTABLE(${APP_NAME} ${coverage_sources})
	     
        TARGET_LINK_LIBRARIES(${APP_NAME} ${ALL_LIBRARIES})	  
      ENDIF(APP_IS_ENABLED)
	  
    ENDIF(_MISSING_DEP)
    
ENDMACRO(MAP_CREATE_APPLICATION)
