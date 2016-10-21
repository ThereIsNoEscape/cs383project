/*  LinkedList.cpp
 *  Jonathan Buch
 *  Section #1
 *  Lab #10
 *  Class for a linked list of ints.
 *  Retrieved from: Bruce Bolden on February 15th 2015
 *  Modified April 9th, 2015 for Lab 10
 */

#include<iostream>
#include"LinkedList.h"

using namespace std;

void LinkedList::AddNode( int x )				// Adds a node to the top of the list
{
    nodeptr n;

        //  allocate new node
    n = new node;
    n->info = x;
    count++;

    if( start == NULL )
    {
        start = n;
        n->next = NULL;
    }
    else
    {
        nodeptr tmp = start;
        n->next = tmp;
        start = n;
    }
}

void LinkedList::DeleteNode( int x )				// Deletes a node from the list
{
    nodeptr prev, curr;

    curr = start;

    while( curr != NULL && x > curr->info )
    {
        prev = curr;
        curr = curr->next;
    }

    if( x == curr->info )
    {
        if( curr == start )
            start = start->next;
        else
            prev->next = curr->next;

        delete curr;
        count--;
    }
}

int LinkedList::FirstNode()					// Returns the first node
{
    return start->info;
}

void LinkedList::Print()					// Prints the nodes
{
        nodeptr n;
        n = start;
        if( start == NULL )
        {
                cout << "No Elements in List" << endl;
        }
        while( n != NULL )
        {
                cout << n->info << " ";
                n = n->next;
        }
	cout << endl;
}


#ifdef NOT_USING_CC_WHATEVER_ITS_PREDEF_IF
bool LinkedList::IsInList( int x )
#else
int LinkedList::IsInList( int x )				// Checks if a value is in the list
#endif
{
    nodeptr p = start;

    while( p != NULL && x > p->info )
        p = p->next;

    return (x == p->info);
}


int LinkedList::Size()						// returns the size of the list
{
    return count;
}

int LinkedList::RemoveFromFront()
{
        nodeptr n;
        int ret;

        if( start == NULL )
        {
        }
        else
        {
                n = start;
                start = start->next;
                ret = n->info;
                delete n;
                count --;
                return ret;
        }
}

void LinkedList::DRemoveAboveLimit( int x )
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
                        Storage[cycles] = RemoveFromFront();
                        cycles++;
                }
                cycles = 0;
                for( int i = 0; i < length; i++ )
                {
                        if( Storage[cycles] <= x )
                        {
                                AddNode( Storage[cycles] );
                        }
                        cycles++;
                }
        }
}

void LinkedList::DRemoveBelowLimit( int x )
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
                        Storage[cycles] = RemoveFromFront();
                        cycles++;
                }
                cycles = 0;
                for( int i = 0; i < length; i++ )
                {
                        if( Storage[cycles] >= x )
                        {
                                AddNode( Storage[cycles] );
                        }
                        cycles++;
                }
        }
}

void LinkedList::NDRemoveAboveLimit( int x, LinkedList& temp )
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
                        Storage[cycles] = RemoveFromFront();
                        cycles++;
                }
                cycles = 0;
                for( int i = 0; i < length; i++ )
                {
                        if( Storage[cycles] <= x )
                        {
                                AddNode( Storage[cycles] );
                                temp.AddNode( Storage[cycles] );
                        }
                        cycles++;
                }
        }
}

void LinkedList::NDRemoveBelowLimit( int x, LinkedList& temp )
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
                        Storage[cycles] = RemoveFromFront();
                        cycles++;
                }
                cycles = 0;
                for( int i = 0; i < length; i++ )
                {
                        if( Storage[cycles] >= x )
                        {
                                AddNode( Storage[cycles] );
                                temp.AddNode( Storage[cycles] );
                        }
                        cycles++;
                }
        }
}

