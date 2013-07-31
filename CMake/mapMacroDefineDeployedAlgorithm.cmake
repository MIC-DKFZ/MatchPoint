
# MAP_DEFINE_DEPLOYED_ALGORITHM(<algName> FILES [file1 [file2 [...]]] LIBS [linkedLib1 [linkedLib2 [...]]])
#
# algName: Name of the target
# FILES: Files that should be added to the library
# LIBS: Libraries the target links to
#
# Helper macro that handles the definition of target for a deployed algorithm, its linkage,
# properties and export of the target information and the install definition for the algorithm.
MACRO(MAP_DEFINE_DEPLOYED_ALGORITHM algName)
  IF(MAP_DEPLOY_INCLUDED_ALGORITHMS)
    MESSAGE (STATUS "generating deployed algorithm: " ${algName})

    MACRO_PARSE_ARGUMENTS(ALG
                        "FILES;INCLUDE_DIRS;DEPENDS;PACKAGE_DEPENDS"
                        ""
                        ${ARGN})
  
    SET(targetName "dep_${algName}")

    MAP_CHECK_MODULE(_MISSING_DEP ${ALG_DEPENDS})
    IF(_MISSING_DEP)
      MESSAGE("Deployed algorithm ${ALG_NAME} won't be built, missing dependency: ${_MISSING_DEP}") 
      SET(ALG_IS_ENABLED 0)
    ELSE(_MISSING_DEP)
      SET(ALG_IS_ENABLED 1)
      # now check for every package if it is enabled. This overlaps a bit with
      # MAP_CHECK_MODULE ... 
      FOREACH(_package ${ALG_PACKAGE_DEPENDS})
        IF((DEFINED MAP_USE_${_package}) AND NOT (MAP_USE_${_package}))
          MESSAGE("Deployd algorithm ${ALG_NAME} won't be built. Turn on MAP_USE_${_package} if you want to use it.")
		  SET(ALG_IS_ENABLED 0)
	    ENDIF()  
      ENDFOREACH()

      IF(ALG_IS_ENABLED)
		SET(DEPENDS "${ALG_DEPENDS}") 
		SET(DEPENDS_BEFORE "not initialized")
		SET(PACKAGE_DEPENDS "${ALG_PACKAGE_DEPENDS}")
		MAP_USE_MODULE("${ALG_DEPENDS}") 
		
		INCLUDE_DIRECTORIES(. ${ALL_INCLUDE_DIRECTORIES})
		INCLUDE(files.cmake)
	
		ORGANIZE_SOURCES(SOURCE ${CPP_FILES}
			     HEADER ${H_FILES}
			     TPP ${TPP_FILES}
			     DOC ${DOX_FILES}
			     )

		LINK_DIRECTORIES(${ALL_LIBRARY_DIRS})
         
		ADD_LIBRARY(${targetName} SHARED ${ALG_FILES})

		TARGET_LINK_LIBRARIES(${targetName} ${ALL_LIBRARIES})

		SET_TARGET_PROPERTIES(${targetName} PROPERTIES
			OUTPUT_NAME "mdra-${MatchPoint_VERSION_MAJOR}-${MatchPoint_VERSION_MINOR}_${algName}"
			OUTPUT_NAME_DEBUG "mdra-D-${MatchPoint_VERSION_MAJOR}-${MatchPoint_VERSION_MINOR}_${algName}"
                        PREFIX "" )

        EXPORT(TARGETS ${targetName} APPEND FILE ${MatchPoint_TARGETS_FILE})
						
        INSTALL(TARGETS ${targetName}
          RUNTIME DESTINATION ${MatchPoint_INSTALL_DEP_DIR} COMPONENT RuntimeLibraries
          LIBRARY DESTINATION ${MatchPoint_INSTALL_DEP_DIR} COMPONENT RuntimeLibraries)
		
      ENDIF(ALG_IS_ENABLED)
    ENDIF(_MISSING_DEP)
  ENDIF(MAP_DEPLOY_INCLUDED_ALGORITHMS)  
ENDMACRO(MAP_DEFINE_DEPLOYED_ALGORITHM)
