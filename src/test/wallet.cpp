#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#include "main.cpp"

using boost::filesystem::path;
using boost::filesystem::exists;
using boost::filesystem::remove;
using boost::filesystem::current_path;

BOOST_AUTO_TEST_SUITE(WalletTests)


BOOST_AUTO_TEST_CASE(WalletBackup) {

	MyFixture fx;

	/* Check if backup under given path exists and fail if so */
	path bPath(current_path());
	bPath += "/wallet.backup";

	if(exists(bPath)) { remove(bPath); }
	BOOST_REQUIRE(!exists(bPath));

	/* Create backup and check if file exists */
	NO_THROW(fx.btc.backupwallet(bPath.generic_string()));

	BOOST_REQUIRE(exists(bPath));

	/* Clean up backup */
	BOOST_REQUIRE(remove(bPath));
}

BOOST_AUTO_TEST_CASE(EncryptWallet) {

	MyFixture fx;

	/* IF wallet is not encrypted THEN wallet will be encrypted
	   IF wallet is encrypted THEN error -15 is thrown
	*/
	NO_THROW_EXCEPT(fx.btc.encryptwallet("123456"), -15);
}

BOOST_AUTO_TEST_CASE(WalletPassphrase) {

	MyFixture fx;

	NO_THROW_EXCEPT(fx.btc.walletpassphrase("123456", 10), -14);
}

BOOST_AUTO_TEST_CASE(WalletLock) {

	MyFixture fx;

	NO_THROW(fx.btc.walletlock());
}

BOOST_AUTO_TEST_CASE(WalletPassphraseChange) {

	MyFixture fx;

	NO_THROW_EXCEPT(fx.btc.walletpassphrasechange("123456", "123456"), -14);
}

BOOST_AUTO_TEST_CASE(ImportDumpPrivkey) {

	MyFixture fx;

	std::string param1 = "5J1F7GHadZG3sCCKHCwg8Jvys9xUbFsjLnGec4H125Ny1V9nR6V";
	std::string param2 = "16UwLL9Risc3QfPqBUvKofHmBQ7wMtjvM";
	std::string response;

	/* Check if passphrase is correct and unlock wallet */
	NO_THROW_EXCEPT(fx.btc.walletpassphrase("123456", 10), -14);

	/* Attempt to import the privkey */
	NO_THROW(fx.btc.importprivkey(param1, "TestKey", false));

	/* Dump private key */
	NO_THROW(response = fx.btc.dumpprivkey(param2));
	BOOST_REQUIRE(param1 == response);

	#ifdef VERBOSE
	std::cout << "=== dumpprivkey ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif

	/* Clean up */
	NO_THROW(fx.btc.walletlock());
}

BOOST_AUTO_TEST_CASE(AddMultisigAddress) {

	MyFixture fx;

	std::string tmp1 = "0287f9169e265380a87cfd717ec543683f572db8b5a6d06231ff59c43429063ae4";
	std::string tmp2 = "0343947d178f20b8267488e488442650c27e1e9956c824077f646d6ce13a285d84";
	std::vector<std::string> param;
	param.push_back(tmp1);
	param.push_back(tmp2);

	std::string response;
	std::string address = "36m2bHwsUnkpGsZgVAEmeJRf2CeViDm6RV";

	NO_THROW(response = fx.btc.addmultisigaddress(2, param));
	BOOST_REQUIRE(response == address);
}

BOOST_AUTO_TEST_CASE(CreateMultisig) {

	MyFixture fx;

	std::string tmp1 = "0287f9169e265380a87cfd717ec543683f572db8b5a6d06231ff59c43429063ae4";
	std::string tmp2 = "0343947d178f20b8267488e488442650c27e1e9956c824077f646d6ce13a285d84";
	std::vector<std::string> param;
	param.push_back(tmp1);
	param.push_back(tmp2);

	multisig_t response;
	std::string address = "36m2bHwsUnkpGsZgVAEmeJRf2CeViDm6RV";
	std::string redeemScript =
			"52210287f9169e265380a87cfd717ec543683f572db8b5a6d06231ff59c4342906"
			"3ae4210343947d178f20b8267488e488442650c27e1e9956c824077f646d6ce13a"
			"285d8452ae";

	NO_THROW(response = fx.btc.createmultisig(2, param));
	BOOST_REQUIRE(response.address == address);
	BOOST_REQUIRE(response.redeemScript == redeemScript);
}

