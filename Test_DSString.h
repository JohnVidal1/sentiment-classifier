#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert> // For assert statements

#include "DSString.h"

/* This file tests your DSString class. 
   It includes more tests and checks if the results are correct. */

int main() {
    // Test default constructor
    DSString emptyString;
    assert(emptyString.length() == 0);
    assert(emptyString.c_str() != nullptr); // Check for null pointer

    // Test constructor with C-style string
    DSString helloString("Hello, World!");
    assert(helloString.length() == 13);
    assert(helloString == "Hello, World!");

    // Test copy constructor
    DSString copyString(helloString);
    assert(copyString == helloString);
    assert(copyString.length() == helloString.length());

    // Test assignment operator
    DSString anotherString;
    anotherString = copyString;
    assert(anotherString == copyString);

    // Test indexing operator
    assert(helloString[0] == 'H');
    assert(helloString[7] == 'W');

    // Test out-of-bounds indexing (should throw an exception)
    try {
        char c = helloString[100]; // This should throw an exception
        assert(false); // This line should not be reached
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Test concatenation operator
    DSString combinedString = helloString + " " + anotherString;
    assert(combinedString == "Hello, World! Hello, World!");

    // Test comparison operators
    DSString str1("apple");
    DSString str2("banana");

    // Print the strings for debugging
    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;

    assert(str1 < str2);  // Check if "apple" is less than "banana"
    assert(str2 > str1);  // Check if "banana" is greater than "apple"
    assert(str1 == "apple"); // Check if str1 is equal to "apple"
    assert(str1 != str2);  // Check if str1 is not equal to str2

    // Test substring method
    DSString subString = helloString.substring(7, 5);
    assert(subString == "World");

    // Test substring with out-of-bounds indices
    DSString subString2 = helloString.substring(10, 5); // Should adjust to "orld!"
    assert(subString2 == "orld!");

    // Test toLower method
    DSString upperString("UPPERCASE");
    DSString lowerString = upperString.toLower();
    assert(lowerString == "uppercase");

    // Test tokenizer with punctuation and spaces
    DSString testString("This is, a test! string.");
    std::vector<DSString> tokens = testString.tokenizer();

    // Print the tokens for debugging
    std::cout << "Tokens: ";
    for (const auto& token : tokens) {
        std::cout << "[" << token << "] ";
    }
    std::cout << std::endl;

    std::vector<DSString> expectedTokens = {"This", "is", "a", "test", "string"};
    assert(tokens.size() == expectedTokens.size());
    for (size_t i = 0; i < tokens.size(); ++i) {
        assert(tokens[i] == expectedTokens[i]);
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}