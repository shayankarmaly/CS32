#include <iostream>
#include <cassert>
#include "ScoreList.hpp"

int main()
{
    ScoreList seq;
    
    for(int j=0; j<100;j++)
    {
        seq.add(j);
    }
    
    assert(seq.size() == 100);
    assert(seq.minimum() == 0);
    assert(seq.maximum() == 99);
    
    for(int j=50; j<100; j++)
    {
        seq.remove(j);
    }
    
    assert(seq.size() == 50);
    assert(seq.minimum() == 0);
    assert(seq.maximum() == 49);
    
    seq.remove(0);
    
    assert(seq.size() == 49);
    assert(seq.minimum() == 1);
    assert(seq.maximum() == 49);
    
    seq.remove(49);
    
    assert(seq.size() == 48);
    assert(seq.minimum() == 1);
    assert(seq.maximum() == 48);
    
    seq.add(48);
    
    assert(seq.size() == 49);
    assert(seq.minimum() == 1);
    assert(seq.maximum() == 48);
    
    seq.remove(48);
    
    assert(seq.size() == 48);
    assert(seq.minimum() == 1);
    assert(seq.maximum() == 48);
    
    seq.remove(48);
    
    assert(seq.size() == 47);
    assert(seq.minimum() == 1);
    assert(seq.maximum() == 47);
    
    std::cout << "Passed all tests" << std::endl;
    return(0);
}

