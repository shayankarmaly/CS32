
#include <stack>
#include <iostream>

using namespace std;

class Coord
{
    public:
        Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
        int r() const { return m_row; }
        int c() const { return m_col; }
    private:
        int m_row;
        int m_col;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
          // Return true if there is a path from (sr,sc) to (er,ec)
          // through the maze; return false otherwise



int main()
{
    string maze[10] = {
                    "XXXXXXXXXX",
                    "X........X",
                    "XX.X.XXXXX",
                    "X..X.X...X",
                    "X..X...X.X",
                    "XXXX.XXX.X",
                    "X.X....XXX",
                    "X..XX.XX.X",
                    "X...X....X",
                    "XXXXXXXXXX"
                };

                if (pathExists(maze, 10,10, 6,4, 1,1))
                    cout << "Solvable!" << endl;
                else
                    cout << "Out of luck!" << endl;
}




bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    std::stack<Coord> stackCoord;
    
    Coord starting(sr, sc);
    
    stackCoord.push(starting);
    maze[sr][sc] = '#';
    
    while(!stackCoord.empty())  //While the stack is not empty,
                               
    {
        Coord first = stackCoord.top();
        
        Coord north(first.r()-1, first.c());
        Coord south(first.r()+1, first.c());
        Coord west(first.r(), first.c()-1);
        Coord east(first.r(), first.c()+1);
        
        stackCoord.pop();
        
        if(first.r() == er && first.c() == ec)
        {
            return true;
        }
    
            
        if(maze[north.r()][north.c()] == '.')
        {
            stackCoord.push(north);
            
            maze[north.r()][north.c()] = '#';
        }
    
        if(maze[east.r()][east.c()] == '.')
        {
            stackCoord.push(east);
        
            maze[east.r()][east.c()] = '#';
        }
          
        if(maze[south.r()][south.c()] == '.')
        {
            stackCoord.push(south);
            maze[south.r()][south.c()] = '#';
        }
                        
                        
        if(maze[west.r()][west.c()] == '.')
        {
            stackCoord.push(west);
    
            maze[west.r()][west.c()] = '#'; 
        }
      
    }
    
    return false; //There was no solution, so return false
     
}
