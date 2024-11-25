#pragma once
#include <string_view>
#include <string>

enum http_method {
	DELETE = 0,
	GET = 1,
	POST = 2,
	UNKNOWN = 3
};

enum states {
	s_init,
	s_get_method,
	s_get_uri,
	s_get_http,
	s_get_headers,
	s_end
};

class HttpParser {
	private:
		http_method _method;
		std::string_view _uri;
		states _state;
	public:
		HttpParser();
		size_t readMethod(const std::string_view data);
		http_method getMethod() const;
		void startParsing(std::string data);
		size_t httpParserExecute();

		static const std::string methodToString(http_method method);
};
