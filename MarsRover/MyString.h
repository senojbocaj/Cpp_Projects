#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

using std::cout, std::cin, std::endl, std::ostream, std::istream;

class MyString {
    private:
        // Variables used within the MyString Class
        char* privData; // Data Array
        size_t privLength; // Length Var
        size_t privCapacity; // Capacity Var
        unsigned int privSize; // Size Var

    public:
        // Constructors
        MyString(); // Default
        MyString(const MyString& str); // Copy
        MyString(const char* s); // From C-String

        // Destructor
        ~MyString();

        // Functions
        void resize(size_t n); // Resize
        size_t capacity() const noexcept; // Capacity
        unsigned int size() const noexcept; // Size
        size_t length() const noexcept; // Length
        const char* data() const noexcept; // Data
        bool empty() const noexcept; // Empty
        const char& front() const; // Front
        const char& at (size_t pos) const; // At 
        void clear() noexcept; // Clear
        size_t find (const MyString& str, size_t pos = 0) const noexcept; // Find

        // Operators
        friend ostream& operator<<(ostream& os, const MyString& str); // Operator<<
        friend istream& operator>>(istream& is, MyString& str); // Operator>> (Given)
        MyString& operator=(const MyString& other); // Operator= 
        MyString& operator+= (const MyString& str); // Operator+=
        int stoi(const MyString& str); // Stoi (Given)

        bool operator==(const MyString& other) const; // Operator== (Bonus)
        MyString operator+(const MyString& other) const; // Operator+ (Bonus)
};

#endif