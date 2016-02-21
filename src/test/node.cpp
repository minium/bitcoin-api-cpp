#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include "main.cpp"

BOOST_AUTO_TEST_SUITE(NodeTests)

BOOST_AUTO_TEST_CASE(AddNode) {

	MyFixture fx;

	/* Add node */
	NO_THROW(fx.btc.addnode("127.0.0.255", "add"));
}

BOOST_AUTO_TEST_CASE(GetAddedNodeInfo) {

	MyFixture fx;

	std::vector<nodeinfo_t> response;
	NO_THROW(response = fx.btc.getaddednodeinfo(true, "127.0.0.255"));

	#ifdef VERBOSE
	std::cout << "=== getaddednodeinfo ===" << std::endl;
	for(std::vector<nodeinfo_t>::iterator it = response.begin(); it != response.end(); it++){
		nodeinfo_t node = (*it);

		BOOST_REQUIRE(node.addednode == "127.0.0.255");
		std::cout << "Addednode: " << node.addednode << std::endl;
		std::cout << "Connected: " << node.connected << std::endl;

		for(std::vector<netaddress_t>::iterator it2 = node.addresses.begin(); it2 != node.addresses.end(); it2++){
			std::cout << "- Address: " << (*it2).address << std::endl;
			std::cout << "- Connected: " << (*it2).connected << std::endl << std::endl;
		}
	}
	#endif
}

BOOST_AUTO_TEST_CASE(RemoveNode){

	MyFixture fx;

	NO_THROW(fx.btc.addnode("127.0.0.255", "remove"));

	std::vector<nodeinfo_t> nodeVec;
	NO_THROW(nodeVec = fx.btc.getaddednodeinfo(false));

	bool found = false;
	for(std::vector<nodeinfo_t>::iterator it = nodeVec.begin(); it != nodeVec.end(); it++){
		nodeinfo_t node = (*it);
		if(node.addednode == "127.0.0.255"){
			found = true;
		}
	}
	BOOST_REQUIRE(!found);
}

BOOST_AUTO_TEST_CASE(ConnectionCount){

	MyFixture fx;

	int count;
	NO_THROW(count = fx.btc.getconnectioncount());
	BOOST_REQUIRE(count >= 1);
}

BOOST_AUTO_TEST_CASE(GetPeerInfo){

	MyFixture fx;

	std::vector<peerinfo_t> response;
	NO_THROW(response = fx.btc.getpeerinfo());
	BOOST_REQUIRE(response.size() >= 1);

	#ifdef VERBOSE
	std::cout << "=== getpeerinfo ===" << std::endl;
	for(std::vector<peerinfo_t>::iterator it = response.begin(); it != response.end(); it++){
		peerinfo_t peer = (*it);

		BOOST_REQUIRE(peer.version >= 60000);
		BOOST_REQUIRE(peer.startingheight >= 10000);

		std::cout << "Addr: " << peer.addr << std::endl;
		std::cout << "Services: " << peer.services << std::endl;
		std::cout << "Lastsend: " << peer.lastsend << std::endl;
		std::cout << "Lastrecv: " << peer.lastrecv << std::endl;
		std::cout << "Bytessent: " << peer.bytessent << std::endl;
		std::cout << "Bytesrecv: " << peer.bytesrecv << std::endl;
		std::cout << "Conntime: " << peer.conntime << std::endl;
		std::cout << "Pingtime: " << peer.pingtime << std::endl;
		std::cout << "Version: " << peer.version << std::endl;
		std::cout << "Subver: " << peer.subver << std::endl;
		std::cout << "Inbound: " << peer.inbound << std::endl;
		std::cout << "Startingheight: " << peer.startingheight << std::endl;
		std::cout << "Banscore: " << peer.banscore << std::endl << std::endl;
	}
	#endif
}

BOOST_AUTO_TEST_SUITE_END()
