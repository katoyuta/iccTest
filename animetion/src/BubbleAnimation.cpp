
#include "BubbleAnimation.h"


BubbleAnimation::BubbleAnimation(){
    
    frame = 0;
    dead = false;
    
    float scale = ofGetWidth()/100.f;
    
    for (int i = 0; i < BUBBLE_NUM; i++) {
        bubblesPos[i].set( ofRandom(-20, 120) * scale, ofRandom(100,300) * scale );
        bubblesSpeed[i].set( ofRandom(-1, 1) * scale, ofRandom(0,-10) * scale );
        bubblesSize[i] = ofRandom(0.2, 5) * scale;
    }
    
};


void BubbleAnimation::update(){
    
    for (int i = 0; i < BUBBLE_NUM; i++) {
        bubblesSpeed[i].x += ofRandom(-0.5, 0.5);
        bubblesSpeed[i].y -= ofRandom(1/bubblesSize[i]);
        bubblesPos[i] += bubblesSpeed[i];
    }
    
    frame ++;
    
    if(frame > 3 * 24){
        dead = true;
    }
   
}

void BubbleAnimation::draw(){
    
    ofSetColor(0, 128, 128);
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    
    for (int i = 0; i < BUBBLE_NUM; i++) {
        
        ofCircle(bubblesPos[i].x, bubblesPos[i].y, bubblesSize[i]);
    }
    
    //ofDisableAlphaBlending();
    ofDisableBlendMode();
    
}