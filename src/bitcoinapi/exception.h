/**
 * @file    exception.h
 * @author  Krzysztof Okupski
 * @date    29.10.2014
 * @version 1.0
 *
 * Declaration of error class for the JSON-RPC wrapper.
 */

#ifndef BITCOIN_API_EXCEPTION_H
#define BITCOIN_API_EXCEPTION_H

#include <string>
#include <sstream>
#include <iostream>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <jsonrpccpp/client.h>

using Json::Value;
using Json::Reader;
using jsonrpc::Errors;


class BitcoinException: public std::exception
{
private:
	int code;
	std::string msg;

public:
	explicit BitcoinException(int errcode, const std::string& message) {
		
		/* Connection error */
		if(errcode == Errors::ERROR_CLIENT_CONNECTOR){
			this->code = errcode;
			this->msg = removePrefix(message, " -> ");		
		/* Authentication error */
		}else if(errcode == Errors::ERROR_RPC_INTERNAL_ERROR && message.size() == 18){
			this->code = errcode;
			this->msg = "Failed to authenticate successfully";
		/* Miscellaneous error */
		}else{
			this->code = parseCode(message);
			this->msg = parseMessage(message);
		}
	}

	~BitcoinException() throw() { };

	int getCode(){
		return code;
	}

	std::string getMessage(){
		return msg;
	}


	std::string removePrefix(const std::string& in, const std::string& pattern){
		std::string ret = in;

		unsigned int pos = ret.find(pattern);

		if(pos <= ret.size()){
			ret.erase(0, pos+pattern.size());
		}

		return ret;
	}

	/* Auxiliary JSON parsing */
	int parseCode(const std::string& in){
		Value root;
		Reader reader;

		/* Remove JSON prefix */
		std::string strJson = removePrefix(in, "INTERNAL_ERROR: : ");
		int ret = -1;

		/* Parse error message */
		bool parsingSuccessful = reader.parse(strJson.c_str(), root);
		if(parsingSuccessful) {
			ret = root["error"]["code"].asInt();
		}

		return ret;
	}

	std::string parseMessage(const std::string& in){
		Value root;
		Reader reader;

		/* Remove JSON prefix */
		std::string strJson = removePrefix(in, "INTERNAL_ERROR: : ");
		std::string ret = "Error during parsing of >>" + strJson + "<<";

		/* Parse error message */
		bool parsingSuccessful = reader.parse(strJson.c_str(), root);
		if(parsingSuccessful) {
			ret = removePrefix(root["error"]["message"].asString(), "Error: ");
			ret[0] = toupper(ret[0]);
		}

		return ret;
	}
};

#endif
