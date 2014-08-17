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
#include <map>

/*
 * Takes in a word and its history of other 
 * words it came from. Returns a vector of 
 * new strings/words that are one letter apart.
 */
vector<string> findNextWords(Lexicon& aLexicon, const string& aWord, const map<string, int>& aTotalHistory) {

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
				auto iterator = aTotalHistory.find(temp);

				// Check that the result is a word which has not been traversed.
				if(aLexicon.containsWord(temp) && iterator == aTotalHistory.end())
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
vector<vector<string>> breadthFirstSearch(const pair<string, vector<string>>& aStartPair, 
						  Lexicon& aLexicon, const string& aDestWord) 
{
	// Create result variable.
	vector<vector<string>> myResult;

	// Create queue.
	queue<pair<string, vector<string>>> myQueue;

	// Enqueue starting pair/node.
	myQueue.push(aStartPair);

	// Set up a vector of previously visited words.
	map<string, int> totalHistory;

	// Start BFS algorithm.
	while(!myQueue.empty())
	{	
		// Dequeue first pair.
		pair<string, vector<string>> myPair = myQueue.front();
		myQueue.pop();

		// Update history.
		totalHistory[myPair.first] = 1;

		// Check if destination word is found.
		if(myPair.first == aDestWord)
		{
			// Dest word, put itself on end of its own history.
			myPair.second.push_back(myPair.first);

			// Check if results exist.
			if(myResult.size() > 0)
			{
				// Check that this result is also optimal.
				if(myPair.second.size() == myResult[0].size())
				{
					// Push ladder onto result vector.
					myResult.push_back(myPair.second);
				}
				else
				{
					// No more optimal solutions
					break;
				}
			}
			else
			{
				// Push ladder onto result vector.
				myResult.push_back(myPair.second);
			}
		}
		else
		{
			// Get list of next words.
			vector<string> nextWords(findNextWords(aLexicon, myPair.first, totalHistory));

			// For each word we prep it and enqueue it.
			for(auto currentWord = nextWords.begin(); currentWord != nextWords.end();currentWord++)
			{
				// Store new word.
				string newWord( (*currentWord) );

				// Store new word's history using previous word's history.
				vector<string> nodeHistory(myPair.second);
				nodeHistory.push_back(myPair.first);

				// Create queue object and enqueue it.
				pair<string, vector<string>> newPair(newWord, nodeHistory);
				myQueue.push(newPair);
			}
		}
	}

	return myResult;
}

/*
 * A Helper function to output
 * the gathered results. 
*/
void outputResult(const vector<vector<string>>& aResultSet)
{
	// Check if results exist.
	if(aResultSet.size() > 0)
	{
		// Exists.
		cout << "Found ladder: "; 

		// Traverse each word ladder.
		for(auto entry = aResultSet.rbegin(); entry != aResultSet.rend(); entry++)
		{	
			// Traverse each word in word ladder.
			for(auto word = (*entry).begin(); word != (*entry).end(); word++)
			{
				if(word == ((*entry).end()-1) )
				{
					cout << (*word); 
				} 
				else
				{
					cout << (*word) << " "; 
				}
			}

			cout << endl;
		}
	}
	else
	{
		// Results not found.
		cout << "No ladder found.";
	}
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
	vector<string> nodeHistory;
	pair<string, vector<string>> startQueuePair(startWord, nodeHistory);

	// Initialize lexicon.
	Lexicon myLexicon("EnglishWords.dat");

	// Perform Breadth first Search.
	vector<vector<string>> myResultSet = breadthFirstSearch(startQueuePair, myLexicon, destWord);

	// Output the results.
	outputResult(myResultSet);

	return 0;
}
