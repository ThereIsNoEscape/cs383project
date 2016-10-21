/*  link.cpp
 *  
 *  Jonathan Buch
 *  Section #1
 *  Lab #5
 *  Retrieved From Prof. Bruce Bolden on February 24th, 2015
 *
 *  Class for a sorted linked list of integers.
 */

#include <iostream>

using namespace std;

#include "link.h"


//  Add an item to the FRONT of the list
void LinkedList::AddNode( int x )
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

//\end{verbatim}  \lecpb  \begin{verbatim}

void LinkedList::DeleteNode( int x )
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

//\end{verbatim}  \lecpb  \begin{verbatim}

int LinkedList::FirstNode()
{
    return start->info;
}


void LinkedList::PrintNodes()
{
    nodeptr p = start;

    while( p != NULL )
    {
        cout << p->info << endl;
        p = p->next;
    }

}

//\end{verbatim}  \lecpb  \begin{verbatim}

bool LinkedList::IsInList(int x)
{
    nodeptr p = start;

    while( p != NULL && x > p->info )
        p = p->next;

    return (x == p->info);
}


int LinkedList::Size()
{
    return count;
}
