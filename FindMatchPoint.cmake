#
# Find an MatchPoint installation or build tree.
#
# When MatchPoint is found, the MatchPointConfig.cmake file is sourced to setup the
# location and configuration of MatchPoint.  Please read this file, or
# MatchPointConfig.cmake.in from the MatchPoint source tree for the full list of
# definitions.  Of particular interest is
#
# MatchPoint_USE_FILE   - A CMake source file that can be included
#                         to set the include directories, library
#                         directories, and preprocessor macros.
#
# In addition to the variables read from MatchPointConfig.cmake, this find
# module also defines
#
# MatchPoint_DIR        - The directory containing MatchPointConfig.cmake.  This is either
#                         the root of the build tree, or the lib/InsightToolkit
#                         directory.  This is the only cache entry.
#
# MatchPoint_FOUND      - Whether MatchPoint was found.  If this is true, MatchPoint_DIR is okay.
#
# USE_MatchPoint_FILE   - The full path to the UseMatchPoint.cmake file.  This is provided
#                         for backward compatability.  Use MatchPoint_USE_FILE instead.
#

SET(MatchPoint_DIR_STRING "directory containing MatchPointConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/MatchPoint for an installation.")

# Search only if the location is not already known.
IF(NOT MatchPoint_DIR)
  # Get the system search path as a list.
  IF(UNIX)
    STRING(REGEX MATCHALL "[^:]+" MatchPoint_DIR_SEARCH1 "$ENV{PATH}")
  ELSE(UNIX)
    STRING(REGEX REPLACE "\\\\" "/" MatchPoint_DIR_SEARCH1 "$ENV{PATH}")
  ENDIF(UNIX)
  STRING(REGEX REPLACE "/;" ";" MatchPoint_DIR_SEARCH2 ${MatchPoint_DIR_SEARCH1})

  # Construct a set of paths relative to the system search path.
  SET(MatchPoint_DIR_SEARCH "")
  FOREACH(dir ${MatchPoint_DIR_SEARCH2})
    SET(MatchPoint_DIR_SEARCH ${ITK_DIR_SEARCH} "${dir}/../lib/MatchPoint")
  ENDFOREACH(dir)

  #
  # Look for an installation or build tree.
  #
  FIND_PATH(MatchPoint_DIR MatchPointConfig.cmake
    # Look for an environment variable MatchPoint_DIR.
    $ENV{MatchPoint_DIR}

    # Look in places relative to the system executable search path.
    ${MatchPoint_DIR_SEARCH}

    # Look in standard UNIX install locations.
    /usr/local/lib/InsightToolkit
    /usr/lib/InsightToolkit

    # Read from the CMakeSetup registry entries.  It is likely that
    # MatchPoint will have been recently built.
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild1]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild2]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild3]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild4]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild5]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild6]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild7]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild8]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild9]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild10]

    # Help the user find it if we cannot.
    DOC "The ${MatchPoint_DIR_STRING}"
  )
ENDIF(NOT MatchPoint_DIR)

# If MatchPoint was found, load the configuration file to get the rest of the
# settings.
IF(MatchPoint_DIR)
  SET(MatchPoint_FOUND 1)
  INCLUDE(${MatchPoint_DIR}/MatchPointConfig.cmake)

  # Set USE_MatchPoint_FILE for backward-compatability.
  SET(USE_MatchPoint_FILE ${MatchPoint_USE_FILE})
ELSE(MatchPoint_DIR)
  SET(MatchPoint_FOUND 0)
  IF(MatchPoint_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Please set MatchPoint_DIR to the ${MatchPoint_DIR_STRING}")
  ENDIF(MatchPoint_FIND_REQUIRED)
ENDIF(MatchPoint_DIR)
