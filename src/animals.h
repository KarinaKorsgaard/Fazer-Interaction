#ifndef animal_H
#define animal_H

#pragma once
#include "ofMain.h"
#include "defines.h"

// Create a simple struct
class animalParticle {
public:
    ofVec2f orgPos;
    ofVec2f pos;

    float uniqueVal;
    
    ofVec3f col;
    int radius;

    
    void setup(int _x , int _y, ofVec3f _col, int _r){
        orgPos=ofVec2f(_x,_y);
        pos = orgPos;
        col=_col;
        radius=_r;
        uniqueVal=ofRandom(-1000,1000);

    }
    
};

class Animal{
public:

    vector<animalParticle>aParts;
   
    ofMesh mesh;
    ofVbo vbo;
    vector<int>sizes;
    
    vector<ofVec3f>colors;
    vector<ofVec3f>positionsAndSize;
    
    ofVec2f animalPos;
    
    int width;
    
    bool reposition;
    
    void setupFromFile(string file, ofVec2f _pos){
     //   mesh.setMode(OF_PRIMITIVE_POINTS);

        ofImage img;
        img.load(file);
        img.resize(img.getWidth()/10,img.getHeight()/10);
        width= img.getWidth()*5;
        animalPos=_pos;
        reposition= false;
        
        // setup particles:
        for(int i = 0 ; i<img.getWidth();i+=2){
            for(int u = 0 ; u<img.getHeight();u+=2){
                int pixColor = img.getColor(i,u).r+img.getColor(i,u).g+img.getColor(i,u).b;
                if(pixColor>0 && pixColor<3*255 && img.getColor(i,u).a>0){
                    animalParticle partone;
                    aParts.push_back(partone);
                    aParts.back().setup((i*5)+animalPos.x,(u*5)+animalPos.y,ofVec3f(img.getColor(i,u).r,img.getColor(i,u).g,img.getColor(i,u).b),int(ofRandom(2,5)));
                    
                    positionsAndSize.push_back(ofVec3f(aParts.back().pos.x,aParts.back().pos.y,aParts.back().radius));
                    colors.push_back(aParts.back().col);
                }
            }
        }
        vbo.setNormalData(&colors[0], colors.size(), GL_STATIC_DRAW);
        vbo.setVertexData(&positionsAndSize[0], positionsAndSize.size(), GL_STATIC_DRAW);
       
        cout<<file + " " +ofToString( aParts.size())+" pos "+ ofToString( animalPos.x) +" pos "+ ofToString( animalPos.y)  <<endl;
 
    }
    
    void update(int mx){
    
    }
    void checkCollision(vector<ofVec2f>userPos){
        reposition=false;
        for(int i = 0; i<userPos.size();i++){
            if(abs(userPos[i].x-animalPos.x)<width+userPos[i].y)reposition=true;
        }
    
    }
    
    
    void draw(){

    }

    
};
#endif
