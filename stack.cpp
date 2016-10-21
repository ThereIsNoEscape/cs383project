/*  stack.cpp
 *
 *  Jonathan Buch
 *  Section #1
 *  Lab #9
 *  April 1st, 2015
 *  Retrieved From Prof. Bruce Bolden on February 24th, 2015
 *
 *  Definition of Stack class
 *  Without the use of Linked List Structure (On its own)
 */

#include <iostream>
#include <assert.h>

#include "stack.h"

/*
Stack::Stack()
{
}
*/

Stack::~Stack()
{
}

//\end{verbatim}  \lecpb  \begin{verbatim}

// Push Items onto a Stack

void Stack::Push( int d )
{
	nodeptr n = new node;
	
	n->data = d;
	
	if( head == NULL )
	{
		head = n;
		n->next = NULL;
	}
	else
	{
		n->next = head;
		head = n;
	}
	count++;
}

// Pop Items off of a Stack

int Stack::Pop()
{
	nodeptr n;
	int ret;

	if( head == NULL )
	{
	}
	else
	{
		n = head;
		head = head->next;
		ret = n->data;
		delete n;
		count --;
		return ret;
	}	
}

//\end{verbatim}  \lecpb  \begin{verbatim}

int Stack::IsEmpty()
{
	if( count == 0 )
		return 1;
	else
		return 0;
}


void Stack::Print()
{
	nodeptr n;
	n = head;
	if( head == NULL )
	{
		cout << "No Elements in List" << endl;
	}
	while( n != NULL )
	{
		cout << n->data << " ";
		n = n->next;
	}
	cout << endl;
}

void Stack::joinstacks( Stack first, Stack second, Stack& newStack, Stack& tempStack )
{
	if( first.count == 0 || second.count == 0 )
	{
		cout << "One or Both of the Lists are Empty" << endl;
	}

	while( !first.IsEmpty() || !second.IsEmpty() )		// Check if either have
	{							// elements remaining
		if( !first.IsEmpty() )
		{
			tempStack.Push( first.Pop() );		// Print Stack 1 Correctly
			newStack.Push( tempStack.Pop() );
		}
		if( !second.IsEmpty() )				// Stack 2 reversed with 
		{	
		  // this method already
			newStack.Push( second.Pop() );
		}
	}
}

void Stack::DRemoveAboveLimit( int x )
{
	int cycles = 0;
	int length = count;
	int Storage[length];
	
	if( length == 0 )
	{
		cout << "No Elements to Remove" << endl;
	}
	else
	{
		while( cycles < length )
		{
			Storage[cycles] = Pop();		
			cycles++;				
		}						
		cycles = 0;	
		for( int i = 0; i < length; i++ ) 
		{
			if( Storage[cycles] <= x )
			{
				Push( Storage[cycles] );	
			}					
			cycles++;				
		}
	}
}	

void Stack::DRemoveBelowLimit( int x )
{
	int cycles = 0;
	int length = count;
	int Storage[length];
	
	if( length == 0 )
	{
		cout << "No Elements to Remove" << endl;
	}
	else
	{
		while( cycles < length )
		{
			Storage[cycles] = Pop();		
			cycles++;				
		}						
		cycles = 0;	
		for( int i = 0; i < length; i++ ) 
		{
			if( Storage[cycles] >= x )
			{
				Push( Storage[cycles] );	
			}					
			cycles++;				
		}
	}
}	

void Stack::NDRemoveAboveLimit( int x, Stack& temp )
{
	int cycles = 0;
	int length = count;
	int Storage[length];
	
	if( length == 0 )
	{
		cout << "No Elements to Remove" << endl;
	}
	else
	{
		while( cycles < length )
		{
			Storage[cycles] = Pop();		
			cycles++;				
		}						
		cycles = 0;	
		for( int i = 0; i < length; i++ ) 
		{
			if( Storage[cycles] <= x )
			{
				Push( Storage[cycles] );	
				temp.Push( Storage[cycles] );	
			}					
			cycles++;				
		}
	}
}	

void Stack::NDRemoveBelowLimit( int x, Stack& temp )
{
	int cycles = 0;
	int length = count;
	int Storage[length];
	
	if( length == 0 )
	{
		cout << "No Elements to Remove" << endl;
	}
	else
	{
		while( cycles < length )
		{
			Storage[cycles] = Pop();		
			cycles++;				
		}						
		cycles = 0;	
		for( int i = 0; i < length; i++ ) 
		{
			if( Storage[cycles] >= x )
			{
				Push( Storage[cycles] );	
				temp.Push( Storage[cycles] );	
			}					
			cycles++;				
		}
	}
}	
