#-----------------------------------------------------------------------------
# Find ITK.
#-----------------------------------------------------------------------------

IF(DEFINED ITK_DIR)
  IF(NOT IS_ABSOLUTE ${ITK_DIR})
    SET(ITK_DIR "${MatchPoint_BINARY_DIR}/${ITK_DIR}")
  ENDIF(NOT IS_ABSOLUTE ${ITK_DIR})
ENDIF(DEFINED ITK_DIR)

FIND_PACKAGE(ITK 5 REQUIRED)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

IF(NOT WIN32 AND NOT ITK_BUILD_SHARED)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK build with shared libs.  Please set CMAKE_BUILD_SHARED to ON in ITK.")
ENDIF(NOT WIN32 AND NOT ITK_BUILD_SHARED)

LIST(APPEND ALL_INCLUDE_DIRECTORIES ${ITK_INCLUDE_DIRS})
LIST(APPEND ALL_LIBRARIES ${ITK_LIBRARIES})

LINK_DIRECTORIES(${ITK_LIBRARY_DIRS}) 

OPTION(MAP_USE_SYSTEM_GDCM "Activate checker to choose a GDCM installation that was linked with ITK. (This is needed e.g. when building against an ITK that is distributed with MITK. MITK uses its own GDCM and not the one distributed with ITK.)" OFF)     

IF (MAP_USE_SYSTEM_GDCM)
  IF(DEFINED GDCM_DIR)
	IF(NOT IS_ABSOLUTE ${GDCM_DIR})
	  SET(GDCM_DIR "${MatchPoint_BINARY_DIR}/${GDCM_DIR}")
	ENDIF(NOT IS_ABSOLUTE ${GDCM_DIR})
  ENDIF(DEFINED GDCM_DIR)

  MESSAGE (STATUS "MatchPoint uses system GDCM instead of ITK distribution.")
  FIND_PACKAGE(GDCM PATHS ${ITK_GDCM_DIR} ${GDCM_DIR} REQUIRED)
  INCLUDE(${GDCM_USE_FILE})
  LIST(APPEND ALL_INCLUDE_DIRECTORIES ${GDCM_INCLUDE_DIRS})
  LIST(APPEND ALL_LIBRARIES ${GDCM_LIBRARIES})	  
ENDIF (MAP_USE_SYSTEM_GDCM)

OPTION(MAP_USE_SYSTEM_HDF5 "Activate checker to choose a HDF5 installation that was linked with ITK. (This is needed e.g. when building against an ITK that is distributed with MITK. MITK uses its own HDF5 and not the one distributed with ITK.)" OFF)     

IF (MAP_USE_SYSTEM_HDF5)
  IF(DEFINED HDF5_DIR)
	IF(NOT IS_ABSOLUTE ${HDF5_DIR})
	  SET(HDF5_DIR "${MatchPoint_BINARY_DIR}/${HDF5_DIR}")
	ENDIF(NOT IS_ABSOLUTE ${HDF5_DIR})
  ENDIF(DEFINED HDF5_DIR)

  MESSAGE (STATUS "MatchPoint uses system HDF5 instead of ITK distribution.")
  FIND_PACKAGE(HDF5)
ENDIF (MAP_USE_SYSTEM_HDF5)


CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/CMake/ITKConfig.cmake.in ${MAP_MODULES_CONF_DIR}/ITKConfig.cmake @ONLY)
