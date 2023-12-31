#include "GameState.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	if (map->getPlayer()->getScore() >= map->getPlayer()->getMaxScore()){
		setNextState("Win");
		setFinished(true);
		map->getPlayer()->setScore(0);
	}

	//copying players location to EntityManager variable:
	map->getPlayer()->getEM()->setPlayerX(map->getPlayer()->getX());
	map->getPlayer()->getEM()->setPlayerY(map->getPlayer()->getY());

	//copying player's score to EntityManager
	map->getPlayer()->getEM()->setPlayerScore(map->getPlayer()->getScore());
	

}

void GameState::render() {
	map->render();
}


void GameState::keyPressed(int key){
	map->keyPressed(key);
	if(key =='y'){
		setNextState("Win");
		setFinished(true);
	}
	if(key == 'p'){
		setNextState("Pause");
		setFinished(true);
	}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
	}

void GameState::reset(){
	setFinished(false);
	setNextState("");
	map = MapBuilder().createMap(mapImage);
}


int GameState::getFinalScore(){
	return finalScore;
}

GameState::~GameState(){
	delete map;
}