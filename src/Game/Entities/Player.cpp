#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"

#include "RandomGhost.h"
#include "PeekABooGhost.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;
    loader.load("images/Background.png");
    infLoader.load("images/Infinity.png");
    
}
void Player::tick(){

    if(invincible){
        if(currentPos > x+y + 200 || currentPos < x+y - 200){
            invincible = false;
            alpha = 255;
        }
    }

    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
            walkUp->tick();
        }else if(facing == DOWN){
            y+=speed;
            walkDown->tick();
        }else if(facing == LEFT){
            x-=speed;
            walkLeft->tick();
        }else if(facing == RIGHT){
            x+=speed;
            walkRight->tick();
        }
    }
}


void Player::render(){
    ofSetColor(255, alpha);
    // ofDrawRectangle(getBounds());
    if(facing == UP){
        walkUp->getCurrentFrame().draw(x, y, width, height);
        
    }else if(facing == DOWN){
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == LEFT){
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == RIGHT){
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }

    ofSetColor(255);
    randPow.cropFrom(loader, 569, 52, 16,16);


    
    for(unsigned int i = 0; i<randomPowerups; i++){
        randPow.draw(ofGetWidth()/2 + 25*i +340, 115, 16,16);
    }

    if(invPowerups>0){
        infLoader.draw(ofGetWidth()/2 + 360, 150, infLoader.getWidth(), infLoader.getHeight());
    }
    ofSetColor(256, 0, 0);


    if(powerups.size() > 0){ 
        ofDrawBitmapString("Next Powerup: " + powerups.back(), ofGetWidth()/2 + 320, 75);
        ofDrawBitmapString("PowerUps Available: ", ofGetWidth()/2 + 320, 95);
    }
    else ofDrawBitmapString("No PowerUps available", ofGetWidth()/2 + 320, 75);



    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            setFacing(UP);
            break;
        case 's':
            setFacing(DOWN);
            break;
        case 'a':
            setFacing(LEFT);
            break;
        case 'd':
            setFacing(RIGHT);
            break;
        case 'n':
            die();
            break;
        case 'm':
            if(this->getHealth()<3){
            health++;
            }
            break;
        
        case ' ':
            activate();
            break;

        case 'i':
            invPowerups++;
            powerups.push_back("inv");
            break;
        
        case 'r':
            randomPowerups++;
            powerups.push_back("rand");
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(FACING facing){
    this->facing = facing;
}

int Player::getHealth(){
    return health;
}

void Player::setHealth(int h){
    health = h;
}
int Player::getScore(){
    return score;
}

void Player::setScore(int h){
    score = h;
}

void Player::checkCollisions(){
    for(BoundBlock* BoundBlock: em->BoundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=10;            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=10;
                em->setKillable(true);
            }
                em->setKillable(true);
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;
            
                if(RandomGhost* rg = dynamic_cast<RandomGhost*>(entity)){
                em->setRGDead(true);
                if(randomPowerups < 3){
                    randomPowerups += 1;
                    powerups.push_back("rand");
                    }
                }

                if(PeekABooGhost* pb = dynamic_cast<PeekABooGhost*>(entity)){
                powerups.push_back("inv");
                invPowerups++; 
                }
                
            }
            else{ 
                if(!invincible){
                    die(); 
                }
            }
        }
    }

    
}

int Player::getMaxScore(){
    maxScore = 0;
	for(Entity* entity: em->entities){
		if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
    		maxScore += 10;
   }
}
	return maxScore + this->getScore();
}

/*getters for the RandomGhost 
set with the intention to spawn
the ghost away from the players
current position*/
int Player::getX(){ return x; }
int Player::getY(){ return y; }

void Player::setX(int equis){ x = equis; }
void Player::setY(int lle){ y = lle; }

EntityManager* Player::getEM(){ return em; }

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}

/*similar to RandomGhost, this function 
swaps the target for a dot in the entities
vector, but here there are no parameters thus 
the player can be swapped for any dot regardless
of distance*/
void Player::RandomActivate(){
    bool finder = false;
    int randInt = ofRandom(0, em->entities.size());
    Entity* entity = em->entities[randInt];
    while(!finder){
        if(Dot* dot = dynamic_cast<Dot*>(entity)){
            setX(dot->getX());
            setY(dot->getY());
            dot->remove = true;
            finder = true;
            }

    }
}

int Player::getRandPowerUps(){ return randomPowerups; }

void Player::InvisibleActivate(){
    /*when starting, alpha = 255 (turns invisible)
    then, when the player moves a certain amount of pixels,
    alpha will be 0 and invincible will be false*/
    invincible = true;
    alpha = 0; 
    currentPos = x + y; 

}

int Player::getInvPowerUps(){ return invPowerups; }


void Player::activate(){
    if(powerups.size() > 0){
        if(powerups.back() == "rand"){
            RandomActivate();
            powerups.pop_back();
            randomPowerups--;
        }
        if(powerups.back() == "inv"){
            InvisibleActivate();
            powerups.pop_back();
            invPowerups--;
        }
    }
}