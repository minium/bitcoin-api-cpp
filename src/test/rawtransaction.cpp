#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#include "main.cpp"

using boost::filesystem::path;
using boost::filesystem::exists;
using boost::filesystem::remove;
using boost::filesystem::current_path;

BOOST_AUTO_TEST_SUITE(RawTransactionTests)

BOOST_AUTO_TEST_CASE(GetRawTransactionVerbose) {

	MyFixture fx;

	getrawtransaction_t response;
	std::string txid = "0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098";

	NO_THROW(response = fx.btc.getrawtransaction(txid,1));

	#ifdef VERBOSE
	std::cout << "=== getrawtransaction (verbose) ===" << std::endl;
	std::cout << "Txid: " << response.txid << std::endl;
	std::cout << "Version: " << response.version << std::endl;
	std::cout << "Locktime: " << response.locktime << std::endl;

	std::cout << "vin: " << std::endl;
	for(std::vector<vin_t>::iterator it = response.vin.begin(); it != response.vin.end(); it++){
		vin_t txin = (*it);
		std::cout << "  txid: " << txin.txid << std::endl;
		std::cout << "  vout: " << txin.n << std::endl;

		std::cout << "  scriptSig: " << std::endl;
		std::cout << "    asm: " << txin.scriptSig.assm << std::endl;
		std::cout << "    hex: " << txin.scriptSig.hex << std::endl;
	}

	std::cout << "vout: " << std::endl;
	for(std::vector<vout_t>::iterator it = response.vout.begin(); it != response.vout.end(); it++){
		vout_t txout = (*it);
		std::cout << "  value: " << txout.value << std::endl;
		std::cout << "  n: " << txout.n << std::endl;

		std::cout << "  scriptPubKey" << std::endl;
		std::cout << "    asm: " << txout.scriptPubKey.assm << std::endl;
		std::cout << "    hex: " << txout.scriptPubKey.hex << std::endl;
		std::cout << "    reqSigs: " << txout.scriptPubKey.reqSigs << std::endl;
		std::cout << "    type: " << txout.scriptPubKey.type << std::endl;

		std::cout << "    addresses: " << std::endl;
		for(std::vector<std::string>::iterator it2 = txout.scriptPubKey.addresses.begin(); it2 != txout.scriptPubKey.addresses.end(); it2++){
			std::cout << "      " << (*it2) << std::endl;
		}
	}

	std::cout << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(DecodeRawTransaction) {

	MyFixture fx;

	decoderawtransaction_t response;
	std::string rawHexTx =
			"0100000001da95ea9ded6ca4d6d47ddebf36e7f6a76992573dfd836ae46abf"
			"12b3ac4d274b010000006b483045022100c475588d9831bc804005e28d9187"
			"864d99804c835a638697911837cc323a83bc02205dc77df1f6e0e1723d355a"
			"8f25cfc86919c24ab060d98e7dce4dab85e888dfa5012102f4fb3ee52627e8"
			"2138b0227a5e95b0cb216a7080143a793f34214236856e5b3bffffffff0386"
			"492500000000001976a9148dd5023478a002a1d3551445c3479f6f6ae611ad"
			"88ac80f0fa02000000001976a91431fbdf399f1f95ff2801fe140f491fb18c"
			"828fd388acec00a0a9010000001976a9146bbc6f8dcd25dfe35222e991b4a1"
			"c3105b302aa588ac00000000";

	NO_THROW(response = fx.btc.decoderawtransaction(rawHexTx));

	#ifdef VERBOSE
	std::cout << "=== decoderawtransaction ===" << std::endl;
	std::cout << "Txid: " << response.txid << std::endl;
	std::cout << "Version: " << response.version << std::endl;
	std::cout << "Locktime: " << response.locktime << std::endl;

	std::cout << "vin: " << std::endl;
	for(std::vector<vin_t>::iterator it = response.vin.begin(); it != response.vin.end(); it++){
		vin_t txin = (*it);
		std::cout << "  txid: " << txin.txid << std::endl;
		std::cout << "  vout: " << txin.n<< std::endl;

		std::cout << "  scriptSig: " << std::endl;
		std::cout << "    asm: " << txin.scriptSig.assm << std::endl;
		std::cout << "    hex: " << txin.scriptSig.hex << std::endl;
	}

	std::cout << "vout: " << std::endl;
	for(std::vector<vout_t>::iterator it = response.vout.begin(); it != response.vout.end(); it++){
		vout_t txout = (*it);
		std::cout << "  value: " << txout.value << std::endl;
		std::cout << "  n: " << txout.n << std::endl;

		std::cout << "  scriptPubKey" << std::endl;
		std::cout << "    asm: " << txout.scriptPubKey.assm << std::endl;
		std::cout << "    hex: " << txout.scriptPubKey.hex << std::endl;
		std::cout << "    reqSigs: " << txout.scriptPubKey.reqSigs << std::endl;
		std::cout << "    type: " << txout.scriptPubKey.type << std::endl;

		std::cout << "    addresses: " << std::endl;
		for(std::vector<std::string>::iterator it2 = txout.scriptPubKey.addresses.begin(); it2 != txout.scriptPubKey.addresses.end(); it2++){
			std::cout << "      " << (*it2) << std::endl;
		}
	}
	std::cout << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(SendRawTransaction) {

	MyFixture fx;

	std::string txid =
			"0100000001da95ea9ded6ca4d6d47ddebf36e7f6a76992573dfd836ae46abf"
			"12b3ac4d274b010000006b483045022100c475588d9831bc804005e28d9187"
			"864d99804c835a638697911837cc323a83bc02205dc77df1f6e0e1723d355a"
			"8f25cfc86919c24ab060d98e7dce4dab85e888dfa5012102f4fb3ee52627e8"
			"2138b0227a5e95b0cb216a7080143a793f34214236856e5b3bffffffff0386"
			"492500000000001976a9148dd5023478a002a1d3551445c3479f6f6ae611ad"
			"88ac80f0fa02000000001976a91431fbdf399f1f95ff2801fe140f491fb18c"
			"828fd388acec00a0a9010000001976a9146bbc6f8dcd25dfe35222e991b4a1"
			"c3105b302aa588ac00000000";

	NO_THROW_EXCEPT(fx.btc.sendrawtransaction(txid, false), -27);
}

BOOST_AUTO_TEST_CASE(CreateRawTransaction) {

	MyFixture fx;

	txout_t tmp1 = {"32df9c334ad982c23c07eb95a597e905ad799ad7639264eaeeb009f4c7d621c7", 1};

	std::vector<txout_t> param1;
	std::map<std::string,double> param2 = {{"1DvwT9U88mLKUztzrXqwZugqYFasr97oLe", 0.0001}};
	param1.push_back(tmp1);

	std::string response;
	std::string expected =
			"0100000001c721d6c7f409b0eeea649263d79a79ad05e997a595eb073cc282d"
			"94a339cdf320100000000ffffffff0110270000000000001976a9148dd50234"
			"78a002a1d3551445c3479f6f6ae611ad88ac00000000";

	NO_THROW(response = fx.btc.createrawtransaction(param1, param2));
	BOOST_REQUIRE(response == expected);
}

BOOST_AUTO_TEST_CASE(SignRawTransaction) {

	MyFixture fx;

	signrawtxin_t tmp1;
	tmp1.txid = "32df9c334ad982c23c07eb95a597e905ad799ad7639264eaeeb009f4c7d621c7";
	tmp1.n = 1;
	tmp1.scriptPubKey = "76a914d420d8993d6266a273583adc31330cc0cf09c5c088ac";

	std::string tmp2 = "KxX3UUreFY8RxFpso8g5RD9tkrn1LNgnZVtUPok23qBpzL2fgdyd";

	std::string param1 =
				"0100000001c721d6c7f409b0eeea649263d79a79ad05e997a595eb073cc282d"
				"94a339cdf320100000000ffffffff0110270000000000001976a9148dd50234"
				"78a002a1d3551445c3479f6f6ae611ad88ac00000000";
	std::vector<signrawtxin_t> param2;
	std::vector<std::string> param3;
	param2.push_back(tmp1);
	param3.push_back(tmp2);

	signrawtransaction_t response;

	NO_THROW(response = fx.btc.signrawtransaction(param1,param2,param3,"ALL"));
	BOOST_REQUIRE(response.hex.size() >= param1.size() + 100);
	BOOST_REQUIRE(response.complete == true);

}

BOOST_AUTO_TEST_CASE(GetRawMempool) {

	MyFixture fx;

	std::vector<std::string> response;
	NO_THROW(response = fx.btc.getrawmempool());
	BOOST_REQUIRE(response.size() >= 0);

	#ifdef VERBOSE
	std::cout << "=== getrawmempool ===" << std::endl;
	for(std::vector<std::string>::iterator it = response.begin(); it != response.end(); it++){
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetRawChangeAddress) {

	MyFixture fx;

	std::string response;
	NO_THROW_EXCEPT(response = fx.btc.getrawchangeaddress(), -12);
	BOOST_REQUIRE(response.size() >= 27 && response.size() <= 34);

	#ifdef VERBOSE
	std::cout << "=== getrawchangeaddress ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_SUITE_END()
