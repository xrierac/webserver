#include "HttpParser.hpp"

HttpParser::HttpParser() : _state(s_init) {}

http_method HttpParser::getMethod() const {return _method;}

size_t HttpParser::readMethod(const std::string_view data)
{
	switch(data[0])
	{
		case 'G':
			_method = GET;
		case 'D':
			_method = DELETE;
		case 'P':
			_method = POST;
		default:
			_method = UNKNOWN;
	}
	for(size_t i = 0; i < data.size(); i++)
	{

	}

}

void HttpParser::startParsing(std::string data)
{
	std::string_view view_data {data};
	for(size_t i = 0; i < view_data.size(); i++)
	{

	}
}

const std::string HttpParser::methodToString(http_method method)
{
	switch(method)
	{
		case GET: return "GET";
		case POST: return "POST";
		case DELETE: return "DELETE";
		default: return "UNKNOWN";
	}
}
