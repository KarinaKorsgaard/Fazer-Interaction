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
    

    
    vector<ofPoint>* attractPoints;
    
    void setup(ofPoint _pos, int _r, string file1, string file2, vector <ofPoint> * _disturbPoints){
        flower1.load(file1);
        flower2.load(file2);
        flower2.setLoopState(OF_LOOP_NONE);
        flower1.setLoopState(OF_LOOP_NORMAL);
        pos = _pos;
        r = _r;
        orgR = _r;
        touched = false;
        attractPoints = _disturbPoints;
    }
    
    void update(){
        r = orgR + sin (ofGetFrameNum()/10)*10;
        if(!touched){
            for(int i = 0; i< attractPoints->size();i++){
                if(dist(pos,attractPoints->at(i)) < (r-50)/2){
                    touched = true;
                    flower2.play();
                    cout<< dist(pos,attractPoints->at(i)) <<endl;
                }
            }
        }
        
        if(!touched){
            flower1.update();
        }
        else if(touched){
            flower2.update();
        }
        

        if(touched && !flower2.isPlaying()){
            touched = false;
            pos = ofPoint(ofRandom(100,RES_W-100),ofRandom(100,RES_H-100));
        }
        

    }
    
    void draw(){
        ofSetColor(255);
        if(!touched)flower1.draw(pos.x-(r)/2,pos.y-(r*3/4)/2,r,r*3/4);
        else if(touched)flower2.draw(pos.x-(r)/2,pos.y-(r*3/4)/2,r,r*3/4);

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
