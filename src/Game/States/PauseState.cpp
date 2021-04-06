#include "PauseState.h"

PauseState::PauseState() {
	startButton = new Button((ofGetWidth()/2) - 150, ofGetHeight()/2, 64, 50, "Press R to resume, press Q to quit the game.");
	
    img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;

	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);
}


void PauseState::tick() {
	startButton->tick();
	anim->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);
	}
}


void PauseState::render() {
	ofDrawBitmapString("Paused Game", ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	startButton->render();
}


void PauseState::keyPressed(int key){
    if(key == 'r'){
		setNextState("Game");
        setFinished(true);
	}
    else if(key == 'q'){
		setNextState("over");
		setFinished(true);
    }
}


void PauseState::mousePressed(int x, int y, int button){
	
}


void PauseState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}


PauseState::~PauseState(){
	delete startButton;
	delete anim;
}