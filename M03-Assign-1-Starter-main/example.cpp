#include <iostream>
#include "HTTPRequest.hpp"
// this code comes from https://github.com/elnormous/HTTPRequest
// You can copy this to the main.cpp to test the http request code.

int main()
{
    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{"http://test.com/test"};

        // send a get request
        const auto response = request.send("GET");
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception &e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    return 0;
}