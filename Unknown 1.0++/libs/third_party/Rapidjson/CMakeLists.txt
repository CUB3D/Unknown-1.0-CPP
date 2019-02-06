# Find rapidjson

add_library(RapidJSON INTERFACE)
target_include_directories(RapidJSON INTERFACE "${THIRD_PARTY}/Rapidjson/rapidjson/include")