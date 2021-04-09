class Coord
{
    public:
    
        Coord(int rr, int cc) : m_r(rr), m_c(cc) {{}}
        int r() const { return m_r; }
        int c() const { return m_c; }
    
    private:
        int m_r;
        int m_c;
    
};


bool pathExists(char maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
    {
        return true;
    }
    Coord starting(sr, sc);
    Coord end(er, ec);
    
    Coord north(sr-1, sc);
    Coord south(sr+1, sc);
    Coord west(sr, sc+1);
    Coord east(sr, sc+1);
    

    
    if(starting.r() == end.r() && starting.c() == end.c())
    {
        return true;
    }
    maze[starting.r(), starting.c()] = '#';
    
    if(maze[north.r(), north.c()] == '.' && pathExists(maze, sr, sc, north.r(), north.c(), end.r(), end.c() ))
    {
      return true;  
    }
    
    if(maze[south.r(), south.c()] == '.' && pathExists(maze, sr, sc, south.r(), south.c(), end.r(), end.c() ))
    {
      return true;  
    }
    
    if(maze[west.r(), west.c()] == '.' && pathExists(maze, sr, sc, west.r(), west.c(), end.r(), end.c() ))
    {
      return true;  
    }
    if(maze[east.r(), east.c()] == '.' && pathExists(maze, sr, sc, east.r(), east.c(), end.r(), end.c() ))
    {
      return true;  
    }

    return false;
}
