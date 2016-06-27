//
//  s.cpp
//  blobReceiverTest
//
//  Created by Karina Jensen on 12/06/16.
//
//


#include "bubbles.h"

//------------------------------------------------------------------
Bubble::Bubble(){
    
}




//------------------------------------------------------------------
void Bubble::reset(int _spawnLocationX){
    pos.x = ofRandom(_spawnLocationX-50,_spawnLocationX+50);
    pos.y = RES_H;

    scale = int(ofRandom(1,5));
    //the unique val allows us to set properties slightly differently for each particle
    uniqueVal = ofRandom(-10000, 10000);
    drag  = ofRandom(0.97, 0.99);
    vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
    vel.y=-vel.y;
    age = 0;
}

//------------------------------------------------------------------
void Bubble::update(){
    age++;
    float fakeWindX = ofSignedNoise(pos.x * 0.002, pos.y * 0.003, ofGetElapsedTimef() * 0.6);
    
    frc.x = fakeWindX * 0.15 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
    frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
    
    vel *= drag;
    vel += frc * -0.4;
    
    pos += vel;
  
}

//------------------------------------------------------------------
void Bubble::draw(){
    
    ofDrawCircle(pos.x, pos.y, scale);
    
}

