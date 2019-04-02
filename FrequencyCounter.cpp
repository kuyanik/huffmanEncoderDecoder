/*
 * FrequencyCounter.h
 *
 * Description: Implementation of FrequencyCounter class
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include "FrequencyCounter.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Desc: Deconstructor
FrequencyCounter::~FrequencyCounter()
{
    delete[] frequency;
    delete[] letters;
}

// Desc: Constructor
FrequencyCounter::FrequencyCounter(ifstream &is)
{

    letters = new char[256];
    elementCount = 0;

    //initialize array
    int i = 0;
    while (i < 256)
    {
        arr[i] = 0;
        ++i;
    }

    //find frequency with map
    if (is.is_open())
    {
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        char *s = new char[length];
        //cout << length << endl;
        is.read(s, length);

        for (int i = 0; i < length; ++i)
        {
            if(s[i] < 0)
            {
                //cout << "took" << int(s[i])<< endl;
                int negativeIndex = 127 - s[i];
                ++arr[negativeIndex];
            }
            else
            {
                ++arr[int(s[i])];   
            }
        }
        delete[] s;
    }

    // Find letter types
    i = 0;
    while (i < 256)
    {
        if (arr[i] != 0)
        {
            if(i > 127)
            {
                //extended
                int negativeChar = (127 - i);
                letters[elementCount] = negativeChar;
                //cout << "boom" << endl;
                ++elementCount;
            }
            else
            {
                letters[elementCount] = i;
                ++elementCount;
            }
        }
        ++i;
    }

    // Find frequency of letters
    frequency = new int[elementCount];

    i = 0;
    while (i < elementCount)
    {
        if(letters[i] < 0)
        {
            frequency[i] = arr[127 - letters[i]];
            ++i;
        }
        else
        {
            frequency[i] = arr[int(letters[i])];
            ++i;
        }
    }
    is.clear();
    is.seekg(0, ios::beg);
}

// Desc: Returns the unique letters(characters) extracted from file
const char *FrequencyCounter::getLetters() const
{
    return letters;
}
// Desc: Returns frequencies of corresponding characters
const int *FrequencyCounter::getFrequency() const
{
    return frequency;
}
// Desc: Returns container sizes for both letters and frequencies
int FrequencyCounter::getElementCount() const
{
    return elementCount;
}