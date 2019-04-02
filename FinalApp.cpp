/*
 * FinalTest.cpp
 *
 * Description: Compression & Decompression of binary file application
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include <fstream>
#include "OutBitStream.h"
#include "InBitStream.h"
#include "HuffmanTree.h"
#include "FrequencyCounter.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    
    if (argc != 4)
    {
        cout << "Need more argument, try again.";
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0)
    {
        ifstream is(argv[2], ios::binary);
        ofstream os(argv[3], ios::binary);

        // Get letters and frequency
        FrequencyCounter FQ(is);
        const char *letters = FQ.getLetters();
        int letters_size = FQ.getElementCount();
        const int *frequency = FQ.getFrequency();

        // Create the tree
        HuffmanTree myTree;
        myTree.createTree(letters, letters_size, frequency);

        // Output decodingNumber to compressed.huff
        os << letters_size << endl;

        // Output frequencies to compressed.huff
        for (int i = 0; i < letters_size; ++i)
        {
            os << frequency[i] << endl;
        }

        //Output letters to compressed.huff
        os.write(letters, letters_size);

        OutBitStream outstream(os);

        // Get codes and write them to compressed.huff
        is.clear();
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        char *s = new char[length];
        is.read(s, length);

        for (int i = 0; i < length; ++i)
        {
            string code = myTree.getCode(s[i]);
            for (int j = 0; j < int(code.length()); ++j)
            {
                outstream.writeBit(code[j] - '0');
            }
        }
        delete[] s;

        // Close files
        outstream.closeWriting();
        is.close();
        os.close();

        // Re-open files to count bytes for each file
        ifstream is2(argv[3], ios::binary);
        int OutputSize = 0;
        if (is2.is_open())
        {
            is2.seekg(0, is.end);
            int length = is2.tellg();
            OutputSize = length;
        }
        is2.close();

        ifstream is3(argv[2], ios::binary);
        int InputSize = 0;
        if (is3.is_open())
        {
            is3.seekg(0, is.end);
            int length = is3.tellg();
            InputSize = length;
        }
        is3.close();
        if (OutputSize > InputSize)
        {
            cout << string(argv[2]) << " -> " << InputSize << " bytes" << endl;
            cout << string(argv[3]) << " -> " << OutputSize << " bytes" << endl;
            cout << "*** Size of compressed file > size of source file ***" << endl;
        }
        else
        {
            cout << string(argv[2]) << " -> " << InputSize << " bytes" << endl;
            cout << string(argv[3]) << " -> " << OutputSize << " bytes" << endl;
        }
    }

    else if (strcmp(argv[1], "-d") == 0)
    {
        ifstream is(argv[2], ios::binary);
        ofstream os(argv[3], ios::binary);

        string temp;
        if (is.is_open())
        {
            getline(is, temp);
        }
        else
        {
            cerr << "File cannot opened." << endl;
            return -1;
        }

        int decodingNumber = stoi(temp);
        cout << "Decoding Number: " << decodingNumber << endl;

        // READ FREQUENCIES
        int *frequencies = new int[decodingNumber];
        for (int i = 0; i < decodingNumber; ++i)
        {
            getline(is, temp);
            frequencies[i] = stoi(temp);
        }

        // READ LETTERS
        char *buf = new char[decodingNumber];
        is.read(buf, decodingNumber);

        // Create Huffman Tree
        HuffmanTree myTree;
        myTree.createTree(buf, decodingNumber, frequencies);

        InBitStream instream(is);
        //Read all encoded data
        string encodedData = "";
        int bit;
        while (instream.getNextBit(bit))
        {
            encodedData += to_string(bit);
        }

        //Find total number of characters
        int totalCharNumber = 0;
        int i = 0;
        while (i < decodingNumber)
        {
            totalCharNumber += frequencies[i];
            ++i;
        }

        char *decodedAnswer = new char[totalCharNumber];
        myTree.decode(decodedAnswer, encodedData, totalCharNumber);
        os.write(decodedAnswer, totalCharNumber);

        is.close();
        os.close();
    }
    else
    {
        cout <<"Use -c to compress or -d to decompress.";
    }

    return 0;
}
// end of file