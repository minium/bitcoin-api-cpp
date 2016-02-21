#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include "main.cpp"

BOOST_AUTO_TEST_SUITE(MiningTests)

BOOST_AUTO_TEST_CASE(GetBestBlockHash) {

	MyFixture fx;
	std::string response;

	NO_THROW(response = fx.btc.getbestblockhash());
	BOOST_REQUIRE(response.size() == 64);

	#ifdef VERBOSE
	std::cout << "=== getbestblockhash ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetBlockHash) {

	MyFixture fx;
	std::string response;

	NO_THROW(response = fx.btc.getblockhash(1));
	BOOST_REQUIRE(response.size() == 64);

	#ifdef VERBOSE
	std::cout << "=== getblockhash ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetBlockCount) {

	MyFixture fx;
	int response;

	NO_THROW(response = fx.btc.getblockcount());
	BOOST_REQUIRE(response >= 10);

	#ifdef VERBOSE
	std::cout << "=== getblockcount ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetBlock) {

	MyFixture fx;
	blockinfo_t response;

	NO_THROW(response = fx.btc.getblock("00000000839a8e6886ab5951d76f411475428afc90947ee320161bbf18eb6048"));
	BOOST_REQUIRE(response.height == 1);

	#ifdef VERBOSE
	std::cout << "=== getblock (10th block) ===" << std::endl;
	std::cout << "hash: " << response.hash << std::endl;
	std::cout << "confirmations: " << response.confirmations << std::endl;
	std::cout << "size: " << response.size << std::endl;
	std::cout << "height: " << response.height << std::endl;
	std::cout << "version: " << response.version << std::endl;
	std::cout << "merkleroot: " << response.merkleroot << std::endl;

	std::cout << "tx: " << std::endl;
	for(std::vector<std::string>::iterator it = response.tx.begin(); it != response.tx.end(); it++){
		std::cout << "  " << (*it) << std::endl;
	}

	std::cout << "time: " << response.time << std::endl;
	std::cout << "nonce: " << response.nonce << std::endl;
	std::cout << "bits: " << response.bits << std::endl;
	std::cout << "difficulty: " << response.difficulty << std::endl;
	std::cout << "chainwork: " << response.chainwork << std::endl;
	std::cout << "previousblockhash: " << response.previousblockhash << std::endl;
	std::cout << "nextblockhash: " << response.nextblockhash << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(GetGenerate) {

	MyFixture fx;
	bool response;

	NO_THROW(response = fx.btc.getgenerate());
	BOOST_REQUIRE(response == true || response == false);

	#ifdef VERBOSE
	std::cout << "=== getgenerate ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(SetGenerate) {

	MyFixture fx;

	NO_THROW(fx.btc.setgenerate(true));
	BOOST_REQUIRE(fx.btc.getgenerate() == true);

	NO_THROW(fx.btc.setgenerate(false));
	BOOST_REQUIRE(fx.btc.getgenerate() == false);
}



BOOST_AUTO_TEST_CASE(GetDifficulty) {

	MyFixture fx;
	double response;

	NO_THROW(response = fx.btc.getdifficulty());
	BOOST_REQUIRE(response >= 100000);

	#ifdef VERBOSE
	std::cout << "=== getdifficulty ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}


BOOST_AUTO_TEST_CASE(GetMiningInfo) {

	MyFixture fx;
	mininginfo_t response;

	NO_THROW(response = fx.btc.getmininginfo());
	BOOST_REQUIRE(response.blocks > 1);

	#ifdef VERBOSE
	std::cout << "=== getmininginfo ===" << std::endl;
	std::cout << "blocks: " << response.blocks << std::endl;
	std::cout << "currentblocksize: " << response.currentblocksize << std::endl;
	std::cout << "currentblocktx: " << response.currentblocktx << std::endl;
	std::cout << "difficulty: " << response.difficulty << std::endl;
	std::cout << "errors: " << response.errors << std::endl;
	std::cout << "genproclimit: " << response.genproclimit << std::endl;
	std::cout << "networkhashps: " << response.networkhashps << std::endl;
	std::cout << "pooledtx: " << response.pooledtx << std::endl;
	std::cout << "testnet: " << response.testnet << std::endl;
	std::cout << "generate: " << response.generate << std::endl;
	std::cout << "hashespersec: " << response.hashespersec << std::endl << std::endl;
	#endif
}


BOOST_AUTO_TEST_CASE(ListSinceBlock) {

	MyFixture fx;
	txsinceblock_t response;

	NO_THROW(response = fx.btc.listsinceblock("", 1));

	#ifdef VERBOSE
	std::cout << "=== listsinceblock ===" << std::endl;
	for(std::vector<transactioninfo_t>::iterator it = response.transactions.begin(); it != response.transactions.end(); it++){
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
	std::cout << "lastblock: " << response.lastblock << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_SUITE_END()
