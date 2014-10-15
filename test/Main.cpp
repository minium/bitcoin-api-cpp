#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test Suite
//#define VERBOSE

#include <boost/test/unit_test.hpp>
#include "BitcoinWallet.h"
#include "BitcoinException.h"

struct MyFixture {

	std::string username;
	std::string password;
	std::string address;
	int port;

	BitcoinAPI btc;

     MyFixture() {
    	 username = "Ulysses";
    	 password = "Random";
    	 address = "127.0.0.1";
    	 port = 8332;
    	 btc = BitcoinAPI(username, password, address, port);
     }
     ~MyFixture() { }
};


BOOST_GLOBAL_FIXTURE(MyFixture);
