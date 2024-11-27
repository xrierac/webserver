#include "HttpParser.hpp"
#include <stdexcept>

// Constructor
HttpParser::HttpParser(size_t size) : _body_size(size) {}

//Getters
e_http_method HttpParser::getMethod() { return _method;}
std::string_view HttpParser::getMethodString() {return _method_string;}
std::string_view HttpParser::getTarget() { return _target;}
bool HttpParser::isValidHttp() { return _valid_http;}
std::unordered_map<std::string_view, std::string_view> HttpParser::getHeaders() { return _headers;}

void	HttpParser::checkReqLineErrors()
{

}

size_t HttpParser::parseMethod()
{
	size_t index = _request.find(' ');
	_method_string = _request.substr(0, index);
	if (_method_string == "GET")
		_method = GET;
	else if (_method_string == "POST")
		_method = POST;
	else if (_method_string == "DELETE")
		_method = DELETE;
	else
		_method = UNKNOWN;
	return index;
}

size_t HttpParser::parseTarget(size_t index)
{
	while (index < _request.size() && std::isspace(_request[index]))
		index++;
	size_t new_index = _request.find(' ', index);
	_target = _request.substr(index, new_index - (index));
	return new_index;
}

size_t HttpParser::parseHttp(size_t index)
{
	while (index < _request.size() && std::isspace(_request[index]))
		index++;
	size_t new_index = _request.find("\r\n", index);
	std::string_view sv = _request.substr(index, new_index - (index));
	if (sv == "HTTP/1.1")
		_valid_http = true;
	else
		_valid_http = false;
	return new_index;
}

size_t HttpParser::parseHeaders(size_t index)
{
	size_t iter, end_line;
	index += 2;
	size_t end_headers = _request.find("\r\n\r\n", index);
	while (index < end_headers)
	{
		iter = index;
		end_line = _request.find("\r\n", index);
		while (iter < end_line && _request[iter] != ':')
			iter++;
		if (_request[iter - 1] == ' ')
			throw std::invalid_argument("Wrong headers.");
		std::string_view key = _request.substr(index, iter - index);
		iter++;
		while (iter < end_line && _request[iter] == ' ')
			iter++;
		index = iter;
		while (iter < end_line)
			iter++;
		std::string_view value = _request.substr(index, iter - index);
		_headers.emplace(key, value);
		index = end_line + 2;
	}
	return end_headers;
}

void HttpParser::parseRequest(std::string_view request)
{
	_request = request;
	size_t index;
	try {
		index = parseMethod();
		if (_method == UNKNOWN)
			throw std::invalid_argument("Wrong method.");
		index = parseTarget(index);
		index = parseHttp(index);
		if (_valid_http == false)
			throw std::invalid_argument("Wrong HTTP version.");
		index = parseHeaders(index);
	} catch (...) {}
}
