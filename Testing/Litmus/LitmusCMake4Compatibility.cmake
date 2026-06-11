# Patch script for the extracted Litmus sources (see ExternalProject_Add in
# Testing/CMakeLists.txt). The bundled Litmus targets CMake 2.6 and calls
# EXPORT_LIBRARY_DEPENDENCIES, which CMake 4.0 removed (CMP0033). The
# generated LitmusLibraryDepends.cmake is not consumed by MatchPoint, so the
# call is simply commented out after extraction.
#
# Invoked as:
#   cmake -DLITMUS_SOURCE_DIR=<extracted-source-dir> -P LitmusCMake4Compatibility.cmake

file(READ "${LITMUS_SOURCE_DIR}/CMakeLists.txt" _litmus_cmakelists)
string(REPLACE "\nEXPORT_LIBRARY_DEPENDENCIES"
               "\n#EXPORT_LIBRARY_DEPENDENCIES"
               _litmus_cmakelists "${_litmus_cmakelists}")
file(WRITE "${LITMUS_SOURCE_DIR}/CMakeLists.txt" "${_litmus_cmakelists}")
