//
//  perlinParticle.h
//  blobReceiverTest
//
//  Created by Karina Jensen on 11/06/16.
//
//

#ifndef perlinParticle_h
#define perlinParticle_h
#include "defines.h"

class PerlinParticle{
public:
    ofVec2f pos;
    ofVec2f vel;
    float randomNoise;
    int age;
    int radius = 5;
    
    vector <ofPoint> * disturbPoints;
    
    void setup(vector <ofPoint> * _disturbPoints){
        vel.x = ofRandom(-15,15);
        vel.y = ofRandom(-15,15);
        
        pos.x = ofRandom(RES_W);
        pos.y = ofRandom(RES_H);
        disturbPoints= _disturbPoints;
    }
    
    void update(){
        age-=0.001;
        for(int i = 0 ; i< disturbPoints->size();i++){
            float a=disturbPoints->at(i).x-pos.x;
            float b=disturbPoints->at(i).y-pos.y;
            float squared = a*a+b*b;
            if(squared<100){
                if(sqrt(squared)<radius+20){
                    addSpeed();
                    age = 1;
                }
            }
        }
        if(age <0)age=0;
        pos+=vel;
        vel*=0.99;
        vel+=ofSignedNoise(-(1-age)*1000,(1-age)*1000);
        
        
        if( pos.x > RES_W ){
            pos.x = RES_W;
            vel.x *= -1.0;
        }else if( pos.x < 0 ){
            pos.x = 0;
            vel.x *= -1.0;
        }
        if( pos.y > RES_H ){
            pos.y = RES_H;
            vel.y *= -1.0;
        }
        else if( pos.y < 0 ){
            pos.y = 0;
            vel.y *= -1.0;
        }
        
    }
    

    void addSpeed(){
        vel.x = ofRandom(-15,15);
        vel.y = ofRandom(-15,15);
    }
    
    void draw(){
        ofDrawCircle(pos,radius);
    }
};
#endif /* perlinParticle_h */
