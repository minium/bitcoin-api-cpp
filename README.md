Bitcoin API
===========

This is a C++ wrapper library for JSON-RPC communication with the Bitcoin daemon. It allows developers to communicate with the Bitcoin daemon without the need to pack and unpack JSON-RPC messages and thus simplifies the interaction with it.

Building the library
--------------------

** Dependencies **
This library requires [CMake](http://www.cmake.org/cmake/resources/software.html) and [Curl](http://curl.haxx.se) packages in order to be built. These can be installed as follows on Debian based systems:

```sh
sudo apt-get cmake install libcurl4-openssl-dev
```

** Build and install **
Navigate to the root directory of the library and proceed as follows:

```sh
cd build
cmake ..
make
sudo make install
```

Using the library
-----------------
This example will show how the library can be used in your project. 

Filename getbalance.cpp

```
#include <bitcoinapi/wallet.h>

int main()
{
    std::string username = "user";
    std::string password = "pass";
    std::string address = "127.0.0.1";
    int port = 8332;

    /* Constructor to connect to the bitcoin daemon */
    BitcoinAPI btc(username, password, address, port);

    /* Example method - getbalance */
    std::cout << "Wallet balance: " << btc.getbalance() << std::endl;
}
```

To successfully compile the program you need to link it with the new library:
```
g++ getbalance.cpp -lbitcoin
```

The full list of available API calls can be found [here](https://en.bitcoin.it/wiki/Original_Bitcoin_client/API_calls_list). Nearly the complete list of calls is implemented and thoroughly tested.

License
-------

The Bitcoin Messaging System is released under the terms of [MIT](http://en.wikipedia.org/wiki/MIT_License).

```
Copyright (c) 2014 Krzysztof Okupski

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in the 
Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
OR OTHER DEALINGS IN THE SOFTWARE.
```

Used libraries
--------------
- [libjson-rpc-cpp](https://github.com/cinemast/libjson-rpc-cpp) C++ framework for JSON-RPC communication. Note that I am using a modified version of this library in order for it to work correctly with the Bitcoin daemon.

Acknowledgements
----------------
The original idea for a C++ wrapper for JSON-RPC communication originates from [here](https://github.com/mmgrant73/bitcoinapi). Upon closer evaluation, however, the library contained too many bugs and was thus completely rebuilt from bottom up.
