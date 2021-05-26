/*
 * word.h
 *
 *  Created on: Nov 4, 2019
 *      Author: gxp180015
 */

#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class word {
private:
	std::string key;
	std::vector<std::string> values;
public:
	//default
	word() {
		key = "";
	}

	//passed in the word to be added to vector, used to make key as well
	word(std::string newWord) {
		key = wordKey(newWord);
		values.push_back(newWord);
	}

	//returns word as folded, and sorted
	std::string wordKey(std::string word);
	//returns the vector of words
	std::vector<std::string> getWords() const;
	//returns key variable
	std::string getKey() const;

	//adds words from newWord into the vector
	void addWords(const word &newWord);

	//comparison of keys
	bool operator==(const word &other) const;
	bool operator<(const word& other) const;
};

//defines print output
std::ostream& operator<<(std::ostream &out, const word &outputWord);


#endif /* WORD_H_ */
