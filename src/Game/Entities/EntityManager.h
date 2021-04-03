#pragma once

#include "BoundBlock.h"

class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> BoundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);

	void setPlayerX(int);
	int getPlayerX();

	void setPlayerY(int);
	int getPlayerY();

	void setOver500(bool);
	//for testing purposes:
	bool getOver500();

	void setRGDead(bool);
	bool getRGDead();

	void setPBDead(bool);
	bool getPBDead();

	void setPlayerScore(int);
	int getPlayerScore();
	

private:
	bool killable = false;
	bool scoreOver500 = false;

	bool rgIsDead = true;
	bool pbIsDead = true;

	int killableCounter;
	int playerX;
	int playerY;

	int playerScore;

};