/*
 * binarySearchTree.h
 *
 *  Created on: Nov 4, 2019
 *      Author: gxp180015
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>

template<class DataType>
class binarySearchTree;

template<class DataType>
class treeNode {
	friend class binarySearchTree<DataType> ;
private:
	DataType keyWord;
	treeNode<DataType>* leftNode;
	treeNode<DataType>* rightNode;
public:
	//default constructor
	treeNode() {
		leftNode = nullptr;
		rightNode = nullptr;
		keyWord("");
	}

	//creates treeNode with newItem
	treeNode(const DataType &newItem) {
		keyWord = newItem;
		leftNode = nullptr;
		rightNode = nullptr;
	}
protected:
	//get the left node
	treeNode* left() const {
		return leftNode;
	}

	//get the right node
	treeNode* right() const {
		return rightNode;
	}

	//returns the data stored in the node
	DataType& data() {
		return keyWord;
	}

	//returns the data stored in the node as a const
	const DataType& data() const {
		return keyWord;
	}

	//replaces keyWord with newItem
	void data(DataType &newItem) {
		keyWord = newItem;
	}

	//replaces keyWord with const newItem
	void data(const DataType& newItem) {
		keyWord = newItem;
	}

	//returns the left node
	void left(treeNode *newLeft) {
		leftNode = newLeft;
	}

	//returns the right node
	void right(treeNode *newRight) {
		rightNode = newRight;
	}
};

template<class DataType>
class binarySearchTree {
private:
	treeNode<DataType>* rootNode;
	unsigned int length = 0;
public:
	//default constructor
	binarySearchTree() {
		rootNode = nullptr;
	}

	//copy constructor
	binarySearchTree(const binarySearchTree &other) {
		deleteAll();
		copyAll(other);
	}

	//destructor
	virtual ~binarySearchTree() {
		deleteAll();
	}

	//copy assignment operator
	binarySearchTree operator=(const binarySearchTree& other) {
		if (this != &other) {
			copyAll(other);
		}
		return *this;
	}

	//returns true if the search tree is empty
	bool empty() const {
		return length == 0;
	}

	//returns the size of the search tree
	std::size_t size() const {
		return length;
	}

	//Display the contents of the binary tree in order by key (inorder traversal)
	void print() const;
	//print helper method
	void print(treeNode<DataType> *printNode, std::ostream &out) const;
	//prints to ostream
	void print(std::ostream &out) const;
	//Display the contents of the binary tree for debugging purposes
	void debug(std::ostream &out) const;
	//returns true if @param - &searchItem is found, false otherwise
	bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
	//The erase member function will remove the specified item from the binary tree (if it finds the entry in the tree)
	//returns true if @param &deleteItem was found and erased, false otherwise
	bool erase(const DataType &deleteItem);
	//Insert the item into the binary tree
	void insert(const DataType &newItem);
	//insert the item into the binary tree. If the item already exists the duplicateItemFound function will be called
	void insert(const DataType &newItem,
			void (*duplicateItemFound)(DataType &existingItem,
					const DataType &newItem));
	//The traverse function will do an inorder traversal of the binary tree
	void traverse(void (*itemFound)(const DataType& foundItem)) const;
	//the traverse function will do an out-order traversal of the binary tree
	void traverseOutOrder(void (itemFound)(const DataType& foundItem)) const;
	//the traverse function will do an preorder traversal of the binary tree
	void traversePreOrder(void (itemFound)(const DataType& foundItem)) const;
	//copies the tree
	void copyAll(const binarySearchTree &other);
private:
	//deletes all elements
	void deleteAll();
	//deletes all children of root
	void deleteAll(treeNode<DataType> *node);
	//inserts all nodes from @param &other
	void insertAll(treeNode<DataType> *node);
	//traverse all
	void traverseAll(treeNode<DataType> *node, std::string traversal,
			void (*itemFound)(const DataType& foundItem)) const;
};

//Display the contents of the binary tree in order by key (inorder traversal)
template<class DataType>
void binarySearchTree<DataType>::print() const {
	print(rootNode, std::cout);
}

//print helper method
template<class DataType>
void binarySearchTree<DataType>::print(treeNode<DataType> *printNode,
		std::ostream &out) const {
	if (printNode == nullptr) {
		return;
	}

	print(printNode->left(), out);
	out << printNode->data() << std::endl;
	print(printNode->right(), out);
}

//prints to ostream
template<class DataType>
void binarySearchTree<DataType>::print(std::ostream &out) const {
	print(rootNode, out);
}

//Display the contents of the binary tree for debugging purposes
template<class DataType>
void binarySearchTree<DataType>::debug(std::ostream &out) const {
	out << "Starting debug" << std::endl;
	print();
	out << "Ending debug" << std::endl;
}

//returns true if @param - &searchItem is found, false otherwise
template<class DataType>
bool binarySearchTree<DataType>::find(const DataType &searchItem,
		void (*foundNode)(const DataType&)) {
	treeNode<DataType> *curNode = rootNode;
	while (curNode != nullptr) {
		if (curNode->data() == searchItem) {
			foundNode(curNode->data());
			return true;
		} else if (searchItem < curNode->data()) {
			curNode = curNode->left();
		} else {
			curNode = curNode->right();
		}
	}
	return false;
}

//The erase member function will remove the specified item from the binary tree (if it finds the entry in the tree)
//returns true if @param &deleteItem was found and erased, false otherwise
template<class DataType>
bool binarySearchTree<DataType>::erase(const DataType &deleteItem) {
	treeNode<DataType> *curNode = rootNode;
	treeNode<DataType> *par = nullptr;
	while (curNode != nullptr) { // Search for node
		if (curNode->data() == deleteItem) { // Node found
			if (curNode->left() == nullptr && curNode->right() == nullptr) { // Remove leaf
				if (par == nullptr) {        // Node is root
					rootNode = nullptr;
				} else if (par->left() == curNode) {
					par->left(nullptr);
				} else {
					par->right(nullptr);
				}
			} else if (curNode->left() != nullptr
					&& curNode->right() == nullptr) { // Remove node with only left child
				if (par == nullptr) {    // Node is root
					rootNode = curNode->left();
				} else if (par->left() == curNode) {
					par->left(curNode->left());
				} else {
					par->right(curNode->left());
				}
			} else if (curNode->left() == nullptr
					&& curNode->right() != nullptr) { // Remove node with only right child
				if (par == nullptr) { // Node is root
					rootNode = curNode->right();
				} else if (par->left() == curNode) {
					par->left(curNode->right());
				} else {
					par->right(curNode->right());
				}
			} else {                            // Remove node with two children
				// Find successor (leftmost child of right subtree)
				treeNode<DataType> *suc = curNode->right();
				while (suc->left() != nullptr) {
					suc = suc->left();
				}
				DataType successorData = suc->data();
				erase(suc->data());     // Remove successor
				//	Assign cur's data with successorData
				curNode->data(successorData);
			}
			length++;
			return true;	            // Node found and removed
		} else if (curNode->data() < deleteItem) { // Search right
			par = curNode;
			curNode = curNode->right();
		} else {                     // Search left
			par = curNode;
			curNode = curNode->left();
		}
	}
	return false;                     // Node not found
}

//Insert the item into the binary tree
template<class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem) {

	treeNode<DataType> *newNode = new treeNode<DataType>(newItem);
	if (rootNode == nullptr) {
		rootNode = newNode;
		newNode->left(nullptr);
		newNode->right(nullptr);
	} else {
		treeNode<DataType> *curNode = rootNode;
		while (curNode != nullptr) {
			if (newNode->data() == curNode->data()) {
				curNode->data(newNode->data());
				return;
			} else if (newNode->data() < curNode->data()) {
				if (curNode->left() == nullptr) {
					curNode->left(newNode);
					curNode = nullptr;
				} else {
					curNode = curNode->left();
				}
			} else {
				if (curNode->right() == nullptr) {
					curNode->right(newNode);
					curNode = nullptr;
				} else {
					curNode = curNode->right();
				}
			}
		}
	}
	newNode->left(nullptr);
	newNode->right(nullptr);
	length++;
}

//insert the item into the binary tree. If the item already exists the duplicateItemFound function will be called
template<class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem,
		void (*duplicateItemFound)(DataType &existingItem,
				const DataType &newItem)) {

	treeNode<DataType>* curNode = rootNode;
	treeNode<DataType> *newNode = new treeNode<DataType>(newItem);
	bool found = false;
	if (size() >= 1) {
		while (curNode != nullptr) {
			if (curNode->data() == newNode->data()) {
				duplicateItemFound(curNode->data(), newNode->data());
				found = true;
				break;
			} else if (newNode->data() < curNode->data()) {
				curNode = curNode->left();
			} else {
				curNode = curNode->right();
			}
		}
	} else {
		insert(newItem);
	}

	if (!found) {
		insert(newItem);
	}
}

//The traverse function will do an inorder traversal of the binary tree
template<class DataType>
void binarySearchTree<DataType>::traverse(
		void (*itemFound)(const DataType& foundItem)) const {
	traverseAll(rootNode, "inorder", itemFound);
}

//the traverse function will do an out-order traversal of the binary tree
template<class DataType>
void binarySearchTree<DataType>::traverseOutOrder(
		void (*itemFound)(const DataType& foundItem)) const {
	traverseAll(rootNode, "outorder", itemFound);
}

//the traverse function will do an preorder traversal of the binary tree
template<class DataType>
void binarySearchTree<DataType>::traversePreOrder(
		void (*itemFound)(const DataType& foundItem)) const {
	traverseAll(rootNode, "preorder", itemFound);
}

//traverses entire tree based on what type of traversal is required
template<class DataType>
void binarySearchTree<DataType>::traverseAll(treeNode<DataType> *node,
		std::string traversal,
		void (*itemFound)(const DataType& foundItem)) const {

	if (node == nullptr) {
		return;
	}

	if (traversal == "outorder") {
		traverseAll(node->left(), "outorder", itemFound);
		traverseAll(node->right(), "outorder", itemFound);
		itemFound(node->data());
	} else if (traversal == "preorder") {
		itemFound(node->data());
		traverseAll(node->left(), "preorder", itemFound);
		traverseAll(node->right(), "preorder", itemFound);
	} else {
		traverseAll(node->left(), "inorder", itemFound);
		itemFound(node->data());
		traverseAll(node->right(), "inorder", itemFound);
	}
}

//deletes all elements
template<class DataType>
void binarySearchTree<DataType>::deleteAll() {
	deleteAll(rootNode);
	rootNode = nullptr;
}

//deletes all children of root
template<class DataType>
void binarySearchTree<DataType>::deleteAll(treeNode<DataType> *node) {
	if (node != nullptr) {
		deleteAll(node->left());
		node->left(nullptr);

		deleteAll(node->right());
		node->right(nullptr);

		delete node;
		length--;
	}
}

//copies the tree
template<class DataType>
void binarySearchTree<DataType>::copyAll(
		const binarySearchTree<DataType> &other) {
	length = 0;
	rootNode = nullptr;
	treeNode<DataType> *current = other.rootNode;
	insertAll(current);
}

//inserts all nodes from @param &other
template<class DataType>
void binarySearchTree<DataType>::insertAll(treeNode<DataType> *node) {
	if (node == nullptr) {
		return;
	}
	insertAll(node->left());
	insert(node->data());
	insertAll(node->right());
}

#endif /* BINARYSEARCHTREE_H_ */
