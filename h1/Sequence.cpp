
#include "Sequence.hpp"
#include <iostream>



Sequence::Sequence()  // Create an empty sequence (i.e., one with no items)
{
    m_size = 0;
}



    bool Sequence::empty() const // Return true if the sequence is empty, otherwise false.
    {
        if(m_size == 0)
        {
            return true;
        }
        return false;
    }

    int Sequence::size() const   // Return the number of items in the sequence.
    {
        return m_size;
    }




    int Sequence::insert(int pos, const ItemType& value)
    {
        if (pos >= 0 && m_size < DEFAULT_MAX_ITEMS && pos <= m_size)
        {
            for (int i = m_size; i > pos; i--)
            {
                m_array[i] = m_array[i-1];
            }
        
            m_array[pos] = value;
            m_size++;

        return pos;
        }
        return -1;
    }
 

    int Sequence::insert(const ItemType& value)
    {
        int pos = m_size;
        for (int i = 0; i < m_size; i++)
        {
            if (value < m_array[i])
            {
                pos = i;
                break;
            }
        }
        return insert(pos,value);
    }
     
     
    bool Sequence::erase(int pos)
    {
        if (pos >= 0 && m_size <= DEFAULT_MAX_ITEMS && pos < m_size)
        {
            for (int i = pos; i < (m_size-1); i++)
            {
                m_array[i] = m_array[i+1];
            }
            m_size--;
            return true;
        }
        
        return false;
    }
      
    int Sequence::remove(const ItemType& value)
    {
        int rem = 0;
        
        for (int i = 0; i < m_size; i++)
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
        if(pos >= 0 && pos < m_size)
        {
            value = m_array[pos];
            return true;
        }
        
        return false;
    }

    bool Sequence::set(int pos, const ItemType& value)
    {
        if(0 <= pos && pos < size())
        {
            m_array[pos] = value;
            return true;
        }
        
        return false;
    }

    int Sequence::find(const ItemType& value) const
    {
        for (int p = 0; p < m_size; p++)
        {
            if(m_array[p] == value)
                return p;
        }
        
        return -1;
    }


    void Sequence::swap(Sequence& other)
    {
        int thism_size = m_size;
        int otherm_size = other.m_size;
        
        int fin = thism_size;
        
        if(otherm_size > thism_size)
            fin = otherm_size;
        
        for (int i = 0; i < fin; i++)
        {
            ItemType temp;
            temp = other.m_array[i];
            other.m_array[i] = m_array[i];
            m_array[i] = temp;
        }
        
        m_size = otherm_size;
        other.m_size = thism_size;
    }
      

