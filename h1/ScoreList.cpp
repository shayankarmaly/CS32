
#include "ScoreList.hpp"
   
        ScoreList::ScoreList()
        {
            
        }

        bool ScoreList::add(unsigned long score)
        {
            int valid = 0;
            if(score >= 0 && score <= 100)
            {
                valid = m_scoreList.insert(m_scoreList.size(), score);
                return true;
            }
            return false;
        }

        bool ScoreList::remove(unsigned long score)
        {
            for(int i = 0; i < m_scoreList.size(); i++)
            {
                unsigned long temp;
                m_scoreList.get(i, temp);
                if(temp == score)
                {
                    m_scoreList.erase(i);
                    return true;
                }
            }
            return false;
        }

        int ScoreList::size() const
        {
            return m_scoreList.size();
        }

        unsigned long ScoreList::minimum() const
        {
            if (m_scoreList.empty())
                return NO_SCORE;
            
            unsigned long min;
            unsigned long current;
            m_scoreList.get(0, min);
            
            
            
            for(int i = 1; i < m_scoreList.size(); i++)
            {
                m_scoreList.get(i, current);
                if(current < min)
                    min = current;
            }
            return min;
        }
        
          

        unsigned long ScoreList::maximum() const
        {
            if (m_scoreList.empty())
                return NO_SCORE;
            
            unsigned long max;
            unsigned long current;
            m_scoreList.get(0, max);
            
            for(int i = 1; i < m_scoreList.size(); i++)
            {
                m_scoreList.get(i, current);
                if(current > max)
                    max = current;
            }
            return max;
        }

