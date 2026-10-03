#include <iostream>
#include <fstream>
#include "SentimentClassifier.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Define the file paths for the training and testing datasets, and the output files.
    const char* trainingFile = "data\\train_dataset_20k.csv";
    const char* testingFile = "data\\test_dataset_10k.csv";
    const char* testingAnswersFile = "data\\test_dataset_sentiment_10k.csv";
    const char* resultsFile = "results.csv";
    const char* accuracyFile = "accuracy.txt";

    try {
        // Create an instance of SentimentClassifier to process the sentiment data.
        SentimentClassifier classifier;

        // Begin training the classifier with the data from the training file.
        cout << "Training the classifier...\n";
        classifier.Train(trainingFile);
        cout << "Training complete.\n";

        // Display the internal state of word sentiment mapping after training.
        const auto& listOfWords = classifier.getListOfWords();
        cout << "listOfWords map contents:\n";
        for (const auto& pair : listOfWords) {
            cout << pair.first.c_str() << ": " << pair.second << endl;
        }

        // Test the classifier using the testing dataset and store the results in a file.
        cout << "Testing the classifier...\n";
        classifier.Test(testingFile, resultsFile);
        cout << "Testing complete.\n";

        // Compare the classifier's predictions with the actual sentiments and evaluate accuracy.
        cout << "Comparing results...\n";
        classifier.Compare(testingAnswersFile, accuracyFile, resultsFile);
        cout << "Comparison complete.\n";

    } catch (const exception& e) {
        // Catch and display any exceptions that might occur during the process.
        cerr << "Error: " << e.what() << endl;
        return 1; // Return an error code if any exceptions are caught.
    }

    // If everything went smoothly, print a success message.
    cout << "Sentiment analysis finished successfully!\n";
    return 0; // Return success code indicating no errors.
}
