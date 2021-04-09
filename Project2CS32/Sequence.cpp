
#include "Sequence.hpp"
#include <iostream>


using namespace std;


Sequence::Sequence() // default constructor sets the head and tail pointer to nullptr and the size to 0 by default
{
    this -> m_size = 0;
    this -> head = nullptr;
    this -> tail = nullptr;
}


Sequence::~Sequence() // destructor
{
    if (!empty()) // condition to make sure not empty
    {
        Node* current = head; // keeps a local node pointer variable and assigns it to head
        while(current != nullptr) // condition making sure that current is not nullptr
        {
            Node* next = current -> next; // assigns a local Node pointer 'next' and takes the next value that current points to.
            delete current; // avoids memory leak here
            current = next;
        }
        
    }
    // default assignments
    m_size = 0;
    head = nullptr;
    tail = nullptr;
        
}

// copy constructor
Sequence::Sequence(const Sequence &src)
{
    if(src.head == nullptr) // checks if the head src points to is nullptr and if it does, it does the following:
    {
        m_size = 0;
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    m_size = 0;
    this -> head = nullptr;
    this -> tail = nullptr;
    
    int thisSize = src.size(); // copys src's size into a local size variable so we know how many nodes to allocate for the copied linked list
    // copying each element into the new list
    for (int j = 0; j < thisSize; j++)
    {
        ItemType local;
        src.get(j, local);
        insert(j, local);
    }
}

//assignment operator
Sequence &Sequence :: operator = (const Sequence &src)
{
    if(this == &src)
        return *this;
    
    Sequence temp(src); // making a temp to hold src's values so we can eventually swap
    this -> swap(temp); // swap the temp values with 'this' values
    return *this; // make sure to return a pointer
    
}

int Sequence:: size() const
{
    return m_size;
}

bool Sequence :: empty() const // returns true if head and tail are nullptr and the size is 0
{
    if (m_size == 0 && head == nullptr && tail == nullptr)
        return true;
    
    return false;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if( pos < 0 || pos > m_size) // condition that executes to initialize a new doubly linked list
        return -1;
    
    if (head == nullptr && pos == 0)
    {
        Node* local = new Node;
        local -> count = value;
        head = local;
        tail = local;
        
        local->prev = nullptr;
        local->next = nullptr;
    }
    
    else if(pos == m_size) // condition that executres to insert at the end of the doubly linked list.
    {
        Node* local = new Node;
        local -> count = value;
        local -> next = nullptr;
        
        //        Node* move = head;
        //        while (move->next != nullptr)
        //        {
        //            move = move->next;
        //        }
        local -> prev = tail;
        tail -> next = local;
        tail = local;
    }
    
    else if(head!= nullptr && pos ==0)
    {
        Node* local = new Node;
        local -> count = value;
        
        int keep = 0;
        Node* transit = head;
        
        while(keep!= pos)
        {
            transit = transit->next;
            keep++;
        }
        local->next = transit;
        local->prev = transit->prev;
        transit->prev->next = local;
        transit->prev = local;
    }
    m_size++;
    return pos;
    
}

int Sequence::insert(const ItemType& value)
{
    Node* transit = head;
    int num = 0;
    
    if(m_size == 0 && head == nullptr) // checks if its an empty list and if so adds to the beginning
        return(insert(0, value));
    
    while(transit!=nullptr) // iterates through the doubly linked list if its not empty
    {
        if(value<= transit->count) // checks the list if there is an instance where value is less than or equal to an element
            break;
        
        num++;
        transit = transit->next;
    }
    
    insert(num, value);
    return num;
}

bool Sequence:: get(int pos, ItemType& value) const
{
    if (pos >= m_size || pos<0) // if one of these conditions true, return false
        return false;
    
    int keep;
    Node* transit = head;
    
    for (keep = 0; keep!= pos; keep++)
        transit = transit->next;
    
    value = transit->count;
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos >= m_size || head == nullptr || pos < 0) // if one of these conditions true, return false
        return false;
    
    Node* transit = head;
    int keep = 0;
    while(keep != pos)
    {
        transit = transit-> next;
        keep++;
    }
    transit-> count = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    if(head == nullptr)// checks if its an empty list
        return -1;
    
    Node* transit = head;
    int keep = 0;
    
    while (transit != nullptr)
    {
        if(transit-> count == value)
            break;
        
        transit = transit->next;
        keep++;
    }
    
    if (keep == m_size)
        return -1;
    
    return keep;
}

void Sequence::swap(Sequence &src)
{
    //swapping current head with src's head
    Node* temp1 = head;
    head = src.head;
    src.head = temp1;
    
    //swapping current tail with src's tail
    Node* temp2 = tail;
    tail = src.tail;
    src.tail = temp2;
    
    //swapping current size with src's size
    int size = m_size;
    m_size = src.m_size;
    src.m_size = size;
}

bool Sequence::erase(int pos)
{
    if(pos >=m_size || m_size == 0 || head == nullptr || tail == nullptr) // returns false if one of these conditions are met
        return false;
    
    if(m_size == 1 && pos == 0) // deleting the only head in the list
    {
        Node* temp = head;
        head = nullptr;
        tail = nullptr;
        
        delete temp;
        
        m_size--;
        return true;
    }
    
    else if(m_size != 0 && pos == 0) // if conditions met, delete the head pointer.
    {
        Node* temp = head;
        head = head-> next;
        head->prev = nullptr;
        
        delete temp;
        
        m_size--;
        return true;
    }
    
    else if(m_size != 0 && pos == (m_size -1)) // if conditions are met, deletes the tail pointer and checks the condition m_size-1 to find the exact element the tail is at.
    {
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        
        delete temp;
        
        m_size--;
        return true;
    }
    
    Node* transit = head;
    int keep = 0;
    
    while(keep!= pos)
    {
        transit = transit->next;
        keep++;
    }
    transit->prev->next = transit->next;
    transit->next->prev = transit -> prev;
    
    delete transit;
    
    m_size--;
    return true;
}


int Sequence::remove(const ItemType& value)
{
    int keep = 0;
    while(find(value) != -1)
    {
        erase(find(value));
        keep++;
    }
    return keep;
}
void Sequence::dump() const
{
    Node *p;

    cout << "forwards" << endl;
    p = head;
    while (p != nullptr)
    {
        cout << p->count << ":";
        p = p->next;
    }
    cout<< endl;
    
    cout << "backwards" << endl;
    p = tail;
    while (p != nullptr)
    {
        cout << p->count << ":";
        p = p->prev;
    }
    cout << endl;
}


