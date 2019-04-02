/*
 * PriorityQueue.h
 *
 * Description: Implementation of Priority Queue with linked list
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Author: Korcan Uyanik
 * Date: 19 March 2019
 *
 */

#pragma once

#include "Node.h"
#include "EmptyQueueException.h"
#include <iostream>

template <class T>
class PriorityQueue {

private:
   Node<T>* head;      
   int elementCount;   


public:

   // Default Constructor
   PriorityQueue();

   // Copy Constructor
   PriorityQueue(const PriorityQueue& rhsPriorityQueue);

   // Destructor
   ~PriorityQueue();

   // Desc: Returns number of elements stored in queue
   int getElementCount() const;

   // Desc: Return true if and only if the priority queue is empty
   bool isEmpty() const;

   // Desc: Inserts element in sort order, returns true if and only if successfull operation
   // Pre: This priority queue is sorted.
   // Post: After element is inserted, this priority queue remains sorted
   bool enqueue(const T& newElement);

   // Desc: Removes the element with the "highest" priority, returns true if and only if successful operation
   // Pre: This priority queue is not empty
   bool dequeue();

   // Description: Returns the element with the "highest" priority
   // Pre: This priority queue is not empty
   // Post: This priority queue is unchanged
   // Exceptions: Throws EmptyQueueException if this Priority Queue is empty
   T& peek() const throw();
  
   // Description: Printing operator overloading
   friend std::ostream& operator<<(std::ostream& out,const PriorityQueue<T>& PQ) {
      Node<T>* current = PQ.head;
      while(current != nullptr) {
          out << current->data << std::endl;
          current = current->next;
      } 
    
      return out;
   }
   
}; 

// Default Constructor
template <class T>
PriorityQueue<T>::PriorityQueue() {
    head = nullptr;
    elementCount = 0;
}

// Copy Constructor
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& rhsPriorityQueue) {
    elementCount = 0;
    head = nullptr;
    bool once = false;

    if(rhsPriorityQueue.elementCount != 0) {
        Node<T>* current1;
        Node<T>* current2 = rhsPriorityQueue.head;
        elementCount = rhsPriorityQueue.elementCount;
        head = new Node<T>;
        head->data = current2->data;
        current1 = head;
        while(current2->next != nullptr) {
            current1->next = new Node<T>;
            current1->next->data = current2->next->data;
            current1 = current1->next;
            current2 = current2->next;

        }
    }
}

// Destructor
template <class T>
PriorityQueue<T>::~PriorityQueue() {
    Node<T> *current, *before;
    current = head;
    head = nullptr;
    while(current != nullptr) {
        before = current;
        current = current->next;
        delete before;
    }
}

// Desc: Returns number of elements stored in queue
template <class T>
int PriorityQueue<T>::getElementCount() const {
    return elementCount;
}

// Desc: Return true if and only if the priority queue is empty
template <class T>
bool PriorityQueue<T>::isEmpty() const {
    return elementCount == 0;
}

// Desc: Inserts element in sort order, returns true if and only if successfull operation
// Pre: This priority queue is sorted.
// Post: After element is inserted, this priority queue remains sorted
template <class T>
bool PriorityQueue<T>::enqueue(const T& newElement) {
    Node<T>* before;
    Node<T>* current = head;
    bool success = false;

    if(current == nullptr || !(current->data < newElement) ) {
        head = new Node<T>;
        head->data = newElement;
        head->next = current;
        success = true;
        ++elementCount;
    }
    else {
        while(current != nullptr && current->data < newElement) {
            before = current;
            current = current->next;
        }
        before->next = new Node<T>;
        before->next->data = newElement;
        before->next->next = current;
        success = true;
        ++elementCount;
    }
    
    return success;
}

// Desc: Removes the element with the "highest" priority, returns true if and only if successful operation
// Pre: This priority queue is not empty
template <class T>
bool PriorityQueue<T>::dequeue() {
    Node<T>* current = head;
    bool success = false;
    if(current != nullptr) {
      head = current->next;
      delete current;
      success = true;
      --elementCount;
    }

    return success;
}

// Description: Returns the element with the "highest" priority
// Pre: This priority queue is not empty
// Post: This priority queue is unchanged
// Exceptions: Throws EmptyQueueException if this Priority Queue is empty
template <class T>
T& PriorityQueue<T>::peek() const throw(){
    if(elementCount == 0) {
    throw EmptyQueueException("Queue is empty, cannot peek!");
    }
    else {
        return head->data;
    }
}
// end of file