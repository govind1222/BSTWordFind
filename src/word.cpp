/*
 * word.cpp
 *
 *  Created on: Nov 4, 2019
 *      Author: gxp180015
 */

#include "word.h"
#include <string>

//returns word as folded, and sorted
std::string word::wordKey(std::string word) {
	for (unsigned int i = 0; i < word.length(); i++) {
		if (word.at(i) >= 65 && word.at(i) <= 90) {
			char c = (char) ((int) word.at(i) + 32);
			word[i] = c;
		}
	}
	std::sort(word.begin(), word.end());
	return word;
}

//returns the vector of words
std::vector<std::string> word::getWords() const {
	return values;
}

//returns key variable
std::string word::getKey() const {
	return key;
}

//compares key values
bool word::operator<(const word& other) const {
	return key < other.getKey();
}

//compares key values
bool word::operator==(const word& other) const {
	return key == other.key;
}

//adds words from newWord into the vector
void word::addWords(const word &newWord) {
	if (key == newWord.getKey()) {
		std::vector<std::string> newValues = newWord.getWords();
		values.insert(values.end(), newValues.begin(), newValues.end());
	}
}

//defines print output
std::ostream& operator<<(std::ostream& out, const word &outputWord) {
	out << "[" << outputWord.getKey() << ", {";
	std::vector<std::string> words = outputWord.getWords();
	for (unsigned int i = 0; i < words.size(); i++) {
		if (i + 1 == words.size()) {
			out << words.at(i) << "}]";
			break;
		} else {
			out << words.at(i) << ", ";
		}
	}
	return out;
}
