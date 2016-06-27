//
//  user.h
//  blobReceiverTest
//
//  Created by Karina Jensen on 21/06/16.
//
//

#ifndef user_h
#define user_h

#include "ofxBiquadFilter.h"

class User{
public:
    ofVec2f pos;
    ofxBiquadFilter2f posistion;
    int deadCount;
    int IdNum;
    bool userExists;
    float radius;
    bool remove;
    int receiverNum;
    ofTrueTypeFont font;
    int age;
    
    void setup(int _IdNum, int _rec, ofVec2f _pos, float _rad){
        posistion.setFc(1.2);
        posistion.clear(pos);
        IdNum = _IdNum;
        pos = _pos;
        receiverNum = _rec;
        age = 0;
        deadCount = 0;
        userExists=true;
        radius = (3000-_rad) / 20 ;
        
        font.load("font.ttf",26,true,true);
    }
    
    void update(ofVec2f _pos, float _rad){
        pos = _pos;
        deadCount=0;
        radius = (3000-_rad) / 20 ;
        age = 0;

    }
    
    void update(){
        age++;
//        radius +=(sin(ofGetElapsedTimef())-0.5) * 20 ;
        posistion.update(pos);
    }
    
    bool isDead(){
        if(age > 10 ) return true;
        else return false;
    }
    
    void draw(){
        
        ofPushMatrix();

     
        ofSetColor(255,0,0);
        ofDrawCircle(posistion.value(), radius);
        ofSetColor(0);
        string s = ofToString(IdNum)+ " " + ofToString(receiverNum);
        font.drawString(s ,posistion.value().x,posistion.value().y);
        font.drawString(ofToString(age) ,posistion.value().x,posistion.value().y+25);
        ofPopMatrix();
    }
    

};
#endif /* user_h */
