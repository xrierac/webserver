#include "Server.hpp"

// Default constructor
Server::Server() {}

// Copy constructor
Server::Server(const Server& other) {
	*this = other;
}

// Default destructor
Server::~Server() {}

// Assignment operator
Server& Server::operator=(const Server& other) {
	if (this != &other) {
		// Copy members here
	}
	return *this;
}
