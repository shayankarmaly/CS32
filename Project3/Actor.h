#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

const int MAX_HOLY_WATER_SPRAYS = 10;
class StudentWorld;

class Actor : public GraphObject
{
    public:
        Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth);

      // Action to perform for each tick.
        virtual void doSomething() = 0;

      // Is this actor dead?
        bool isDead() const;
    
      // Mark this actor as dead.
        void setDead();

      // Get this actor's world
        StudentWorld* world() const;

      // Get this actor's vertical speed.
        double getVerticalSpeed() const;

      // Set this actor's vertical speed.
        void setVerticalSpeed(double speed);
    
        void setHorizontalSpeed(double speed);
    
        double getHorizontalSpeed() const;

    
        void isAlive();

      // If this actor is affected by holy water projectiles, then inflict that
      // affect on it and return true; otherwise, return false.
        virtual bool beSprayedIfAppropriate();

      // Does this object affect zombie cab placement and speed?
        virtual bool isCollisionAvoidanceWorthy() const;

    
        virtual bool isDamageable();
    
        virtual void damageActor(int damage);
    
        virtual void setScore(int score);
    
        virtual int getScore() const;
    
        GraphObject* getGme() const;
    
    private:
        StudentWorld* m_ptr;
        int m_health;
        bool m_dead;
        bool m_alive;
        double m_verticalSpeed;
        double m_horizontalSpeed;
        int m_score;
        GraphObject* gme;
    

};

class Agent : public Actor
{
    public:
        Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp);

        // Get hit points.
        virtual int getHP() const;

        // Increase hit points by hp.
        virtual void getHP(int hp);

        // Do what the spec says happens when hp units of damage is inflicted.
        // Return true if this agent dies as a result, otherwise false.
        virtual bool takeDamageAndPossiblyDie(int hp);

        // What sound should play when this agent is damaged but does not die?
        virtual int soundWhenHurt();

        // What sound should play when this agent is damaged and dies?
        virtual int soundWhenDie();
        
    
        Actor* getAct();
    
    
        virtual void setHP(int hp);
    
    private:
        int m_hp;
        Actor* act;
        Agent* spy;
};

class BorderLine : public Actor
{
    public:
        BorderLine(StudentWorld* sw, double x, double y, bool isYellow);
        virtual void doSomething();
};

class GhostRacer : public Agent
{
    public:
        GhostRacer(StudentWorld* sw, double x, double y);
        virtual void doSomething();
        virtual int soundWhenDie() const;

        // How many holy water projectiles does the object have?
        int getNumSprays() const;

        // Increase the number of holy water projectiles the object has.
        void increaseSprays(int amt);

        // Spin as a result of hitting an oil slick.
        void spin();
        virtual void setHolyWaterSprays(int sprays);
    
       
    void moveHere(int deg);
    
    private:
        int m_holyWaterSpraysLeft;
        double angle;
};

class Pedestrian : public Agent
{
public:
    Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size);
    virtual int soundWhenHurt() const;
    virtual int soundWhenDie() const;

     

      // Move the pedestrian.  If the pedestrian doesn't go off screen and
      // should pick a new movement plan, pick a new plan.
    void moveAndPossiblyPickPlan();
};

class HumanPedestrian : public Pedestrian
{
public:
    HumanPedestrian(StudentWorld* sw, double x, double y);
    virtual void doSomething();
    virtual bool beSprayedIfAppropriate();
    virtual bool takeDamageAndPossiblyDie(int hp);
    
};

class ZombiePedestrian : public Pedestrian
{
public:
    ZombiePedestrian(StudentWorld* sw, double x, double y);
    virtual void doSomething();
    virtual bool beSprayedIfAppropriate();
    
};

class ZombieCab : public Agent
{
    public:
        ZombieCab(StudentWorld* sw, double x, double y);
        virtual void doSomething();
        virtual bool beSprayedIfAppropriate();
    
    private :
        int damageCount;
};


class Spray : public Actor
{
public:
    Spray(StudentWorld* sw, double x, double y, int dir);
    virtual void doSomething();
};








class GhostRacerActivatedObject : public Actor
{
public:
    GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir);
    virtual bool beSprayedIfAppropriate();
      // Do the object's special activity (increase health, spin Ghostracer, etc.)
    virtual void doActivity(GhostRacer* gr) = 0;

      // Return the object's increase to the score when activated.
    virtual int getScoreIncrease() const = 0;

      // Return the sound to be played when the object is activated.
    virtual int getSound() const;

      // Return whether the object dies after activation.
    virtual bool selfDestructs() const = 0;

      // Return whether the object is affected by a holy water projectile.
    virtual bool isSprayable() const = 0;
    
};










class OilSlick : public GhostRacerActivatedObject
{
public:
    OilSlick(StudentWorld* sw, double x, double y);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual int getSound() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
};









class HealingGoodie : public GhostRacerActivatedObject
{
public:
    HealingGoodie(StudentWorld* sw, double x, double y);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
};










class HolyWaterGoodie : public GhostRacerActivatedObject
{
public:
    HolyWaterGoodie(StudentWorld* sw, double x, double y);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
};










class SoulGoodie : public GhostRacerActivatedObject
{
public:
    SoulGoodie(StudentWorld* sw, double x, double y);
    virtual void doSomething();
    virtual void doActivity(GhostRacer* gr);
    virtual int getScoreIncrease() const;
    virtual int getSound() const;
    virtual bool selfDestructs() const;
    virtual bool isSprayable() const;
};

#endif // ACTOR_H_
