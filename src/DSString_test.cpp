#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert> // For assert statements
#include "DSString.h"

/* This file tests your DSString class. 
    It includes more tests and checks if the results are correct. */

int main() {
    // Test the default constructor by creating an empty string.
    DSString emptyString;
    assert(emptyString.length() == 0); // Ensure the length is zero for an empty string.
    assert(emptyString.c_str() != nullptr); // Ensure the internal C-string is not a null pointer.

    // Test the constructor that takes a C-style string.
    DSString helloString("Hello, World!");
    assert(helloString.length() == 13); // The length should be 13 characters.
    assert(helloString == "Hello, World!"); // The string content should match exactly.

    // Test the copy constructor to ensure it duplicates the string correctly.
    DSString copyString(helloString);
    assert(copyString == helloString); // Both strings should be equal.
    assert(copyString.length() == helloString.length()); // Lengths must also match.

    // Test the assignment operator for copying content between DSStrings.
    DSString anotherString;
    anotherString = copyString;
    assert(anotherString == copyString); // The target string should now be equal to the source string.

    // Test accessing characters by index.
    assert(helloString[0] == 'H'); // The first character should be 'H'.
    assert(helloString[7] == 'W'); // The eighth character should be 'W'.

    // Test out-of-bounds indexing, which should throw an exception.
    try {
        char c = helloString[100]; // This should throw an out_of_range exception because it is beyond the string's length.
        assert(false); // If no exception is thrown, fail the test.
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl; // Report the caught exception.
    }

    // Test the concatenation of two strings.
    DSString combinedString = helloString + " " + anotherString;
    assert(combinedString == "Hello, World! Hello, World!"); // The result should be a properly concatenated string.

    // Test comparison operators by comparing two strings.
    DSString str1("apple");
    DSString str2("banana");
    assert(str1 < str2);  // "apple" should be lexicographically less than "banana".
    assert(str2 > str1);  // Conversely, "banana" should be greater than "apple".
    assert(str1 == "apple"); // str1 should exactly match "apple".
    assert(str1 != str2);  // str1 and str2 are not the same string.

    // Test the substring extraction.
    DSString subString = helloString.substring(7, 5);
    assert(subString == "World"); // The substring should exactly match "World".

    // Test substring method with out-of-bounds indices which should adjust automatically.
    DSString subString2 = helloString.substring(10, 5); // Asking for "orld!" starting from position 10.
    assert(subString2 == "orld!"); // Should adjust the length automatically to fit the string bounds.

    // Test converting a string to lowercase.
    DSString upperString("UPPERCASE");
    DSString lowerString = upperString.toLower();
    assert(lowerString == "uppercase"); // The entire string should be converted to lowercase.

    // Test the tokenizer by breaking a string into words, ignoring punctuation and spaces.
    DSString testString("This is, a test! string.");
    std::vector<DSString> tokens = testString.tokenizer();
    std::vector<DSString> expectedTokens = {"This", "is", "a", "test", "string"};

    // Check if the number of tokens and their content matches the expected results.
    assert(tokens.size() == expectedTokens.size());
    for (size_t i = 0; i < tokens.size(); ++i) {
        assert(tokens[i] == expectedTokens[i]);
    }

    // Confirm all tests passed successfully.
    std::cout << "All tests passed!" << std::endl;
    return 0;
} // Main function ends here, having successfully tested various functionalities of the DSString class.
