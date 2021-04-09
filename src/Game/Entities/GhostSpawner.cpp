#include "GhostSpawner.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"
#include <string>

string colors[]= {"red", "pink","cyan", "orange"};
GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(){
    std::vector<string> colors;
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");

    if(em->ghosts.size()<4){
        if(spawnCounter == 0){
            spawnGhost(colors[ofRandom(4)]);
            spawnCounter = 30*5;
        }else{
            spawnCounter--;
        }
    }

    if(em->getRGDead()){
        spawnGhost("random");
    }

    if(em->getPBDead()){
        spawnGhost("PeekABoo");
    }
}

//^Dead variables to detect when has the ghost been eaten^

/*special ghosts were given a special color
so that they can have a secure authentification
and no errors when being spawned*/
void GhostSpawner::spawnGhost(string color){
    if(color != "random" && color != "PeekABoo"){
        Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
        em->ghosts.push_back(g);
    }
    else if(em->getPlayerScore() >= 500 && color == "random"){
        RandomGhost* rg = new RandomGhost(x,y,width-2,height-2,sprite,em, color);
        int x = em->getPlayerX();
        int y = em->getPlayerY();
        rg->replaceDot(x,y);
        em->setRGDead(false);

        Ghost* g = rg;
        em->ghosts.push_back(g);
    }
    else if(em->getPlayerScore() >= 1000 && color == "PeekABoo"){
        PeekABooGhost* pb = new PeekABooGhost(x,y,width-2,height-2,sprite,em, color, 0);
        int x = em->getPlayerX();
        int y = em->getPlayerY();
        pb->findPlayer(x,y);
        em->setPBDead(false);

        Ghost* g = pb;
        em->ghosts.push_back(g);
    }
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        int x = ofRandom(0,4);
        spawnGhost(colors[x]);
    }
}