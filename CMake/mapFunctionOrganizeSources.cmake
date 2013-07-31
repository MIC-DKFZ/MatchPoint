##################################################################
#
# ORGANIZE_SOURCES
#
#! this functions gets a filelist as input and looks
#! for corresponding h-files and adds all files in according
#! source groups.
#!  
#! USAGE:
#!
#! \code
#! ORGANIZE_SOURCE( 
#!     [HEADER <list of header files>]
#!     [SOURCE <list of source files>]
#!     [TPP <list of template files>]
#!     [DOC <list of documentation files>]
#! \endcode
#
##################################################################
FUNCTION(ORGANIZE_SOURCES)



  MACRO_PARSE_ARGUMENTS(_ORG "HEADER;SOURCE;TPP;DOC" "" ${ARGN})

  SET(CORRESPONDING__H_FILES "" )
  SET(GLOBBED__H_FILES "" )

  IF(_ORG_HEADER)
    FOREACH(_file ${_ORG_SOURCE})
      STRING(REGEX REPLACE "(.*)\\.(txx|tpp|cpp|c|cxx)$" "\\1.h" H_FILE ${_file})
      IF(EXISTS ${H_FILE})
        LIST(APPEND CORRESPONDING__H_FILES "${H_FILE}")
      ENDIF()
    ENDFOREACH()
  ELSE()
    FILE(GLOB_RECURSE GLOBBED__H_FILES *.h)
  ENDIF()
  
  
  #_MACRO_APPEND_TO_LIST(_ORG_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/")
  SOURCE_GROUP("Source Files" FILES ${_ORG_SOURCE})
  
  #_MACRO_APPEND_TO_LIST(_ORG_TXX "${CMAKE_CURRENT_SOURCE_DIR}/")
  SOURCE_GROUP("Template Files" FILES ${_ORG_TXX} ${_ORG_TPP})
 
  #_MACRO_APPEND_TO_LIST(_ORG_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/")
  SOURCE_GROUP("Header Files" FILES ${_ORG_HEADER} ${CORRESPONDING__H_FILES} ${GLOBBED__H_FILES})
   
  #_MACRO_APPEND_TO_LIST(_ORG_DOC "${CMAKE_CURRENT_SOURCE_DIR}/")
  SOURCE_GROUP("Doxygen Files" FILES ${_ORG_DOC})
    
ENDFUNCTION(ORGANIZE_SOURCES)
