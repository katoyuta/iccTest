#pragma once

#include "ofMain.h"
#include "BubbleAnimation.h"


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    private:
    
        ofVideoGrabber webcam;
    
        int webcam_w, webcam_h;
        float webcam_scale;
        ofVec2f webcam_pos;
    
    
        vector<BubbleAnimation> bubbles;
    
    
};
