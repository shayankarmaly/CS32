#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include <string>

using ItemType = std::string;

class Sequence
{
    public:
    
        Sequence();
        ~Sequence();
        Sequence(const Sequence &src);
        Sequence &operator = (const Sequence &src);
    
        
        bool empty() const;
        int size() const;
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool get(int pos, ItemType& value) const;
        bool set(int pos, const ItemType& value);
        int find(const ItemType& value) const;
        void swap(Sequence& src);
    void dump() const;
    
    private:
    
        struct Node
        {
            ItemType count;
            Node* prev;
            Node* next;
        };
    
        Node* head;
        Node* tail;
        int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif