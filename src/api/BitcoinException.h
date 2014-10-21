/**
 * BitcoinException.h
 * 
 * Declaration of error class for the JSON-RPC wrapper.
 *
 * @author Krzysztof Okupski
 * @version 1.0
 */

#ifndef BITCOINERROR_H
#define BITCOINERROR_H

#include <string>
#include <sstream>

class BitcoinException: public std::exception
{
private:
	int code;
	std::string msg;

public:
	explicit BitcoinException(int errcode, const std::string& message) {
		this->code = errcode;
		this->msg = parse(message);

	}
	~BitcoinException() throw() { };

	int getCode(){
		return code;
	}

	std::string getMessage(){
		return msg;
	}

	std::string parse(const std::string& in){
		std::string out = in;
		std::string pattern = ": ";
		unsigned int pos = out.find(pattern);
		if(pos <= out.size()){
			out.erase(pos, pattern.size());
			out[0] = toupper(out[0]);
		}

		return out;
	}

	virtual const char* what() const throw (){
		std::stringstream out;
		out << "Error " << code << ": " << msg;
		return out.str().c_str();
	}
};



#endif
