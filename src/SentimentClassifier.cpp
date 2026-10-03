#include "SentimentClassifier.h"  // Include the header file for the SentimentClassifier class
#include <fstream>              // Include for file input/output operations
#include <iostream>             // Include for standard input/output operations (like printing to the console)
#include <map>                 // Include for using the map data structure (like a dictionary)
#include <sstream>             // Include for using stringstreams (for easy string manipulation)
#include <vector>              // Include for using the vector data structure (like a dynamic array)
#include <iomanip>             // Include for manipulating output formatting (like setting precision)
#include "DSString.h"          // Include the header file for your custom string class

using namespace std; // Use the standard namespace (so you don't have to write std::cout, std::endl, etc.)

// Constructor for the SentimentClassifier class (doesn't do anything special here)
SentimentClassifier::SentimentClassifier() {} 

// Function to train the sentiment classifier using a training dataset
void SentimentClassifier::Train(const char* trainingFile) {
    ifstream trainingStream(trainingFile); // Open the training dataset file

    if (!trainingStream.is_open()) {  // Check if the file was opened successfully
        cerr << "Error: Unable to open " << trainingFile << endl; // Print an error message to the console
        return; // Exit the function if the file couldn't be opened
    }

    string line; 
    getline(trainingStream, line); // Read the first line (header) and discard it

    while (getline(trainingStream, line)) { // Read the file line by line
        stringstream ss(line);  // Create a stringstream to easily process the line
        string temp;

        // Extract sentiment (whether the tweet is positive or negative)
        getline(ss, temp, ',');  // Read the first value (sentiment) from the line
        bool sentiment = (temp == "4"); // Convert the sentiment to a boolean (true for positive, false for negative)

        // Skip columns (ignore other data in the line that we don't need)
        for (int i = 0; i < 4; i++) {
            getline(ss, temp, ','); 
        }

        // Extract tweet (the actual text of the tweet)
        getline(ss, temp); 
        DSString tweet(temp.c_str()); // Convert the tweet to a DSString object

        TrainOneTweet(tweet, sentiment); // Process the tweet and its sentiment to train the classifier
    }

    trainingStream.close(); // Close the training dataset file
}

// Function to process a single tweet and update the sentiment scores of words
void SentimentClassifier::TrainOneTweet(DSString tweet, bool sentiment) {
    DSString lowerTweet = tweet.toLower();  // Convert the tweet to lowercase
    vector<DSString> tokens = lowerTweet.tokenizer(); // Split the tweet into individual words (tokens)

    for (const auto& token : tokens) {  // Loop through each word in the tweet
        listOfWords[token] += sentiment ? 1 : -1;  // Update the sentiment score of the word in the listOfWords map
                                                   // If the sentiment is positive, add 1 to the score; otherwise, subtract 1
    }
}

// Function to test the sentiment classifier on a testing dataset
void SentimentClassifier::Test(const char* testingFile, const char* resultsFile) {
    ifstream testStream(testingFile);  // Open the testing dataset file
    ofstream resultsStream(resultsFile); // Open the results file (in overwrite mode)

    if (!testStream.is_open() || !resultsStream.is_open()) { // Check if the files were opened successfully
        cerr << "Error: Unable to open files" << endl;  // Print an error message if there was a problem
        return; // Exit the function if the files couldn't be opened
    }

    string line;
    getline(testStream, line); // Read and discard the header line

    while (getline(testStream, line)) {  // Read the file line by line
        stringstream ss(line); // Create a stringstream to process the line
        string temp;

        // Extract tweet ID (the unique identifier for the tweet)
        getline(ss, temp, ',');   // Read the first value (tweet ID) from the line
        DSString tweetID(temp.c_str()); // Convert the tweet ID to a DSString object

        // Skip three columns (ignore other data in the line that we don't need)
        for (int i = 0; i < 3; i++) { 
            getline(ss, temp, ','); 
        }

        // Extract the tweet (the actual text of the tweet)
        getline(ss, temp); // Read the rest of the line
        DSString tweet(temp.c_str()); // Convert the tweet to a DSString object

        try {
            // Classify the tweet
            int predictedSentiment = TestOneTweet(tweet); // Predict the sentiment of the tweet
            guesses[tweetID] = predictedSentiment;  // Store the prediction in the guesses map

            // Write prediction to results file (use c_str() here)
            resultsStream << predictedSentiment << ", " << tweetID.c_str() << endl; // Write the prediction and tweet ID to the results file
        } catch (const bad_alloc& e) {  // Catch any memory allocation errors
            cerr << "Error: Memory allocation failed. " << e.what() << endl; // Print an error message if memory allocation fails
        }
    }

    testStream.close();  // Close the testing dataset file
    resultsStream.close(); // Close the results file
}

