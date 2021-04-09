
    void removeBad(list<Movie*>& li)
    {
        for(list<Movie*> :: iterator it = li.begin(); it!= li.end(); it++)
        {
            if((*it) -> rating() < 55)
            {
                list <Movie*> :: iterator tempo = it;
                delete *tempo;
                it = li.erase(it);
            }
        }
    }


