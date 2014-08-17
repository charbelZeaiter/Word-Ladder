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
 * Takes in a word and its history of other 
 * words it came from. Returns a vector of 
 * new strings/words that are one letter apart.
 */
vector<string> findNextWords(Lexicon& aLexicon, const string& aWord, const vector<string>& aHistory) {

	// Set constants.
	const int ASCII_A = 97;
	const int ASCII_Z = 122;

	// Create result list to be returned.
	vector<string> wordList;

	// For each letter position in the word.
	for(size_t i=0;i<aWord.length();i++)
	{
		// Cycle through another letter
		for(int j=ASCII_A;j<=ASCII_Z;j++)
		{
			// Check old letter is not same as new letter.
			if(aWord[i] != j)
			{
				string temp(aWord);
				temp[i] = (char) j;

				// Check that word has not been traversed before.
				int found = 0;
				for(auto start = aHistory.begin();start != aHistory.end();start++)
				{
					if( (*start) == temp)
					{	
						// Word has been traversed before.
						found = 1;
						break;
					}
				}

				// Check that the result is a word which has not been traversed.
				if(aLexicon.containsWord(temp) && !found)
				{
					// Add to connected word/node list.
					wordList.push_back(temp);
				}
			}
		}
	}

	return wordList;
}

/*
 * Takes in a starting pair (i.e. node), a lexicon  
 * and a destination word. Conducts a BFS to find the
 * word ladder.
 */
string breadthFirstSearch(const pair<string, vector<string>>& aStartPair, 
						  Lexicon& aLexicon, const string& aDestWord) {

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

	// Create start queue object.
	vector<string> history;
	pair<string, vector<string>> startQueuePair(startWord, history);

	// Initialize lexicon.
	Lexicon myLexicon("EnglishWords.dat");

	// Perform Breadth first Search.
	string result = breadthFirstSearch(startQueuePair, myLexicon, destWord);

	vector<string> a;
	a.push_back("eat");

	vector<string> l(findNextWords(myLexicon, "cat", a));

	for(auto start = l.begin();start != l.end();start++)
	{
		cout << (*start) << endl;
	}	


	return 0;
}