// Function to predict the sentiment of a single tweet
int SentimentClassifier::TestOneTweet(DSString tweet) {
    int sentimentScore = 0;      // Initialize a variable to keep track of the sentiment score
    DSString lowerTweet = tweet.toLower();  // Convert the tweet to lowercase
    vector<DSString> tokens = lowerTweet.tokenizer(); // Split the tweet into individual words (tokens)
    cout << "Testing tweet: " << tweet.c_str() << endl; // Print the tweet being tested (for debugging)

    for (const auto& token : tokens) {  // Loop through each word in the tweet
        auto it = listOfWords.find(token); // Try to find the word in the listOfWords map
        if (it != listOfWords.end()) {   // If the word is found in the map
            cout << "Token: " << token.c_str() << ", Score: " << it->second << endl; // Print the word and its sentiment score (for debugging)
            sentimentScore += it->second;  // Add the word's sentiment score to the total score
        } else {
            cout << "Token: " << token.c_str() << " not found." << endl; // Print a message if the word is not found (for debugging)
        }
    }

    cout << "Total score: " << sentimentScore << endl; // Print the total sentiment score (for debugging)
    return (sentimentScore > 0) ? 4 : 0;  // If the total score is positive, return 4 (positive sentiment); otherwise, return 0 (negative sentiment)
}

// Function to compare the predicted sentiments with the actual sentiments and calculate the accuracy
void SentimentClassifier::Compare(const char* testingAnswersFile, const char* answersFile, const char* resultsFile) {
    ifstream testingAnswerStream(testingAnswersFile); // Open the file with the actual sentiments
    ofstream answersStream(answersFile);  // Open the file to write the accuracy
    ofstream resultsStream(resultsFile); // Open the file to write the misclassified tweets

    if (!testingAnswerStream.is_open() || !answersStream.is_open() || !resultsStream.is_open()) { // Check if the files were opened successfully
        cerr << "Error: Unable to open files\n"; // Print an error message if there was a problem
        return; // Exit the function if the files couldn't be opened
    }

    int actualSentiment, totalPredictions = 0, correctPredictions = 0; // Initialize variables to keep track of sentiments and predictions
    string line, temp; 
    DSString tweetID;

    getline(testingAnswerStream, line);  // Discard the header line

    while (getline(testingAnswerStream, line)) { // Read the file line by line
        stringstream ss(line); // Create a stringstream to process the line

        getline(ss, temp, ',');  // Extract the actual sentiment from the first column
        actualSentiment = stoi(temp); // Convert the sentiment from a string to an integer

        getline(ss, temp, ',');  // Extract the tweet ID from the second column
        tweetID = temp.c_str();  // Convert the tweet ID to a DSString object

        int predictedSentiment = guesses[tweetID]; // Get the predicted sentiment for this tweet from the guesses map

        if (predictedSentiment == actualSentiment) { // If the prediction matches the actual sentiment
            correctPredictions++;  // Increment the count of correct predictions
        } else {  // If the prediction is incorrect
            resultsStream << "Tweet ID: " << tweetID.c_str() << ", Predicted: "  // Write the tweet ID, predicted sentiment, and actual sentiment to the results file
                          << predictedSentiment << ", Actual: " << actualSentiment << '\n';
        }
        totalPredictions++; // Increment the total number of predictions
    }

    double accuracy = (totalPredictions > 0) ? (double)correctPredictions / totalPredictions : 0.0; // Calculate the accuracy 
                                                                                                   // (avoid division by zero if there are no predictions)
    answersStream << fixed << setprecision(3) << accuracy; // Write the accuracy to the answers file with 3 decimal places

    testingAnswerStream.close(); // Close the file with the actual sentiments
    answersStream.close();  // Close the accuracy file
    resultsStream.close(); // Close the results file
}