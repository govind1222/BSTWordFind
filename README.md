# BST Word Find 

## Overview
This program creates a binary search tree from a list of words from a file (its path 
is given as input to the program). After the tree is populated, the user can input a
word (scrambled or not), and the program will unscramble it and find it in the tree, 
if it exists. 

For example, when given the scrambled word "posigs", the output will be

```text
Scrambled word posigs maps to word: gossip
```

If the scrambled word does not map to any word in the tree, the output will be

```text
Scrambled word <word> was not found
```

## Running the program

The first input the program takes upon execution is the path to a file containing
the words with which the tree is populated. You should receive an output like

```text
The dictionary has been built with # keys in the dictionary
```

Now the user can enter a scrambled word and the program will try to unscramble the 
input and find it in the tree. 

If the user inputs

```text
quit-now
```

the program will terminate.