# ifndef LINKEDLIST
# define LINKEDLIST

# include <iostream>
# include <string>
# include "Node.h"

class LinkedList {
	private:
		Node* head;
		Node* tail;

	public:
		LinkedList(); // Default Constructor
		~LinkedList(); // Destructor
		LinkedList(const LinkedList& other); // Copy Constructor
		LinkedList& operator=(const LinkedList& other); // Copy Assignment
		void insert(std::string location, int year, int month, double temperature); // Insert a record to the linked list
		void clear(); // Clear the content of this linked list
		std::string print() const; // Print Function
		Node* getHead() const; // Clear Function
};

std::ostream& operator<<(std::ostream& os, const LinkedList& ll); // << Operator

# endif
