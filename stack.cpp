/*  stack.cpp
 *
 *  Jonathan Buch
 *  Section #1
 *  Lab #5
 *  Retrieved From Prof. Bruce Bolden on February 24th, 2015
 *
 *  Definition of Stack class member functions.
 */

#include <iostream>
#include <assert.h>

#include "stack.h"


Stack::Stack()
{
}


Stack::~Stack()
{
   //delete topPtr;
   while( !IsEmpty() ) {
       int  n = topPtr.FirstNode();
       topPtr.DeleteNode( n );
   }
}

//\end{verbatim}  \lecpb  \begin{verbatim}

void Stack::Push(int n)
{
   topPtr.AddNode( n );
}


int Stack::Pop()
{
   assert(!IsEmpty());

   int  n = topPtr.FirstNode();
   topPtr.DeleteNode( n );
   return n;
}

//\end{verbatim}  \lecpb  \begin{verbatim}

int Stack::IsEmpty()
{
    int n = topPtr.Size();
    return (n == 0);
}


void Stack::Print()
{
    topPtr.PrintNodes();
}


