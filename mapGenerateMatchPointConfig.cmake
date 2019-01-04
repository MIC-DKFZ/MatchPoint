# Generate the MatchPointConfig.cmake file in the build tree.  Also configure
# one for installation.  The file tells external projects how to use
# MatchPoint.

#-----------------------------------------------------------------------------
# Settings specific to the build tree.

# The "use" file.
SET(MatchPoint_USE_FILE ${MatchPoint_BINARY_DIR}/UseMatchPoint.cmake)

# The library dependencies file.
SET(MatchPoint_LIBRARY_DEPENDS_FILE ${MatchPoint_BINARY_DIR}/MatchPointLibraryDepends.cmake)

# Library directory.
SET(MatchPoint_LIBRARY_DIRS_CONFIG ${MatchPoint_LIBRARY_PATH})

# Determine the include directories needed.
SET(MatchPoint_INCLUDE_DIRS_CONFIG ${MatchPoint_BINARY_DIR} ${MatchPoint_BINARY_DIR}/modulesConf ${MatchPoint_SOURCE_DIR}/Code)

foreach(dir Algorithms/Common Algorithms/ITK Core Deployment IO ITK Utilities)
  list(APPEND MatchPoint_INCLUDE_DIRS_CONFIG ${MatchPoint_SOURCE_DIR}/Code/${dir} ${MatchPoint_SOURCE_DIR}/Code/${dir}/include)
endforeach()

foreach(dir Algorithms/Common Algorithms/ITK)
  list(APPEND MatchPoint_INCLUDE_DIRS_CONFIG ${MatchPoint_SOURCE_DIR}/Code/${dir}/boxed ${MatchPoint_SOURCE_DIR}/Code/${dir}/deployed)
endforeach()

list(APPEND MatchPoint_INCLUDE_DIRS_CONFIG ${MatchPoint_SOURCE_DIR}/Code/Deployment/deployed)

IF(MAP_BUILD_Ontology)
  list(APPEND MatchPoint_INCLUDE_DIRS_CONFIG ${MatchPoint_SOURCE_DIR}/Code/Ontology/Common/include)
  IF(MAP_BUILD_Ontology_simple)
    list(APPEND MatchPoint_INCLUDE_DIRS_CONFIG ${MatchPoint_SOURCE_DIR}/Code/Ontology/Simple/include)
  ENDIF(MAP_BUILD_Ontology_simple)
ENDIF(MAP_BUILD_Ontology)

#-----------------------------------------------------------------------------
# Configure MatchPointConfig.cmake for the build tree.
CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/MatchPointConfig.cmake.in
               ${MatchPoint_BINARY_DIR}/MatchPointConfig.cmake @ONLY IMMEDIATE)

#-----------------------------------------------------------------------------
# Settings specific to the install tree.

# The "use" file.
SET(MatchPoint_USE_FILE ${CMAKE_INSTALL_PREFIX}${MatchPoint_INSTALL_PACKAGE_DIR}/UseMatchPoint.cmake)

# The library dependencies file.
SET(MatchPoint_LIBRARY_DEPENDS_FILE
    ${CMAKE_INSTALL_PREFIX}${MatchPoint_INSTALL_PACKAGE_DIR}/MatchPointLibraryDepends.cmake)

# The build settings file.
SET(MatchPoint_BUILD_SETTINGS_FILE
    ${CMAKE_INSTALL_PREFIX}${MatchPoint_INSTALL_PACKAGE_DIR}/MatchPointBuildSettings.cmake)

# Include directories.
SET(MatchPoint_INCLUDE_DIRS_CONFIG
  ${MatchPoint_INCLUDE_DIRS_INSTALL_TREE}
  ${MatchPoint_INCLUDE_DIRS_SYSTEM}
)

# Link directories.
SET(MatchPoint_LIBRARY_DIRS_CONFIG ${CMAKE_INSTALL_PREFIX}${MatchPoint_INSTALL_LIB_DIR})

#-----------------------------------------------------------------------------
# Configure MatchPointConfig.cmake for the install tree.
CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/MatchPointConfig.cmake.in
               ${MatchPoint_BINARY_DIR}/MatchPointConfig.cmake.install @ONLY IMMEDIATE)
