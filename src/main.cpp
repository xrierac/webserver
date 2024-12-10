
#include "HttpParser.hpp"
#include <iostream>

void printParserResults(HttpParser& parser) {
    // You'll need to add getter methods to your HttpParser class to access these
    std::cout << "Method:<" << parser.getMethodString() << ">\n";
    std::cout << "Target:<" << parser.getTarget() << ">\n";
    std::cout << "Valid HTTP: " << (parser.isValidHttp() ? "yes" : "no") << std::endl;

    std::cout << "Headers:" << std::endl;
    for (const auto& [key, value] : parser.getHeaders()) {
        std::cout << "<" << key << ">:<" << value << ">\n";
    }

    std::cout << "\nBody:<" << parser.getBody() << ">\n";
}

int main() {
    // Test case 1: Valid GET request
    std::string request1 =
        "GET        /index.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0\r\n"
        "Accept: text/html\r\n"
        "\r\n";

    // Test case 2: Valid POST request with body
    std::string request2 =
        "POST /submit HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Content-Type: multipart/form-data; boundary=------------------------a3a1875fe37fee60     \r\n"
        //"Content-Type: application/json               \r\n"
        "Content-Length: 189\r\n"
        "\r\n"
        "{\"username\": \"john_doe\"}";

    // Test case 3: Invalid method
    std::string request3 =
        "PUT /resource HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "\r\n";

    std::cout << "Testing GET request:" << std::endl;
    std::cout << "===================" << std::endl;
    HttpParser parser1(8000);
    parser1.parseRequest(request1);
    printParserResults(parser1);

    std::cout << "\nTesting POST request:" << std::endl;
    std::cout << "====================" << std::endl;
    HttpParser parser2(8000);
    parser2.parseRequest(request2);
    printParserResults(parser2);

    std::cout << "\nTesting invalid method:" << std::endl;
    std::cout << "======================" << std::endl;
    HttpParser parser3(8000);
    parser3.parseRequest(request3);
    printParserResults(parser3);
    // Test case 4: Chunked body request
    std::string request4 =
        "POST /upload HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
        "4\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "3\r\n"
        " in\r\n"
        "8\r\n"
        " chunks.\r\n"
        "0\r\n"
        "\r\n";

    std::cout << "\nTesting chunked body:" << std::endl;
    std::cout << "====================" << std::endl;
    HttpParser parser4(8000);
    parser4.parseRequest(request4);
    printParserResults(parser4);
    return 0;
}
