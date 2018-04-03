MESSAGE (STATUS "processing MatchPoint documentation")

CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/Documentation/doxygen.config.in
               ${MatchPoint_BINARY_DIR}/Documentation/doxygen.config)

