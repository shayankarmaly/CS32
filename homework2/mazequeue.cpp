/*#include <iostream>
#include <queue>

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
    std::queue<Coord> queueCoord;
    Coord starting(sr,sc);
    queueCoord.push(starting);
    maze[sr][sc] = '#';
    
    while(!queueCoord.empty())
    {
        Coord first = queueCoord.front();
        
        Coord north(first.r()-1, first.c());
        Coord south(first.r()+1, first.c());
        Coord west(first.r(), first.c()-1);
        Coord east(first.r(), first.c()+1);
        
        queueCoord.pop();
        
        if(first.r() == er && first.c() == ec)
        {
            return true;
        }
        
        
        if(maze[north.r()][north.c()] == '.')
        {
            queueCoord.push(north);
            
            maze[north.r()][north.c()] = '#';
        }
    
        if(maze[east.r()][east.c()] == '.')
        {
            queueCoord.push(east);
        
            maze[east.r()][east.c()] = '#';
        }
          
        if(maze[south.r()][south.c()] == '.')
        {
            queueCoord.push(south);
            maze[south.r()][south.c()] = '#';
        }
                        
                        
        if(maze[west.r()][west.c()] == '.')
        {
            queueCoord.push(west);
    
            maze[west.r()][west.c()] = '#';
        }
      
    }
    return false;
}
*/
