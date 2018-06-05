#-----------------------------------------------------------------------------
# Find Litmus
#-----------------------------------------------------------------------------

set(Litmus_INCLUDE_DIRS "${LITMUS_SOURCE_DIR}/code/common;${LITMUS_SOURCE_DIR}/code/itk;${LITMUS_BUILD_DIR}")
set(Litmus_LIBRARY_DIRS "${LITMUS_BUILD_DIR}/bin")

LIST(APPEND ALL_INCLUDE_DIRECTORIES ${Litmus_INCLUDE_DIRS})
LIST(APPEND ALL_LIBRARIES LitmusCommon LitmusITK)

LINK_DIRECTORIES(${Litmus_LIBRARY_DIRS}) 
