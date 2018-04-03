#-----------------------------------------------------------------------------
# Find VirtuosIOCore
#-----------------------------------------------------------------------------
IF(DEFINED VirtuosIOCore_DIR)
  IF(NOT IS_ABSOLUTE ${VirtuosIOCore_DIR})
    SET(VirtuosIOCore_DIR "${MatchPoint_BINARY_DIR}/${VirtuosIOCore_DIR}")
  ENDIF(NOT IS_ABSOLUTE ${VirtuosIOCore_DIR})
ENDIF(DEFINED VirtuosIOCore_DIR)

FIND_PACKAGE(VirtuosIOCore)
IF(VirtuosIOCore_FOUND)
  INCLUDE(${VirtuosIOCore_USE_FILE})
ELSE(VirtuosIOCore_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without VirtuosIOCore.  Please set VirtuosIOCore_DIR.")
ENDIF(VirtuosIOCore_FOUND)

LIST(APPEND ALL_INCLUDE_DIRECTORIES ${VirtuosIOCore_INCLUDE_DIRS})
LIST(APPEND ALL_LIBRARIES VirtuosIO)

LINK_DIRECTORIES(${VirtuosIOCore_LIBRARY_DIRS}) 
