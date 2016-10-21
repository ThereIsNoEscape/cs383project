/*  stack.h
 *
 *  Jonathan Buch
 *  Section #1
 *  Lab #9
 *  April 1st, 2015
 *  Retrieved From Prof. Bruce Bolden on February 24th, 2015
 *
 *  Definition of Stack class without Linked List Structure
 */
 
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <assert.h>

using namespace std;

// Hello, this is an edit
// Hello, this is an edit 2
// Hello, this is an edit 3

class Stack 
{
public:
   Stack()
   {
	head = NULL;
	count = 0;
   }
   ~Stack();

   void Push(int n);     // push item onto stack
   int Pop();            // remove item from stack
   int Peek();
   void DRemoveAboveLimit( int x );
   void DRemoveBelowLimit( int x );
   void NDRemoveAboveLimit( int, Stack & );
   void NDRemoveBelowLimit( int, Stack & );
   int IsEmpty();        // is the stack empty?
   void Print();         // print the stack
   void joinstacks( Stack, Stack, Stack&, Stack& );

private:
   struct node
   {
	int data;
	node* next;
   };  typedef node * nodeptr;

   nodeptr head;
   int count;
};


#endif
