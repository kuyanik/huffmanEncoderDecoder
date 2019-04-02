/*
 * HuffmanTree.h
 *
 * Description: Implementation of HuffmanTree for encoding and decoding data
 * Class Invariant: Each code is a prefix-code
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include <string>
#include "TreeNode.h"

using namespace std;

#pragma once

class HuffmanTree
{
public:
  TreeNode *root;
  string code;
  int weight;
  int childCount;
  void encode(char c, TreeNode *root, string str);
public:
  // Desc: Constructor
  HuffmanTree();
  // Desc: Parameterized Constructor
  HuffmanTree(const HuffmanTree &);
  // Desc: Deconstructor
  ~HuffmanTree();
  // Desc: Takes two trees and merges them under a main tree
  // Post: Placed first parameter to left , second parameter to right subtree
  HuffmanTree mergeTrees(const HuffmanTree &leftHuffmanTree, const HuffmanTree &rightHuffmanTree);
  // Desc: Removes all nodes from a subtree
  // Post: All node memories are deallocated
  void RemoveSubtree(TreeNode *ptr);
  // Desc: Deep copies a subtree, returns a handle of the newly created subtree
  // Post: Tree is deep copied and handle returned
  TreeNode *cloneSubtrees(const TreeNode *ptr) const;
  // Desc: Less than operator
  // Post: The value returned by the function is true if and only if rhsHuffmanTree's weight is bigger than left hand
  bool operator<(const HuffmanTree &rhsHuffmanTree) const;
  // Desc: Assignment operator
  // Post: Deallocates object then deep copies rhsHuffmanTree to it
  HuffmanTree &operator=(const HuffmanTree &rhsHuffmanTree);
  // Desc: Creates and populates the Huffman tree
  // Pre: letterSize should be the size of the letters and frequency
  // Post: Huffman tree leaves are filled, tree ready to be used for the purposes of decoding & encoding
  void createTree(const char *letters, int letterSize, const int *frequency);
  // Desc: Decodes a given data
  // Pre: numberOfChars is the number of estimated decompressed character count
  // Post: c_str is populated with the decoded data
  void decode(char *c_str, string code, int numberOfChars);
  // Desc: Encodes the character
  // Post: Returns corresponding code string
  string getCode(char c);
  // Desc: Checks if the node is a child
  // Post: Returns true if and only if ptr is a child
  bool isChild(TreeNode *ptr);
  // Desc: Prints all leaves of the HuffmanTree
  // Post: Outputs data to standard output
  void printOutChilds(TreeNode *ptr);
}; // end of file