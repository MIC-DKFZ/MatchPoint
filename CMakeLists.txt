#-----------------------------------------------------------------------------
# This is the root MatchPoint CMakeList file.
#-----------------------------------------------------------------------------

PROJECT(MatchPoint)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

# MatchPoint version number.
SET(MatchPoint_VERSION_MAJOR "0")
SET(MatchPoint_VERSION_MINOR "13")
SET(MatchPoint_VERSION_PATCH "0")

# Version string should not include patch level.  The major.minor is
# enough to distinguish available features of the toolkit.
SET(MatchPoint_VERSION_STRING "${MatchPoint_VERSION_MAJOR}.${MatchPoint_VERSION_MINOR}")
SET(MatchPoint_FULL_VERSION_STRING "${MatchPoint_VERSION_MAJOR}.${MatchPoint_VERSION_MINOR}.${MatchPoint_VERSION_PATCH}")

# MatchPoint DLL interface version number.
SET(MatchPoint_DLL_INTERFACE_VERSION_MAJOR "3")
SET(MatchPoint_DLL_INTERFACE_VERSION_MINOR "0")

# Version string.
SET(MatchPoint_DLL_INTERFACE_VERSION_STRING "${MatchPoint_DLL_INTERFACE_VERSION_MAJOR}.${MatchPoint_DLL_INTERFACE_VERSION_MINOR}")

#-----------------------------------------------------------------------------
# CMake Function(s) and Macro(s)
#-----------------------------------------------------------------------------

include(CMake/MacroParseArguments.cmake)
include(CMake/mapMacroCreateModuleConf.cmake)
include(CMake/mapMacroCreateModule.cmake)
include(CMake/mapMacroCreateModuleTests.cmake)
include(CMake/mapMacroCheckModule.cmake)
include(CMake/mapMacroUseModule.cmake)
include(CMake/mapFunctionOrganizeSources.cmake)
include(CMake/mapFunctionCreateAlgorithmProfile.cmake)
include(CMake/mapMacroCreateApplication.cmake)
include(CMake/mapMacroCreateApplicationTests.cmake)
include(CMake/mapMacroDefineDeployedAlgorithm.cmake)
include(CMake/mapMacroCheckITKState.cmake)

#-----------------------------------------------------------------------------
# Basis config MatchPoint module infrastructure
#-----------------------------------------------------------------------------

set(MAP_MODULES_CONF_DIR ${MatchPoint_BINARY_DIR}/modulesConf CACHE INTERNAL "Modules Conf")
set(MAP_MODULES_PACKAGE_DEPENDS_DIR ${MatchPoint_SOURCE_DIR}/CMake/PackageDepends)
set(MODULES_PACKAGE_DEPENDS_DIRS ${MAP_MODULES_PACKAGE_DEPENDS_DIR})

#-----------------------------------------------------------------------------
# Testing setup
# Configure Dart testing support.  This should be done before any
# MESSAGE(FATAL_ERROR ...) commands are invoked.
#-----------------------------------------------------------------------------

