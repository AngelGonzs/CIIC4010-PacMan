#include "Dot.h"

Dot::Dot(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 623, 18,16,16);
}

int Dot::getY() { return y; }
int Dot::getX() { return x; }