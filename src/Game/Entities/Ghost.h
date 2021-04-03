#pragma once
#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);

    private:
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=3;
        
    
//moved em here so that RandomGhost (and PeekABooGhost) can use it.
    protected:
        EntityManager* em;
        Animation* killableAnim;
        bool killable = false;


};