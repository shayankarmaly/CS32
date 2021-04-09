#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
#include <sstream>
#include <iomanip>


using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath)
{
}
// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp


StudentWorld::~StudentWorld()
{
    cleanUp();
}

double StudentWorld :: degreeToRadians(double deg)
{
    return deg / 180 * 3.1415;
}

double StudentWorld :: radiansToDegree(double rad)
{
    return rad / 3.1415 * 180;
}

double StudentWorld :: distance(double x, double y, double a, double b)
{
    return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

void StudentWorld :: randomPoint( int &x, int &y)
{
    int theta = randInt(0, 359);
        x = graph -> getRadius() * cos(theta) + VIEW_WIDTH / 2;
        y = graph -> getRadius() * sin(theta) + VIEW_HEIGHT / 2;
}

int StudentWorld::init()
{
   
    
    struct Coord
    {
        int x;
        int y;
    };
    int level = getLevel();     
        
        ghost = new GhostRacer(this, 128 ,32);
    
    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new HumanPedestrian(this,x,y));
    }
    
    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new ZombiePedestrian(this,x,y));
    }
    
    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new ZombieCab(this,x,y));
    }
    
    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        
        actors.push_back(new Spray(this,x,y, 0));
    }
    
   for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new OilSlick(this,x,y));
    }

    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new HealingGoodie(this,x,y));
    }
    
    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new HolyWaterGoodie(this,x,y));
    }
    
    for (int i = 0; i < level; i++)
    {
        int x, y;
        randomPoint(x, y);
        
        actors.push_back(new SoulGoodie(this,x,y));
    }
    
    
    for (int i = 0; i < level; i++)
    {
        int x = -4;
        int y = 32;
        actors.push_back(new BorderLine(this,x,y, true));
    }
    
    for (int i = 0; i < level; i++)
    {
        int x = -4;
        int y = 32;
        actors.push_back(new BorderLine(this,x,y, false));
    }
    
   
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::addActor(Actor* a)
{
    actors.push_back(a);
}


GhostRacer* StudentWorld :: getGhostRacer()
{
    return ghost;
}

bool StudentWorld :: overlaps (const Actor* a1, const Actor* a2)
{
    for(list<Actor*>::iterator it = actors.begin(); it!= actors.end(); it++)
    {
        if(*it == a1)
            continue;
        if((*it) -> isDead())
            continue;
        double new_x = (*it) -> getX();
        double new_y = (*it) -> getY();
        
        distance(a1-> getX(), a1-> getY(), new_x, new_y);
        return true;
    }
    return false;
}

void StudentWorld::cleanUp()
{
    delete ghost;
    for(list<Actor*>::iterator it = actors.begin(); it!= actors.end();)
    {
        delete *it;
        auto toErase = it;
        it++;
        actors.erase(toErase);
    }
}

GhostRacer* StudentWorld :: getOverlappingGhostRacer(Actor*a)
{
    if(overlaps(ghost, a))
    {
        return ghost;
    }
    return nullptr;
}

bool StudentWorld :: sprayFirstAppropriateActor(Actor* a)
{
    if(getOverlappingGhostRacer(a))
    {
        a -> beSprayedIfAppropriate();
        return true;
    }
    return false;
}

void StudentWorld :: recordSoulSaved()
{
    m_recordSoul+= 1;
}

int StudentWorld :: getRecordSoulSaved()
{
    return m_recordSoul;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    double sze = actors.size();
    ghost -> doSomething();
    
    list<Actor*>::iterator it = actors.begin();
    for (int i = 0; i < sze + 1; i++)
    {
        if((getLevel() * 2 ) + 5)
        {
            return GWSTATUS_FINISHED_LEVEL;
        }
        
        if(ghost -> isDead())
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        
        if (i == sze)
        {
            break;
        }
        
        (*it) -> doSomething();
        it++;
    }
    
    ostringstream sb;
    
    sb << "Score: " << setw(6) << setfill('0') << internal << ghost -> getScore()
    << "  Level: " << getLevel()
    << "  Souls2Save: " << (getRecordSoulSaved() - (2*getLevel())+ 5)
    << "   Lives: "<< getLives()
    << "  Health: " << ghost -> getHP()
    << "  Sprays : " << ghost -> getNumSprays()
    << "  Bonus: " ;
    
    setGameStatText(sb.str());
    
    return GWSTATUS_CONTINUE_GAME;
}
