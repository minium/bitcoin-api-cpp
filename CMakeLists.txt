cmake_minimum_required(VERSION 2.6)
project(BitcoinAPI)

# Check if Curl lib is there
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# Set compiler flags
SET(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")
SET(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -g -Wall")

# Set version number
SET(MAJOR_VERSION 1)
SET(MINOR_VERSION 0)

# Add source directory
add_subdirectory(src/bitcoin)
add_subdirectory(src/test)


IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
INCLUDE(InstallRequiredSystemLibraries)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(CPACK_GENERATOR "PackageMaker")
	SET(CPACK_PACKAGING_INSTALL_PREFIX "/opt/local")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET(CPACK_GENERATOR "DEB")
	SET(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

SET(CPACK_PACKAGE_DESCRIPTION "C++ interface for communication with Bitcoin Wallet.")
SET(CPACK_PACKAGE_VENDOR "Krzysztof Okupski")
SET(CPACK_PACKAGE_CONTACT "Krzysztof Okupski <k.okupski@gmail.com>")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")

SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}")

SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

SET(CPACK_COMPONENTS_ALL bitcoin jsonrpc jsoncpp mongoose)
INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
