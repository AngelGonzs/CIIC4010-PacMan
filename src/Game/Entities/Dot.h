#pragma once
#include "Entity.h"

class Dot: public Entity{
    public:
        Dot(int, int, int, int, ofImage);

        int getX();
        int getY();
};