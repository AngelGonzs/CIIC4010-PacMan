#pragma once
#include "Ghost.h"
#include "EntityManager.h"

class RandomGhost: public Ghost{
    public:
        RandomGhost(int, int, int, int, ofImage, EntityManager*, string);
        void setX(int);
        void setY(int);

        void replaceDot(int,int);

    private:
        bool found = false;
};