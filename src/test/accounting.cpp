#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#include "main.cpp"

using boost::filesystem::path;
using boost::filesystem::exists;
using boost::filesystem::remove;
using boost::filesystem::current_path;

BOOST_AUTO_TEST_SUITE(AccountingTests)

BOOST_AUTO_TEST_CASE(GetBalance) {

	MyFixture fx;

	NO_THROW(fx.btc.getbalance());
	NO_THROW(fx.btc.getbalance(""));

	#ifdef VERBOSE
	double response = fx.btc.getbalance();
	std::cout << "=== getbalance ===" << std::endl;
	std::cout << "Balance: " << response << std::endl;
	std::cout << "Balance (default account): " << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetReceivedByAccount) {

	MyFixture fx;

	NO_THROW(fx.btc.getreceivedbyaccount(""));

	#ifdef VERBOSE
	double response = fx.btc.getreceivedbyaccount("");
	std::cout << "=== getreceivedbyaccount ===" << std::endl;
	std::cout << "Balance (default account): " << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetReceivedByAddress) {

	MyFixture fx;

	std::string param = "36m2bHwsUnkpGsZgVAEmeJRf2CeViDm6RV";

	NO_THROW(fx.btc.getreceivedbyaddress(param));

	#ifdef VERBOSE
	double response = fx.btc.getreceivedbyaddress(param);

	std::cout << "=== getreceivedbyaddress ===" << std::endl;
	std::cout << "Balance (new address): " << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(ListReceivedByAccount) {

	MyFixture fx;

	std::vector<accountinfo_t> response;
	NO_THROW(response = fx.btc.listreceivedbyaccount(1,true));

	#ifdef VERBOSE
	std::cout << "=== listreceivedbyaccount ===" << std::endl;
	for(std::vector<accountinfo_t>::iterator it = response.begin(); it != response.end(); it++){
		accountinfo_t acct = (*it);
		std::cout << "Account: " << acct.account << std::endl;
		std::cout << "Amount: " << acct.amount << std::endl;
		std::cout << "Confirmations: " << acct.confirmations << std::endl << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_CASE(ListReceivedByAddress) {

	MyFixture fx;

	std::vector<addressinfo_t> response;
	NO_THROW(response = fx.btc.listreceivedbyaddress(1,true));

	#ifdef VERBOSE
	std::cout << "=== listreceivedbyaccount ===" << std::endl;
	for(std::vector<addressinfo_t>::iterator it = response.begin(); it != response.end(); it++){
		addressinfo_t acct = (*it);
		std::cout << "Address: " << acct.address << std::endl;
		std::cout << "Account: " << acct.account << std::endl;
		std::cout << "Amount: " << acct.amount << std::endl;
		std::cout << "Confirmations: " << acct.confirmations << std::endl;

		for(std::vector<std::string>::iterator it2 = acct.txids.begin(); it2 != acct.txids.end(); it2++){
			std::cout << "  " << (*it2) << std::endl;
		}

		std::cout << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_CASE(GetTransaction) {

	MyFixture fx;

	std::string txid = "5a8f750129702d4e0ccd3e6fa91193d8191ea9742a36835b43d3b3c56ad816d1";
	gettransaction_t response;
	
	NO_THROW_EXCEPT(response = fx.btc.gettransaction(txid, false), -5);

	#ifdef VERBOSE
	std::cout << "=== gettransaction ===" << std::endl;
	std::cout << "Amount: " << response.amount << std::endl;
	std::cout << "Fee: " << response.fee << std::endl;
	std::cout << "Confirmations: " << response.confirmations << std::endl;
	std::cout << "Blockhash: " << response.blockhash << std::endl;
	std::cout << "Blockindex: " << response.blockindex << std::endl;
	std::cout << "Blocktime: " << response.blocktime << std::endl;
	std::cout << "Txid: " << response.txid << std::endl;
	std::cout << "Walletconflicts: " << std::endl;

	for(std::vector<std::string>::iterator it = response.walletconflicts.begin(); it != response.walletconflicts.end(); it++){
		std::cout << "  " << (*it) << std::endl;
	}

	std::cout << "Time: " << response.time << std::endl;
	std::cout << "Timereceived: " << response.timereceived << std::endl;
	std::cout << "Details: " << std::endl;

	for(std::vector<transactiondetails_t>::iterator it = response.details.begin(); it != response.details.end(); it++){
		transactiondetails_t det = (*it);
		std::cout << "  Account: " << det.account << std::endl;
		std::cout << "  Address: " << det.address << std::endl;
		std::cout << "  Category: " << det.category << std::endl;
		std::cout << "  Amount: " << det.amount << std::endl;
		std::cout << "  Vout: " << det.vout << std::endl;
		std::cout << "  Fee: " << det.fee << std::endl;
	}

	std::cout << "Hex: " << response.hex << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(ListTransactions) {

	MyFixture fx;

	std::vector<transactioninfo_t> response;
	NO_THROW(response = fx.btc.listtransactions());

	#ifdef VERBOSE
	std::cout << "=== listtransactions ===" << std::endl;
	for(std::vector<transactioninfo_t>::iterator it = response.begin(); it != response.end(); it++){
		transactioninfo_t tx = (*it);
		std::cout << "Account: " << tx.account << std::endl;
		std::cout << "Address: " << tx.address << std::endl;
		std::cout << "Category: " << tx.category << std::endl;
		std::cout << "Amount: " << tx.amount << std::endl;
		std::cout << "Confirmations: " << tx.confirmations << std::endl;
		std::cout << "Blockhash: " << tx.blockhash << std::endl;
		std::cout << "Blockindex: " << tx.blockindex << std::endl;
		std::cout << "Blocktime: " << tx.blocktime << std::endl;
		std::cout << "Txid: " << tx.txid << std::endl;
		std::cout << "Walletconflicts: " << std::endl;

		for(std::vector<std::string>::iterator it2 = tx.walletconflicts.begin(); it2 != tx.walletconflicts.end(); it2++){
			std::cout << "  " << (*it2) << std::endl;
		}

		std::cout << "Time: " << tx.time << std::endl;
		std::cout << "Timereceived: " << tx.timereceived << std::endl << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_CASE(GetAccount) {

	MyFixture fx;

	std::string address;
	std::string response;
	
	NO_THROW_EXCEPT(address = fx.btc.getnewaddress("TestUser"), -12);

	NO_THROW(response = fx.btc.getaccount(address));
	BOOST_REQUIRE(response == "TestUser");

	#ifdef VERBOSE
	std::cout << "=== getaccount ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetAccountAddress) {

	MyFixture fx;

	std::string address;
	std::string response;

	/* Unlock wallet and refill the keypool */
	NO_THROW_EXCEPT(fx.btc.walletpassphrase("123456", 10), -14);

	NO_THROW(fx.btc.keypoolrefill());
	NO_THROW(address = fx.btc.getnewaddress("TestUser"));
	BOOST_REQUIRE(address.length() >= 27 && address.length() <= 34);

	#ifdef VERBOSE
	std::cout << "=== getaccountddress ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetAddressesByAccount) {

	MyFixture fx;

	std::vector<std::string> response;
	NO_THROW(response = fx.btc.getaddressesbyaccount("TestUser"));
	BOOST_REQUIRE(response.size() >= 1);

	#ifdef VERBOSE
	std::cout << "=== getaddressesbyaccount ===" << std::endl;
	for(std::vector<std::string>::iterator it = response.begin(); it !=  response.end(); it++){
		std::cout << (*it) << std::endl;
	}
	std::cout << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(ListAccounts) {

	MyFixture fx;

	std::map<std::string, double> response;
	NO_THROW(response = fx.btc.listaccounts());

	#ifdef VERBOSE
	std::cout << "=== listaccounts ===" << std::endl;
	for(std::map<std::string, double>::iterator it = response.begin(); it != response.end(); it++){
		std::cout << (*it).first << ": " << (*it).second << std::endl;
	}
	std::cout << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(Move) {
/*
	MyFixture fx;

	double acc1_old, acc2_old;
	double acc1_new, acc2_new;
	bool response;

	BOOST_REQUIRE_NO_THROW(acc1_old = fx.btc.getbalance("Bitonic"));
	BOOST_REQUIRE_NO_THROW(acc2_old = fx.btc.getbalance("Bitonic 2"));

	BOOST_REQUIRE_NO_THROW(response = fx.btc.move("Bitonic", "Bitonic 2", 0.001));
	BOOST_REQUIRE(response == true);

	BOOST_REQUIRE_NO_THROW(acc1_new = fx.btc.getbalance("Bitonic"));
	BOOST_REQUIRE_NO_THROW(acc2_new = fx.btc.getbalance("Bitonic 2"));

	BOOST_REQUIRE((acc1_old - 0.001) == acc1_new);
	BOOST_REQUIRE((acc2_old + 0.001) == acc2_new);
*/
}

BOOST_AUTO_TEST_CASE(SetAccount) {

	MyFixture fx;

	std::string address;
	NO_THROW_EXCEPT(address = fx.btc.getnewaddress("TestUser"), -12);
	NO_THROW(fx.btc.setaccount(address,"TestUser2"));
}

BOOST_AUTO_TEST_CASE(SendToAddress) {
/*
	MyFixture fx;
	std::string addr;
	std::string txid;

	BOOST_REQUIRE_NO_THROW(addr = fx.btc.getnewaddress("TestUser"));
	BOOST_REQUIRE_NO_THROW(fx.btc.walletpassphrase("123456", 5));
	BOOST_REQUIRE_NO_THROW(txid = fx.btc.sendtoaddress(addr, 0.0001));
	std::cout << "=== sendtoaddress ===" << std::endl;
	std::cout << "txid: " << txid << std::endl << std::endl;
*/
}

BOOST_AUTO_TEST_CASE(SendFrom) {
/*
	MyFixture fx;
	std::string response;

	BOOST_REQUIRE_NO_THROW(fx.btc.walletpassphrase("123456", 3));
	BOOST_REQUIRE_NO_THROW(response = fx.btc.sendfrom("Bitonic 2", "1DvwT9U88mLKUztzrXqwZugqYFasr97oLe", 0.0002));
	BOOST_REQUIRE(response.size() == 64);

	#ifdef VERBOSE
	std::cout << "=== sendfrom ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
*/
}

BOOST_AUTO_TEST_CASE(SendMany) {
/*
	MyFixture fx;
	std::string response;

	txaddressamount_t tmp = { "1DvwT9U88mLKUztzrXqwZugqYFasr97oLe", 0.0003 };
	std::vector<txaddressamount_t> param;
	param.push_back(tmp);

	BOOST_REQUIRE_NO_THROW(fx.btc.walletpassphrase("123456", 3));
	BOOST_REQUIRE_NO_THROW(response = fx.btc.sendmany("Bitonic 2", param));
	BOOST_REQUIRE(response.size() == 64);

	#ifdef VERBOSE
	std::cout << "=== sendmany ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
*/
}

BOOST_AUTO_TEST_CASE(GetTxOut) {

	MyFixture fx;

	std::string txid = "105d8fd318533d4559492b85a27039f2bf8bdfed39b8e671753289eaeb3829ae";
	utxoinfo_t response;

	NO_THROW(response = fx.btc.gettxout(txid, 0));

	#ifdef VERBOSE
	std::cout << "=== gettxout ===" << std::endl;
	std::cout << "bestblock: " << response.bestblock << std::endl;
	std::cout << "confirmations: " << response.confirmations << std::endl;
	std::cout << "scriptPubKey: " << std::endl;
	std::cout << "  asm: " << response.scriptPubKey.assm << std::endl;
	std::cout << "  hex: " << response.scriptPubKey.hex << std::endl;
	std::cout << "  reqSigs: " << response.scriptPubKey.reqSigs << std::endl;
	std::cout << "  type: " << response.scriptPubKey.type << std::endl;

	std::cout << "  addresses: " << std::endl;
	for(std::vector<std::string>::iterator it = response.scriptPubKey.addresses.begin(); it != response.scriptPubKey.addresses.end(); it++){
		std::cout << "    " << (*it) << std::endl;
	}
	std::cout << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetTxOutSetInfo) {

	MyFixture fx;

	utxosetinfo_t response;

	NO_THROW(response = fx.btc.gettxoutsetinfo());

	#ifdef VERBOSE
	std::cout << "=== gettxoutsetinfo ===" << std::endl;
	std::cout << "height: " << response.height << std::endl;
	std::cout << "bestblock: " << response.bestblock << std::endl;
	std::cout << "transactions: " << response.transactions << std::endl;
	std::cout << "txouts: " << response.txouts << std::endl;
	std::cout << "bytes_serialized: " << response.bytes_serialized << std::endl;
	std::cout << "hash_serialized: " << response.hash_serialized << std::endl;
	std::cout << "total_amount: " << response.total_amount << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(ListUnspent) {

	MyFixture fx;

	std::vector<unspenttxout_t> response;
	NO_THROW(response = fx.btc.listunspent());

	#ifdef VERBOSE
	std::cout << "=== listunspent ===" << std::endl;
	for(std::vector<unspenttxout_t>::iterator it = response.begin(); it != response.end(); it++){
		unspenttxout_t tmp = (*it);
		std::cout << "txid: " << tmp.txid << std::endl;
		std::cout << "vout: " << tmp.n << std::endl;
		std::cout << "address: " << tmp.address << std::endl;
		std::cout << "account: " << tmp.account << std::endl;
		std::cout << "scriptPubKey: " << tmp.scriptPubKey << std::endl;
		std::cout << "amount: " << tmp.amount << std::endl;
		std::cout << "confirmations: " << tmp.confirmations << std::endl << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_CASE(ListLockUnspent) {

	MyFixture fx;

	std::vector<txout_t> response;
	NO_THROW(response = fx.btc.listlockunspent());

	#ifdef VERBOSE
	std::cout << "=== listlockunspent ===" << std::endl;
	for(std::vector<txout_t>::iterator it = response.begin(); it != response.end(); it++){
		txout_t tmp = (*it);
		std::cout << "txid: " << tmp.txid << std::endl;
		std::cout << "vout: " << tmp.n << std::endl << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_CASE(LockUnspent) {

	MyFixture fx;

	std::vector<txout_t> param;
	txout_t tmp = {"a1986a3b971a4bfca2705b8117b39e7d41dcc0e134c1639bb740f666fae2ed93", 1};
	param.push_back(tmp);
	bool response;

	NO_THROW(response = fx.btc.lockunspent(false, param));
	BOOST_REQUIRE(response == true);
}

BOOST_AUTO_TEST_CASE(ListAddressGroupings) {

	MyFixture fx;
	std::vector< std::vector<addressgrouping_t> > response;

	NO_THROW(response = fx.btc.listaddressgroupings());

	#ifdef VERBOSE
	std::cout << "=== listaddressgroupings ===" << std::endl;
	for(std::vector< std::vector<addressgrouping_t> >::iterator it1 = response.begin(); it1 != response.end(); it1++){
		std::vector<addressgrouping_t> tmp1 = (*it1);
		std::cout << "[" << std::endl;
		for(std::vector<addressgrouping_t>::iterator it2 = tmp1.begin(); it2 != tmp1.end(); it2++){
			addressgrouping_t tmp2 = (*it2);
			std::cout << "  [" << std::endl;

			std::cout << "    " << tmp2.address << std::endl;
			std::cout << "    " << tmp2.balance << std::endl;

			if(tmp2.account != "")
				std::cout << "    " << tmp2.account << std::endl;

			std::cout << "  ]" << std::endl;
		}
		std::cout << "]" << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_SUITE_END()
