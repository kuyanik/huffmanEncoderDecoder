/*
 * HuffmanTree.cpp
 *
 * Description: Implementation of HuffmanTree for encoding and decoding data
 * Class Invariant: Each code is a prefix-code
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include "TreeNode.h"
#include <string>
#include <iostream>

using namespace std;

// Desc: Constructor
HuffmanTree::HuffmanTree() : root(nullptr), code(""), weight(0), childCount(0) {}

// Desc: Parameterized Constructor
HuffmanTree::HuffmanTree(const HuffmanTree &rhsHuffmanTree)
{
    root = cloneSubtrees(rhsHuffmanTree.root);
    weight = rhsHuffmanTree.weight;
}

// Desc: Takes two trees and merges them under a main tree
// Post: Placed first parameter to left , second parameter to right subtree
HuffmanTree HuffmanTree::mergeTrees(const HuffmanTree &leftHuffmanTree, const HuffmanTree &rightHuffmanTree)
{
    HuffmanTree temp;
    temp.root = new TreeNode();
    temp.root->c = '\0';
    temp.root->left = cloneSubtrees(leftHuffmanTree.root);
    temp.root->right = cloneSubtrees(rightHuffmanTree.root);
    temp.weight = leftHuffmanTree.weight + rightHuffmanTree.weight;

    return temp;
}

// Desc: Assignment operator
// Post: Deallocates object then deep copies rhsHuffmanTree to it
HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhsHuffmanTree)
{
    RemoveSubtree(root);
    root = cloneSubtrees(rhsHuffmanTree.root);
    weight = rhsHuffmanTree.weight;

    return *this;
}

// Desc: Removes all nodes from a subtree
// Post: All node memories are deallocated
void HuffmanTree::RemoveSubtree(TreeNode *ptr)
{
    if (ptr != nullptr)
    {
        RemoveSubtree(ptr->left);
        ptr->left = nullptr;
        RemoveSubtree(ptr->right);
        ptr->right = nullptr;
        delete ptr;
    }
}
// Desc: Deconstructor
HuffmanTree::~HuffmanTree()
{
    RemoveSubtree(root);
}

// Desc: Deep copies a subtree, returns a handle of the newly created subtree
// Post: Tree is deep copied and handle returned
TreeNode *HuffmanTree::cloneSubtrees(const TreeNode *ptr) const
{
    if (ptr == nullptr)
    {
        return nullptr;
    }
    else
    {
        TreeNode *copy = new TreeNode();
        copy->c = ptr->c;
        copy->left = cloneSubtrees(ptr->left);
        copy->right = cloneSubtrees(ptr->right);
        return copy;
    }
}

// Desc: Less than operator
// Post: The value returned by the function is true if and only if rhsHuffmanTree's weight is bigger than left hand
bool HuffmanTree::operator<(const HuffmanTree &rhsHuff) const
{

    bool isBigger = false;
    if (this->weight < rhsHuff.weight)
    {
        isBigger = true;
    }

    return isBigger;
}

// Desc: Creates and populates the Huffman tree
// Pre: letterSize should be the size of the letters and frequency
// Post: Huffman tree leaves are filled, tree ready to be used for the purposes of decoding & encoding
void HuffmanTree::createTree(const char *letters, int letterSize, const int *frequency)
{

    int lettersLength = letterSize;
    PriorityQueue<HuffmanTree> PQ;

    int i = 0;
    while (i < lettersLength)
    {
        HuffmanTree temp;
        temp.root = new TreeNode();
        temp.root->c = letters[i];
        temp.root->left = nullptr;
        temp.root->right = nullptr;
        temp.weight = frequency[i];
        PQ.enqueue(temp);
        ++i;
    }
    try
    {
        while (PQ.getElementCount() > 1)
        {
            HuffmanTree t1(PQ.peek());
            PQ.dequeue();
            HuffmanTree t2(PQ.peek());
            PQ.dequeue();
            HuffmanTree t3(mergeTrees(t1, t2));
            PQ.enqueue(t3);
        }

        this->root = cloneSubtrees((PQ.peek()).root);
        this->weight = PQ.peek().weight;
    }
    catch (EmptyQueueException ex)
    {
        std::cerr << ex.what() << '\n';
    }
}

void HuffmanTree::encode(char c, TreeNode *ptr, string code)
{
    if (ptr != nullptr)
    {
        if (ptr->left != nullptr)
        {
            encode(c, ptr->left, code + '0');
        }
        if (ptr->right != nullptr)
        {
            encode(c, ptr->right, code + '1');
        }
        if (isChild(ptr))
        {
            if (ptr->c == c)
            {
                this->code = code;
            }
        }
    }
    return;
}

// Desc: Decodes a given data
// Pre: numberOfChars is the number of estimated decompressed character count
// Post: c_str is populated with the decoded data 
void HuffmanTree::decode(char *c_str, string code, int numberOfChars)
{
    int elementCount = 0;
    TreeNode *temp = this->root;

    int i = 0;
    while (i < int(code.length()) && elementCount < numberOfChars)
    {
        if (temp != nullptr)
        {
            if (code[i] == '0')
            {
                temp = temp->left;
            }
            else if (code[i] == '1')
            {
                temp = temp->right;
            }
            if (isChild(temp) == 1)
            {
                c_str[elementCount] = temp->c;
                ++elementCount;
                temp = root;
            }
        }
        else
        {
            cout << "problem in HufmannTree::decode" << endl;
        }

        ++i;
    }
}

// Desc: Prints all leaves of the HuffmanTree
// Post: Outputs data to standard output
void HuffmanTree::printOutChilds(TreeNode *ptr)
{
    if (ptr != nullptr)
    {
        if (ptr->left == nullptr && ptr->right == nullptr)
        {
            ++childCount;
            cout << int(ptr->c) << endl;
        }
        else
        {
            printOutChilds(ptr->left);
            printOutChilds(ptr->right);
        }
    }
}

// Desc: Checks if the node is a child
// Post: Returns true if and only if ptr is a child
bool HuffmanTree::isChild(TreeNode *ptr)
{
    bool check = false;
    if (ptr != nullptr)
    {
        if (ptr->left == nullptr && ptr->right == nullptr)
        {
            check = true;
        }
    }
    return check;
}

// Desc: Encodes the character
// Post: Returns corresponding code string  
string HuffmanTree::getCode(char c)
{
    encode(c, this->root, "");
    string toBeReturned = code;
    this->code = "";

    return toBeReturned;
}

// end of file