#-----------------------------------------------------------------------------
# Find Elastix.
#-----------------------------------------------------------------------------

if(NOT Elastix_FOUND AND NOT Elastix_DIR)
  SET( Elastix_DIR "" CACHE PATH "Path to Elastix binary folder" )
endif()

IF(NOT Elastix_FOUND)
  set(Elastix_FOUND True)

IF(DEFINED Elastix_DIR)
  IF(NOT IS_ABSOLUTE ${Elastix_DIR})
    SET(Elastix_DIR "${MatchPoint_BINARY_DIR}/${Elastix_DIR}")
  ENDIF(NOT IS_ABSOLUTE ${Elastix_DIR})
ENDIF(DEFINED Elastix_DIR)

SET( Elastix_USE_FILE ${Elastix_DIR}/UseElastix.cmake )

IF( EXISTS ${Elastix_USE_FILE} )
 MESSAGE( STATUS "Including Elastix settings." )
 INCLUDE( ${Elastix_USE_FILE} )
ELSE( EXISTS ${Elastix_USE_FILE} )
 MESSAGE( FATAL_ERROR "Cannot find Elastix settings (Use Elastix.cmake). Check Elastix_DIR." )
ENDIF( EXISTS ${Elastix_USE_FILE} )

IF(${ELASTIX_VERSION_MAJOR} LESS 4 OR (${ELASTIX_VERSION_MAJOR} EQUAL 4 AND ${ELASTIX_VERSION_MINOR} LESS 6))
  MESSAGE(FATAL_ERROR
          "Outdated Elastix version. Cannot build MatchPoint without sufficient Elastix version. Elastix 4.6 or above is needed.")
ENDIF(${ELASTIX_VERSION_MAJOR} LESS 4 OR (${ELASTIX_VERSION_MAJOR} EQUAL 4 AND ${ELASTIX_VERSION_MINOR} LESS 6))

#-----------------------------------------------------------
# Dynamic search for Elastix libs to include them with path
#-----------------------------------------------------------

foreach(lib
FixedGenericPyramid
FixedRecursivePyramid
FixedSmoothingPyramid
FullSampler
GridSampler
MultiInputRandomCoordinateSampler
RandomSampler
RandomCoordinateSampler
RandomSamplerSparseMask
BSplineInterpolator
ReducedDimensionBSplineInterpolator
AdvancedMattesMutualInformationMetric
AdvancedMeanSquaresMetric
AdvancedNormalizedCorrelationMetric
TransformBendingEnergyPenalty
CorrespondingPointsEuclideanDistanceMetric
KNNGraphAlphaMutualInformationMetric
NormalizedMutualInformationMetric
TransformRigidityPenalty
VarianceOverLastDimensionMetric
MovingRecursivePyramid
MovingSmoothingPyramid
AdaptiveStochasticGradientDescent
ConjugateGradient
FiniteDifferenceGradientDescent
FullSearch
Powell
QuasiNewtonLBFGS
RegularStepGradientDescent
StandardGradientDescent
MultiMetricMultiResolutionRegistration
MultiResolutionRegistration
MultiResolutionRegistrationWithFeatures
BSplineResampleInterpolator
ReducedDimensionBSplineResampleInterpolator
MyStandardResampler
AdvancedAffineTransformElastix
AdvancedBSplineTransform
DeformationFieldTransform
EulerTransformElastix
SplineKernelTransform
BSplineStackTransform
TranslationTransformElastix
elxCommon
elxCore
param
)

  find_library(Elastix_${lib}_DEBUG_LIBRARY
    ${lib}
    PATHS
    ${Elastix_DIR}/bin
    ${Elastix_DIR}/bin/Debug)

  find_library(Elastix_${lib}_LIBRARY
    ${lib}
    PATHS
    ${Elastix_DIR}/bin/Release
    ${Elastix_DIR}/bin)	
	
  mark_as_advanced(Elastix_${lib}_LIBRARY)
  mark_as_advanced(Elastix_${lib}_DEBUG_LIBRARY)
	
  add_library(${lib} STATIC IMPORTED)
  set_target_properties(${lib} PROPERTIES IMPORTED_LOCATION ${Elastix_${lib}_LIBRARY} IMPORTED_LOCATION_DEBUG ${Elastix_${lib}_DEBUG_LIBRARY})
  
  if(Elastix_${lib}_LIBRARY OR Elastix_${lib}_DEBUG_LIBRARY)
    list(APPEND Elastix_LIBRARIES ${lib})
  endif() 

  if(${Elastix_${lib}_LIBRARY} STREQUAL Elastix_${lib}_LIBRARY-NOTFOUND)
	message(WARNING "Cannot find release version of library Elastix_${lib}_LIBRARY")
  endif()

  if(${Elastix_${lib}_DEBUG_LIBRARY} STREQUAL Elastix_${lib}_DEBUG_LIBRARY-NOTFOUND)
	message(WARNING "Cannot find debug version of library Elastix_${lib}_DEBUG_LIBRARY")
  endif()

 endforeach()

ENDIF(NOT Elastix_FOUND)

IF(NOT Elastix_FOUND)
  MESSAGE(SEND_ERROR "Elastix development files not found.\n Please check variables (e.g. Elastix_DIR)")
ENDIF(NOT Elastix_FOUND)
 
LIST(APPEND ALL_INCLUDE_DIRECTORIES ${ELASTIX_INCLUDE_DIRECTORIES})
LIST(APPEND ALL_LIBRARIES ${Elastix_LIBRARIES})

CONFIGURE_FILE(${MatchPoint_SOURCE_DIR}/CMake/ElastixConfig.cmake.in ${MAP_MODULES_CONF_DIR}/ElastixConfig.cmake @ONLY)
