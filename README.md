# Tweet Sentiment Classifier (C++)

A word-score sentiment classifier for tweets, built on a custom string class (`DSString`) instead of `std::string`.

## How it works
- **Training:** Reads 20,000 labeled tweets. Each tweet is lowercased and split into words on whitespace and punctuation. Every word gets +1 for each positive tweet it appears in and −1 for each negative tweet.
- **Prediction:** Adds up the scores of the words in a tweet. A total above 0 means positive (4); otherwise the tweet is negative (0).
- **Evaluation:** Compares predictions against the answer key and reports accuracy.

**Accuracy:** 61.3% on the 10,000-tweet test set.

## Project layout
```
src/DSString.*             custom dynamic string class (rule of three, tokenizer, comparisons)
src/SentimentClassifier.*  training, testing, and evaluation
src/main.cpp               runs train -> test -> compare
src/DSString_test.cpp      assert-based tests for DSString
data/                      training set, test set, and answer key (CSV)
```

## Build and run
```
mkdir build && cd build
cmake ..
cmake --build .
./sentiment
```
Writes `accuracy.txt` and `results.csv` (the misclassified tweets).
