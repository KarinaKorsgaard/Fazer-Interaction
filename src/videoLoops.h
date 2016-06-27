//
//  burstingBubbles.h
//  blobReceiverTest
//
//  Created by Karina Jensen on 23/06/16.
//
//

#ifndef burstingBubbles_h
#define burstingBubbles_h
#include "defines.h"

class burstingBubbles{

public:
    
    float r;
    ofPoint pos;
    bool touched;
    int thres;
    int alpha;
    float orgR;
    
    ofVideoPlayer flower1;
    ofVideoPlayer flower2;
    
    int f1NumFrames;
    int width, height;
    bool play1, play2;
    vector<ofPoint>* attractPoints;
    
    void setup(ofPoint _pos, int _r, string file1, string file2, vector <ofPoint> * _disturbPoints){
        flower1.load(file1);
        flower2.load(file2);
        flower2.setLoopState(OF_LOOP_NONE);
        flower1.setLoopState(OF_LOOP_NORMAL);
        flower1.play();
        f1NumFrames=flower1.getTotalNumFrames();
        pos = _pos;
        width = flower1.getWidth();
        height = flower1.getHeight();
       // r = _r;
       // orgR = _r;
        touched = false;
        play1 = true;

        attractPoints = _disturbPoints;
    }
    
    void update(){
       // r = orgR + sin (ofGetFrameNum()/10)*10;
        if(!touched){
            for(int i = 0; i< attractPoints->size();i++){
                if(abs((pos.x+width/2)-attractPoints->at(i).x)<20){
                    touched = true;
                    //flower1.setLoopState(OF_LOOP_NONE);
                    flower2.play();
                    flower1.stop();
                    //cout<< dist(pos,attractPoints->at(i)) <<endl;
                }
            }
        }
//        if(touched && !flower1.isPlaying()){
//            flower2.play();
//            play1 = false;
//        }
//        if(touched && flower1.isPlaying()){
//            flower1.update();
//        }
        if(touched){
            flower2.update();
        }
        
        if(!touched){
            flower1.update();
        }

        

        if(touched && !flower2.isPlaying()){
            touched = false;
            flower2.stop();
            //flower1.setLoopState(OF_LOOP_NORMAL);
            flower1.play();
           // play1 = true;
            //pos = ofPoint(ofRandom(100,RES_W-100),ofRandom(100,RES_H-100));
        }
        

    }
    
    void draw(){
        ofSetColor(255);
        if(!touched){
            ofSetColor(255,0,0);
            flower1.draw(pos.x,pos.y-height,width,height);
        
        }
        else if(touched){
            ofSetColor(255,255,0);
            flower2.draw(pos.x,pos.y-height,width,height);
        }

    }
    
    float dist(ofPoint p,ofPoint o){
        return 1/b2InvSqrt((p.x-o.x)*(p.x-o.x)+(p.y-o.y)*(p.y-o.y));
    }

    inline Float32 b2InvSqrt(Float32 x)
    {
        int ix = 0;
        memcpy(&ix, &x, sizeof(x));
        
        Float32 xhalf = 0.5f * x;
        ix = 0x5f3759df - (ix >> 1);
        memcpy(&x, &ix, sizeof(x));
        x = x * (1.5f - xhalf * x * x);
        return x;
    }
};
#endif /* burstingBubbles_h */
