# Find rapidjson
#set(${COMBINED_INCLUDE} ${COMBINED_INCLUDE} "${UK_CORE}/Rapidjson/RapidJson/include")

add_library(RapidJSON INTERFACE)
target_include_directories(RapidJSON INTERFACE "${UK_CORE}/Rapidjson/RapidJson/include")