#include "newSequence.hpp"
#include <iostream>
#include <cstdlib>


    Sequence::Sequence()
    {
        m_current = 0;
        m_max = DEFAULT_MAX_ITEMS;
    }

    Sequence::Sequence(int num)
    {
        
        
        if (num < 0 )
            exit(0);
        m_max = num;
        m_array = new ItemType[m_max];
        m_current = 0;
                
    }

    Sequence& Sequence :: operator = (const Sequence &src)
    {
        if(this==&src)
        {
            return *this;
        }
       
        delete[] m_array;

        m_max = src.m_max;
        m_current = src.m_current;
        
        m_array = new ItemType[src.m_max];
        
        for (int i = 0; i < src.m_current;i++)
            m_array[i] = src.m_array[i];
        
        return *this;
        
    }
    Sequence::Sequence(const Sequence &src)
    {
        m_current = src.m_current;
        m_max = src.m_max;
        
        m_array = new ItemType[m_max];
        
        for (int j = 0; j < m_current; j++)
            m_array[j] = src.m_array[j];
        
    }
Sequence::~Sequence()
{
    delete [] m_array;
}

bool Sequence::empty() const // Return true if the sequence is empty, otherwise false.
{
    if(m_current == 0)
    {
        return true;
    }
    return false;
}

int Sequence::size() const   // Return the number of items in the sequence.
{
    return m_current;
}


int Sequence::insert(int pos, const ItemType& value)
{
    if (pos >= 0 && m_current < m_max && pos <= m_current)
    {
        for (int i = m_current; i > pos; i--)
        {
            m_array[i] = m_array[i-1];
        }
    
        m_array[pos] = value;
        m_current++;

    return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value)
{
    int pos = m_current;
    for (int i = 0; i < m_current; i++)
    {
        if (value < m_array[i])
        {
            pos = i;
            break;
        }
    }
    return insert(pos,value);
}
        
bool Sequence:: erase(int pos)
{
    if (pos >= 0 && m_current <= DEFAULT_MAX_ITEMS && pos < m_current)
    {
        for (int i = pos; i < (m_current-1); i++)
        {
            m_array[i] = m_array[i+1];
        }
        m_current--;
        return true;
    }
    
    return false;
}
        
int Sequence::remove(const ItemType& value)
{
    int rem = 0;
    
    for (int i = 0; i < m_current; i++)
    {
        if(m_array[i] == value)
        {
            erase(i);
            i--;
            rem++;
        }
    }
    return rem;
}
        
bool Sequence::get(int pos, ItemType& value) const
{
    if(pos >= 0 && pos < m_current)
    {
        value = m_array[pos];
        return true;
    }
    
    return false;
}
        
bool Sequence::set(int pos, const ItemType& value)
{
    if(0 <= pos && pos < m_current)
    {
        m_array[pos] = value;
        return true;
    }
    
    return false;
}
        
int Sequence::find(const ItemType& value) const
{
    for (int p = 0; p < m_current; p++)
    {
        if(m_array[p] == value)
            return p;
    }
    
    return -1;
}
        
void Sequence::swap(Sequence& other)
{
    int currentTemp = other.m_current;
    other.m_current = m_current;
    m_current = currentTemp;
    
    int maxTemp = other.m_max;
    other.m_max = m_max;
    m_max = maxTemp;
    
    ItemType* arrayTemp = other.m_array;
    other.m_array = m_array;
    m_array = arrayTemp;
}
    
    
   



