# Find assimp
# Need to build zlib also
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Enable to build zlib")
# No build tests
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Enable to build tests")
# No need for tools
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Enable to build additional tools")
# Don't add (d) to end of debug libs
set(INJECT_DEBUG_POSTFIX OFF CACHE BOOL "Enable to add postfix to debug libraries")
# Currently no need for exporting
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Enable to build exporters")
# Currently this importer won't build with emscripten
set(ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "Enable to build GLTF importer (not currently working with emscripten)")
# Disable CPack, as well as others
set(ASSIMP_OPT_BUILD_PACKAGES OFF CACHE BOOL "Enable to build additional packages")
add_subdirectory(assimp)