#pragma once
#include "ofMain.h"

#define BUBBLE_NUM 50


class BubbleAnimation{
    
public:
    
    BubbleAnimation();
    
    void update();
    void draw();
    
    bool dead;
    
private:
    
    int frame = 0;
    
    float scale = 1;
    
    ofVec2f bubblesPos[BUBBLE_NUM];
    ofVec2f bubblesSpeed[BUBBLE_NUM];
    float bubblesSize[BUBBLE_NUM];
    
};

