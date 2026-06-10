MESSAGE (STATUS "processing MatchPoint testing code")

# Testing branch
PROJECT(MatchPointTesting)

file(MAKE_DIRECTORY ${MatchPointTesting_BINARY_DIR}/Temporary)
#ADD_SUBDIRECTORY (Applications)


#-----------------------------------------------------------------------------
# extract and build Litmus
#-----------------------------------------------------------------------------

include(ExternalProject)
message(STATUS "Litmus will be automatically downloaded and built.")

set(LITMUS_SOURCE_DIR "${MatchPoint_BINARY_DIR}/external/Litmus-src" PARENT_SCOPE)
set(LITMUS_BUILD_DIR "${MatchPoint_BINARY_DIR}/external/Litmus-build" PARENT_SCOPE)
set(LITMUS_CMAKE_DIR "${MatchPoint_BINARY_DIR}/external/Litmus-cmake" PARENT_SCOPE)
set(LITMUS_SOURCE_DIR "${MatchPoint_BINARY_DIR}/external/Litmus-src" )
set(LITMUS_BUILD_DIR "${MatchPoint_BINARY_DIR}/external/Litmus-build" )
set(LITMUS_CMAKE_DIR "${MatchPoint_BINARY_DIR}/external/Litmus-cmake" )


# The bundled Litmus declares cmake_minimum_required(VERSION 2.6.2);
# CMake >= 4.0 refuses anything older than 3.5 unless the minimum policy
# version is raised externally. CMAKE_POLICY_VERSION_MINIMUM is new in
# CMake 4.0, so only pass it when the configuring CMake understands it
# (otherwise CMake 3.x warns about the unused cache variable).
set(LITMUS_POLICY_ARGS "")
if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.0)
	set(LITMUS_POLICY_ARGS "-DCMAKE_POLICY_VERSION_MINIMUM:STRING=3.5")
endif()

set(ENABLE_ITK "-DLIT_ENABLE_ITK_SUPPORT:BOOL=ON")
set(ITK_DIRECTORY "-DITK_DIR:PATH=${ITK_DIR}")
IF (MAP_USE_SYSTEM_HDF5)
	set(SYSTEM_HDF5 "-DLIT_USE_SYSTEM_HDF5:BOOL=ON")
	set(LITMUS_HDF5_DIR "-DHDF5_DIR:PATH=${HDF5_DIR}")
ENDIF()

#extract and build Litmus
ExternalProject_Add(
	Litmus
	URL ${MatchPoint_SOURCE_DIR}/Testing/Litmus/Litmus_matchpoint_v1.tar.gz
	URL_HASH SHA1=180a6a83ae0b170bea7d51c6d6f77c198894f726
	SOURCE_DIR ${LITMUS_SOURCE_DIR}
	BINARY_DIR ${LITMUS_BUILD_DIR}
	PREFIX ${LITMUS_CMAKE_DIR}
	INSTALL_COMMAND ""
	UPDATE_COMMAND "" # Don't update SVN on every build
	CMAKE_ARGS
		${LITMUS_POLICY_ARGS}
		-DBUILD_TESTING:BOOL=OFF
		-DCMAKE_CXX_STANDARD=${MAP_CXX_STANDARD}
		-DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
		${ENABLE_ITK}
		${ITK_DIRECTORY}
		${SYSTEM_HDF5}
		${LITMUS_HDF5_DIR}
)
