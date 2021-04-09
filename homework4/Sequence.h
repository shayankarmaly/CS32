#ifndef Sequence_h
#define Sequence_h

template <typename Temp>

class Sequence
{
  public:
    Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const Temp& value);
    int insert(const Temp& value);
    bool erase(int pos);
    int remove(const Temp& value);
    bool get(int pos, Temp& value) const;
    bool set(int pos, const Temp& value);
    int find(const Temp& value) const;
    void swap(Sequence& other);
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);

  private:
    
    struct Node
    {
        Temp m_value;
        Node*    m_next;
        Node*    m_prev;
    };

    Node* m_head;
    int   m_size;

    void createEmpty();
    void insertBefore(Node* p, const Temp& value);
    Node* doErase(Node* p);
    Node* nodeAtPos(int pos) const;
};

// Declarations of non-member functions
template <typename Temp>
int subsequence(const Sequence<Temp>& seq1, const Sequence<Temp>& seq2);

template <typename Temp>
void interleave(const Sequence<Temp>& seq1, const Sequence<Temp>& seq2, Sequence<Temp>& result);



// Inline implementations

// Return the number of items in the sequence.
template<typename Temp>
inline
int Sequence<Temp>::size() const
{
    return m_size;
}


// Return true if the sequence is empty, otherwise false.
template<typename Temp>
inline
bool Sequence<Temp>::empty() const
{
    return size() == 0;
}





// Sequence class implementations


template<typename Temp>
Sequence<Temp> :: Sequence()// Create an empty sequence (i.e., one whose size() is 0).
{
    createEmpty();
}


// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
template<typename Temp>
int Sequence <Temp> :: insert(int pos, const Temp& value)
{
  if ( pos > m_size || pos < 0)
  {
      return -1;
  }
    Node* temp = nodeAtPos(pos);
    insertBefore(temp, value);
    
    return pos;
}


// Let p be the smallest integer such that value <= the item at
  // position p in the sequence; if no such item exists (i.e.,
  // value > all items in the sequence), let p be size().  Insert
  // value into the sequence so that it becomes the item in position
  // p.  The original item at position p and those that follow it end
  // up at positions one higher than before.  Return p if the value
  // was actually inserted.  Return -1 if the value was not inserted
  // (perhaps because the sequence has a fixed capacity and is full).
template <typename Temp>
int Sequence <Temp> :: insert(const Temp& value)
{
    int position;
    Node* temp;
    
    for(temp = m_head -> m_next, position = 0; temp!= m_head && value > temp -> m_value; temp = temp -> m_next, position++)
    ;
        insertBefore(temp, value);
    
    return position;
    
}


// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
template <typename Temp>
bool Sequence <Temp> :: erase(int pos)
{
    if (pos >= size() || pos < 0)
    {
        return false;
    }
    
    Node* temp = nodeAtPos(pos);
    doErase(temp);
    return true;
}

// Erase all items from the sequence that == value.  Return the
  // number of items removed (which will be 0 if no item == value).
template <typename Temp>
int Sequence<Temp> :: remove(const Temp& value)
{
    Node* temp = m_head-> m_next;
    int removeCount = 0;
    
    while(temp!= m_head)
    {
        if(temp -> m_value == value)
        {
            removeCount++;
            temp = doErase(temp);
        }
        
        else
        {
            temp = temp -> m_next;
        }
    }
    
    
    return removeCount;
}
 
// If 0 <= pos < size(), copy into value the item at position pos
  // of the sequence and return true.  Otherwise, leave value unchanged
  // and return false.
template <typename Temp>
bool Sequence<Temp> :: get(int pos, Temp& value) const
{
    if (pos >= size() || pos < 0)
    {
        return false;
    }
    
        Node* temp = nodeAtPos(pos);
        value = temp -> m_value;
        return true;
}

// If 0 <= pos < size(), replace the item at position pos of the
  // sequence with value and return true.  Otherwise, leave the sequence
  // unchanged and return false.
template <typename Temp>
bool Sequence<Temp> :: set(int pos, const Temp& value)
{
    if (pos >= size() || pos < 0)
    {
        return false;
    }
    
        Node* temp = nodeAtPos(pos);
        temp -> m_value = value;
        return true;
}
  
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
template <typename Temp>
int Sequence <Temp> :: find(const Temp& value) const
{
    Node* temp = m_head -> m_next;
    int position = 0;
    
    for(; temp != m_head && temp -> m_value != value; temp = temp-> m_next, position++)
        ;
    
    return temp == m_head ? -1 : position;
}
 
