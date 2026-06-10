IF(NOT Boost_FOUND)

  IF(DEFINED Boost_INCLUDE_DIR)
    IF(NOT IS_ABSOLUTE ${Boost_INCLUDE_DIR})
      SET(Boost_INCLUDE_DIR "${MatchPoint_BINARY_DIR}/${Boost_INCLUDE_DIR}")
    ENDIF(NOT IS_ABSOLUTE ${Boost_INCLUDE_DIR})
  ENDIF(DEFINED Boost_INCLUDE_DIR)

  SET(BOOST_MIN_VERSION "1.58.0")
  # This intentionally still works via CMake's FindBoost module (CMP0167
  # emits a warning under CMake >= 3.30): MatchPoint only needs the Boost
  # headers and is regularly built against headers-only Boost distributions
  # (e.g. MITK's) that provide no BoostConfig.cmake for config mode.
  FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED QUIET)

  LIST(APPEND ALL_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
	
  MARK_AS_ADVANCED(CLEAR Boost_INCLUDE_DIR)
	
ENDIF(NOT Boost_FOUND)
