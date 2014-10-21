/**
 * WalletTypes.h
 * 
 * Type definitions for the JSON-RPC C++ interface.
 *
 * @author Krzysztof Okupski
 * @version 1.0
 */

#ifndef WALLETTYPES_H
#define WALLETTYPES_H

	/* === General types === */
	struct getinfo_t{
		int version;
		int protocolversion;
		int walletversion;
		double balance;
		int blocks;
		int timeoffset;
		int connections;
		std::string proxy;
		double difficulty;
		bool testnet;
		int keypoololdest;
		int keypoolsize;
		double paytxfee;
		int unlocked_until;
		std::string errors;
	};


	/* === Node types === */
	struct netaddress_t{
		std::string address;
		bool connected;
	};

	struct nodeinfo_t{
		std::string addednode;
		bool connected;
		std::vector<netaddress_t> addresses;
	};

	struct peerinfo_t{
		std::string addr;
		std::string services;
		int lastsend;
		int lastrecv;
		int bytessent;
		int bytesrecv;
		int conntime;
		double pingtime;
		int version;
		std::string subver;
		bool inbound;
		int startingheight;
		int banscore;
	};


	/* === Account, address types === */
	struct accountinfo_t{
		std::string account;
		double amount;
		int confirmations;
	};

	struct addressinfo_t: accountinfo_t{
		std::string address;
		std::vector<std::string> txids;
	};

	struct transactioninfo_t: accountinfo_t{
		std::string address;
		std::string category;
		std::string blockhash;
		int blockindex;
		int blocktime;
		std::string txid;
		std::vector<std::string> walletconflicts;
		int time;
		int timereceived;
	};

	struct multisig_t{
		std::string address;
		std::string redeemScript;
	};

	struct validateaddress_t{
		bool isvalid;
		std::string address;
		bool ismine;
		bool isscript;
		std::string pubkey;
		bool iscompressed;
		std::string account;
	};

	struct addressgrouping_t{
		std::string address;
		double balance;
		std::string account;
	};

	/* === Transactions === */
	struct transactiondetails_t{
		std::string account;
		std::string address;
		std::string category;
		double amount;
	};

	struct gettransaction_t{
		double amount;
		int confirmations;
		std::string blockhash;
		int blockindex;
		int blocktime;
		std::string txid;
		std::vector<std::string> walletconflicts;
		int time;
		int timereceived;
		std::vector<transactiondetails_t> details;
		std::string hex;
	};


	/* decoderawtransaction return type */
	struct scriptSig_t{
		std::string assm;
		std::string hex;
	};

	struct scriptPubKey_t{
		std::string assm;
		std::string hex;
		int reqSigs;
		std::string type;
		std::vector<std::string> addresses;
	};

	struct txout_t{
		std::string txid;
		unsigned int n;
	};

	struct vin_t: txout_t{
		scriptSig_t scriptSig;
		unsigned int sequence;
	};

	struct vout_t{
		double value;
		unsigned int n;
		scriptPubKey_t scriptPubKey;
	};

	struct decoderawtransaction_t{
		std::string txid;
		int version;
		int locktime;
		std::vector<vin_t> vin;
		std::vector<vout_t> vout;
	};

	/* getrawtransaction return type */
	struct getrawtransaction_t: decoderawtransaction_t{
		std::string hex;
		std::string blockhash;
		unsigned int confirmations;
		unsigned int time;
		unsigned int blocktime;
	};

	/* signrawtransaction return type */
	struct signrawtxin_t: txout_t{
		std::string scriptPubKey;
		std::string redeemScript;
	};

	/* signrawtransaction return type */
	struct signrawtransaction_t{
		std::string hex;
		bool complete;
	};





	/* === Other === */
	struct utxoinfo_t{
		std::string bestblock;
		int confirmations;
		double value;
		scriptPubKey_t scriptPubKey;
		int version;
		bool coinbase;
	};

	struct utxosetinfo_t{
		int height;
		std::string bestblock;
		int transactions;
		int txouts;
		int bytes_serialized;
		std::string hash_serialized;
		double total_amount;
	};

	struct unspenttxout_t: txout_t{
		std::string address;
		std::string account;
		std::string scriptPubKey;
		double amount;
		int confirmations;
	};


	/* === Unused yet === */
	struct blockinfo_t{
		std::string hash;
		int confirmations;
		int size;
		int height;
		int version;
		std::string merkleroot;
		std::vector<std::string> tx;
		unsigned int time;
		unsigned int nonce;
		std::string bits;
		double difficulty;
		std::string chainwork;
		std::string previousblockhash;
		std::string nextblockhash;
	};

	struct mininginfo_t{
		int blocks;
		int currentblocksize;
		int currentblocktx;
		double difficulty;
		std::string errors;
		int genproclimit;
		double networkhashps;
		int pooledtx;
		bool testnet;
		bool generate;
		int hashespersec;
	};

	struct workdata_t{
		std::string midstate;
		std::string data;
		std::string hash1;
		std::string target;
	};

	struct txsinceblock_t{
		std::vector<transactioninfo_t> transactions;
		std::string lastblock;
	};

#endif /* TYPES_H_ */
