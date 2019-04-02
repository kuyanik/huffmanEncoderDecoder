/*
 * EmptyQueueException.cpp
 *
 * Description: Exception class
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#include <string>
#include "EmptyQueueException.h"

EmptyQueueException::EmptyQueueException(std::string s) : str(s) {}

EmptyQueueException::~EmptyQueueException() throw () {}

const char* EmptyQueueException::what() const throw() 
{ 
    return str.c_str();
}
// end of file
