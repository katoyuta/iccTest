#include "testApp.h"



void testApp::setup(){
    // 画面設定
    ofSetFullscreen(true);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(11);
    
    // 照明とカメラ
    ofEnableLighting();
    light.setPosition(200, 300, 50);
    light.enable();
    
    cam.setFov(40);
    cam.setPosition(0, 200, -400);
    cam.setOrientation(ofPoint(-20,180,0));
    
    
    // GL設定
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    //フォント設定だよ
    //oFのfontsexample/bin/data内にデフォルトで入ってるのをつかってます
    verdana.loadFont("verdana.ttf", 20, true, true);
    verdana.setLineHeight(18.0f);
    //verdana.setLetterSpacing(1.037);
    
    bike_img.loadImage("bike.png");
    
    // Leap Motion開始
    leap.open();
    
    
    //ウェブカメラ設定
    webcam_w = 640;
    webcam_h = 480;
    
    webcam_scale = (float)ofGetWidth()/(float)webcam_w;
    webcam_y_shift = ((float)ofGetHeight()-(float)webcam_h*webcam_scale)/2;
    
    webcam.setDeviceID(0);
    webcam.initGrabber(webcam_w, webcam_h);
    
    
    //背景差分
    colorImage.allocate(webcam_w, webcam_h);
    baseImage.allocate(webcam_w/4, webcam_h/4);
    resultImage.allocate(webcam_w/4, webcam_h/4);
    
}

void testApp::update(){
    
    
    //webカメラ
    webcam.update();
    
    if (webcam.isFrameNew()) {
        
        colorImage.allocate(webcam_w, webcam_h);
        colorImage.setFromPixels(webcam.getPixels(),webcam_w, webcam_h);
        
        colorImage.resize(webcam_w/4, webcam_h/4);
        colorImage.mirror(0, 1);
        
        resultImage.set(255);
        
        if (!baseImageAvailable) {
            baseImage.setFromPixels(colorImage.getPixels(), colorImage.width, colorImage.height);
            baseImageAvailable = true;
        }
        
        unsigned char *px = colorImage.getPixels();
        unsigned char *bpx = baseImage.getPixels();
        unsigned char *rpx = resultImage.getPixels();
        
        for (int x=0; x<colorImage.width; x++) {
            for (int y=0; y<colorImage.height; y++) {
                
                int dr = abs(px[colorImage.width*3*y + x*3] - bpx[colorImage.width*3*y + x*3]);
                int dg = abs(px[colorImage.width*3*y + x*3+1] - bpx[colorImage.width*3*y + x*3+1]);
                int db = abs(px[colorImage.width*3*y + x*3+2] - bpx[colorImage.width*3*y + x*3+2]);
                
                if(dr > 20 || dg > 20 || db > 20 ){
                    rpx[colorImage.width*y + x] = 80;
                }
            }
        }
    }
    
    
    // 検出された手の数だけ、ofxLeapMotionSimpleHandのvector配列に追加
    hands = leap.getSimpleHands();
    
    // フレーム更新して、手が検出されたら
    if( leap.isFrameNew() && hands.size() ){
        
        //指と手の位置をクリア
        fingerPos.clear();
        handPos.clear();

        
        // 画面の大きさにあわせて、スケールをマッピング
        //leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        //leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        //leap.setMappingZ(-150, 150, -200, 200);
        
        
        // 検出された手の数だけくりかえし
        for(int i = 0; i < hands.size(); i++){
            
            // 手の位置を取得
            handPos.push_back(hands[i].handPos);

            
            // 検出された指の数だけくりかえし
            for(int j = 0; j < hands[i].fingers.size(); j++){
                // 位置をvectorに保存
                ofVec3f pos = hands[i].fingers[j].pos;
                fingerPos.push_back(pos);
            }
        }
        
        //■■■■手をあわせているかの検出■■■■
       //手が２本あるなら
        if(hands.size() == 2) {
            palm_distance = ofDist(handPos[0].x, handPos[0].y, handPos[1].x, handPos[1].y );
        }
        //手の数が1以下もしくは３以上の場合、両手の距離＝2000にする
        else{ palm_distance = 2000;}
        
        //手の距離が規定値(250)以下のときにtearai = trueになる
        if(palm_distance<250){
            tearai = true;
        }
        else{tearai = false;}
        
        
        //■■■■手をこすりあわせているかの検出■■■■
        
        //前回の手のひら位置と今の手のひらの位置の差の絶対値(z軸の値です）
        diff0 = abs(prev_palm0 - handPos[0].z);
        diff1 = abs( prev_palm1 - handPos[1].z);
        
        //現在の手のひらの位置を前回の手のひらの位置の変数に代入
           prev_palm0 = handPos[0].z;
           prev_palm1 = handPos[1].z;

        //手が合わさってる状態＆手の動きの合計が2.5以上の時に kosuriが追加される
        if(diff0 + diff1 > 3 && tearai){
            kosuri ++;
        }
        
        //■■■■バイクのポーズだよ！！！■■■■■■■■■
        
        if((hands[0].fingers.size() == 4) && (hands[1].fingers.size() == 0))
        {
            bike = true;
        }
        else if((hands[1].fingers.size() == 4) && (hands[0].fingers.size() == 0))
        {
            bike = true;
        }
        else{
        
            bike = false;
        }
        
        
        
        //リープが動き出したことを合図
        leapstarted = true;
    }

    
    
    // ofxLeapMotionに現在のフレームは古くなったことを通知
    leap.markFrameAsOld();
    
    
    
    
}

