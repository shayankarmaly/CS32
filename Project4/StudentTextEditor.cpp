#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo), m_row(0), m_column(0)
{
    m_line.push_back("");
    currentRow = m_line.begin();
}

StudentTextEditor::~StudentTextEditor()
{
	// TODO
}

bool StudentTextEditor::load(std::string file)
{
    ifstream infile(file);
    
    if(!infile)
    {
        return false; // do nothing if file cannot be opened
    }
    
    reset(); // reset old contents if currently editing an existing file
    
    string temp;
    while (getline(infile, temp))
    {
        if(temp.back() == '\r' && !temp.empty())
        {
            temp.pop_back();
        }
        
        m_line.push_back(temp);
    }
    
    currentRow = m_line.begin();
    
    
    return true;
}

bool StudentTextEditor::save(std::string file)
{
    ofstream outfile(file);
    if(!outfile)
    {
        return false; // do nothing if file cannot be opened
    }
    
    auto it = m_line.begin();
    for(int i = 0; i < m_line.size() && it != m_line.end(); i++)
    {
        outfile << *it << endl; // saving contents to the new file and adds a new line after each line
        it++;
    }
    return true;
}

void StudentTextEditor::reset()
{
	while(!m_line.empty())
    {
        m_line.pop_back();
    }
    
    currentRow = m_line.begin();
    m_row = 0;
    m_column = 0;
    if(getUndo() != nullptr)
    {
        getUndo() -> clear();
    }
}

void StudentTextEditor::move(Dir dir)
{
    size_t newSize = 0;
    
    switch(dir)
    {
        case Dir :: UP:
            if((m_row = 0))
            {
                return; // just return if the program finds itself on the first row
            }
            // cursor gets moved up a row and checks if the line above it is longer then it moves the cursor at the end of the line above it.
            currentRow--;
            newSize = (*currentRow).size();
            
            if (newSize < m_column)
            {
                m_column = newSize;
            }
            m_row--;
            break;
            
            
        case Dir :: DOWN:
            if(currentRow == m_line.end() || m_row == m_line.size() - 1)
            {
                return; // base case to check if the cursor is on the last row
            }
            // if doesn't return from base case, move the cursor down one row and check if the line below it is longer than the line its currently on and move the cursor to the end of the line below
            currentRow++;
            newSize  = (*currentRow).size();
            
            if(newSize < m_column)
            {
                m_column = newSize;
            }
            
            m_row++;
            break;
            
        case Dir::LEFT:
            if(m_column == 0 && m_row == 0)
            {
                return; // base case to check if the cursor is at the start of the file
            }
            // checks if the position is already on the first charcter of the line, if so move the cursor behind the last charcter of the line before it
            else if(m_column == 0)
            {
                m_row--;
                currentRow--;
                m_column = (*currentRow).size();
            }
            
            else
            {
                m_column--;
            }
            
            break;
            
            
        case Dir::RIGHT:
            if(m_column == (*currentRow).size() && m_row == m_line.size() - 1)
            {
                return; // base case to check if the cursor is after the last letter of the last line
            }
            // checks if the position is after the last character in the line, if so move to the first character of the next line
            else if(m_column == (*currentRow).size())
            {
                m_row++;
                currentRow++;
                m_column = 0;
            }
            
            else
            {
                m_column++;
            }
            
            break;
            
            
        case Dir::HOME:
            m_column = 0; // first character in the line
            break;
            
        case Dir::END:
            m_column = (*currentRow).size(); // last character in the line
            
    }
}


void StudentTextEditor::del()
{
	if(m_column != (*currentRow).size())
    { 
        char a = (*currentRow).at(m_column);
        (*currentRow).erase((*currentRow).begin() + m_column);
        getUndo() -> submit(Undo::Action::DELETE, m_row, m_column, a);
    }
    
    else // merge
    {
        if (m_row == m_line.size() - 1)
        {
            return;
        }
        
        auto it = currentRow;
        it++;
        
        (*currentRow).append(*it);
        m_line.erase(it);
        
        getUndo() -> submit(Undo::Action::JOIN, m_row, m_column);
    }
}

void StudentTextEditor::backspace()
{
	if(m_row == 0 && m_column == 0) // invalid to backspace if true
    {
        return;
    }
    
    else if(m_column > 0)
    {
        char a = (*currentRow).at(m_column - 1);
        (*currentRow).erase((*currentRow).begin() + m_column - 1);
        
        m_column--;
        getUndo() -> submit(Undo::Action::DELETE, m_row, m_column, a);
    }
    
    else if(m_column == 0)
    {
        //merge
        auto it = currentRow;
        
        string below = *it;
        it--;
        
        m_column = (*it). size();
        
        (*it).append(below);
        m_row--;
        currentRow--;
        auto remove = currentRow;
        remove++;
        
        m_line.erase(remove);
        getUndo() -> submit(Undo::Action::JOIN, m_row, m_column);
    }
}

void StudentTextEditor::insert(char ch)
{
	if(ch == '\t') // checks if the tab key is pressed
    {
        for (int k = 0; k<4;k++)
        {
            justInsert(' '); // adds for empty spaces
        }
    }
    
    else
    {
        justInsert(ch);
    }
}


void StudentTextEditor::enter()
{
	// split up the line into two
    getUndo() -> submit(Undo::Action::SPLIT, m_row, m_column);
    string after = (*currentRow).substr(m_column);
    string before = (*currentRow).substr(0,m_column);
    
    *currentRow = before;
    auto it = currentRow;
    it++;
    
    m_line.insert(it, after);
    m_row++;
    currentRow++;
    m_column = 0;
}

void StudentTextEditor::getPos(int& row, int& col) const
{
	row = m_row; col = m_column;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const
{
	if (numRows < 0 || startRow > lines.size() || startRow < 0)
    {
        return -1;
    }
    
    int dist = abs(m_row - startRow);
    auto it = currentRow;
    
    while(dist > 0)
    {
        if(m_row < startRow)
        {
            it++;
        }
        
        else
        {
            it--;
        }
        
        dist--;
    }
    
    for (int k = 0; k!= m_line.size();k++)
    {
        lines.pop_back(); // to clear data
    }
    
    if(startRow == m_line.size())
    {
        return 0; // invalid to start here
    }
    
    for(int i = 0; i < numRows && it != m_line.end(); i++)
    {
        lines.push_back(*it);
        it++;
    }
    
    return lines.size();
}

void StudentTextEditor::undo()
{
    int row = 0; int column = 0; int tracker = 0;
    string txt = "";
    
    Undo::Action act = getUndo() -> get(row, column, tracker, txt); // returns the top of the undo stack
    int dist = abs(m_row - row);
    
    if(act == Undo::Action::ERROR)
    {
        return;
    }
    
    while(dist > 0)
    {
        if (m_row < row)
        {
            currentRow++;
        }
        
        else
        {
            currentRow--;
        }
        
        dist--;
    }
    m_row = row; m_column = column;
}

void StudentTextEditor::justInsert(char a)
{
    (*currentRow).insert((*currentRow). begin() + m_column, a);
    
    m_column++;
    getUndo() -> submit(Undo::Action::INSERT, m_row, m_column, a);
}


