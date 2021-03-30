#include "RandomGhost.h"
#include "Dot.h"
#include <vector>

RandomGhost::RandomGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Ghost(x, y, width, height,spriteSheet, em, color){
    color = "random";
    sprite.cropFrom(spriteSheet,632,113,16,16);
}

void RandomGhost::setX(int equis){
    x = equis;
}

void RandomGhost::setY(int ye){
    y = ye;
}

void RandomGhost::replaceDot(int x, int y){
    bool xTrue;
    bool yTrue;
    while(!found){
        int randInt = ofRandom(0 , em->entities.size());
        Entity* entity = em->entities[randInt];
        if(Dot* dot = dynamic_cast<Dot*>(entity)){
                if(dot->getX() > x + 100 || dot->getX() < x - 100){
                    xTrue = true;
                }
                if(dot->getY() > y + 100 || dot->getY() < y - 100){
                    yTrue = true;
                }

                if(xTrue && yTrue){
                    found = true;
                    setX(dot->getX());
                    setY(dot->getY());
                    dot->remove = true;
                }
            }
        }
    }