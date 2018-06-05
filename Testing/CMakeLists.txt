MESSAGE (STATUS "processing MatchPoint testing code")

# Testing branch
PROJECT(MatchPointTesting)

MAKE_DIRECTORY(${MatchPointTesting_BINARY_DIR}/Temporary)
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


set(ENABLE_ITK "-DLIT_ENABLE_ITK_SUPPORT:BOOL=ON")
set(ITK_DIRECTORY "-DITK_DIR:PATH=${ITK_DIR}")
IF (MAP_USE_SYSTEM_HDF5)
	set(SYSTEM_HDF5 "-DLIT_USE_SYSTEM_HDF5:BOOL=ON")
	set(LITMUS_HDF5_DIR "-DHDF5_DIR:PATH=${HDF5_DIR}")
ENDIF()

#extract and build Litmus
ExternalProject_Add(
	Litmus
	URL ${MatchPoint_SOURCE_DIR}/Testing/Litmus/Litmus_rev1298.tar.gz
	URL_HASH SHA1=20CCE03B65826049F49E39A7B66F0802D8D637F8
	SOURCE_DIR ${LITMUS_SOURCE_DIR}
	BINARY_DIR ${LITMUS_BUILD_DIR}
	PREFIX ${LITMUS_CMAKE_DIR}
	INSTALL_COMMAND ""
	UPDATE_COMMAND "" # Don't update SVN on every build
	CMAKE_ARGS
		-DBUILD_TESTING:BOOL=OFF
		-DCMAKE_CXX_STANDARD=${MAP_CXX_STANDARD}
		${ENABLE_ITK}
		${ITK_DIRECTORY}
		${SYSTEM_HDF5}
		${LITMUS_HDF5_DIR}
)
