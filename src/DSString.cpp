#include "DSString.h"  // Include the header file that defines the DSString class
#include <iostream>   // Include for input/output operations (like printing to the console)
#include <algorithm>  // Include for std::copy (used for efficient copying)
#include <cctype>     // Include for character classification functions (like std::isspace and std::ispunct)

// Constructor implementations

// Default constructor: Creates an empty string
DSString::DSString() : data(nullptr), len(0) {
    data = new char[1]; 
    data[0] = '\0'; // Null-terminate the empty string (mark the end of the string)
}

// Constructor that takes a C-style string (char array) as input
DSString::DSString(const char *str) : len(0) {
    if (str != nullptr) {  // If the input string is not empty
        const char *ptr = str;
        while (*ptr++) {   // Calculate the length of the input string
            len++;
        }
        data = new char[len + 1]; // Allocate memory for the string (including space for the null terminator)
        for (size_t i = 0; i < len; ++i) {
            data[i] = str[i];  // Copy the characters from the input string to the data array
        }
    } else {
        data = new char[1]; 
        data[0] = '\0'; // Null-terminate the empty string
    }
    data[len] = '\0'; // Ensure null-termination (mark the end of the string)
}

// Copy constructor: Creates a new DSString object that is a copy of another DSString object
DSString::DSString(const DSString &other) : len(other.len) {
    data = new char[len + 1]; // Allocate memory for the new string
    std::copy(other.data, other.data + len + 1, data); // Efficiently copy the contents of the other string
}

// Copy assignment operator: Assigns the contents of one DSString object to another
DSString& DSString::operator=(const DSString &other) {
    if (this != &other) {  // Make sure we're not assigning to ourselves
        delete[] data;     // Deallocate the existing string data
        len = other.len;    // Update the length
        data = new char[len + 1]; // Allocate memory for the new string
        std::copy(other.data, other.data + len + 1, data); // Copy the contents
    }
    return *this;  // Return the updated object
}

// Destructor: Cleans up the memory used by the DSString object
DSString::~DSString() {
    delete[] data;  // Deallocate the memory used for the string data
}

// Returns the length of the string
size_t DSString::length() const {
    return len;
}

// Allows accessing individual characters of the string using [] (e.g., str[0] to get the first character)
char &DSString::operator[](size_t index) {
    if (index >= len) {   // Check if the index is valid
        throw std::out_of_range("Index out of bounds"); // Throw an exception if the index is out of bounds
    }
    return data[index];  // Return the character at the given index
}

// Concatenates two DSString objects (joins them together)
DSString DSString::operator+(const DSString &other) const {
    DSString result;
    result.len = len + other.len;  // Calculate the length of the combined string
    result.data = new char[result.len + 1]; // Allocate memory for the new string

    for (size_t i = 0; i < len; ++i) {
        result.data[i] = data[i];   // Copy the first string
    }
    for (size_t i = 0; i < other.len; ++i) {
        result.data[len + i] = other.data[i]; // Copy the second string
    }
    result.data[result.len] = '\0'; // Null-terminate the new string
    return result;
}

// Checks if two DSString objects are equal
bool DSString::operator==(const DSString &other) const {
    if (len != other.len) {   // If the lengths are different, they can't be equal
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        if (data[i] != other.data[i]) { // If any characters are different, they're not equal
            return false;
        }
    }
    return true;  // If all characters are the same, they're equal
}

// Checks if one DSString object is less than another (for alphabetical sorting)
bool DSString::operator<(const DSString &other) const {
    size_t minLen = std::min(len, other.len); // Find the length of the shorter string
    for (size_t i = 0; i < minLen; ++i) {
        if (data[i] != other.data[i]) {  // If any characters are different
            return data[i] < other.data[i]; // Compare the characters to determine which is "less"
        }
    }
    return len < other.len; // If all characters are the same, the shorter string is "less"
}

// Checks if one DSString object is greater than another
bool DSString::operator>(const DSString &other) const {
    return other < *this;  // Use the "less than" operator to determine "greater than"
}

// Checks if two DSString objects are not equal
bool DSString::operator!=(const DSString &other) const {
    return !(*this == other); // Use the "equals" operator to determine "not equals"
}

// Extracts a portion of the string (a substring)
DSString DSString::substring(size_t start, size_t numChars) const {
    if (start >= len) {  // Check if the starting index is valid
        throw std::out_of_range("Substring start index out of bounds");
    }
    if (start + numChars > len) { // Adjust the number of characters if it goes beyond the string length
        numChars = len - start;
    }

    DSString result;
    result.len = numChars;  // Set the length of the substring
    result.data = new char[numChars + 1]; // Allocate memory for the substring

    for (size_t i = 0; i < numChars; ++i) {
        result.data[i] = data[start + i]; // Copy the characters from the original string
    }
    result.data[numChars] = '\0'; // Null-terminate the substring
    return result;
}

// Converts the string to lowercase
DSString DSString::toLower() const {
    DSString result(*this);  // Create a copy of the current string
    for (size_t i = 0; i < len; ++i) {
        result.data[i] = std::tolower(result.data[i]); // Convert each character to lowercase
    }
    return result;
}

// Returns a pointer to the underlying C-style string (char array)
const char *DSString::c_str() const {
    return data;
}

// Allows printing DSString objects using std::cout
std::ostream &operator<<(std::ostream &out, const DSString &str) {
    out << str.data;
    return out;
}

// Splits the string into words (tokens) based on spaces and punctuation
std::vector<DSString> DSString::tokenizer() {
    std::vector<DSString> tokens;  // Create a vector to store the tokens
    size_t start = 0;   // Keep track of the starting position of each token

    for (size_t i = 0; i < len; ++i) {
        if (std::isspace(data[i]) || std::ispunct(data[i])) { // If we encounter a space or punctuation
            if (start != i) {   // If there's a word before the space/punctuation
                tokens.push_back(substring(start, i - start)); // Add the word to the vector
            }
            start = i + 1;  // Move the starting position to the next character
        }
    }

    if (start < len) {  // If there's a word at the end of the string
        tokens.push_back(substring(start, len - start));  // Add the last word to the vector
    }

    return tokens;
}