#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxLeapMotion.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
  
    /*
    
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
     */
    
    void keyPressed  (int key);
    void windowResized(int w, int h);

    
    ofxLeapMotion leap; // Leap Motionのメインクラスをインスタンス化
    vector <ofxLeapMotionSimpleHand> hands; // シンプルな手のモデルのvector配列
    ofCamera cam; //カメラ
    ofLight light; //ライト
    //指の位置
    vector <ofVec3f> fingerPos;
    //手のひらの位置
    vector <ofVec3f> handPos;
    
    //■■■重要■■■■手洗いをしているか
    bool tearai = false;
    
    //■■■重要■■■■こすったらあがっていく
    int kosuri = 0;
    
    //■■■重要■■■■手のひらの距離
    float palm_distance;
    
    //■■■重要■■■■バイク
    bool bike = false;
    ofImage bike_img; //画像ファイルより読みこまれたイメージデータ
    
    //フォント
    ofTrueTypeFont verdana;
    
    //前回の手のひらの位置
    float prev_palm0;
    float prev_palm1;
    
    //前回と今回の手のひらの位置の差
    float diff0 ;
    float diff1 ;
    
    //リープは起動しているか
    bool leapstarted = false;
 

    
    //webカメラ
    ofVideoGrabber webcam;
    
    int webcam_w, webcam_h;
    
    float webcam_scale;
    int webcam_y_shift;
    
    //差分
    ofxCvColorImage baseImage;
    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage resultImage;
    
    bool baseImageAvailable;

};