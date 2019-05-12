//============================================================================
// Name        : CS20AProj5.cpp
// Author      : Brian Tehrani
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

/*
 * Part 1 Analysis:
 *	The problem begins with assuming the set is already implemented and thus we should focus 
 *	on the implementation of the algorithm. From Lecture 13 slide 7, the set has operations 
 *  add(), remove(), contains() which cost O(1) (although in the stl set they would be O(lgn)).
 *	First we are given a word, then we have to swap its characters until all combinations of  
 *  the altered word is known. This is knows as a permutation. The example in the pdf shows the 
 *  word cat having 6 possible word combinations (3! = 6). Thus the number of permutations depends
 *	on the length of the string. Considering the length of the string being size n, there will be 
 *	n! permutations of the words. With the given runtimes of the functions above we can acheive a 
 *	runtime of: O(n!) for permuting * O(1) for either a lookup, add, remove = O(n!). Therefore, we
 *	must find a better runtime as this algorithm would be too slow to consider implementing.
 *
 *  O(?) = O(n!)
 *
 */



/*
 *  Part 2 Implementation
 */
class WordFinder {
private:
	// experiment with this size to see how it affects efficiency
	/*	Original Table Size: 11,117
		Dictionary file has max 99,167 words
		The max hash value is 2411. Therefore the size can be adjusted to 2412.
		The word with this hash is: counterrevolutionaries
	*/ 
	static const int TABLE_SIZE = 2412;

	// an array of lists of strings
	list<string> table[TABLE_SIZE];

  // Add any private functions you need here

public:
	/*
	 * Constructor
	 */
	WordFinder(string dictionaryFile) {
	
		// read in the file and populate the table
		/*
		*	Table Issues with caracters: é >> gives negative ASCII
		*	Case matters as well: NAME & name are different hashes
		*/

		fstream file(dictionaryFile);
		if (!file.is_open())
			cerr << "Error Opening File!" << endl;
		else {

			string word;
		
			while (file >> word) {
				//compute hash of the word & insert word
				table[hash_func(word)].push_back(word);
			}
			file.close();
		}
	}


	/*
	 * Find the dictionary words that have the same letters as the given word.
	 * Differences in letter cases are ignored.
	 *
	 * If the prnt flag is set, print the given word (same case as given)
	 * and the matching words (all in lowercase).
	 *
	 * If the prnt flag is not set, the words are found (i.e. all the work to find
	 * them is performed) but they are not printed.
	 *
	 * e.g.: findMatches("NAME", true) would print ONE LINE exactly as below
	 *
	 * 			NAME -> amen, mane, mean,
	 *
	 * 		note that the word "name" is not on the right side, although "name" is in the dictionary.
	 *
	 */
	void findMatches(string word, bool prnt) {
		
		// use the table to find the words
		
		// do not print them if prnt is false
		if(prnt)
			cout << word << " -> ";

		transform(word.begin(), word.end(), word.begin(), ::tolower);

		list<string>::iterator itr;
		string sorted_word, temp;
		itr = table[hash_func(word)].begin();
		//sorted_word = word;
		//sort(sorted_word.begin(), sorted_word.end());
		
		for (itr;  itr != table[hash_func(word)].end(); itr++) {
			
			if (prnt)
			{	
				sorted_word = word; sort(sorted_word.begin(), sorted_word.end());
				temp = *itr; sort(temp.begin(), temp.end());
				if (strcmp(temp.c_str(), sorted_word.c_str()) == 0 && itr->compare(word) != 0) {
					cout << *itr << ", ";
				}
			}

		}
		
		cout << endl;
		
	}

	//Added for easy paste of hash func
	int hash_func(string word) {

		int sum = 0;
		for (int i = 0; i < word.length(); i++) {
			sum += abs(word[i]);
		}
		return sum % TABLE_SIZE;
	}

};



/*************** DO NOT CHANGE THE CODE BELOW **************/

int main() {
	WordFinder finder("dictionary.txt");
	// test code for functionality
	int wordsLen = 17;
	string words[] = { "NAME", "act", "hug", "cafe", "node", "canoe", "dusty",
			"friend", "silent", "meteor", "markers", "aStewSir", "dirtyRoom",
			"stampStore", "moonStarers", "theClassroom", "accordNotInIt" };
	for (int i = 0; i < wordsLen; ++i) {
		finder.findMatches(words[i], true);
	}
	/*
	 * Would print as below:
	 *
	 *  NAME -> amen, mane, mean,
	 *  act -> cat,
	 *  ...
	 *  accordNotInIt -> ...
	 */

	// Stress the application to ensure it runs efficiently under load.
	// All runs below should complete practically in an instant.
	
	
	const int RUNS = 100000;
	for (int i = 0; i <= RUNS; i++) {
		finder.findMatches("noMoreStars", false); // print nothing, just do the crunching
		if (i % 1000 == 0) {
			cout << ".";
		}
	}
	cout << endl;
	finder.findMatches("noMoreStars", true);
	
	return 0;
}