// Exchange the contents of this sequence with the other one.
template <typename Temp>
void Sequence <Temp> :: swap(Sequence& other)
{
    Node* temp = other.m_head;
    other.m_head = this->m_head;
    m_head = temp;
    
    int sze = other.m_size;
    other.m_size = this -> m_size;
    m_size = sze;
}


// Destructor
template<typename Temp>
Sequence<Temp> :: ~ Sequence()
{
    while(m_head -> m_next != m_head)
    {
        doErase(m_head-> m_next);
        
    }
    
    delete m_head;
}


template <typename Temp>
Sequence<Temp> :: Sequence(const Sequence& other)
{
    createEmpty();
    
    for(Node* temp = other.m_head -> m_next; temp!= other.m_head; temp = temp -> m_next)
    {
        insertBefore(m_head, temp-> m_value);
    }
}



template <typename Temp>
Sequence<Temp>& Sequence<Temp> :: operator=(const Sequence<Temp>& rhs)
{
   if(this != &rhs)
   {
    
       Sequence<Temp> temporary(rhs);
       swap(temporary);
   }
    return *this;
}


// Create an empty list.  (Should be called only by constructors.)
template <typename Temp>
void Sequence <Temp> :: createEmpty()
{
    m_size = 0;
    
    m_head = new Node;
    m_head -> m_next = m_head;
    m_head -> m_prev = m_head;
}

// Insert value in a new Node before Node p, incrementing m_size.
template <typename Temp>
void Sequence <Temp> :: insertBefore(Node* p, const Temp& value)
{
    Node* newNode = new Node;
    
    newNode -> m_value = value;
    newNode -> m_prev = p -> m_prev;
    newNode -> m_next = p;
    newNode -> m_prev -> m_next = newNode;
    newNode -> m_next -> m_prev = newNode;
    
    m_size++;
}

// Remove the Node p, decrementing m_size.  Return the Node that
// followed p.
template <typename Temp>
typename Sequence<Temp> :: Node* Sequence<Temp> :: doErase(Node* p)
{
    Node* newNext = new Node;
    
    newNext = p -> m_next;
    p -> m_prev -> m_next = p-> m_next;
    p -> m_next -> m_prev = p-> m_prev;
    delete p;
    m_size--;
    return newNext;
}
 

// Return pointer to Node at position pos.  If pos == m_size, return
// m_head.  (Will be called only when 0 <= pos <= size().)

template <typename Temp>
typename Sequence <Temp> :: Node* Sequence <Temp> :: nodeAtPos(int pos) const
{
    Node* temp;
    if (pos <= m_size /2)
    {
        temp = m_head -> m_next;
        for(int i = 0; i != pos; i++)
        {
            temp = temp -> m_next;
        }
    }
    
    else
    {
        temp = m_head;
        for (int i = m_size; i!= pos; i--)
        {
            temp = temp -> m_prev;
        }
    }
    return temp;
}

// Declarations of non-member functions

// If seq2 is a contiguous subsequence of seq1, return the position in
// seq1 where that subsequence starts (the earliest such position if more
// than one).  If not, or if seq2 is empty, return -1.
template <typename Temp>
int subsequence(const Sequence<Temp>& seq1, const Sequence<Temp>& seq2)
{
    if(seq2.empty())
    {
        return -1;
    }
    
    for (int i = 0; i <= seq1.size() - seq2.size(); i++)
    {
        bool match = true;
        for (int j = 0; j < seq2.size(); j++)
        {
            Temp a;
            Temp b;
            seq1.get(i+j, a);
            seq2.get(j, b);
            if(a != b)
            {
                match = false;
                break;
            }
        }
        
        if(match)
        {
            return i;
        }
    }
    return -1;
}


// Set result to a Sequence that interleaves seq1 and seq2.
template <typename Temp>
void interleave(const Sequence<Temp>& seq1, const Sequence<Temp>& seq2, Sequence<Temp>& result)
{
    int resu = 0;
    Sequence<Temp> tempRes;
    int a = seq1.size();
    int b = seq2.size();
    int min = (a < b ? a : b);
    for (int i = 0; i < min; i++)
    {
        Temp tempo;
        
        seq1.get(i, tempo);
        tempRes.insert(resu, tempo);
        resu++;
        seq2.get(i, tempo);
        resu++;
    }
        
        const Sequence<Temp>& sui = (a > min ? seq1 : seq2);
        int num = (a > min ? a : b);
        for ( int j = 0; j < num; j++)
        {
            Temp var;
            sui.get(j, var);
            tempRes.insert(resu, var);
            resu++;
        }
        
        result.swap(tempRes);
        
}
    

#endif /* Sequence_hpp */
