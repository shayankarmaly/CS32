#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor class implementations

Actor::Actor(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int depth): GraphObject(imageID, x, y, dir, size, depth)
{
    m_ptr = sw;
}

bool Actor :: isDead() const
{
    if(m_dead == true)
        return true;
    
    return false;
}

void Actor :: setDead()
{
    if(m_health < 0)
        {
            m_dead = true;
        }
}

StudentWorld* Actor:: world() const
{
    return m_ptr;
}

double Actor :: getVerticalSpeed() const
{
    return m_verticalSpeed;
}

bool Actor :: isDamageable()
{
    if(isCollisionAvoidanceWorthy())
        return true;
    
    return false;
}

void Actor :: setVerticalSpeed(double speed)
{
    m_verticalSpeed = speed;
}

void Actor :: damageActor(int damage)
{
    m_health -= damage;
}


bool Actor :: beSprayedIfAppropriate()
{
    if(isDamageable())
    {
        damageActor(1);
        return true;
    }
    return false;
}

bool Actor :: isCollisionAvoidanceWorthy() const
{
    return true;
}

void Actor :: setHorizontalSpeed(double speed)
{
    m_horizontalSpeed = speed;
}

void Actor :: isAlive()
{
    m_alive = true;
}

double Actor:: getHorizontalSpeed() const
{
    return m_horizontalSpeed;
}

void Actor :: setScore(int score)
{
    m_score = score;
}

int Actor :: getScore() const
{
    return m_score;
}

GraphObject* Actor :: getGme() const
{
    return gme;
}

BorderLine::BorderLine(StudentWorld* sw, double x, double y, bool isYellow) : Actor(sw, IID_YELLOW_BORDER_LINE , x, y, 2.0 , 0, 2)
{
    if(isYellow == false)
    {

    }
    setHorizontalSpeed(0);
    setVerticalSpeed(-4);
    isAlive();
    
}

void BorderLine :: doSomething()
{
    setVerticalSpeed(getVerticalSpeed());
    int vert_speed = getVerticalSpeed();
    int horiz_speed = getHorizontalSpeed();
    
    int new_y = getY() + vert_speed;
    int new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
    
    if(new_x < 0 || new_y < 0 || new_x > VIEW_WIDTH || new_y > VIEW_HEIGHT)
    {
        isDead();
        return;
    }
    
}

Agent::Agent(StudentWorld* sw, int imageID, double x, double y, double size, int dir, int hp) :
Actor(sw, imageID, x, y, dir,0, size)
{
}

Actor* Agent :: getAct()
{
    return act;
}


int Agent :: getHP() const
{
    return m_hp;
}

void Agent :: getHP(int hp)
{
    m_hp += hp;
}


bool Agent:: takeDamageAndPossiblyDie(int hp)
{
    m_hp -= hp;
    if(m_hp <= 0)
        return true;
    
    return false;
}

void Agent :: setHP(int hp)
{
    m_hp = hp;
}

int Agent :: soundWhenHurt()
{
    return 0;
}

int Agent :: soundWhenDie()
{
    return 0;
}

GhostRacer::GhostRacer(StudentWorld* sw, double x, double y) : Agent(sw, IID_GHOST_RACER, x, y, 4.0, 90, 100)
{
    setHP(100);
    setVerticalSpeed(0);
    isCollisionAvoidanceWorthy();
    m_holyWaterSpraysLeft = MAX_HOLY_WATER_SPRAYS;
    isDamageable();
    isAlive();
}


int GhostRacer::getNumSprays() const
{
    return m_holyWaterSpraysLeft;
}

void GhostRacer::increaseSprays(int amt)
{
    m_holyWaterSpraysLeft += amt;
}

void GhostRacer::spin()
{
    if(world() -> getOverlappingGhostRacer(this))
    {
        setDirection(getDirection() + (rand() % 20 + 5));
    }
}

