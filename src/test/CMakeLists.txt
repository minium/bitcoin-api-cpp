file(GLOB bitcoin_tests_src *.cpp)

# Set library path
INCLUDE_DIRECTORIES(/usr/local/include/bitcoin)

# Create new target
add_executable(bitcoinapi_tests ${bitcoin_tests_src})
target_link_libraries(bitcoinapi_tests bitcoinapi boost_system boost_filesystem boost_unit_test_framework)


