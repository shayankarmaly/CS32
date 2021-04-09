
      // Remove the odd integers from v.
      // It is acceptable if the order of the remaining even integers is not
      // the same as in the original vector.
    void removeOdds(vector<int>& v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if(v.at(i) % 2 != 0)
            {
                v.erase(v.begin() + i);
                i--;
            }
        }
        
    }
