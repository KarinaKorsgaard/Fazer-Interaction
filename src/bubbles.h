#pragma once
#include "ofMain.h"
#include "defines.h"

class Bubble{
    
public:
    Bubble();
    
    
    void reset(int _spawnLocationX);
    void update();
    void draw();
    
    int spawnLocationX;
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    int age;
    
    bool isDead(){
        bool result = false;
        if(pos.y<0){
            result =true;
        }
        return result;
    }
    
};

class bubbleSpawn{
    
    public:
    vector <ofPoint> * attractPoints;
    int spawnLocationX;
    bool spawn();
    vector<Bubble>bubbles;
    ofMesh drawMesh;
    
    void setup(vector <ofPoint> * _attractPoints){
        attractPoints=_attractPoints;
        spawnLocationX = int(ofRandom(RES_W));
    }

    void update(){
        drawMesh.clear();
        for(int i = 0; i<attractPoints->size();i++){
            int x = attractPoints->at(i).x;
            if(abs(spawnLocationX-x)<100 && ofRandom(1)<0.05){
                Bubble b;
                bubbles.push_back(b);
                bubbles.back().reset(spawnLocationX);
            }
            
        }
        
        for (vector<Bubble>::iterator it=bubbles.begin(); it!=bubbles.end();)    {
            it->update();
            if(it->isDead()){
                
                it = bubbles.erase(it);
            }
            else{
                drawMesh.addVertex(it->pos);
                ++it;
                //   userParticlesMesh.addVertex(it->pos);
            }
        }
    }
    void draw(){
        glPointSize(5);
        drawMesh.drawVertices();
    }
    
};