BOOST_AUTO_TEST_CASE(GetNewAddress) {

	MyFixture fx;

	std::string response;
	
	NO_THROW_EXCEPT(response = fx.btc.getnewaddress(), -12);
	BOOST_REQUIRE(response.length() >= 27 && response.length() <= 34);

	#ifdef VERBOSE
	std::cout << "=== getnewaddress ===" << std::endl;
	std::cout << response << std::endl << std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(ValidateAddress) {

	MyFixture fx;

	std::string param;
	validateaddress_t response;

	NO_THROW(param = fx.btc.getaccountaddress(""));
	NO_THROW(response = fx.btc.validateaddress(param));

	#ifdef VERBOSE
	std::cout << "=== validateaddress ===" << std::endl;
	std::cout << "isvalid: " << response.isvalid << std::endl;
	std::cout << "address: " << response.address << std::endl;
	std::cout << "ismine: " << response.ismine << std::endl;
	std::cout << "isscript: " << response.isscript << std::endl;
	std::cout << "pubkey: " << response.pubkey << std::endl;
	std::cout << "iscompressed: " << response.iscompressed << std::endl
			<< std::endl;
	#endif
}

BOOST_AUTO_TEST_CASE(KeypoolRefill) {

	MyFixture fx;

	int oldkeypoolsize;
	int newkeypoolsize;
	int refreshedkeypoolsize;	
	std::string addr;

	/* Get current keypool size and use one key */
	NO_THROW(oldkeypoolsize = fx.btc.getinfo().keypoolsize);
	NO_THROW(addr = fx.btc.getnewaddress());
	NO_THROW(newkeypoolsize = fx.btc.getinfo().keypoolsize);
	
	BOOST_REQUIRE((oldkeypoolsize - 1) == newkeypoolsize || newkeypoolsize == 101);

	/* Check if passphrase is correct and unlock wallet */
	NO_THROW_EXCEPT(fx.btc.walletpassphrase("123456", 10), -14);

	/* Then refill the keypool */
	NO_THROW(fx.btc.keypoolrefill());
	NO_THROW(refreshedkeypoolsize = fx.btc.getinfo().keypoolsize);
	BOOST_REQUIRE(refreshedkeypoolsize == 101);
}

BOOST_AUTO_TEST_CASE(SetTxFee) {

	MyFixture fx;

	bool response;
	double getinfofee;

	NO_THROW(response = fx.btc.settxfee(0.0002));
	BOOST_REQUIRE(response == true);

	NO_THROW(getinfofee = fx.btc.getinfo().paytxfee);
	BOOST_REQUIRE(getinfofee == 0.0002);
}

BOOST_AUTO_TEST_CASE(SignVerifyMessage) {

	MyFixture fx;

	std::string msg1 = "Test1";
	std::string msg2 = "Test2";
	std::string addr;
	std::string sig;
	bool response = false;

	/* Check if passphrase is correct and unlock wallet */
	NO_THROW_EXCEPT(fx.btc.walletpassphrase("123456", 10), -14);

	NO_THROW(addr = fx.btc.getaccountaddress(""));
	NO_THROW(sig = fx.btc.signmessage(addr, msg1));

	NO_THROW(response = fx.btc.verifymessage(addr, sig, msg1));
	BOOST_REQUIRE(response == true);

	BOOST_REQUIRE_NO_THROW(response = fx.btc.verifymessage(addr, sig, msg2));
	BOOST_REQUIRE(response == false);
}

BOOST_AUTO_TEST_SUITE_END()
