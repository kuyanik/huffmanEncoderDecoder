/*
 * OutBitStream.cpp
 *
 * Description: Implementation of OutBitStream to write binary to a file.
 * 
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include "OutBitStream.h"
#include <fstream>

using namespace std;

// Desc: Parameterized constructor
OutBitStream::OutBitStream(ofstream &out) : outFile(out)
{
    buf = new char;
    *buf = '\0';
    pos = 7;
}

// Desc: If any unwritten bits remaining in the buffer, writes one last time
// Post: Last unwritten bits in the buffer are written on output
void OutBitStream::closeWriting()
{
    if (pos != 7)
    {
        outFile.write(buf, 1);
    }
}

// Desc: Deconstructor
OutBitStream::~OutBitStream()
{
    delete[] buf;
}

// Desc: Write given bit to the output file
// Pre: input bit is assumed to be 1 or 0
// Post: One bit depending on bit, '0' or '1' is written to the output file
void OutBitStream::writeBit(int bit)
{

    if (pos > 0)
    {
        *buf |= bit << pos;
        --pos;
    }
    else if (pos == 0)
    {
        *buf |= bit << pos;
        outFile.write(buf, 1);
        *buf = '\0';
        pos = 7;
    }
}
// end of file