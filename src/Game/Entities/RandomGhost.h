#pragma once
#include "Ghost.h"
#include "EntityManager.h"
#include <vector>

class RandomGhost: public Ghost{
    public:
        RandomGhost(int, int, int, int, ofImage, EntityManager*, string);
        void setX(int);
        void setY(int);

        void replaceDot(int,int);


    private:
        bool found = false;
        bool isDead = true;
        vector<ofImage> RandGhosts;
        ofImage rand;
        ofImage froggy;

};