void GhostRacer::doSomething()
{
    if(isDead())
        return;
    
    if( getX() < 5) // left side boundary)
       {
           if (getDirection()< 90)
           {
               getHP(10);
               setDirection(82);
               world()->playSound(SOUND_VEHICLE_CRASH);
           }
       }
    
    if (getX() > 5) // right road boundary
    {
        if (getDirection()< 90)
        {
            getHP(10);
            setDirection(98);
            world()->playSound(SOUND_VEHICLE_CRASH);
        }
    }
    int key;
    
    if(world()-> getKey(key))
    {
        switch(key)
        {
                if(getNumSprays() > 1)
                {
                    case KEY_PRESS_LEFT:
                        moveHere(5);
                        break;
        
                    case KEY_PRESS_RIGHT:
                        moveHere(-5);
                        break;
            
                    case KEY_PRESS_SPACE:
                        //spray();
                        break;
                }
        }
    }
}

int GhostRacer:: soundWhenDie() const
{
    world()-> playSound(SOUND_PLAYER_DIE);
    return 0;
}


void GhostRacer:: moveHere(int deg)
{
    double r = getRadius();
    double delta_x = VIEW_WIDTH / 2;
    double delta_y = VIEW_WIDTH / 2;
    double rad_angle;
    
    angle += deg;
    if(angle >= 360)
    {
        angle -= 360;
    }
    
    rad_angle = world()->degreeToRadians(angle);
    moveTo(r*cos(rad_angle) + delta_x, r * sin(rad_angle) + delta_y);
    
    double dir = angle - 180;
    if(dir < 0)
    {
        dir+=360;
    }
    setDirection(dir);
}

void GhostRacer :: setHolyWaterSprays(int sprays)
{
    m_holyWaterSpraysLeft = sprays;
}

Pedestrian :: Pedestrian(StudentWorld* sw, int imageID, double x, double y, double size) : Agent(sw, imageID, x, y, size, 0, 2)
{
    isCollisionAvoidanceWorthy();
}

int Pedestrian :: soundWhenHurt() const
{
    world() -> playSound(SOUND_PED_HURT);
    return 0;
}

int Pedestrian :: soundWhenDie() const
{
    world() -> playSound(SOUND_PED_DIE);
    return 0;
}

// Move the pedestrian.  If the pedestrian doesn't go off screen and
// should pick a new movement plan, pick a new plan.
void Pedestrian :: moveAndPossiblyPickPlan()
{
    /*
    Decrement the human pedestrian’s movement plan distance.
    5. If the distance is greater than zero, then immediately return.
    6. Otherwise, it’s time to pick a new movement plan for the human pedestrian:
    a. Set the human pedestrian’s horizontal speed to a random integer from -3 to 3, inclusive, NOT including zero.
    b. Set the length of the movement plan to a random integer between 4 and 32, inclusive.
    c. Set the human pedestrian’s direction to 180 degrees if its new horizontal speed is less than zero. Otherwise set its direction to 0 degrees if its new horizontal speed is greater than zero.
    What Human Pedestrian Must Do In Other Circumstances
    ● A human pedestrian is affected by holy water. When damaged by holy water the human pedestrian will reverse its direction:
    o Ignore all hit point damage (holy water doesn’t actually injure the pedestrian)
    o Change its current horizontal speed by multiplying it by -1 (e.g., if the ped was going left at 2 pixels/tick, it must change its direction to right at 2 pixels/tick).
    o Change the direction the human is facing (e.g., from 0 to 180 degrees, or 180 degrees to 0) as appropriate.
    o The human pedestrian must play a sound of SOUND_PED_HURT.
    ● A human pedestrian cannot be damaged by any collisions with zombie peds or
    zombie cabs. The zombies will simply pass over them.
    ● A human pedestrian cannot be spun around by an oil slick.
    ● A human pedestrian cannot be healed by a specified number of hit points.
     */
}
HumanPedestrian :: HumanPedestrian(StudentWorld* sw, double x, double y) : Pedestrian(sw, IID_HUMAN_PED, x, y, 2.0)
{
    isAlive();
    isCollisionAvoidanceWorthy();
    setHorizontalSpeed(0);
    setVerticalSpeed(-4);
    setHP(2);
}

