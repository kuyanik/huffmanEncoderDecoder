/*
 * FrequencyCounter.h
 *
 * Description: Implementation of FrequencyCounter class
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include <fstream>
#include <string>

using namespace std;

class FrequencyCounter
{
  private:
    int arr[256];
    char *letters;
    int elementCount;
    int *frequency;

  public:
    // Desc: Constructor
    FrequencyCounter(ifstream &);
    // Desc: Deconstructor
    ~FrequencyCounter();
    // Desc: Returns the unique letters(characters) extracted from file
    const char *getLetters() const;
    // Desc: Returns frequencies of corresponding characters
    const int *getFrequency() const;
    // Desc: Returns container sizes for both letters and frequencies
    int getElementCount() const;
};