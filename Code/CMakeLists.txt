MESSAGE (STATUS "processing MatchPoint code")
ADD_SUBDIRECTORY (ITK)
ADD_SUBDIRECTORY (Core)
ADD_SUBDIRECTORY (Utilities)
ADD_SUBDIRECTORY (Algorithms/Common)
ADD_SUBDIRECTORY (Deployment)
ADD_SUBDIRECTORY (Algorithms/ITK)
ADD_SUBDIRECTORY (IO)

OPTION(MAP_WRAP_FSL "Activate the wrappers for FMRIB/FSL." ON)

IF(MAP_WRAP_FSL)
  ADD_SUBDIRECTORY (Algorithms/FSL)
ENDIF(MAP_WRAP_FSL)

OPTION(MAP_WRAP_Elastix "Activate the wrappers for Elastix." OFF)

IF(MAP_WRAP_Elastix)
  ADD_SUBDIRECTORY (Algorithms/Elastix)
ENDIF(MAP_WRAP_Elastix)

OPTION(MAP_WRAP_Plastimatch "Activate the wrappers for Plastimatch." OFF)

IF(MAP_WRAP_Plastimatch)
  ADD_SUBDIRECTORY (Algorithms/Plastimatch)
ENDIF(MAP_WRAP_Plastimatch)