void HumanPedestrian :: doSomething()
{
    if(isDead())
        return;
    
    
    if(world()-> getOverlappingGhostRacer(this))
    {
        world() -> decLives();
        int vert_speed = getVerticalSpeed() -  getVerticalSpeed();
        int horiz_speed = getVerticalSpeed();
        int new_y = getVerticalSpeed() + vert_speed;
        int new_x = getHorizontalSpeed() + horiz_speed;
        moveTo(new_x, new_y);
        if(new_x < 0 || new_y < 0 || new_x > VIEW_WIDTH || new_y > VIEW_HEIGHT)
        {
            isDead();
            moveAndPossiblyPickPlan();
        }
        else
        {
            setHorizontalSpeed(randInt(-3, 3));
            moveAndPossiblyPickPlan();
            if(getHorizontalSpeed() < 0)
            {
                setDirection(180);
            }
            
            else
                setDirection(0);

        }
        
    }
}

bool HumanPedestrian :: beSprayedIfAppropriate()
{
    if(isDamageable())
    {
        int horiz_speed = (getHorizontalSpeed() * -1);
        setHorizontalSpeed(horiz_speed);
        
        if(getDirection() == 0)
            setDirection(180);
        
        else
            setDirection(0);
        world() -> playSound(SOUND_PED_HURT);
        
        return true;
    }
    return false;
}

bool HumanPedestrian :: takeDamageAndPossiblyDie(int hp)
{
    if((getHP() - hp) <= 0)
        return true;
    
    return false;
}

ZombiePedestrian :: ZombiePedestrian(StudentWorld* sw, double x, double y) : Pedestrian(sw, IID_ZOMBIE_PED , x, y, 3.0)
{
    setHorizontalSpeed(0);
    isCollisionAvoidanceWorthy();
    isAlive();
    setHP(2);
    setVerticalSpeed(-4);
    isDamageable();
}

void ZombiePedestrian :: doSomething()
{
    
    if(isDead())
        {
            return;
        }
    
    
    if(world()-> getOverlappingGhostRacer(this))
        {
            takeDamageAndPossiblyDie(2);
            return;
        }
    /*If the zombie pedestrian’s X coordinate is within 30 pixels of Ghost Racer’s X coordinate, either left or right, AND the zombie pedestrian is in front of the Ghost Racer on the road then:
    a. The zombie pedestrian will set its direction to 270 degrees (facing down).
    b. If the zombie ped is to the left of Ghost Racer, it will set its horizontal
    speed to 1, else if the zombie ped is to the right of Ghost Racer, it will set its horizontal speed to -1. Otherwise (they have the same X coordinate), it will set its horizontal speed to zero.
    c. The zombie ped decreases the number of ticks before it grunts next.
     If the ticks until its next grunt is less than or equal to zero, the zombie ped must:
     i. Play a sound of SOUND_ZOMBIE_ATTACK.
     ii. Reset the number of ticks before its next grunt to 20.
     The zombie pedestrian must then move, using the following algorithm:
    a.
    b. c. d. e.
    f.
    Let vert_speed = the zombie ped’s current vertical speed - Ghost Racer’s current vertical speed
    Let horiz_speed = the zombie ped’s horizontal speed
    Let new_y = zombie ped’s current y + vert_speed
    Let new_x = zombie ped’s current x + horiz_speed
    Adjust the zombie ped’s location to new_x, new_y using the GraphObject::moveTo() method.
    If the zombie pedestrian has gone off of the screen (either its X or Y coordinate is less than zero, or its X coordinate is > VIEW_WIDTH, or its Y coordinate > VIEW_HEIGHT), it must set its status to not-alive, so it will be removed by StudentWorld later in this tick. It must then immediately return.
    5. If the
    decrement it by one and immediately return.
    zombie pedestrian’s movement plan distance is greater than zero, then
    6. Otherwise, it’s time to pick a new movement plan for the zombie pedestrian:
    a. Set the zombie pedestrian’s horizontal speed to a random integer from -3
    to 3 inclusive, NOT including zero.
    b. Set the movement plan distance to a random integer between 4 and 32,
    inclusive.
    c. Set the zombie pedestrian’s direction to 180 degrees if its new horizontal
    speed is less than zero. Otherwise, set its direction to 0 degrees if its new horizontal speed is greater than zero.
     */
}


