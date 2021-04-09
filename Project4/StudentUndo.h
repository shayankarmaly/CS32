#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <stack>
#include <list>
#include <queue>

class StudentUndo : public Undo
{
    public:

        void submit(Action action, int row, int col, char ch = 0);
        Action get(int& row, int& col, int& count, std::string& text);
        void clear();

    private:

        struct Comm
        {
            Comm(Action a, int row) : act(a), m_row(row), tracker(0) {}
            
            std::list<char> redo; // tracks how many chars were deleted to undo
            int tracker; // tracks how many chars were deleted to insert
            int m_row; // tracks the row the action was done
            std::queue <int> column;
            Action act; // tracks actions done
        };
    // undo comm stack
    std::stack<Comm> m_comm;
};

#endif // STUDENTUNDO_H_
