//
//  main.cpp
//  Project-2
//
//  Created by Casey Taylor on 4/23/18.
//  Copyright © 2018 Casey Taylor. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Sequence.h"
using namespace std;
 
int main() {
    

 
     
    //////////// TESTS FOR TYPE UNSIGNED LONG ///////////////////////
     
     
    // default constructor
    Sequence s;
    assert(s.size() == 0);          // test size
    assert(s.empty() == 1);         // test empty
    assert(s.remove(10) == 0);      // nothing to remove
    
    /////////////// test cases for insert() functions
    
    s.insert(0,10);                 // insert value 10 at position 0
    // CASE: pos equals size, empty list
    s.dump();                       // 10, size of 1
    
    s.insert(1,30);                 // insert value 20 at position 1
    // CASE: pos equals size
    s.dump();                       // 10 30, size of 2
    
    s.insert(1,20);                 // insert value 20 at position 1
    // CASE: insertion in middle of list (pos != size())
    s.dump();                       // 10 20 30, size of 3
    
    s.insert(15);                   // insert value 15
    // CASE: list not empty, insert in ascending order
    s.dump();                       // 10 15 20 30, size of 4
    
    
    ////////////////////// test case for erase() functions
    
    assert(s.erase(1) == 1);        // erase value 15
    s.dump();                       // 10 20 30, size of 3
    
    
    ////////////////////// test cases for get() function
    
    ItemType x;
    // get values at specified positions
    assert(s.get(0, x)  &&  x == 10);
    assert(s.get(1, x)  &&  x == 20);
    assert(s.get(2, x)  &&  x == 30);
    
    
    //////////////// test cases for remove() function
    
    s.insert(15); s.insert(25); s.insert (25);
    
    s.dump();                       // 10 15 20 25 25 30, size of 6
    
    assert(s.remove(25) == 2);      // remove all instances of value 25 (consecutive)
    s.dump();                       // 10 15 20 30, size of 4
    assert(s.size() == 4);
    
    
  
    assert(s.insert(3,15) == 1);
    assert(s.insert(0,15) == 1);
    s.dump();                       // 15 10 15 20 15 30, size of 6
    
    assert(s.remove(15) == 3);      // case: instances of value 15 are not consecutive in list
    s.dump();                       // 10 20 30, size of 3
    
    assert(s.insert(40) == 3);
    assert(s.insert(50) == 4);
    assert(s.insert(5,60) == 1);
    assert(s.size() == 6);
    s.dump();                       // 10 20 30 40 50 60
    
    
    ///////////////// test cases for set() function
    
    Sequence s1;
    assert(s1.set(12,12) == 0);     // invalid position
    
    assert(s.set(2,20) == 1);
    s.dump();                       // 10 20 20 40 50 60
    assert(s.set(0,80) == 1);
    s.dump();                       // 80 20 20 40 50 60
    assert(s.set(6,70) == 0);       // invalid position
    
    
    //////////////// test cases for find() function
    
    s.dump();                       // 80 20 20 40 50 60
    assert(s.find(80) == 0);
    assert(s.find(20) == 1);
    assert(s.find(100) == -1);
    Sequence s2;
    assert(s2.empty());
    s2.dump();
    assert(s2.find(0) == -1);
    
    
    //////////////////// test cases for swap() function
    
    Sequence mySeq;
    for(int i = 1; i <= 10; i++)
        mySeq.insert(i);
    mySeq.dump();                   // 1 2 3 4 5 6 7 8 9 10
    assert(mySeq.size() == 10);
    
    Sequence otherSeq;
    for(int i = 1; i <= 5; i++)
        otherSeq.insert(i);
    otherSeq.dump();                   // 1 2 3 4 5
    assert(otherSeq.size() == 5);
    
    cerr << "before swap: " << endl;
    cerr << "mySeq: ";
    mySeq.dump();
    cerr << "otherSeq: ";
    otherSeq.dump();
    cerr << endl;
    
    mySeq.swap(otherSeq);
    
    cerr << "after swap: " << endl;
    cerr << "mySeq: ";
    mySeq.dump();
    cerr << "otherSeq: ";
    otherSeq.dump();
    
    
    ////////////////////////////// test case for destructor
    
    Sequence banana;
    for (int i = 1; i <= 5; i++)
        banana.insert(i);
    banana.dump();
    banana.~Sequence();
    
    /////////////////////// test case for copy constructor
    Sequence obj1;
    for (int i = 1; i <= 5; i++)
        obj1.insert(i);
    obj1.dump();
    Sequence obj2(obj1);
    obj2.dump();
    
    /////////////////// test case for assignment operator
    Sequence lhs;
    for (int i=1; i<=5; i++)
        lhs.insert(i);
    lhs.dump();
    
    Sequence rhs;
    for (int i=1; i<=10; i++)
        rhs.insert(i);
    rhs.dump();
    lhs = rhs;
    lhs.dump();
    
    
    ////////////////////// test cases for subsequence() function
    
    // TEST CASE ONE: basic case with one matching subsequence
    Sequence seqOne;
    seqOne.insert(0,30); seqOne.insert(1,21); seqOne.insert(2,63); seqOne.insert(3,42); seqOne.insert(4,17); seqOne.insert(5,63); seqOne.insert(6,17); seqOne.insert(7,29); seqOne.insert(8,8); seqOne.insert(9,32);
    
    Sequence seqTwo;
    seqTwo.insert(0,63); seqTwo.insert(1,17); seqTwo.insert(2,29);
    seqOne.dump();
    seqTwo.dump();
    assert (subsequence(seqOne,seqTwo) == 5);
    
    // TEST CASE TWO: possible starting element is last element of seq one
    Sequence one;
    one.insert(0,10); one.insert(1,20); one.insert(2,30); one.insert(3,40);
    Sequence two;
    two.insert(0,40); two.insert(1,50); two.insert(2,60);
    one.dump();
    two.dump();
    assert (subsequence(one,two) == -1);
    
    // TEST CASE THREE: end of seq 1 reached before full subsequence is completed
    Sequence uno;
    uno.insert(0,10); uno.insert(1,20); uno.insert(2,30); uno.insert(3,40); uno.insert(4,50);
    Sequence dos;
    dos.insert(0,40); dos.insert(1,50); dos.insert(2,60);
    uno.dump();
    dos.dump();
    assert (subsequence(uno,dos) == -1);
    
    // TEST CASE FOUR: subsequence exists at very end of list
    Sequence uno1;
    uno1.insert(0,10); uno1.insert(1,20); uno1.insert(2,30); uno1.insert(3,40); uno1.insert(4,50); uno1.insert(5,60);
    Sequence dos2;
    dos2.insert(0,40); dos2.insert(1,50); dos2.insert(2,60);
    uno1.dump();
    dos2.dump();
    assert (subsequence(uno1,dos2) == 3);
    
    // TEST CASE FOUR: no matching starting value at all
    Sequence noMatch1;
    noMatch1.insert(2); noMatch1.insert(4); noMatch1.insert(6); noMatch1.insert(8);
    Sequence noMatch2;
    noMatch2.insert(80); noMatch2.insert(81); noMatch2.insert(86); noMatch2.insert(80);
    noMatch1.dump();
    noMatch2.dump();
    assert (subsequence(noMatch1,noMatch2) == -1);
    
    // TEST CASE FIVE: multiple subsequences, should return starting value of first one
    Sequence multiple;
    multiple.insert(0,1); multiple.insert(1,2); multiple.insert(2,3); multiple.insert(3,4);  multiple.insert(4,7); multiple.insert(5,11); multiple.insert(6,2); multiple.insert(7,3);  multiple.insert(8,4); multiple.insert(9,8);
    Sequence subSequence;
    subSequence.insert(2); subSequence.insert(3); subSequence.insert(4);
    multiple.dump();
    subSequence.dump();
    assert(subsequence(multiple,subSequence) == 1);
    
    // TEST CASE SIX: sequence one is empty list
    Sequence empty;
    Sequence notEmpty;
    notEmpty.insert(0, 10);
    assert(subsequence(empty,notEmpty) == -1);
    
    // TEST CASE SIX 1/2: sequence two is empty list
    Sequence imNotEmpty;
    Sequence imEmpty;
    imNotEmpty.insert(0, 10);
    assert(subsequence(imNotEmpty,imEmpty) == -1);
    
    // TEST CASE SEVEN: one element list
    Sequence oneEl;
    Sequence El;
    oneEl.insert(0,10);
    El.insert(0,10);
    assert(subsequence(oneEl, El) == 0);
    
    // TEST CASE SEVEN: subsequence is one element only
    Sequence one_El;
    Sequence two_El;
    one_El.insert(0,10);
    two_El.insert(0,10); two_El.insert(1,20);
    assert(subsequence(two_El, one_El) == 0);
    
    // TEST CASE EIGHT: seq2 larger than seq1
    
    Sequence small;
    Sequence big;
    small.insert(1);
    big.insert(10); big.insert(15);  big.insert(17);
    assert(subsequence(small,big) == -1);
    
    
    ///////////////////// test cases for interleave() function
    
    // case 1: sequences of same size
    Sequence a;
    for (int i = 0; i <= 10; i++)
        a.insert(i);
    Sequence b;
    for (int i = 10; i <= 20; i++)
        b.insert(i);
    a.dump();
    b.dump();
    
    Sequence result;
    interleave(a,b,result);
    result.dump();
    
    
    // case 2: seq 1 larger than seq 2
    Sequence c;
    for (int i = 0; i <= 5; i++)
        c.insert(i);
    Sequence d;
    for (int i = 10; i <= 12; i++)
        d.insert(i);
    c.dump();
    d.dump();
    
    Sequence result2;
    interleave(c,d,result2);
    result2.dump();
    
    
    // case 3: seq 2 larger than seq 1
    Sequence e;
    for (int i = 0; i <= 5; i++)
        e.insert(i);
    Sequence f;
    for (int i = 10; i <= 20; i++)
        f.insert(i);
    e.dump();
    f.dump();
    
    Sequence result3;
    interleave(e,f,result3);
    result3.dump();
    
    // case 4: seq 1 is empty
    Sequence g;
    Sequence h;
    for (int i = 0; i <= 5; i++)
        h.insert(i);
    g.dump();
    h.dump();
    
    Sequence result4;
    interleave(g,h,result4);
    result4.dump();
    
    // case 5: seq 2 is empty
    Sequence i;
    for (int k = 0; k <= 5; k++)
        i.insert(k);
    Sequence j;
    i.dump();
    j.dump();
    
    Sequence result5;
    interleave(i,j,result5);
    result5.dump();
    
    // case 6: aliasing; seq1 and result refer to the same sequence
    Sequence yo;
    for (int k = 0; k <= 5; k++)
        yo.insert(k);
    yo.dump();
    i.dump();
    interleave(yo,i,yo);
    yo.dump();
 
    return 0;
}


 
