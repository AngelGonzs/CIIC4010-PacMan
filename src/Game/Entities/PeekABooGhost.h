#pragma once
#include "Ghost.h"
#include "EntityManager.h"

class PeekABooGhost: public Ghost{
    public:
        PeekABooGhost(int, int, int, int, ofImage, EntityManager*, string, int);

        int getX();
        int getY();

        void setAlpha(int);
        int getAlpha();

        void render();
        void findPlayer(int,int);


    private:
        bool visible = false;
        bool isDead = true;
        int alpha = 0;
        ofImage amogus;
};