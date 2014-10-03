# Install script for directory: /home/minium/Desktop/BitcoinAPI/src/bitcoin

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bitcoin" TYPE FILE FILES
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/BitcoinWallet.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/WalletTypes.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/BitcoinException.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bitcoin/jsonrpc" TYPE FILE FILES
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/errors.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/specificationparser.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/specification.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/serverconnector.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/clientconnector.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/procedure.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/client.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/abstractauthenticator.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/rpc.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/server.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/rpcprotocolserver.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/abstractrequesthandler.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/rpcprotocolclient.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/exception.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/specificationwriter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bitcoin/jsonrpc/connectors" TYPE FILE FILES
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/connectors/httpserver.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/connectors/mongoose.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/connectors/httpclient.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bitcoin/jsonrpc/json" TYPE FILE FILES
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/json.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/config.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/value.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/forwards.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/features.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/reader.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/writer.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/json_batchallocator.h"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/jsonrpc/json/autolink.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbitcoinapi.so.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbitcoinapi.so."
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbitcoinapi.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/libbitcoinapi.so.1.0"
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/libbitcoinapi.so."
    "/home/minium/Desktop/BitcoinAPI/src/bitcoin/libbitcoinapi.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbitcoinapi.so.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbitcoinapi.so."
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libbitcoinapi.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/minium/Desktop/BitcoinAPI/src/bitcoin/libbitcoinapi.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

