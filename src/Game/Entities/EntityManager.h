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
	void setOver500(bool);
	//for testing purposes:
	bool getOver500();
	

private:
	bool killable = false;
	bool scoreOver500 = false;
	int killableCounter;

};