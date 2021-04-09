
#ifndef ScoreList_hpp
#define ScoreList_hpp


#include "Sequence.hpp"
#include <limits>

    const unsigned long NO_SCORE = std::numeric_limits<unsigned long>::max();

    class ScoreList
    {
        public:
        
            ScoreList();
            bool add(unsigned long score);
            bool remove(unsigned long score);
            int size() const;
            unsigned long minimum() const;
            unsigned long maximum() const;
      
        private:
        
            Sequence m_scoreList;
    };



#endif /* ScoreList_hpp */

