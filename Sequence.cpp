//
//  Sequence.cpp
//  Project-2
//
//  Created by Casey Taylor on 4/23/18.
//  Copyright © 2018 Casey Taylor. All rights reserved.
//

#include "Sequence.h"
#include <iostream>


// Create an empty circular linked list
Sequence::Sequence()
:m_size(0)
{
    m_head = new Node; // new Node object
    // circular; node points back to itself in both directions
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}


// Destructor
// When a Sequence is destroyed, the nodes in the linked list must be deallocated.
Sequence::~Sequence()
{
    while (m_head->m_next != m_head) // while not empty list
    {
        Node* ptr = m_head->m_next; // points to first element in list
        ptr->m_prev->m_next = ptr->m_next; // to-be-deleted node's preceding element now points to element after to-be-deleted node
        ptr->m_next->m_prev = ptr->m_prev;
        delete ptr; // delete node
    }
}

// Copy constructor
// When a brand new Sequence is created as a copy of an existing Sequence, enough new nodes must be allocated to hold a duplicate of the original list.
Sequence::Sequence(const Sequence& other)
: m_size(other.m_size)
{
    // creates a new Sequence object from an existing sequence object
    
    // new head node; pointers set as if empty list
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    
    Node* prevNode = m_head; // refers to new node's previous node
    
    for (Node* itr = other.m_head->m_next; itr != other.m_head; itr = itr->m_next)
    {
        Node* newDude = new Node; // create new node
        newDude->m_value = itr->m_value;
        
        newDude->m_prev =  prevNode;
        prevNode->m_next = newDude;
        newDude->m_next = m_head; // circular linked list
        m_head->m_prev = newDude;
        
        prevNode = newDude; // advance previous node
    }
}

// assignment operator
//  When an existing Sequence (the left-hand side) is assigned the value of another Sequence (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
Sequence& Sequence::operator=(const Sequence& other)
{
    if (&other == this)    // Do nothing if we are other
        return (*this);
    
    // free up memory in lhs Sequence by deleting all nodes
    while (m_head->m_next != m_head) // while not empty list
    {
        Node* ptr = m_head->m_next; // points to first element in list
        ptr->m_prev->m_next = ptr->m_next; // to-be-deleted node's preceding element now points to element after to-be-deleted node
        ptr->m_next->m_prev = ptr->m_prev;
        delete ptr; // delete node
    }
    
    // copy over rhs Sequence into now empty lhs Sequence
    
    Node* prevNode = m_head; // refers to new node's previous node
    
    for (Node* itr = other.m_head->m_next; itr != other.m_head; itr = itr->m_next)
    {
        Node* newDude = new Node; // create new node
        newDude->m_value = itr->m_value;
        
        newDude->m_prev =  prevNode;
        prevNode->m_next = newDude;
        newDude->m_next = m_head; // circular linked list
        m_head->m_prev = newDude;
        
        prevNode = newDude; // advance previous node
    }
    
    m_size = other.size();
    
    return *this;
}

// Return true if the linked list is empty, otherwise false.
bool Sequence::empty() const
{
    if (m_size == 0)
        return true;
    return false;
}

// Return the number of items in the linked list.
int Sequence::size() const
{
    return m_size;
}

