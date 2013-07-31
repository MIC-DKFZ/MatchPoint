SET(CPP_FILES 
 source/mapPlmAlgorithmHelper.cpp
)

SET(H_FILES 
include/mapPlmCLIRegistrationAlgorithmBase.h
include/mapPlmParameterFileRegistrationAlgorithm.h
include/mapPlmAlgorithmHelper.h
boxed/mapPlmBSplineCLIRegistrationAlgorithm.h
)

SET(TPP_FILES
include/mapPlmCLIRegistrationAlgorithmBase.tpp
include/mapPlmParameterFileRegistrationAlgorithm.tpp
boxed/mapPlmBSplineCLIRegistrationAlgorithm.tpp
)

SET(TEST_CPP_FILES
test/mapAlgorithmsPlastimatchTests.cpp
test/mapPlmParameterFileRegistrationAlgorithmTest.cpp
)