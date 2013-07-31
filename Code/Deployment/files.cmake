SET(CPP_FILES 
source/mapCheckDLLInterfaceVersion.cpp
source/mapDeploymentExceptions.cpp
source/mapDeploymentDLLInfo.cpp
source/mapDeploymentDLLHandle.cpp
source/mapDeploymentDLLAccess.cpp
source/mapDeploymentDLLDirectoryBrowser.cpp
source/mapDeploymentSync.cpp
)

SET(H_FILES 
include/mapDeploymentDLLInterface.h
include/mapDeploymentDLLHelper.h
include/mapCheckDLLInterfaceVersion.h
include/mapDeploymentExceptions.h
include/mapDeploymentDLLInfo.h
include/mapDeploymentDLLHandle.h
include/mapDeploymentDLLAccess.h
include/mapDeploymentDLLDirectoryBrowser.h
include/mapDeploymentSync.h  
)

SET(TPP_FILES
include/mapDeploymentDLLHelper.tpp
)

SET( TEST_CPP_FILES
test/mapDeploymentTests.cpp
test/mapDeploymentDLLAccessTest.cpp
test/mapDeploymentDLLConfigTest.cpp
test/mapDeploymentDLLHandleTest.cpp
test/mapDeploymentDLLHelperTest.cpp
test/mapDeploymentDLLInfoTest.cpp
test/mapDeploymentDLLBrowserTest.cpp
)
