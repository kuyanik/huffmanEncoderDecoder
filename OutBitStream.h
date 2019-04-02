/*
 * OutBitStream.h
 *
 * Description: Implementation of OutBitStream to write binary to a file.
 * 
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include <fstream>

using namespace std;

#pragma once

class OutBitStream {
    private:
    ofstream& outFile;
    char* buf;
    int pos;

    public:
    // Desc: Constructor
    OutBitStream();
    // Desc: Deconstructor
    ~OutBitStream();
    // Desc: Parameterized constructor takes output file stream
    OutBitStream(ofstream&);
    // Desc: Write given bit to the output file
    // Pre: input bit is assumed to be 1 or 0
    // Post: One bit depending on bit, '0' or '1' is written to the output file
    void writeBit(int bit);
    // Desc: If any unwritten bits remaining in the buffer, writes one last time
    // Post: Last unwritten bits in the buffer are written on output
    void closeWriting();
};
// end of file