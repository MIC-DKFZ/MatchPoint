#-----------------------------------------------------------------------------
# Find VII
#-----------------------------------------------------------------------------
IF(DEFINED VII_DIR)
  IF(NOT IS_ABSOLUTE ${VII_DIR})
    SET(VII_DIR "${MatchPoint_BINARY_DIR}/${VII_DIR}")
  ENDIF(NOT IS_ABSOLUTE ${VII_DIR})
ENDIF(DEFINED VII_DIR)

FIND_PACKAGE(VII)
IF(VII_FOUND)
  INCLUDE(${VII_USE_FILE})
ELSE(VII_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without VII.  Please set VII_DIR.")
ENDIF(VII_FOUND)

LIST(APPEND ALL_INCLUDE_DIRECTORIES ${VII_INCLUDE_DIRS} ${VII_BINARY_DIR} ${VII_VIRTUOSIOCORE_SOURCE_DIR})
LIST(APPEND ALL_LIBRARIES VirtuosIO_ITKInterface)

LINK_DIRECTORIES(${VII_LIBRARY_DIRS}) 
