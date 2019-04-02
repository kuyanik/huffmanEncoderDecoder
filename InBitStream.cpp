/*
 * InBitStream.cpp
 *
 * Description: Implementation of InBitStream to read binary data from a file
 * 
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include "InBitStream.h"
#include <fstream>
#include <iostream>

using namespace std;

// Desc: Parameterized constructor
InBitStream::InBitStream(ifstream &is) : InFile(is)
{
    int start = is.tellg();
    is.seekg(0, is.end);
    size = (int(is.tellg()) - start) + 1;
    is.seekg(start, is.beg);
    data = new char[size];
    is.read(data, size);
    index = -1;
    countRead = 8;
}

// Desc: Destructor
InBitStream::~InBitStream()
{
    delete[] data;
}

// Desc: Gets the next bit from the input buffer
// Post: If string is out of bounds returns false
bool InBitStream::getNextBit(int &bit)
{

    if (countRead == 8)
    {
        ++index;
        countRead = 0;
    }
    if (index >= size-1)
    {
        return false;
    }
    bit = (data[index] >> (7 - countRead)) & 1;
    ++countRead;

    return true;
}
// end of file