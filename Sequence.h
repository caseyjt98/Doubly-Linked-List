//
//  Sequence.h
//  Project-2
//
//  Created by Casey Taylor on 4/23/18.
//  Copyright © 2018 Casey Taylor. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <stdio.h>
#include <string>
//using ItemType = std::string;
using ItemType = unsigned long;


// implemented as a Doubley Linked List
class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump();
private:
    struct Node
    {
        ItemType m_value;      // value held by node
        Node* m_next;     // pointer to next node
        Node* m_prev;     // pointer to previous node
    };
    
    int m_size;     // number of elements in linked list
    Node* m_head;   // pointer to first (dummy) node in linked list
    
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);



#endif /* Sequence_h */
