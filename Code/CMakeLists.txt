MESSAGE (STATUS "processing MatchPoint code")
ADD_SUBDIRECTORY (ITK)
ADD_SUBDIRECTORY (Core)
ADD_SUBDIRECTORY (Utilities)
ADD_SUBDIRECTORY (Algorithms/Common)
ADD_SUBDIRECTORY (Deployment)
ADD_SUBDIRECTORY (Algorithms/ITK)
ADD_SUBDIRECTORY (IO)

OPTION(MAP_WRAP_FSL "Activate the wrappers for FMRIB/FSL." OFF)

IF(MAP_WRAP_FSL OR MAP_BUILD_ALL)
  ADD_SUBDIRECTORY (Algorithms/FSL)
ENDIF(MAP_WRAP_FSL OR MAP_BUILD_ALL)

OPTION(MAP_WRAP_Elastix "Activate the wrappers for Elastix." OFF)

IF(MAP_WRAP_Elastix OR MAP_BUILD_ALL)
  ADD_SUBDIRECTORY (Algorithms/Elastix)
ENDIF(MAP_WRAP_Elastix OR MAP_BUILD_ALL)

OPTION(MAP_WRAP_Plastimatch "Activate the wrappers for Plastimatch." OFF)

IF(MAP_WRAP_Plastimatch OR MAP_BUILD_ALL)
  ADD_SUBDIRECTORY (Algorithms/Plastimatch)
ENDIF(MAP_WRAP_Plastimatch OR MAP_BUILD_ALL)

OPTION(MAP_BUILD_Ontology "Activate the registration ontology." OFF)

IF(MAP_BUILD_Ontology OR MAP_BUILD_ALL)
  ADD_SUBDIRECTORY (Ontology/Common)
  OPTION(MAP_BUILD_Ontology_simple "Activate the simple implementation of registration ontology." OFF)
  IF(MAP_BUILD_Ontology_simple OR MAP_BUILD_ALL)
    ADD_SUBDIRECTORY (Ontology/Simple)
  ENDIF(MAP_BUILD_Ontology_simple OR MAP_BUILD_ALL)
ENDIF(MAP_BUILD_Ontology OR MAP_BUILD_ALL)