// Insert value into specified position pos within the list.
// Return true if 0 <= pos <= size() and the value could be
// inserted. If pos is equal to size(), the value is inserted at the end.
bool Sequence::insert(int pos, const ItemType& value)
{
    // check for valid position
    
    if (pos < 0 || pos > size())
        return false;
    
    else
    {
        // CASE 1: pos == size()
        if (pos == size())
        {
            // insert at end of list
            
            Node* itr = m_head->m_prev;     // pointer to last node in list
            // also accounts for case of empty list
            Node* newDude = new Node;
            newDude->m_value = value;
            newDude->m_prev = itr;
            newDude->m_next = m_head;
            itr->m_next = newDude;
            m_head->m_prev = newDude; // newDude is now last in list
            
            m_size++; // increment size
            return true;
        }
        
        else // position in middle of list
        {
            int index = 0; // to keep track of element index as we traverse
            for (Node* itr = m_head->m_next; itr != m_head; itr = itr->m_next)
            {
                if (index == pos)
                    // at this point, itr points to the node at position pos
                {
                    // new Node
                    Node* newDude = new Node;
                    newDude->m_value = value;
                    
                    // adjust pointers; change newDude first to avoid memory leaks
                    newDude->m_prev = itr->m_prev;
                    newDude->m_next = itr;
                    itr->m_prev->m_next = newDude;
                    itr->m_prev = newDude;
                    
                    // increment size
                    m_size++;
                }
                index++; // advance element index
            }
            
        }
        return true;
    }
}

// Let p be the smallest integer such that value <= the item at
// position p in the linked list; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the list so that it becomes the item at position
// p. Return p if the value was actually inserted.
int Sequence::insert(const ItemType& value)
{
    int pos = size(); // by default, insert at end of list
    
    // Case: empty list; insert at beginning
    if (empty() == 1)
    {
        pos = 0;
        Node* newDude = new Node;
        newDude->m_value = value;
        // adjust pointers
        m_head->m_next = newDude;
        m_head->m_prev = newDude;
        newDude->m_prev = m_head;
        newDude->m_next = m_head;
        
        m_size++; // increment size
        return pos;
    }
    
    // Case: list not empty
    else
    {
        // determine proper position
        
        int index = 0; // to keep track of element index as we traverse
        for (Node* itr = m_head->m_next; itr != m_head; itr = itr->m_next)
        {
            if (itr->m_value >= value)
            {
                pos = index;
                break;
            }
            index++; // advance element index
        }
        insert(pos, value);
        return pos;
        
    }
}

// If 0 <= pos < size(), remove the item at position pos from
// the linked list and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    // check for valid position
    if (0 <= pos && pos < size())
    {
        
        int index = 0; // to keep track of element index as we traverse
        for (Node* itr = m_head->m_next; itr != m_head; itr = itr->m_next)
        {
            if (index == pos)
            {
                // remove item at pos and move down following items
                Node* temp = itr; // temporary pointer to node being removed
                itr->m_prev->m_next = temp->m_next;
                itr->m_next->m_prev = temp->m_prev;
                delete temp;
                m_size--;
                return true;
            }
            index++; // advance element index
        }
    }
    
    return false;
}

// Erase all items from the linked list that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int removed = 0; // keep track of elements removed
    
    // Case: empty list
    if (empty() == 1)
        return 0;
    
    // Case: list not empty
    else
    {
        int pos = 0; // keep track of element index as we traverse
        
        Node* itr = m_head->m_next;
        while (itr != m_head)
        {
            if (itr->m_value == value)
            {
                itr = itr->m_next;
                erase(pos); // erase node at that index
                removed++; // increment number of removed elements
                pos--; // account for lost element
            }
            else // value not found
            {
                itr = itr->m_next;
            }
            pos++; // advance element index
            
        }
        return removed;
    }
    
}

// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const
{
    // check valid position
    if (0 <= pos && pos < size())
    {
        // get item at pos
        
        int index = 0; // keep track of element index as we traverse
        for (Node* itr = m_head->m_next; itr != m_head; itr = itr->m_next)
        {
            if (index == pos)
            {
                // get item at pos
                value = itr->m_value;
                return true;
            }
            index++; // advance element index
        }
    }
    
    return false;
}

// If 0 <= pos < size(), replace the item at position pos of the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    // check valid position
    if (0 <= pos && pos < size())
    {
        // set item at pos
        
        int index = 0; // keep track of element index as we traverse
        for (Node* itr = m_head->m_next; itr != m_head; itr = itr->m_next)
        {
            if (index == pos)
            {
                // set item at pos
                itr->m_value = value;
                return true;
            }
            index++; // advance element index
        }
    }
    return false;
}