bool ZombiePedestrian :: beSprayedIfAppropriate()
{
    if(isDamageable())
    {
        int localHP = (getHP() -1);
        setHP(localHP);
        if(getHP() <= 0)
        {
            isDead();
            world()-> playSound(SOUND_PED_DIE);
        }
        else
        {
            world() -> playSound(SOUND_PED_HURT);
            
            if(world() -> getOverlappingGhostRacer(this))
            {
                return true; // delete after figure how to add goodie
            }
           // if(world() -> !overlaps(ghost, zom))
                //addHealingGoodie rand() 1 in 5 chance
                //ensure player recieves 150 pts
        }
        return true;
    }
    return false;
}


ZombieCab :: ZombieCab(StudentWorld* sw, double x, double y) : Agent(sw, IID_ZOMBIE_CAB, x, y, 4.0, 90, 3)
{
    isAlive();
    isCollisionAvoidanceWorthy();
    setHorizontalSpeed(0);
}

void ZombieCab:: doSomething()
{

    if(isDead())
        return;
    
    if(world() -> getOverlappingGhostRacer(this))
       {
            //if(damageCount > 0)
                //move
            
        
            //else
           // {
                world() -> playSound(SOUND_VEHICLE_CRASH);
                world() -> getGhostRacer() -> takeDamageAndPossiblyDie(20);
                /*
                 If the zombie cab is to the left of the Ghost Racer or has the same X coordinate as Ghost Racer then the zombie cab must:
                 i. Set its horizontal speed to -5.
                 ii. Set its direction equal to: 120 degrees plus a random integer
                 between [0,20).
                 f. If the zombie cab is right of the Ghost Racer then it must:
                 i. Set its horizontal speed to 5.
                 ii. Set its direction equal to: 60 degrees minus a random integer
                 between [0,20).
                 */
                damageCount += 1;
                
                int vert_speed = this -> getVerticalSpeed() - world() -> getGhostRacer() -> getVerticalSpeed();
                int horiz_speed = this -> getHorizontalSpeed();
                
                int new_y = this -> getY() + vert_speed;
                int new_x = this -> getX() + horiz_speed;
                
                 moveTo(new_x, new_y);
                
                if(this -> getX() < 0 || this -> getY() < 0 || this -> getX() > VIEW_WIDTH || this -> getY() > VIEW_HEIGHT)
                {
                    isDead();
                }
                /*
                 If the
                 the cab is moving up the screen) and there is a "collision-avoidance worthy" actor in the zombie cab's lane that is in front of that zombie cab:
                 zombie cab’s vertical speed is greater than Ghost Racer’s vertical speed (so
                 a. If the closest such actor is less than 96 vertical pixels in front of the zombie cab, decrease the zombie cab's vertical speed by .5 and immediately return.
                 5. If the zombie cab's vertical speed is the same as or slower than Ghost Racer's vertical speed (so the cab is moving down the screen or holding steady with Ghost Racer) and there is a "collision-avoidance worthy" actor in the zombie cab's lane that is behind that zombie cab:
                 a. If the closest such actor is less than 96 vertical pixels behind the zombie cab and is not Ghost Racer, increase the zombie cab's vertical speed by .5 and immediately return.
                 6. Decrement the zombie cab’s movement plan distance by one.
                 7. If the zombie cab’s movement plan distance is greater than zero, then
                 immediately return.
                 8. Otherwise, it’s time to pick a new movement plan for the zombie cab:
                 a. Set the zombie cab’s movement plan distance to a random integer between 4 and 32, inclusive.
                 b. Set the zombie cab’s vertical speed to its vertical speed + a random integer between -2 and 2, inclusive.
                 */
            //}
       }
}

