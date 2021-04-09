#include "StudentUndo.h"
#include <queue>
#include <list>
#include <stack>

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch)
{
	if(m_comm.empty()) // only executes if the stack is empty
    {
        Comm newComm(action, row);
        newComm.column.push(col);
        
        newComm.redo.push_back(ch);
        m_comm.push(newComm);
        
        return;
    }
    
    Comm& topComm = m_comm.top();
    
    switch(action) // cases checked for either deletion or insertion 
    {
        case Undo::Action::INSERT:
        
            if(col == topComm.column.back() + 1 && action == topComm.act && row == topComm.m_row)
            {
                topComm.column.push(col);
                topComm.tracker += 1;
                return;
            }
            break;
            
        case Undo::Action::DELETE:
            if (row == topComm.m_row && action == topComm.act)
            {
                if((col = topComm.column.back()))
                {
                    topComm.column.push(col);
                    topComm.redo.push_back(ch);
                    return;
                }
                
                if(col == topComm.column.back() - 1)
                { // reverse characters
                    topComm.column.push(col);
                    topComm.redo.push_front(ch);
                    return;
                }
            }
            break;
          
        default:
            break;
    }
    
    // if no case was found...
    
    Comm newComm(action, row);
    newComm.column.push(col);
    
    newComm.tracker +=1;
    newComm.redo.push_back(ch);
    m_comm.push(newComm);
}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text)
{
    
    if(m_comm.empty())
    {
        return Action::ERROR;
    }
    count = 1;
    Comm top = m_comm.top();
    row = top.m_row;
    text = "";
    Action undo = Action::ERROR;
    col = top.column.back();
    // defualt values
    
    switch(top.act)
    {
        case Undo::Action::INSERT:
        {
            undo = Undo::Action::DELETE;
            col = top.column.front() - 1;
            count = top.tracker;
            break;
        }
            
        case Undo::Action::DELETE:
        {
            undo = Undo::Action::INSERT;
            for(std::list<char> ::iterator iter = top.redo.begin(); iter != top.redo.end(); iter++)
            {
                text += (*iter);
            }
            break;
        }
            
        case Undo :: Action::SPLIT:
        {
            undo = Undo::Action::JOIN;
            break;
        }
            
        case Undo::Action::JOIN:
        {
            undo = Undo::Action::SPLIT;
            break;
        }
        case Undo::ERROR: {
            break;
        }
    }
    
    m_comm.pop();
    return undo;
    
}

void StudentUndo::clear()
{
    while (!m_comm.empty())
    {
        m_comm.pop(); // keeps deleting while not empty
    }
}
