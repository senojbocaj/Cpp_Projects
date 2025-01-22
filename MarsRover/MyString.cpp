#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>
#include <stdexcept>

#include "MyString.h"

using std::cout, std::cin, std::endl, std::ifstream, std::ofstream, std::istream, std::ostream, std::copy;

// Constructors
MyString::MyString() : privData(new char[1]), privLength(0), privCapacity(1), privSize(0) {} // Default

MyString::MyString(const MyString& other) : privData(other.privData), privLength(other.privLength), privCapacity(other.privCapacity), privSize(other.privSize) { // Copy
    privData = new char[privCapacity];
    for (size_t i = 0; i <= privSize; i++) {
        privData[i] = other.privData[i];
    }
}

MyString::MyString(const char* str) : privData(nullptr), privLength(0), privCapacity(1), privSize(0) { // From C-String
    if (str != nullptr) {
        privLength = std::char_traits<char>::length(str);
        privCapacity = privLength + 1;
        privData = new char[privCapacity];
        for (size_t i = 0; i <= privSize; i++) {
            privData[i] = str[i];
        }
        privData[privLength] = '\0';
        privSize = privLength;

    }
}

// Destructor
MyString::~MyString() {
    clear();
}

// Functions

void MyString::resize(size_t n) {
    if (n < privCapacity) {
        privSize = n;
        privData[privLength] = '\0';
    } else {
        privCapacity = n;
    }
} 

size_t MyString::capacity() const noexcept {return privCapacity;} // Capacity

unsigned int MyString::size() const noexcept {return privSize;} // Size

size_t MyString::length() const noexcept {return privLength;} // Length

const char* MyString::data() const noexcept {return privData;} // Data ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MyString::empty() const noexcept{return bool (privSize == 0);} // Empty

const char& MyString::front() const {return privData[0];} // Front

const char& MyString::at(size_t pos) const { // At ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (pos >= privLength) {
        throw std::out_of_range("Out of range.");
    }
    return privData[pos];
}

void MyString::clear() noexcept { // Clear ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    delete[] privData;  
    privData = 0; 
    privLength = 0;     
    privCapacity = 0;   
    privSize = 0;       
}

size_t MyString::find(const MyString& str, size_t pos) const noexcept { // Find //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
return 7;
}



// Operators 

ostream& operator<<(ostream& os, MyString& str) {str=str; return os;} // Operator<<

MyString& MyString::operator=(const MyString& other) {privLength -= other.privLength; privLength += other.privLength; return *this;} // Operator=

MyString& MyString::operator+= (const MyString& str) { // Operator += ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    size_t comboLength = privLength + str.privLength;
    size_t comboCap = comboLength + 1;

    char* newFreezer = new char[comboCap];

    std::copy(privData, privData + privLength, newFreezer);

    std::copy(str.privData, str.privData + str.privLength + 1, newFreezer + privLength);

    delete[] privData;

    privData = newFreezer;
    privLength = comboLength;
    privCapacity = comboCap;

    return *this;
}

bool MyString::operator==(const MyString& other) const { // Operator ==
    if (privLength != other.privLength) { // Compares lengths
        return false;
    }

    for (size_t i = 0; i < privLength; ++i) { // Compares each element of data from one string to another, if they don't match, return false
        if (privData[i] != other.privData[i]) {
            return false;
        }
    }

    return true; // All tests passed, return true
}

MyString MyString::operator+(const MyString& other) const { // Operator + /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    MyString newPlug;
    newPlug.privLength = privLength + other.privLength;
    newPlug.privCapacity = newPlug.privLength + 1;
    newPlug.privData = new char[newPlug.privCapacity];
    
    std::copy(privData, privData + privLength, newPlug.privData);

    std::copy(other.privData, other.privData + other.privLength + 1, newPlug.privData + privLength);

    return newPlug;
}