bool ZombieCab :: beSprayedIfAppropriate()
{
    if(isDamageable())
    {
        int localHP = (getHP() -1);
        setHP(localHP);
        if(getHP() <= 0)
        {
            isDead();
            world()-> playSound(SOUND_VEHICLE_DIE);
            
            if ( world() -> getOverlappingGhostRacer(this))
            {
                return true; // delete
            }
            // if(world() -> !overlaps(ghost, zom))
                            //addOiislick rand() 1 in 5 chance at its current position
                            //ensure player recieves 200 pts
        }
        else
        {
            world() -> playSound(SOUND_VEHICLE_HURT);
        }
        return true;
    }
    return false;
}



Spray :: Spray(StudentWorld* sw, double x, double y, int dir) : Actor(sw, IID_HOLY_WATER_PROJECTILE, x, y, 1.0, 0, 1)
    {
        isAlive();
    }
       
void Spray :: doSomething()
{
    if(isDead())
        return;
    Actor* a;
    if(world() -> overlaps(a, this))
    {
        a -> damageActor(1);
        this -> isDead();
        return;
    }
    else
    {
        this-> moveForward(SPRITE_HEIGHT);
        if(this -> getX() < 0 || this -> getY() < 0 || this -> getX() > VIEW_WIDTH || this -> getY() > VIEW_HEIGHT)
        {
            isDead();
        }
        /*
         If the holy water projectile has moved a total of 160 pixels, then it immediately sets its status to not-alive (it dissipates) and will be removed by StudentWorld later in this tick.
         */
    }
}


GhostRacerActivatedObject :: GhostRacerActivatedObject(StudentWorld* sw, int imageID, double x, double y, double size, int dir) : Actor(sw, imageID, x, y, size, dir, 2)
{
}


 bool GhostRacerActivatedObject :: beSprayedIfAppropriate()
{
    if(isDamageable())
    {
        damageActor(1);
        return true;
    }
    return false;
}


int GhostRacerActivatedObject:: getSound() const
{
    world() -> playSound(SOUND_NONE);
    return 0;
}

OilSlick :: OilSlick(StudentWorld* sw, double x, double y) : GhostRacerActivatedObject(sw, IID_OIL_SLICK, x, y, randInt(2, 5), 0)
{
    setHorizontalSpeed(0);
    setVerticalSpeed(-4);
}
   




void OilSlick :: doSomething()
{
    if(world() -> getOverlappingGhostRacer(this))
    {
        GhostRacer* ghost = world() -> getOverlappingGhostRacer(this);
        
        doActivity(ghost);
        
        
        int vert_speed = getVerticalSpeed() - ghost -> getVerticalSpeed();
        int horiz_speed = 0;
        
        double new_y = getY() + vert_speed;
        double new_x  = getX() + horiz_speed;
        
        moveTo(new_x, new_y);
        
        if(getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT )
        {
            isDead();
            return;
        }
        
    }
}
       
void OilSlick :: doActivity(GhostRacer* gr)
{
    world() -> playSound(SOUND_OIL_SLICK);
    gr -> spin();
}

int OilSlick :: getScoreIncrease() const
{
    return getScore();
}
       
int OilSlick :: getSound() const
{
    world() -> playSound(SOUND_OIL_SLICK);
    return 0;
}
       
bool OilSlick:: selfDestructs() const
{
    return false;
}
   
bool OilSlick :: isSprayable() const
{
    return false;
}
       



 HealingGoodie :: HealingGoodie(StudentWorld* sw, double x, double y) : GhostRacerActivatedObject(sw, IID_HEAL_GOODIE, x, y, 1.0, 0)
{
           setHorizontalSpeed(0);
           setVerticalSpeed(-4);
}
              

