#include "newSequence.hpp"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s(1);
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
    
    Sequence first(1000);
    Sequence second(5);
    Sequence third;
    ItemType run = 5;
    
    
    for (int i = 0; i < 5; i++)
        assert(second.insert(run) != -1);
    
    // Failure if we try to insert a sixth item into b
    assert(second.insert(run) == -1);
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    first.swap(second);
    assert(first.insert(run) == -1  &&  second.insert(run) != -1);
    
    Sequence seq1(4);
    seq1.insert(0, 20);
    seq1.insert(0, 10);
    seq1.insert(15);
    assert(seq1.size() == 3);
    ItemType num = 999;
    assert(seq1.get(0, num) && num == 10);
    assert(seq1.get(1, num) && num == 15);
    assert(seq1.get(2, num) && num == 20);
    seq1.erase(0);
    assert(seq1.size() == 2);
    assert(seq1.get(0, num) && num == 15);
    assert(seq1.get(1, num) && num == 20);
    seq1.insert(20);
    assert(seq1.size() == 3);
    assert(seq1.get(0, num) && num == 15);
    assert(seq1.get(1, num) && num == 20);
    assert(seq1.get(2, num) && num == 20);
    assert(seq1.remove(20) == 2);
    assert(seq1.size() == 1);
    assert(seq1.get(0, num) && num == 15);
    seq1.insert(1, 25);
    seq1.insert(2, 40);
    seq1.insert(3, 22);
    assert(seq1.size() == 4);
    assert(seq1.get(0, num) && num == 15);
    assert(seq1.get(1, num) && num == 25);
    assert(seq1.get(2, num) && num == 40);
    assert(seq1.get(3, num) && num == 22);
    seq1.set(3, 25);
    assert(seq1.size() == 4);
    assert(seq1.get(0, num) && num == 15);
    assert(seq1.get(1, num) && num == 25);
    assert(seq1.get(2, num) && num == 40);
    assert(seq1.get(3, num) && num == 25);
    assert(seq1.find(25) == 1);
    assert(seq1.remove(25) == 2);
    assert(seq1.size() == 2);
    assert(seq1.get(0, num) && num == 15);
    assert(seq1.get(1, num) && num == 40);
    assert(seq1.find(40) == 1);
    
    Sequence seq2(3);
    seq2.insert(5);
    seq2.insert(10);
    seq2.insert(8);
    assert(seq2.get(0, num) && num == 5);
    assert(seq2.get(1, num) && num == 8);
    assert(seq2.get(2, num) && num == 10);
    
    seq1.swap(seq2);
    
    assert(seq1.size() == 3);
    assert(seq1.get(0, num) && num == 5);
    assert(seq1.get(1, num) && num == 8);
    assert(seq1.get(2, num) && num == 10);
    
    assert(seq2.size() == 2);
    assert(seq2.get(0, num) && num == 15);
    assert(seq2.get(1, num) && num == 40);
    
    Sequence seq3(seq2);
    
    assert(seq3.size() == 2);
    assert(seq3.get(0, num) && num == 15);
    assert(seq3.get(1, num) && num == 40);
    
    seq3 = seq1;
    
    assert(seq3.size() == 3);
    assert(seq3.get(0, num) && num == 5);
    assert(seq3.get(1, num) && num == 8);
    assert(seq3.get(2, num) && num == 10);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
