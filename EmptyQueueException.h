/*
 * EmptyQueueException.h
 *
 * Description: Exception class
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */
#pragma once

#include <stdexcept>
#include <string>

class EmptyQueueException : public std::exception
{
   private:
   std::string str;

   public:
   ~EmptyQueueException() throw ();
   EmptyQueueException(std::string s);
   const char* what() const throw();
};
// end of file