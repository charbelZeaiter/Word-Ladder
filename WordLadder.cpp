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
#include <cstdlib>
#include <algorithm>
#include <locale> 

/*
 * Takes in a word and its history of other 
 * words it came from. Returns a vector of 
 * new strings/words that are one letter apart.
 */
vector<string> findNextWords(Lexicon& aLexicon, const string& aWord, Lexicon& aTotalHistory) {

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

				// Check that the result is a word which has not been traversed.
				if(aLexicon.containsWord(temp) && !aTotalHistory.containsWord(temp))
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
	Lexicon totalHistory;

	// Start BFS algorithm.
	while(!myQueue.empty())
	{	
		// Dequeue first pair.
		pair<string, vector<string>> myPair = myQueue.front();
		myQueue.pop();

		// Update history.
		totalHistory.add(myPair.first);

		// All Longer ladders are not considered if a shorter solution is found.
		if(myResult.size() > 0 && (myResult[0].size()-1) < myPair.second.size() )  
		{
			break;
		}

		// Check case.
		if(myPair.first == aDestWord)
		{
			// Dest word, put itself on end of its own history.
			myPair.second.push_back(myPair.first);

			// Push ladder onto result vector.
			myResult.push_back(myPair.second);
		}
		else
		{ 
			// Get list of next words.
			vector<string> nextWords(findNextWords(aLexicon, myPair.first, totalHistory));

			// For each word we prep it and enqueue it.
			for(auto currentWord : nextWords)
			{
				// Store new word.
				string newWord(currentWord);

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
 * the gathered results in the correct manner. 
*/
void outputResult(const vector<vector<string>>& aResultSet)
{
	// Check if results exist.
	if(aResultSet.size() > 0)
	{	
		// Create result vector of string ladders.
		vector<string> myLadders;

		// Exists.
		cout << "Found ladder: "; 

		for(auto wordSet : aResultSet)
		{	
			// Create ladder varibale.
			string newLadder;

			for(auto word : wordSet)
			{
				newLadder.append(word+" "); 
			}

			// Remove last space.
			newLadder.erase(newLadder.length()-1);

			// Add string to vector of string ladders
			myLadders.push_back(newLadder);
		}

		// Sort entries.
		sort(myLadders.begin(), myLadders.end());

		// Print to stdout.
		for (string entry : myLadders)
		{
			cout << entry << endl;
		}
	}
	else
	{
		// Results not found.
		cout << "No ladder found." << endl;
	}
}

/*
 * Performs a quick check of obvious rules
 * for translation before a BFS is done.
*/
bool quickCheck(Lexicon& aLexicon, const string aStartWord, const string aDestWord)
{	
	bool result = false;

	// Check both word are of sae length.
	if(aStartWord.length() == aDestWord.length())
	{	
		// Check start word exists in lex
		if(aLexicon.containsWord(aStartWord))
		{	
			// Check dest word exists in lex
			if(aLexicon.containsWord(aDestWord))
			{	
				// Initial checks passed. 
				result = true;
			}
		}
	}

	return result;
}

/*
 * Converts input string to lowercase.
*/
string toLowercase(const string aString)
{
	string result(aString);
	locale loc;
	for (size_t i=0; i<result.length(); ++i)
	{
    	result[i] = tolower(result[i],loc);
	}

	return result;
}

int main() {

	// Bootstrap the program //

	// Display prompts, also read-in start and destination words.
	cout << "Enter start word (RETURN to quit): ";

	string startWord, destWord;
	cin >> startWord;
	
	cout << "Enter destination word: ";

	cin >> destWord;
	
	// Convert to lower case.
	startWord = toLowercase(startWord);
	destWord = toLowercase(destWord);

	// Initialize lexicon.
	Lexicon myLexicon("EnglishWords.dat");

	// Declare result set.
	vector<vector<string>> myResultSet;

	// Quick check for obvious non translations.
	if(quickCheck(myLexicon, startWord, destWord))
	{
		// Create start queue object.
		vector<string> nodeHistory;
		pair<string, vector<string>> startQueuePair(startWord, nodeHistory);

		// Perform Breadth first Search.
		myResultSet = breadthFirstSearch(startQueuePair, myLexicon, destWord);
	}

	// Output the results.
	outputResult(myResultSet);

	return EXIT_SUCCESS;
}