void HealingGoodie :: doSomething()
{
    if(world() -> getOverlappingGhostRacer(this))
    {
        GhostRacer* ghost = world() -> getOverlappingGhostRacer(this);
        
        doActivity(ghost);
        
        int vert_speed = getVerticalSpeed() - ghost -> getVerticalSpeed();
        int horiz_speed = 0;
        
        double new_y = getY() + vert_speed;
        double new_x  = getX() + horiz_speed;
        
        moveTo(new_x, new_y);
        
        if(getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT )
        {
            isDead();
            return;
        }
        
    }
}
              
void HealingGoodie :: doActivity(GhostRacer* gr)
{
    world() -> playSound(SOUND_GOT_GOODIE);
    gr -> getHP(10);
    gr -> setScore(250);
}

int HealingGoodie :: getScoreIncrease() const
{
    return getScore();
}
              
              
bool HealingGoodie:: selfDestructs() const
{
    return true;
}
          
bool HealingGoodie :: isSprayable() const
{
    return true;
}
       
HolyWaterGoodie :: HolyWaterGoodie(StudentWorld* sw, double x, double y) : GhostRacerActivatedObject(sw, IID_HOLY_WATER_GOODIE, x, y, 2.0, 90)
{
    setHorizontalSpeed(0);
    setVerticalSpeed(-4);
}
                    

void HolyWaterGoodie :: doSomething()
{
    if(world() -> getOverlappingGhostRacer(this))
    {
        GhostRacer* ghost = world() -> getOverlappingGhostRacer(this);
        doActivity(ghost);
        
        int vert_speed = getVerticalSpeed() - ghost -> getVerticalSpeed();
        int horiz_speed = 0;
        
        double new_y = getY() + vert_speed;
        double new_x  = getX() + horiz_speed;
        
        moveTo(new_x, new_y);
        
        if(getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT )
        {
            isDead();
            return;
        }
        
    }
}
       
void HolyWaterGoodie :: doActivity(GhostRacer* gr)
{
    world() -> playSound(SOUND_GOT_GOODIE);
    gr -> setScore(50);
    gr -> setHolyWaterSprays(10);
}

int HolyWaterGoodie :: getScoreIncrease() const
{
    return getScore();
}
                    
                    
bool HolyWaterGoodie:: selfDestructs() const
{
    return true;
}
                
bool HolyWaterGoodie :: isSprayable() const
{
    return true;
}

SoulGoodie :: SoulGoodie(StudentWorld* sw, double x, double y) : GhostRacerActivatedObject(sw, IID_SOUL_GOODIE, x, y, 4.0, 0)
       {
           setHorizontalSpeed(0);
           setVerticalSpeed(-4);
       }
                           

void SoulGoodie :: doSomething()
{
    if(world() -> getOverlappingGhostRacer(this))
    {
        GhostRacer* ghost = world() -> getOverlappingGhostRacer(this);
        
        doActivity(ghost);
        
        int dir = getDirection() + 10;
        setDirection(dir);
        
        
        int vert_speed = getVerticalSpeed() - ghost -> getVerticalSpeed();
        int horiz_speed = 0;
        
        double new_y = getY() + vert_speed;
        double new_x  = getX() + horiz_speed;
        
        moveTo(new_x, new_y);
        
        if(getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT )
        {
            isDead();
            return;
        }
        
    }
}
              
void SoulGoodie :: doActivity(GhostRacer* gr)
{
    gr -> setScore(100);
    world() -> playSound(SOUND_GOT_SOUL);
    world() -> recordSoulSaved();
}

int SoulGoodie :: getScoreIncrease() const
{
    return getScore();
}
                           
                           
bool SoulGoodie:: selfDestructs() const
{
    return true;
}
                       
bool SoulGoodie :: isSprayable() const
{
    return false;
}

int SoulGoodie :: getSound() const
{
    world() -> playSound(SOUND_GOT_SOUL);
    return 0;
}
