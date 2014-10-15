# Set compiler settings
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")
SET(CMAKE_C_FLAGS "-Wall")

# Require curl to be present
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(CURL REQUIRED)

# Find header and source files
FILE(GLOB jsonrpc_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB connector_header ${CMAKE_CURRENT_SOURCE_DIR}/connectors/*.h)
FILE(GLOB jsoncpp_header ${CMAKE_CURRENT_SOURCE_DIR}/json/*.h)
FILE(GLOB_RECURSE jsonrpc_source ${CMAKE_CURRENT_SOURCE_DIR}/*.c*)

# Set target libraries
ADD_LIBRARY(jsonrpc SHARED ${jsonrpc_source})
ADD_LIBRARY(jsonrpc_static STATIC ${jsonrpc_source})

# Set output name of static library
SET_TARGET_PROPERTIES(jsonrpc_static PROPERTIES OUTPUT_NAME jsonrpc)

# Set version number of both libraries
SET(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}) 
SET_TARGET_PROPERTIES(jsonrpc jsonrpc_static PROPERTIES VERSION "${VERSION_STRING}" SOVERSION "${VERSION_MAJOR}")

# Link the library with dependencies
TARGET_LINK_LIBRARIES(jsonrpc pthread dl curl)
TARGET_LINK_LIBRARIES(jsonrpc_static pthread dl curl)

# Install to appropriate destinations
INSTALL(FILES ${jsonrpc_header} DESTINATION include/jsonrpc) 
INSTALL(FILES ${connector_header} DESTINATION include/jsonrpc/connectors)
INSTALL(FILES ${jsoncpp_header} DESTINATION include/jsonrpc/json) 

INSTALL(TARGETS jsonrpc jsonrpc_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin)

# Make library public for other includes
TARGET_INCLUDE_DIRECTORIES(jsonrpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
