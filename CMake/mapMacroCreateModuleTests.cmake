##################################################################
#
# MAP_CREATE_MODULE_TESTS
#
#! Creates tests for a module.
#!
#! USAGE:
#!
#! \code
#! MAP_CREATE_MODULE_TESTS( <moduleName>
#!     [INCLUDE_DIRS <include directories>]
#!     [INTERNAL_INCLUDE_DIRS <internally used include directories>]
#!     [DEPENDS <additional modules we need>]
#!     [PROVIDES <library name which is built>]
#!     [PACKAGE_DEPENDS <packages we need, like ITK, Litmus>]
#!     [HEADER_TEST]
#! \endcode
#!
#! \param MODULE_NAME_IN The name for the new module
#
##################################################################

SET(MAP_HEADER_TESTS_HEADER
"// -----------------------------------------------------------------------\n"
"// MatchPoint - DKFZ Registration Platform\n"
"//\n"
"// (c) Copyright 2007, DKFZ, Heidelberg, Germany\n"
"// ALL RIGHTS RESERVED\n"
"//\n"
"// THIS FILE CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION OF DKFZ.\n"
"// ANY DUPLICATION, MODIFICATION, DISTRIBUTION, OR\n"
"// DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY PROHIBITED\n"
"// WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF DKFZ.\n"
"//\n"
"//------------------------------------------------------------------------\n"
"// Automatically generated header test file \n"
"#if defined(_MSC_VER)\n"
"#pragma warning ( disable : 4786 )\n"
"#endif\n"
"#include <iostream>\n")

SET(MAP_HEADER_TESTS_FOOTER
"\nint main ( int , char**  )\n"
"{\n"
"  return EXIT_SUCCESS\;\n"
"}\n")

MACRO(MAP_CREATE_MODULE_TESTS MODULE_NAME_IN)
  MACRO_PARSE_ARGUMENTS(MODULE
                        "INCLUDE_DIRS;INTERNAL_INCLUDE_DIRS;DEPENDS;DEPENDS_INTERNAL;PROVIDES;PACKAGE_DEPENDS;ADDITIONAL_LIBS"
                        "HEADER_TESTS"
                        ${ARGN})

  SET(MODULE_NAME "test${MODULE_NAME_IN}")

  #Allways needs his own module for tests
  SET(MODULE_DEPENDS ${MODULE_DEPENDS} ${MODULE_NAME_IN})

  IF(BUILD_TESTING)
    MESSAGE(STATUS "configuring Tests ${MODULE_NAME}...")

    # first of all we check for the dependencies
    MAP_CHECK_MODULE(_MISSING_DEP ${MODULE_DEPENDS})
    IF(_MISSING_DEP)
      MESSAGE("Module ${MODULE_NAME} won't be built, missing dependency: ${_MISSING_DEP}")
      SET(MODULE_IS_ENABLED 0)
    ELSE(_MISSING_DEP)
      SET(MODULE_IS_ENABLED 1)
      # now check for every package if it is enabled. This overlaps a bit with
      # MAP_CHECK_MODULE ...
      FOREACH(_package ${MODULE_PACKAGE_DEPENDS})
        IF((DEFINED MAP_USE_${_package}) AND NOT (MAP_USE_${_package}))
          MESSAGE("Module ${MODULE_NAME} won't be built. Turn on MAP_USE_${_package} if you want to use it.")
		  SET(MODULE_IS_ENABLED 0)
	    ENDIF()
      ENDFOREACH()

	  SET(DEPENDS "${MODULE_DEPENDS}")
	  SET(DEPENDS_BEFORE "not initialized")
	  SET(PACKAGE_DEPENDS "${MODULE_PACKAGE_DEPENDS}")
	  SET(ALL_INCLUDE_DIRECTORIES "")
	  SET(ALL_LIBRARIES "")
	  SET(ALL_LIBRARY_DIRS "")
	  MAP_USE_MODULE("${MODULE_DEPENDS}")

	  # ok, now create the module itself
	  INCLUDE_DIRECTORIES(. ${ALL_INCLUDE_DIRECTORIES})
	  INCLUDE(files.cmake)

      SET(MODULE_TESTS ${CXX_TEST_PATH}/${MODULE_NAME})

	  INCLUDE(tests.cmake)

	  ORGANIZE_SOURCES(SOURCE ${TEST_CPP_FILES})

       IF(ALL_LIBRARY_DIRS)
         # LINK_DIRECTORIES applies only to targets which are added after the call to LINK_DIRECTORIES
		 LINK_DIRECTORIES(${ALL_LIBRARY_DIRS})
       ENDIF(ALL_LIBRARY_DIRS)

       # Check if we have test source code
       LIST(LENGTH TEST_CPP_FILES TEST_CPP_COUNT)
       IF(NOT ${TEST_CPP_COUNT})
	     MESSAGE("Cannot generate test module ${MODULE_NAME}. No test source code specified in files.cmake (TEST_CPP_FILES).")
       ENDIF(NOT ${TEST_CPP_COUNT})
       ADD_EXECUTABLE(${MODULE_NAME} ${TEST_CPP_FILES})

       IF(ALL_LIBRARIES)
         TARGET_LINK_LIBRARIES(${MODULE_NAME} ${ALL_LIBRARIES})
       ENDIF(ALL_LIBRARIES)

	   # Necessary so the build waits for Litmus to build
       ADD_DEPENDENCIES(${MODULE_NAME} Litmus)

	   IF(MODULE_HEADER_TESTS)
         MESSAGE(STATUS "generating header tests ${MODULE_NAME}...")
     	 SET(HEADER_TEST_CPP "${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}Header.cpp")
         MESSAGE(STATUS "generating header tests ${HEADER_TEST_CPP}")

	     FILE(WRITE ${HEADER_TEST_CPP} ${MAP_HEADER_TESTS_HEADER})
		 FOREACH(_h_file ${H_FILES})
		   FILE(APPEND ${HEADER_TEST_CPP} "#include <${_h_file}>\n")
		 ENDFOREACH()
         FILE(APPEND ${HEADER_TEST_CPP} ${MAP_HEADER_TESTS_FOOTER})

         ADD_EXECUTABLE(${MODULE_NAME}Header ${HEADER_TEST_CPP})

         IF(ALL_LIBRARIES)
           TARGET_LINK_LIBRARIES(${MODULE_NAME}Header ${ALL_LIBRARIES})
         ENDIF(ALL_LIBRARIES)

         ADD_TEST(${MODULE_NAME}Header ${CXX_TEST_PATH}/${MODULE_NAME}Header)

         # Necessary so the build waits for Litmus to build
         ADD_DEPENDENCIES(${MODULE_NAME}Header Litmus)

	   ENDIF(MODULE_HEADER_TESTS)


    ENDIF(_MISSING_DEP)
  ENDIF(BUILD_TESTING)
ENDMACRO(MAP_CREATE_MODULE_TESTS)
