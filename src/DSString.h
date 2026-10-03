#ifndef DSSTRING_H  // Include guard to prevent multiple inclusions of this header file
#define DSSTRING_H

#include <iostream>  // Include for standard input/output operations (like printing to the console)
#include <vector>   // Include for using the vector data structure (like a dynamic array)
#include <cctype>    // Include for character classification functions (like std::isspace and std::ispunct)

// Definition of the DSString class (a custom string class)
class DSString
{
private:
    char *data;   // Pointer to the character array that stores the string data
    size_t len;  // Length of the string (number of characters)

public:
    // Constructors (ways to create DSString objects)
    DSString();                       // Default constructor (creates an empty string)
    DSString(const char *);          // Constructor that takes a C-style string (char array) as input
    DSString(const DSString &);      // Copy constructor (creates a copy of another DSString object)

    // Assignment operator (allows assigning one DSString object to another)
    DSString& operator=(const DSString &); 

    // Destructor (cleans up memory when a DSString object is destroyed)
    ~DSString(); 

    // Member functions (actions you can perform on DSString objects)

    size_t length() const;            // Returns the length of the string
    char &operator[](size_t index);   // Allows accessing individual characters of the string using [] (e.g., str[0] to get the first character)

    DSString operator+(const DSString &) const; // Concatenates two DSString objects (joins them together)

    // Comparison operators (to compare DSString objects)
    bool operator==(const DSString &) const;  // Checks if two DSString objects are equal
    bool operator<(const DSString &) const;   // Checks if one DSString object is less than another (for alphabetical sorting)
    bool operator>(const DSString &) const;   // Checks if one DSString object is greater than another
    bool operator!=(const DSString &) const;  // Checks if two DSString objects are not equal

    DSString substring(size_t start, size_t numChars) const; // Extracts a portion of the string (a substring)
    DSString toLower() const;       // Converts the string to lowercase
    const char *c_str() const;      // Returns a pointer to the underlying C-style string (char array)

    friend std::ostream &operator<<(std::ostream &, const DSString &); // Allows printing DSString objects using std::cout

    std::vector<DSString> tokenizer();  // Splits the string into words (tokens) based on spaces and punctuation
};

#endif // End of the include guard