void testApp::draw(){
    
    
    //webカメラ
    glDisable(GL_DEPTH_TEST);
    
    ofSetColor(255);
    webcam.draw(ofGetWidth(), webcam_y_shift, -webcam_w*webcam_scale, webcam_h*webcam_scale);
    
    
    if (baseImageAvailable) {
        
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        resultImage.draw(0, webcam_y_shift, webcam_w*webcam_scale, webcam_h*webcam_scale);
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(255);
        baseImage.draw(0, 0);
        colorImage.draw(200,0);
        resultImage.draw(400,0);
    }
    
    
    //cam.begin();
    
    glEnable(GL_DEPTH_TEST);
    
    cam.begin(ofRectangle(0, webcam_y_shift, webcam_w*webcam_scale, webcam_h*webcam_scale));
    
    ofPushMatrix();
    ofScale(-1, 1);
    
    //手洗ってるときに背景の色をカエル
    //if(tearai)
    //{ofBackground(100,100,255);}
    //else
    //{ofBackground(31);}
  
    
    // 検出された指の数だけくりかえし
    for(int i = 0; i < fingerPos.size(); i++){
        // 検出された位置に立方体を描画
        ofSetColor(255);
        ofBoxPrimitive box;
        box.setPosition(fingerPos[i].x, fingerPos[i].y, fingerPos[i].z);
        box.set(10);
        box.draw();
    }
    
    
    //手の平の描画
    for(int i=0; i<handPos.size(); ++i){
        
        ofSetColor(255);
        ofBoxPrimitive box2;
        box2.setPosition(handPos[i].x, handPos[i].y, handPos[i].z);
        box2.set(30);
        box2.draw();
        
        //ofSetColor(100,255,0);
        //verdana.drawString("   PALM(Z) :" + ofToString(i),handPos[i].x, handPos[i].y);
    }
    
    ofPopMatrix();
    
    cam.end();
    
    
    
    //テキスト表示まわり
    //リープが起動してるのなら
    /*if(leapstarted){
    
        //ばいくさん
        if(bike){
            ofSetColor(255);
            bike_img.draw(1000,100,600,700);
        }
        else{}

    //表示
    ofSetColor(255);
   verdana.drawString("PALM_DISTANCE : " + ofToString(palm_distance), 100, 100);
   verdana.drawString("FRAMERATE: " + ofToString(ofGetFrameRate()), 100, 200);
   verdana.drawString("KOSURI: " + ofToString(kosuri),100,300);
   verdana.drawString("BIKE: " + ofToString(bike),100,500);


        //verdana.drawString("PALM0 Zdiff : " + ofToString(diff0),900,100);
        //verdana.drawString("PALM1 Zdiff : " + ofToString(diff1),900,200);
        
        //こすりゲージ
        ofSetColor(0,200,100);
        ofRect(100,400,kosuri*1.5,50);

    }
     */
 
    verdana.drawString("FRAMERATE: " + ofToString(ofGetFrameRate()), 100, 200);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    switch (key) {
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'r':
            
            if (baseImageAvailable) {
                baseImage.setFromPixels(colorImage.getPixels(), colorImage.width, colorImage.height);
            }
            
            break;
            
    }
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    //幅をフィットさせてセンタリング
    webcam_scale = (float)w/(float)webcam_w;
    webcam_y_shift = ((float)h-(float)webcam_h*webcam_scale)/2;
}
