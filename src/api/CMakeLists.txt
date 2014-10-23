# Set compiler settings
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

# Find header and source files
FILE(GLOB bitcoinapi_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB bitcoinapi_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add jsonrpc directory
ADD_SUBDIRECTORY(jsonrpc)

# Set target libraries
ADD_LIBRARY(bitcoinapi SHARED ${bitcoinapi_source})
ADD_LIBRARY(bitcoinapi_static STATIC ${bitcoinapi_source})

# Set output name of static library
SET_TARGET_PROPERTIES(bitcoinapi_static PROPERTIES OUTPUT_NAME bitcoinapi)

# Link the library with jsonrpc libs
TARGET_LINK_LIBRARIES(bitcoinapi jsonrpc)
TARGET_LINK_LIBRARIES(bitcoinapi_static jsonrpc)

# Install to appropriate destinations
INSTALL(FILES ${bitcoinapi_header} DESTINATION include/bitcoinapi)

INSTALL(TARGETS bitcoinapi bitcoinapi_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
