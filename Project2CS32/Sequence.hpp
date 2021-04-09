
#ifndef Sequence_hpp
#define Sequence_hpp


#include <limits>
#include <string>


using ItemType = std :: string;

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

#endif /* Sequence_hpp */
