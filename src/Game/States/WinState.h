#pragma once
#include "State.h"
// #include "EntityManager.h"
// #include "Dot.h"
// #include "BigDot.h"
#include "Button.h"
#include "Animation.h" 

class WinState: public State{
    private:
    int MaxScore = 0;
    ofImage img1;
	Button *startButton;
	Animation* anim;

    public:
    WinState();
    ~WinState();
    void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();

};