# include <iostream>
# include <string>
# include "LinkedList.h"
# include "Node.h"
# include <sstream>

using std::string, std::ostream;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {} // Default Constructor

LinkedList::~LinkedList() {clear();} // Destructor

LinkedList::LinkedList(const LinkedList& source) : head(source.head), tail(source.tail) { // Copy Constructor
    Node* current = source.head;

    while (current != nullptr) {
        Node* newNode = new Node(current->data.id, current->data.year, current->data.month, current->data.temperature);

        if (head == nullptr) { 
            head = newNode;
            tail = newNode;
        } else { 
            tail->next = newNode;
            tail = newNode;
        }
        current = current->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& source) { // = Operator
    if (this != &source) {
        clear();

        head = nullptr;
        tail = nullptr;

        Node* current = source.head;

        while (current != nullptr) {
            insert(current->data.id, current->data.year, current->data.month, current->data.temperature);
            current = current->next;    
        }
    }
    return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) { // Insert Function

    Node* newNode = new Node(location, year, month, temperature);

    if (head == nullptr && tail == nullptr) { // Checks for empty linked list
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }

    if (newNode->data < head->data) { // Checks if new node should go at the head
        newNode->next = head;
        head = newNode;
    } else if (tail->data < newNode->data) { // Checks if new node should go at the tail
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
    } else { // Checks if new node should go in the middle of the llist
        Node* current = head;

        while (current != nullptr) {
            if (current->next != nullptr && (newNode->data < (current->next->data)) && (current->data < newNode->data)) {
                newNode->next = current->next;
                current->next = newNode;
                break;
            }
            current = current->next;
        }
    }
}

void LinkedList::clear() { // Clear Function
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

Node* LinkedList::getHead() const {return head;} // GetHead Function

string LinkedList::print() const {
    // Variables
    string outputString;
    std::stringstream outputStringStream;

    // Pointer to traverse the list
    Node* current = head;

    while (current != nullptr) {
        outputStringStream << current->data.id << " " << current->data.year << " " << current->data.month << " " << current->data.temperature << "\n";
        current = current->next;
    }

    outputString = outputStringStream.str();
    return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) { // << Function
	os << ll.print();
	return os;
}
