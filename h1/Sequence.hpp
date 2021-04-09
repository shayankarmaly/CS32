
#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>

const int DEFAULT_MAX_ITEMS = 150;
using ItemType = unsigned long;

class Sequence
{
    public:
    
        Sequence();
        bool empty() const;
        int size() const;
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool get(int pos, ItemType& value) const;
        bool set(int pos, const ItemType& value);
        int find(const ItemType& value) const;
        void swap(Sequence& other);
    
    
    private:
    
        int m_size;
        ItemType m_array[DEFAULT_MAX_ITEMS];
};
#endif /* Sequence_hpp */
