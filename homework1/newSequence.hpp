#ifndef newSequence_hpp
#define newSequence_hpp

const int DEFAULT_MAX_ITEMS = 150;
using ItemType = unsigned long;

class Sequence
{
    public:
    
        Sequence();
        Sequence(int num);
        Sequence &operator = (const Sequence &src);
        Sequence(const Sequence &other);
        ~Sequence();
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
        ItemType *m_array;
        int m_current;
        int m_max;
};


#endif /* newSequence_hpp */
