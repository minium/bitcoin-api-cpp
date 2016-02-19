FIND_PACKAGE(JSONCPP REQUIRED)
FIND_PACKAGE(JSONRPCCPP REQUIRED)
FIND_PACKAGE(CURL REQUIRED)

# Find header and source files
FILE(GLOB bitcoinapi_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB bitcoinapi_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Set target libraries
ADD_LIBRARY(bitcoinapi SHARED ${bitcoinapi_source})
ADD_LIBRARY(bitcoinapi_static STATIC ${bitcoinapi_source})

# Set output name of static library
SET_TARGET_PROPERTIES(bitcoinapi_static PROPERTIES OUTPUT_NAME bitcoinapi)

# Link the library with json-rpc-cpp libs
TARGET_LINK_LIBRARIES(bitcoinapi
                        ${CURL_LIBRARY}
                        ${JSONCPP_LIBRARY}
                        jsonrpccpp-common
                        jsonrpccpp-client)

TARGET_LINK_LIBRARIES(bitcoinapi_static
                        ${CURL_LIBRARY}
                        ${JSONCPP_LIBRARY}
                        jsonrpccpp-common
                        jsonrpccpp-client)

# Set version settings
SET(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
SET_TARGET_PROPERTIES(bitcoinapi bitcoinapi_static PROPERTIES
    VERSION "${VERSION_STRING}"
    SOVERSION "${SO_VERSION}")

# Install to appropriate destinations
INSTALL(FILES ${bitcoinapi_header} DESTINATION include/bitcoinapi)

INSTALL(TARGETS bitcoinapi bitcoinapi_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
