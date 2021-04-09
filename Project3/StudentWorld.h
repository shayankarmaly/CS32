#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GraphObject.h"
#include "Actor.h"
#include <string>
#include <list>


using namespace std;
class Actor;
class GhostRacer;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    GameWorld* createStudentWorld(string assetPath);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();

      // Return a pointer to the world's GhostRacer.
    GhostRacer* getGhostRacer();

      // Add an actor to the world.
    void addActor(Actor* a);

      // Record that a soul was saved.
    void recordSoulSaved();

      // If actor a overlaps some live actor that is affected by a holy water
      // projectile, inflict a holy water spray on that actor and return true;
      // otherwise, return false.  (See Actor::beSprayedIfAppropriate.)
    bool sprayFirstAppropriateActor(Actor* a);

      // Return true if actor a1 overlaps actor a2, otherwise false.
    bool overlaps(const Actor* a1, const Actor* a2);

      // If actor a overlaps this world's GhostRacer, return a pointer to the
      // GhostRacer; otherwise, return nullptr
    GhostRacer* getOverlappingGhostRacer(Actor* a);
    
    void randomPoint(int &x, int &y);
    
    double degreeToRadians(double deg);
    
    double radiansToDegree(double rad);
    
    double distance(double x, double y, double a, double b);
    
    int getRecordSoulSaved();

    
private:
    GhostRacer* ghost;
    GameWorld* gme;
    list<Actor*> actors;
    int m_recordSoul;
    GraphObject* graph;
};

#endif // STUDENTWORLD_H_

