# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g  # Enable warnings and debugging

# Object files for the main program
MAIN_OBJS = DSString.o SentimentClassifier.o main.o

# Object files for the test program
TEST_OBJS = DSString.o DSString_test.o

# Main program target
DSString_main: $(MAIN_OBJS)
	$(CXX) -o DSString_main $(MAIN_OBJS)

# Test program target
DSString_test: $(TEST_OBJS)
	$(CXX) -o DSString_test $(TEST_OBJS)

# Compile DSString.cpp to DSString.o
DSString.o: DSString.cpp DSString.h
	$(CXX) $(CXXFLAGS) -c DSString.cpp

# Compile SentimentClassifier.cpp to SentimentClassifier.o
SentimentClassifier.o: SentimentClassifier.cpp SentimentClassifier.h
	$(CXX) $(CXXFLAGS) -c SentimentClassifier.cpp

# Compile DSString_test.cpp to DSString_test.o with RUN_DSSTRING_TEST defined
DSString_test.o: DSString_test.cpp DSString.h
	$(CXX) $(CXXFLAGS) -DRUN_DSSTRING_TEST -c DSString_test.cpp

# Compile main.cpp to main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean up object files and executables
clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) DSString_main DSString_test
