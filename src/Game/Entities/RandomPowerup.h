#pragma once
#include "Powerup.h"

class RandomPowerup: public PowerUp{
    virtual void RandomActivate() = 0;
};