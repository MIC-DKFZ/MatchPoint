
# MAP_DEFINE_DEPLOYED_ALGORITHM(<algName> FILES [file1 [file2 [...]]] LIBS [linkedLib1 [linkedLib2 [...]]])
#
# algName: Name of the target
# FILES: Files that should be added to the algorithm project
# INCLUDE_DIRS: All directories that should be added as include dirs to the project
# MODULE_DEPENDS: MatchPoint modules that the algorithm depends on (you need MatchPoint cmake macros for the module facility).
# PACKAGE_DEPENDS: MatchPoint third party packages the algorithm depends on (you need MatchPoint cmake macros for the module facility).
# DEPENDS: Cmake targets the algorithm depend on and should be linked to
# PROFILE: The profile file that should be used for the algorithm. If not set it is "./<algname>.profile".
# INSTALL_DIR: Installation directory for the algorithm. If not set ${MatchPoint_INSTALL_DEP_DIR} will be used.
# TARGETS_FILE: Targets file that should be used for export target informations. If not set ${MatchPoint_TARGETS_FILE} will be used.
#
# Helper macro that handles the definition of target for a deployed algorithm, its linkage,
# properties and export of the target information and the install definition for the algorithm.
MACRO(MAP_DEFINE_DEPLOYED_ALGORITHM algName)
  IF(MAP_DEPLOY_INCLUDED_ALGORITHMS)
    MESSAGE (STATUS "generating deployed algorithm: " ${algName})
    MACRO_PARSE_ARGUMENTS(ALG
                        "FILES;INCLUDE_DIRS;DEPENDS;PACKAGE_DEPENDS;MODULE_DEPENDS;PROFILE;INSTALL_DIR;TARGETS_FILE"
                        ""
                        ${ARGN})
  
    SET(targetName "dep_${algName}")

	IF(ALG_MODULE_DEPENDS OR ALG_PACKAGE_DEPENDS)
        MESSAGE (STATUS "... checking MatchPoint modules and packages...")
		#we have module dependencies or target dependencies given, so we need to check
		#them and compile the information
		MAP_CHECK_MODULE(_MISSING_DEP ${ALG_MODULE_DEPENDS})
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
		  
		  SET(DEPENDS "${ALG_MODULE_DEPENDS}") 
		  SET(DEPENDS_BEFORE "not initialized")
		  SET(PACKAGE_DEPENDS "${ALG_PACKAGE_DEPENDS}")
		  MAP_USE_MODULE("${ALG_MODULE_DEPENDS}") 
		  
		ENDIF(_MISSING_DEP)
	ELSE(ALG_MODULE_DEPENDS OR ALG_PACKAGE_DEPENDS)
	  SET(ALG_IS_ENABLED 1)
	ENDIF(ALG_MODULE_DEPENDS OR ALG_PACKAGE_DEPENDS)

	IF(NOT ALG_TARGETS_FILE)
	 SET(ALG_TARGETS_FILE ${MatchPoint_TARGETS_FILE})
	ENDIF(NOT ALG_TARGETS_FILE)

	IF(NOT ALG_INSTALL_DIR)
	 SET(ALG_INSTALL_DIR ${MatchPoint_INSTALL_DEP_DIR})
	ENDIF(NOT ALG_INSTALL_DIR)

	IF(NOT ALG_PROFILE)
	 SET(ALG_PROFILE "${algName}.profile")
	ENDIF(NOT ALG_PROFILE)

    IF(NOT _MISSING_DEP)
      IF(ALG_IS_ENABLED)
		
        MESSAGE(STATUS "... generate MDRA profile (from ${ALG_PROFILE})...")
		
		CREATE_ALGORITHM_PROFILE(${algName} ${ALG_PROFILE})
		
        MESSAGE(STATUS "... algorithm UID: ${ALGORITHM_PROFILE_UID}")

		INCLUDE_DIRECTORIES(. ${CURRENT_BINARY_DIR} ${ALL_INCLUDE_DIRECTORIES} ${ALG_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
	
		LINK_DIRECTORIES(${ALL_LIBRARY_DIRS})
         
		ADD_LIBRARY(${targetName} SHARED ${ALG_FILES} ${ALGORITHM_PROFILE_FILE})

		TARGET_LINK_LIBRARIES(${targetName} ${ALL_LIBRARIES} ${ALG_DEPENDS})

		SET_TARGET_PROPERTIES(${targetName} PROPERTIES
			OUTPUT_NAME "mdra-${MatchPoint_VERSION_MAJOR}-${MatchPoint_VERSION_MINOR}_${algName}"
			OUTPUT_NAME_DEBUG "mdra-D-${MatchPoint_VERSION_MAJOR}-${MatchPoint_VERSION_MINOR}_${algName}"
                        PREFIX "" )

        EXPORT(TARGETS ${targetName} APPEND FILE ${ALG_TARGETS_FILE})
						
        INSTALL(TARGETS ${targetName}
          RUNTIME DESTINATION ${ALG_INSTALL_DIR} COMPONENT RuntimeLibraries
          LIBRARY DESTINATION ${ALG_INSTALL_DIR} COMPONENT RuntimeLibraries)

        INSTALL(FILES ${ALGORITHM_PROFILE_XML_FILE} DESTINATION ${ALG_INSTALL_DIR} COMPONENT RuntimeLibraries)		  

		ENDIF(ALG_IS_ENABLED)
    ENDIF(NOT _MISSING_DEP)
  ENDIF(MAP_DEPLOY_INCLUDED_ALGORITHMS)  
ENDMACRO(MAP_DEFINE_DEPLOYED_ALGORITHM)
