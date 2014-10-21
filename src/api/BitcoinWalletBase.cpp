/**
 * BitcoinWalletBase.cpp
 *
 * @author Krzysztof Okupski
 * @version 1.0
 */

#include <stdexcept>
#include "BitcoinWallet.h"
#include "BitcoinException.h"

using jsonrpc::Client;
using jsonrpc::HttpClient;
using jsonrpc::JsonRpcException;

using Json::Value;
using std::string;


BitcoinAPI::BitcoinAPI() {
	conn = {};
}

BitcoinAPI::BitcoinAPI(const string& user, const string& password, const string& host, int port){
	conn.user = user;
	conn.password = password;
	conn.host = host;
	conn.port = port;
	conn.url = "http://"+ conn.user + ":"+ conn.password + "@" + conn.host + ":" + NumberToString(conn.port);
}

bool BitcoinAPI::IsInit(){
	return !(conn.user.empty() || conn.password.empty() || conn.host.empty() || conn.port == 0);
}

string BitcoinAPI::NumberToString (int number){
	std::ostringstream ss;
	ss << number;
	return ss.str();
}

int BitcoinAPI::StringToNumber (const string &text){
	std::istringstream ss(text);
	int result;
	return ss >> result ? result : 0;
}

Value BitcoinAPI::sendcommand(const string& command, const Value& params){
	Value result;
	Client c(new HttpClient(conn.url));

	try{
		result = c.CallMethod(command, params);
	}
	catch (JsonRpcException& e){
		BitcoinException err(e.GetCode(), e.GetMessage());
		throw err;
	}

	return result;
}

