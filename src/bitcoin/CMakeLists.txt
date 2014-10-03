file(GLOB_RECURSE bitcoin_source *.c*)
file(GLOB bitcoin_header *.h)

file(GLOB jsonrpc_header jsonrpc/*.h)
file(GLOB connector_header jsonrpc/connectors/*.h)
file(GLOB jsoncpp_header jsonrpc/json/*.h)

# Set target 'bitcoin' to be shared library
add_library(bitcoinapi SHARED ${bitcoin_source})

# Set target 'bitcoinStatic' to be static library
add_library(bitcoinapi_static STATIC ${bitcoin_source})

# Set properties of both targets
set_target_properties(bitcoinapi_static PROPERTIES OUTPUT_NAME bitcoinapi)

set(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}) 
set_target_properties(bitcoinapi bitcoinapi_static PROPERTIES VERSION "${VERSION_STRING}" SOVERSION "${VERSION_MAJOR}")


target_link_libraries(bitcoinapi ${CURL_LIBRARIES})
target_link_libraries(bitcoinapi_static ${CURL_LIBRARIES})

install(FILES ${bitcoin_header} DESTINATION include/bitcoin) 
install(FILES ${jsonrpc_header} DESTINATION include/bitcoin/jsonrpc) 
install(FILES ${connector_header} DESTINATION include/bitcoin/jsonrpc/connectors)
install(FILES ${jsoncpp_header} DESTINATION include/bitcoin/jsonrpc/json) 

install(TARGETS bitcoinapi bitcoinapi_static LIBRARY DESTINATION lib
                      ARCHIVE DESTINATION lib
                      RUNTIME DESTINATION bin)

