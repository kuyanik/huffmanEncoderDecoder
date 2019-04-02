/*
 * InBitStream.h
 *
 * Description: Implementation of InBitStream to read binary data from a file
 * 
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include <fstream>

using namespace std;

#pragma once

class InBitStream
{
private:
  ifstream &InFile;
  char *data;
  int index;
  int size;
  int countRead;

public:
  // Desc: Destructor
  ~InBitStream();
  // Desc: Constructor
  InBitStream();
  // Desc: Parameterized constructor
  InBitStream(ifstream &);
  // Desc: Gets the next bit from the input buffer
  // Post: If string is out of bounds returns false
  bool getNextBit(int &bit);
};
// end of file
