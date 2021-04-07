#pragma once
#include "Animation.h"
#include "Powerup.h"
#include "EntityManager.h"
#include "RandomPowerup.h"
#include "InvisiblePowerup.h"

class Player: public Entity, public PowerUp{

    private:
        int spawnX, spawnY;
        int health=3;

        int randomPowerups = 0; //counter for RandomPowerUps, to regulate random activate.
        vector<string> powerups; //vector to detect what 

        bool invincible = false; //to detect whether the player is invincible or not
        int alpha = 255; //to make the player invisible
        int currentPos; //to track the pixels the player moves
        
        //debugging purposes:
        int invPowerups = 0;

        int score=0;
        int maxScore=0;

        bool canMove;
        int speed = 8;
        bool walking = false;
                
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        void setHealth(int);

        int getScore();
        void setScore(int);
        int getMaxScore();

        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
        void die();


        void activate();

        void RandomActivate();
        int getRandPowerUps(); //getters to detect if >= 3

        void InvisibleActivate();
        int getInvPowerUps();

        int getX();
        int getY();

        void setX(int);
        void setY(int);



        EntityManager* getEM();
};