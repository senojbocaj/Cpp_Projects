# include <string>
# include "Node.h"

using std::string;

Node::Node() : data(), next(nullptr) {} // Default Constructor

Node::Node(string id, int year, int month, double temperature) : data(id, year, month, temperature), next(nullptr) {} // Copy Constructor

bool Node::operator<(const Node& b) { // < Operator
	return this->data < b.data;
}
