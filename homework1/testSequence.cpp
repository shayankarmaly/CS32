
#include <stdio.h>
#include "Sequence.hpp"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence seq;
    assert(seq.empty());
    assert(seq.find(30) == -1);
    assert(seq.insert(30) == 0);
    assert(seq.size() == 1  &&  seq.find(30) == 0);


    Sequence seq1;
    seq1.insert(0, 20);
    seq1.insert(0, 10);
    seq1.insert(15);
    seq1.insert(35);
    assert(seq1.size() == 4);
    ItemType val = 678;
    assert(seq1.get(0, val) && val == 10);
    assert(seq1.get(1, val) && val == 15);
    assert(seq1.get(2, val) && val == 20);
    assert(seq1.get(3, val) && val == 35);
    seq1.erase(0);
    assert(seq1.size() == 3);
    assert(seq1.get(0, val) && val == 15);
    assert(seq1.get(1, val) && val == 20);
    assert(seq1.get(2, val) && val == 35);
    seq1.set(2, 20);
    assert(seq1.size() == 3);
    assert(seq1.get(0, val) && val == 15);
    assert(seq1.get(1, val) && val == 20);
    assert(seq1.get(2, val) && val == 20);
    seq1.remove(20);
    assert(seq1.size() == 1);
    assert(seq1.get(0, val) && val == 15);

    Sequence seq2;
    seq2.insert(10);
    seq2.insert(199);
    seq2.insert(25);
    assert(seq2.find(25) == 1);

    seq1.swap(seq2);

    assert(seq1.size() == 3);
    assert(seq1.get(0, val) && val == 10);
    assert(seq1.get(1, val) && val == 25);
    assert(seq1.get(2, val) && val == 199);

    assert(seq2.size() == 1);
    assert(seq2.get(0, val) && val == 15);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

