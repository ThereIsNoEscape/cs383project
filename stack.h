/* stack.h
 *
 *  Jonathan Buch
 *  Section #1
 *  Lab #5
 *  Retrieved From Prof. Bruce Bolden on February 24th, 2015
 *
 * Definition of Stack class
 */
 
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <assert.h>

#include "link.h"

// Hello, this is an edit
// Hello, this is an edit 2
// Hello, this is an edit 3

class Stack {
public:
   Stack();
   ~Stack();

   void Push(int n);     // push item onto stack
   int Pop();            // remove item from stack
   int IsEmpty();        // is the stack empty?
   void Print();         // print the stack

private:
   LinkedList topPtr;    // pointer to list
};


#endif
