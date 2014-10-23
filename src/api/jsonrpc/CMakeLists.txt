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

# Link the library with dependencies
TARGET_LINK_LIBRARIES(jsonrpc pthread dl curl)
TARGET_LINK_LIBRARIES(jsonrpc_static pthread dl curl)

# Install to appropriate destinations
INSTALL(FILES ${jsonrpc_header} DESTINATION include/jsonrpc) 
INSTALL(FILES ${connector_header} DESTINATION include/jsonrpc/connectors)
INSTALL(FILES ${jsoncpp_header} DESTINATION include/jsonrpc/json) 

INSTALL(TARGETS jsonrpc jsonrpc_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
