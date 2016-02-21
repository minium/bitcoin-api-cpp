#define BOOST_TEST_DYN_LINK


#include <boost/test/unit_test.hpp>
#include <algorithm>
#include "main.cpp"

BOOST_AUTO_TEST_SUITE(GeneralTests)

BOOST_AUTO_TEST_CASE(GetInfo) {

	MyFixture fx;
	getinfo_t info;
	
	NO_THROW(info = fx.btc.getinfo());
	BOOST_REQUIRE(info.protocolversion >= 70002);

	#ifdef VERBOSE
	std::cout <<  "=== getinfo ===" << std::endl;
	std::cout << "Version: " << info.version << std::endl;
	std::cout << "Protocol Version: " << info.protocolversion << std::endl;
	std::cout << "Wallet Version: " << info.walletversion << std::endl;
	std::cout << "Balance: " << info.balance << std::endl;
	std::cout << "Blocks: " << info.blocks << std::endl;
	std::cout << "Timeoffset: " << info.timeoffset << std::endl;
	std::cout << "Connections: " << info.connections << std::endl;
	std::cout << "Proxy: " << info.proxy << std::endl;
	std::cout << "Difficulty: " << info.difficulty << std::endl;
	std::cout << "Testnet: " << info.testnet << std::endl;
	std::cout << "Keypoololdest: " << info.keypoololdest << std::endl;
	std::cout << "Keypool size: " << info.keypoolsize << std::endl;
	std::cout << "Paytxfee: " << info.paytxfee << std::endl;
	std::cout << "Unlocked_until: " << info.unlocked_until << std::endl;
	std::cout << "Errors: " << info.errors << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_SUITE_END()
