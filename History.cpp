#include "History.h"


#include <iostream>

using namespace std;

History :: History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            m_record[i][j] = '.';
            
        }
    }
}


bool History :: record(int r, int c)
{
    if (r < 1 || r < m_rows || c < 1 || c < m_cols)
    {
        return false;
    }
    
     if (m_record[r-1][c-1] == '.')
     {
        m_record[r-1][c-1] = 'A';
     }

    else if (m_record[r-1][c-1] != 'Z')
    {
        m_record[r-1][c-1] += 1;
    }
    return true;
    
}


void History :: display() const
{
    clearScreen();
    
    for (int i = 0; i <m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            cout << m_record[i][j];
           /* if (m_record[i][j] == 0)
            {
                cout << '.';
            }
            else if (m_record[i][j] >= 26)
            {
                cout << 'Z';
            }
            else
            {
                char disp = 'A' + m_record[i][j] - 1;
                cout << disp;
            }*/
        }
        cout << endl;
    }
    cout << endl;
}
