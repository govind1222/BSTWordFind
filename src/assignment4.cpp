/*
 * assignment4.cpp
 *
 *  Created on: Nov 4, 2019
 *      Author: gxp180015
 */

#include <iostream>
#include <fstream>
#include <string>
#include "word.h"
#include "binarySearchTree.h"

static void foundNode(const word& word) {
	std::vector<std::string> words = word.getWords();
	std::string list = "";
	if (words.size() == 1) {
		std::cout << "maps to word: ";
	} else {
		std::cout << "maps to words: ";

	}
	for (unsigned int i = 0; i < words.size(); i++) {
		list += words.at(i) + " ";
	}
	std::cout << list << "\n" << std::endl;
}

static void duplicateItemFound(word &existingItem, const word &newItem) {
	existingItem.addWords(newItem);
}

static void itemFound(const word&) {

}

int main() {

	std::ifstream input;
	std::string fileName = "../english_words.txt";
	std::string text = "";
	binarySearchTree<word> dictionary;
	input.open(fileName);

	if (!input.is_open()) {
		return 0;
	}

	std::cout << "Test of find words\n" << std::endl;
	input>>text;
	while (input) {
		word newWord(text);
		dictionary.insert(newWord, &duplicateItemFound);
		input >> text;
	}
	std::cout << "The dictionary has been built with " << dictionary.size()
			<< " keys in the dictionary" << std::endl;

	dictionary.traverse(&itemFound);

	std::string userInput;
	do {
		std::cout << "Word to unscramble (quit-now to stop):" << std::endl;
		std::cin >> userInput;
		if (userInput == "quit-now") {
			break;
		}
		word keyWord(userInput);
		std::cout << "\nScrambled word " << userInput << " ";
		if (!dictionary.find(keyWord, &foundNode)) {
			std::cout << "was not found\n" << std::endl;
		}
	} while (userInput != "quit-now");

}

