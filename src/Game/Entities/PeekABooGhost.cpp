#include "PeekABooGhost.h"

PeekABooGhost::PeekABooGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color, int alpha): Ghost(x, y, width, height,spriteSheet, em, color){
    color = "PeekABoo";
    sprite.cropFrom(spriteSheet,632,113,16,16);
    this->alpha = alpha;
}

int PeekABooGhost::getX(){ return x; }
int PeekABooGhost::getY(){ return y; }

int PeekABooGhost::getAlpha(){ return alpha; }
void PeekABooGhost::setAlpha(int a){ alpha = a; }


void PeekABooGhost::render(){
        if(killable){
        killableAnim->getCurrentFrame().draw(x,y,width,height);
    }else{
        int xP = em->getPlayerX();
        int yP = em->getPlayerY();
        findPlayer(xP,yP);
        ofSetColor(255, getAlpha());
        sprite.draw(x,y,width, height);
    }
}

void PeekABooGhost::findPlayer(int xP, int yP){
    bool xTrue = false;
    bool yTrue = false;
    if(x <= xP + 50 && x >= xP - 50){
        xTrue = true;
    }
    if(y <= yP + 50 && y >= yP - 50){
        yTrue = true;
    }
    if(xTrue && yTrue){
        setAlpha(255);
    }
    else{
        setAlpha(0);
    }
}