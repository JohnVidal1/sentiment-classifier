#ifndef SENTIMENT_CLASSIFIER_H
#define SENTIMENT_CLASSIFIER_H

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "DSString.h"

class SentimentClassifier {
private:
    std::map<DSString, int> listOfWords; // Maps each word to its sentiment score.
    std::map<DSString, int> guesses; // Stores the sentiment predictions for each tweet.
    std::vector<DSString> wrongClassification; // List of incorrectly classified tweets for analysis.
    int amountCorrect; // Number of correct predictions.
    int amountIncorrect; // Number of incorrect predictions.

public:
    // Constructor initializes the classifier.
    SentimentClassifier(); 

    // Trains the classifier with data from a specified file.
    void Train(const char* trainingFile); 

    // Processes a single tweet to update word sentiment scores.
    void TrainOneTweet(DSString tweet, bool sentiment); 

    // Tests the classifier with data from a specified file and records the results.
    void Test(const char* testingFile, const char* resultsFile); 

    // Analyzes a single tweet and returns a sentiment prediction.
    int TestOneTweet(DSString tweet); 

    // Compares the classifier's predictions against actual sentiments and logs detailed results.
    void Compare(const char* testingAnswersFile, const char* answersFile, const char* resultsFile);

    // Provides access to the list of words and their associated sentiment scores.
    const std::map<DSString, int>& getListOfWords() const { 
        return listOfWords; 
    } 
};

#endif // SENTIMENT_CLASSIFIER_H
