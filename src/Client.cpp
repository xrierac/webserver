#include "Client.hpp"

// Default constructor
Client::Client() {}

// Copy constructor
Client::Client(const Client& other) {

}

// Default destructor
Client::~Client() {}

// Assignment operator
Client& Client::operator=(const Client& other) {
	if (this != &other) {
		// Copy members here
	}
	return *this;
}
