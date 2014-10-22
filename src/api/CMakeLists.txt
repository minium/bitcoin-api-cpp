# Set compiler settings
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

# Find header and source files
FILE(GLOB bitcoinapi_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB bitcoinapi_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Set target libraries
ADD_LIBRARY(bitcoinapi SHARED ${bitcoinapi_source})
ADD_LIBRARY(bitcoinapi_static STATIC ${bitcoinapi_source})

# Add boost header include
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/..)

# Set output name of static library
SET_TARGET_PROPERTIES(bitcoinapi_static PROPERTIES OUTPUT_NAME bitcoinapi)

# Set version number of both libraries
SET(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}) 
SET_TARGET_PROPERTIES(bitcoinapi bitcoinapi_static PROPERTIES VERSION "${VERSION_STRING}" SOVERSION "${VERSION_MAJOR}")

# Link the library with jsonrpc libs
TARGET_LINK_LIBRARIES(bitcoinapi jsonrpc)
TARGET_LINK_LIBRARIES(bitcoinapi_static jsonrpc)

# Install to appropriate destinations
INSTALL(FILES ${bitcoinapi_header} DESTINATION include/bitcoinapi)

INSTALL(TARGETS bitcoinapi bitcoinapi_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