SET(CTEST_NEW_FORMAT 1)
INCLUDE(CTest)
ENABLE_TESTING()
IF(BUILD_TESTING)
  CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/CMake/RemoveTemporaryFiles.cmake.in
    ${MatchPoint_BINARY_DIR}/CMake/RemoveTemporaryFiles.cmake @ONLY IMMEDIATE)
  CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/CMake/mapSampleBuildTest.cmake.in
    ${MatchPoint_BINARY_DIR}/CMake/mapSampleBuildTest.cmake @ONLY)
  CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/CMake/CTestCustom.ctest.in
    ${MatchPoint_BINARY_DIR}/CMake/CTestCustom.ctest @ONLY)
  FILE(WRITE ${MatchPoint_BINARY_DIR}/CTestCustom.cmake
    "INCLUDE(\"${MatchPoint_BINARY_DIR}/CMake/CTestCustom.ctest\")\n")

  SET(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  MARK_AS_ADVANCED(BUILDNAME)
ENDIF(BUILD_TESTING)



#-----------------------------------------------------------------------------
# Output directories.
#-----------------------------------------------------------------------------

IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH ${MatchPoint_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")
ENDIF(NOT LIBRARY_OUTPUT_PATH)
IF(NOT EXECUTABLE_OUTPUT_PATH)
  SET (EXECUTABLE_OUTPUT_PATH ${MatchPoint_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
ENDIF(NOT EXECUTABLE_OUTPUT_PATH)

MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)
SET(MatchPoint_LIBRARY_PATH "${LIBRARY_OUTPUT_PATH}")
SET(MatchPoint_EXECUTABLE_PATH "${EXECUTABLE_OUTPUT_PATH}")

SET(CXX_TEST_PATH ${EXECUTABLE_OUTPUT_PATH})

#-----------------------------------------------------------------------------
# Installation vars.
# MatchPoint_INSTALL_BIN_DIR          - binary dir (executables)
# MatchPoint_INSTALL_LIB_DIR          - library dir (libs)
# MatchPoint_INSTALL_DEP_DIR          - deployed algorithms dir
# MatchPoint_INSTALL_DATA_DIR         - share dir ( data, etc)
# MatchPoint_INSTALL_EXAMPLE_DIR      - examples dir
# MatchPoint_INSTALL_INCLUDE_DIR      - include dir (headers)
# MatchPoint_INSTALL_PACKAGE_DIR      - package/export configuration files
# MatchPoint_INSTALL_NO_DEVELOPMENT   - do not install development files
# MatchPoint_INSTALL_NO_RUNTIME       - do not install runtime files
# MatchPoint_INSTALL_NO_DOCUMENTATION - do not install documentation files
# Remark: needs directory are stored with no leading slash (CMake 2.4 and newer)
#-----------------------------------------------------------------------------

SET(MatchPoint_INSTALL_VERSION_PATH "MatchPoint-${MatchPoint_VERSION_MAJOR}.${MatchPoint_VERSION_MINOR}")

IF(NOT MatchPoint_INSTALL_BIN_DIR)
  SET(MatchPoint_INSTALL_BIN_DIR "bin")
ENDIF(NOT MatchPoint_INSTALL_BIN_DIR)

IF(NOT MatchPoint_INSTALL_LIB_DIR)
  SET(MatchPoint_INSTALL_LIB_DIR "lib")
ENDIF(NOT MatchPoint_INSTALL_LIB_DIR)

IF(NOT MatchPoint_INSTALL_DEP_DIR)
  SET(MatchPoint_INSTALL_DEP_DIR "deployed/${MatchPoint_INSTALL_VERSION_PATH}")
ENDIF(NOT MatchPoint_INSTALL_DEP_DIR)

IF(NOT MatchPoint_INSTALL_DATA_DIR)
  SET(MatchPoint_INSTALL_DATA_DIR "share/${MatchPoint_INSTALL_VERSION_PATH}")
ENDIF(NOT MatchPoint_INSTALL_DATA_DIR)

IF(NOT MatchPoint_INSTALL_INCLUDE_DIR)
  SET(MatchPoint_INSTALL_INCLUDE_DIR "include/${MatchPoint_INSTALL_VERSION_PATH}")
ENDIF(NOT MatchPoint_INSTALL_INCLUDE_DIR)

IF(NOT MatchPoint_INSTALL_EXAMPLE_DIR)
  SET(MatchPoint_INSTALL_EXAMPLE_DIR "examples/${MatchPoint_INSTALL_VERSION_PATH}")
ENDIF(NOT MatchPoint_INSTALL_EXAMPLE_DIR)

IF(NOT MatchPoint_INSTALL_PACKAGE_DIR)
  SET(MatchPoint_INSTALL_PACKAGE_DIR "${MatchPoint_INSTALL_LIB_DIR}/cmake/${MatchPoint_INSTALL_VERSION_PATH}"
    CACHE INTERNAL "")
ENDIF(NOT MatchPoint_INSTALL_PACKAGE_DIR)

IF(NOT MatchPoint_INSTALL_NO_DEVELOPMENT)
  SET(MatchPoint_INSTALL_NO_DEVELOPMENT 0)
ENDIF(NOT MatchPoint_INSTALL_NO_DEVELOPMENT)

IF(NOT MatchPoint_INSTALL_NO_DOCUMENTATION)
  SET(MatchPoint_INSTALL_NO_DOCUMENTATION 0)
ENDIF(NOT MatchPoint_INSTALL_NO_DOCUMENTATION)

IF(NOT MatchPoint_INSTALL_NO_EXAMPLES)
  SET(MatchPoint_INSTALL_NO_EXAMPLES 0)
ENDIF(NOT MatchPoint_INSTALL_NO_EXAMPLES)

# set MatchPoint_DIR so it can be used by subprojects
SET(MatchPoint_DIR "${CMAKE_BINARY_DIR}" CACHE INTERNAL "MatchPoint dir to be used by subprojects")

# set Testing dirs
SET(MatchPointTesting_SOURCE_DIR ${MatchPoint_SOURCE_DIR}/Testing)
SET(MatchPointTesting_BINARY_DIR ${MatchPoint_BINARY_DIR}/Testing)

#-----------------------------------------------------------------------------
# generate deploy algorithms
OPTION(MAP_DEPLOY_INCLUDED_ALGORITHMS "Activate the generation and deployment of the default algorithms bundled in MatchPoint." ON)

#-----------------------------------------------------------------------------
# Advanced MatchPoint configuration
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# turn on concept checking
IF( NOT BORLAND )
  OPTION(MAP_USE_CONCEPT_CHECKING "Turn on concept checking to give helpful errors at compile time if a type cannot be used as a template parameter." ON)
  MARK_AS_ADVANCED(MAP_USE_CONCEPT_CHECKING)
  OPTION(MAP_USE_STRICT_CONCEPT_CHECKING "Turn on Strict concept checking to give more stringent errors at compile time if a type cannot be used as a template parameter." OFF)
  MARK_AS_ADVANCED(MAP_USE_STRICT_CONCEPT_CHECKING)
ELSE( NOT BORLAND )
  SET(MAP_USE_CONCEPT_CHECKING OFF)
  MARK_AS_ADVANCED(MAP_USE_CONCEPT_CHECKING)
  SET(MAP_USE_STRICT_CONCEPT_CHECKING OFF)
  MARK_AS_ADVANCED(MAP_USE_STRICT_CONCEPT_CHECKING)
ENDIF( NOT BORLAND )

#-----------------------------------------------------------------------------
# turn off "lean and mean" mode
OPTION(MAP_LEAN_AND_MEAN "When switching to \"lean and mean\" MatchPoint will be build without any code used in the context of debug or status information (e.g. mapLogDebugMacro or mapLogInfoMacro are ignored). Only use this mode, if you are sure that you need plain working code and cannot spare the maintanance overhead." OFF)
MARK_AS_ADVANCED(MAP_LEAN_AND_MEAN)

#-----------------------------------------------------------------------------
# turn off "enforce mature code" mode
OPTION(MAP_ENFORCE_MATURE_CODE "When switching to \"mature code enforcement\" MatchPoint will follow the SIDT coding policy an only alow and build code not labeled as experimental." OFF)
MARK_AS_ADVANCED(MAP_ENFORCE_MATURE_CODE)

#-----------------------------------------------------------------------------
# turn off "disable ITK IO factory auto register" mode
OPTION(MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER "When activated MatchPoint will disable the ITK io factory auot registration. This is needed for useage in applications like MITK. Please check dokumentation (mapConfigure.h) for more information." OFF)
MARK_AS_ADVANCED(MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER)

#-----------------------------------------------------------------------------
# MatchPoint build configuration options.
IF (WIN32)
  OPTION(BUILD_SHARED_LIBS "Build MatchPoint with shared libraries." OFF)
ELSE (WIN32)
  OPTION(BUILD_SHARED_LIBS "Build MatchPoint with shared libraries." ON)
ENDIF (WIN32)

SET(MAP_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

IF(NOT MAP_NO_LIBRARY_VERSION)
  # This setting of SOVERSION assumes that any API change
  # will increment either the minor or major version number of MatchPoint.
  SET(MAP_LIBRARY_PROPERTIES 
      VERSION   "${MatchPoint_VERSION_MAJOR}.${MatchPoint_VERSION_MINOR}.${MatchPoint_VERSION_PATCH}"
      SOVERSION "${MatchPoint_VERSION_MAJOR}.${MatchPoint_VERSION_MINOR}"
     )
ENDIF(NOT MAP_NO_LIBRARY_VERSION)

#-----------------------------------------------------------------------------
# Configure the default MatchPoint_DATA_ROOT for the location of MatchPoint data.
#-----------------------------------------------------------------------------

FIND_PATH(MatchPoint_DATA_ROOT MatchPointData.readme ${MatchPoint_SOURCE_DIR}/Testing/Data $ENV{MatchPoint_DATA_ROOT})
MARK_AS_ADVANCED(MatchPoint_DATA_ROOT)

#-----------------------------------------------------------------------------
# Configure files with settings for use by the build.
# e.g. 
#-----------------------------------------------------------------------------

CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/mapConfigure.h.in 
  ${MatchPoint_BINARY_DIR}/mapConfigure.h)
  
IF(NOT MatchPoint_INSTALL_NO_DEVELOPMENT)
  INSTALL(FILES ${MatchPoint_BINARY_DIR}/mapConfigure.h
    DESTINATION ${MatchPoint_INSTALL_INCLUDE_DIR}
    COMPONENT Development)
ENDIF(NOT MatchPoint_INSTALL_NO_DEVELOPMENT)

#-----------------------------------------------------------------------------
# The entire MatchPoint tree should use the same include path, except for the
# Wrapping directory.
#-----------------------------------------------------------------------------

#Default include dir. Others dirs will be defined by activated subprojects
INCLUDE_DIRECTORIES( ${MatchPoint_BINARY_DIR}
)

LINK_DIRECTORIES(${LIBARY_OUTPUT_PATH})

#Prepare the correct target information export by the subprojects
SET(MatchPoint_TARGETS_FILE "${MatchPoint_BINARY_DIR}/MatchPointTargets.cmake")
FILE(WRITE ${MatchPoint_TARGETS_FILE} "# Generated by CMake, do not edit!")

#-----------------------------------------------------------------------------
# Dispatch the build into the proper subdirectories.
#-----------------------------------------------------------------------------

OPTION(MAP_BUILD_APPS "Build MatchPoint applications." ON)

MESSAGE (STATUS "generating Project MatchPoint")
ADD_SUBDIRECTORY (Code)
ADD_SUBDIRECTORY (Documentation)

IF (BUILD_TESTING)
  ADD_SUBDIRECTORY (Testing)
ENDIF (BUILD_TESTING)

ADD_SUBDIRECTORY (Examples)
IF (MAP_BUILD_APPS)
	ADD_SUBDIRECTORY (Applications)
ENDIF()

#-----------------------------------------------------------------------------
# Help other projects use MatchPoint.
#-----------------------------------------------------------------------------

EXPORT(PACKAGE MatchPoint)

# Copy the UseMatchPoint.cmake file to the binary tree for backward compatability.
CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/UseMatchPoint.cmake.in
               ${MatchPoint_BINARY_DIR}/UseMatchPoint.cmake COPYONLY IMMEDIATE)
		   
# Create the MatchPointConfig.cmake file containing the MatchPoint configuration.
INCLUDE(${MAP_MODULES_CONF_DIR}/ITKConfig.cmake)
INCLUDE(${MatchPoint_SOURCE_DIR}/mapGenerateMatchPointConfig.cmake)

IF(NOT MatchPoint_INSTALL_NO_DEVELOPMENT)
  INSTALL(FILES
    ${MatchPoint_BINARY_DIR}/MatchPointConfig.cmake
    ${MatchPoint_BINARY_DIR}/UseMatchPoint.cmake
    DESTINATION ${MatchPoint_INSTALL_PACKAGE_DIR}
    COMPONENT Development
    )

   INSTALL(EXPORT MatchPointExport DESTINATION ${MatchPoint_INSTALL_PACKAGE_DIR} COMPONENT Development)
ENDIF(NOT MatchPoint_INSTALL_NO_DEVELOPMENT)


#-----------------------------------------------------------------------------
# Installer
#-----------------------------------------------------------------------------
#INCLUDE (CPack)
