/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [Charbel John Zeaiter]
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>

/*
 * Takes in a word and returns a vector of strings/words 
 * that are one letter apart.
 */
vector<string> findNextWords(const string& aWord) {

	vector<string> temp;

	return temp;
}

/*
 * Takes in a starting pair (i.e. node), a lexicon  
 * and a destination word. Conducts a BFS to find the
 * word ladder.
 */
string breadthFirstSearch(const pair<string, vector<string>>& aStartPair, 
						  const Lexicon& aLexicon, const string& aDestWord) {

	return "";
}

int main() {

	// Bootstrap the program //

	// Display prompts, also read-in start and destination words.
	cout << "Enter start word (RETURN to quit): ";

	string startWord, destWord;
	cin >> startWord;

	cout << "Enter destination word: ";

	cin >> destWord;
cout << "You read in: (" << startWord << ")(" << destWord << ")" << endl;
	// Create start queue object.
	vector<string> history;
	pair<string, vector<string>> startQueuePair(startWord, history);

	// Initialize lexicon.
	Lexicon myLexicon("EnglishWords.dat");

	// Perform Breadth first Search.
	string result = breadthFirstSearch(startQueuePair, myLexicon, destWord);


	

	return 0;
}
