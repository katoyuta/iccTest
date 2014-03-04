#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    webcam_w = 640;
    webcam_h = 480;
    
    webcam.initGrabber(640, 480);
    
    int w = ofGetWidth();
    int h = ofGetHeight();
    
    //幅にフィットさせる
    webcam_scale = (float)w/(float)webcam_w;
    
    if (webcam_h * webcam_scale < h) {
        //高さが余っていたら高さにフィットさせる
        webcam_scale = (float)h/(float)webcam_h;
        webcam_pos.set( ((float)w-(float)webcam_w*webcam_scale)/2, 0 );
    }
    
    else {
        webcam_pos.set( 0, ((float)h-(float)webcam_h*webcam_scale)/2 );
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    webcam.update();
    
    for (int i =0; i < bubbles.size(); i++) {
        bubbles[i].update();
        if(bubbles[i].dead ){
            std::vector<BubbleAnimation>::iterator it = bubbles.erase(bubbles.begin() + i);
            i--;
        }
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
    webcam.draw(ofGetWidth() - webcam_pos.x, webcam_pos.y, -webcam_w*webcam_scale, webcam_h*webcam_scale);
    
    for (int i =0; i < bubbles.size(); i++) {
        bubbles[i].draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch(key) {
        case 'a':
            BubbleAnimation b;
            bubbles.push_back(b);
            break;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
    //幅にフィットさせる
    webcam_scale = (float)w/(float)webcam_w;
    
    if (webcam_h * webcam_scale < h) {
        //高さが余っていたら高さにフィットさせる
        webcam_scale = (float)h/(float)webcam_h;
        webcam_pos.set( ((float)w-(float)webcam_w*webcam_scale)/2, 0 );
    }
    
    else {
    
        webcam_pos.set( 0, ((float)h-(float)webcam_h*webcam_scale)/2 );
    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}