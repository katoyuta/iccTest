#pragma once
#include "ofMain.h"

#define BUBBLE_NUM 50
#define BUBBLE_UP_SPEED 6
#define BUBBLE_MOVE_SPEED 2


class BubbleAnimation{
    
public:
    
    BubbleAnimation();
    
    void update();
    void draw();
    
    bool dead;
    
private:
    
    int frame;
    
    ofVec2f bubblesPos[BUBBLE_NUM];
    ofVec2f bubblesSpeed[BUBBLE_NUM];
    float bubblesSize[BUBBLE_NUM];
    
};