// Let p be the smallest integer such that value == the item at
// position p in the linked list; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const
{
    int pos = -1; // default, if no item found
    
    int index = 0; // keep track of element index as we traverse
    
    for (Node* itr = m_head->m_next; itr != m_head; itr = itr->m_next)
    {
        if (itr->m_value == value) // item found
        {
            pos = index;
            break;
        }
        
        index++; // advance element index
    }
    
    return pos;
}

// Exchange the contents of this sequence with the other one.
// The number of statement executions when swapping two sequences
// must be the same no matter how many items are in the sequences.
void Sequence::swap(Sequence& other)
{
    // temporary pointer to head of linked list
    Node* tempHead = m_head;
    
    // swap head pointers
    m_head = other.m_head;
    other.m_head = tempHead;
    
    // temporary variable to store size of linked list
    int tempSize = m_size;
    
    // swap sizes
    m_size = other.m_size;
    other.m_size = tempSize;
}

// testing purposes
void Sequence::dump()
{
    for (Node* n = m_head->m_next; n != m_head; n = n->m_next)
    {
        std::cerr << n->m_value << " ";
    }
    std::cerr << std:: endl;
    std::cerr << "size of list: " << m_size << std::endl;
    
    std::cerr << std::endl;
    
    //std::cerr << "element 1: " << m_head->m_next->m_value << " points to NEXT element " << m_head->m_next->m_next->m_value << std::endl;
}

// Find and returbn the starting position at which seq2 exists
// both exactly and consecutively within seq1. Return -1 if
// no subsequence is found
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // no valid subsequence is seq2 is empty or larger than seq1
    if (seq2.size() > seq1.size() || seq2.empty() == 1)
        return -1;
    
    int k = -1; // default
    ItemType value1;
    ItemType value2;
    int index = 0; // to iterate over sequence 2
    
    // loop through seq 1 and see if matching value exists
    for(int i = 0; i < seq1.size(); i++)
    {
        seq1.get(i,value1);
        seq2.get(index,value2);
        if (value1 == value2) // matching value found
        {
            k = i; // store possible starting position of subsequence
            
            // if possible starting element is last element in list
            if (k >= seq1.size()-1 && seq2.size() > 1)
                return -1;
            
            // check that subsequent items in seq 1 match seq 2
            for (int i = k+1; i <= seq1.size();i++)
            {
                // note: implementation counts one- element subsequence as valid
                if (index == seq2.size()-1)
                    // end of seq2, all values match up to this point
                    return k;
                
                index++; // advance to next element of seq 2
                seq1.get(i,value1);
                seq2.get(index,value2);
                
                if (value1 != value2) // if subsequence does not match
                {
                    index = 0; // restart seq 2 iteration
                    k = -1;
                    break;
                }
                
            }
        }
    }
    return k;
}

// This function creates as a resulting sequence that consists
// of the first item in seq1, then the first in seq2, then
// the second in seq1, then the second in seq2, etc.
// Be sure this function behaves correctly in the face of aliasing:
// What if seq1 and result refer to the same Sequence, for example?
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    
    Sequence temp(result);      // avoid case of aliasing with temporary sequence
    while (temp.empty() == 0)   // clear contents of temp result sequence
        temp.erase(0);
    
    int resultIndex = 0; // keep track of index position in resulting Sequence
    
    // figure out which sequence is longer
    int max_size;
    if (seq1.size() >= seq2.size())
        max_size = seq1.size();
    else // seq 2 is larger
        max_size = seq2.size();
    
    ItemType value; // value to be inserted
    
    for (int i = 0; i < max_size; i++)
    {
        if (seq1.get(i,value)) // if valid index
        {
            temp.insert(resultIndex,value); // insert sequence 1 value into result
            resultIndex++;
        }
        
        if (seq2.get(i,value))
        {
            temp.insert(resultIndex, value); // insert sequence 2 value into result
            resultIndex++;
        }
        
    }
    result = temp; // copy values over into result
}

