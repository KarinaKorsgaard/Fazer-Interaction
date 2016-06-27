//
//  binnedSystem.h
//  blobReceiverTest
//
//  Created by Karina Jensen on 12/06/16.
//
//

#ifndef binnedSystem_h
#define binnedSystem_h

#include "BinnedParticleSystem.h"
#include "defines.h"
#include "BinnedParticle.h"

class binnedSystem{
public:
    

    int radius;
    int padding;
    ofColor col;
    // binned
    float timeStep;
    float particleNeighborhood, particleRepulsion;
    float centerAttraction;
  
    vector<ofPoint>* attractPoints;
    int kBinnedParticles;
    BinnedParticleSystem particleSystem;
    bool bRepelFrom, slowMotion;
    ofImage* tree;
    vector<ofVec2f> repelFrom;
    ofVec2f binCenter;
    
    bool drawBalls = true;
    float originalBincenter;
    ofPath trunk;
    
    ofMesh mesh;
    ofVbo vbo;
    int uniqueWillow;
    int uniqueSpeed;
    int r,g,b;
    
    int theWidth;
    
    void setup(ofVec2f _center, int _amount, float _radius, ofColor _col){
        originalBincenter=_center.x;
        r = int(ofRandom(20));
        g = int(ofRandom(20));
        b = int(ofRandom(20));
      //  theWidth=1.05*sqrt(_amount)*_radius;
        uniqueWillow=int(ofRandom(10,35));
        uniqueSpeed=int(ofRandom(50,90));
        int modCount = 0;

//        for(int i = 0;i<RES_H-_center.y + uniqueSpeed ;i+=uniqueSpeed){
//            int modInverse = modCount%2 - 1;
//            trunk.curveTo(ofVec2f(_center.x+(uniqueWillow*modInverse),i+_center.y));
//            modCount++;
//        }

        
        theWidth = 1.05*sqrt(_amount)*_radius;
        
        col = _col;
        //// binned
        int binPower = 5;
        kBinnedParticles = _amount;
        padding = 20;
        particleNeighborhood = _radius;
        particleSystem.setup(RES_W + padding * 2, RES_H + padding * 2, binPower);
        
        for(int i = 0; i < kBinnedParticles; i++) {
            float x =  ofRandom(0,RES_W);
            float y = ofRandom(0, RES_H);
            BinnedParticle particle(x, y, 0, 0);
            particleSystem.add(particle);
        }
        
        vbo.disableNormals();
        mesh.disableNormals();
        slowMotion = true;
        particleRepulsion = .3;
        centerAttraction = .005;
  
        binCenter = _center;
        timeStep=60;

    }

    void drawTree(){
        float w =  tree->getWidth();
        float h = tree->getHeight() ;
        float newW = theWidth* 0.85;
        float newH   = ( h/w ) * newW;
     
        ofSetColor(0,200);
        tree->draw(originalBincenter - (newW / 2) , binCenter.y -newH/4, newW, newH );
      
    }

    
    void update(){


        
        // clusters
        repelFrom.clear();
        bRepelFrom = false;
        for(int i = 0; i<attractPoints->size();i++){
            if(1/b2InvSqrt((binCenter.x-attractPoints->at(i).x)*(binCenter.x-attractPoints->at(i).x)+(binCenter.y-attractPoints->at(i).y)*(binCenter.y-attractPoints->at(i).y))< particleSystem.getWidth()/2){
                repelFrom.push_back(attractPoints->at(i));
                bRepelFrom = true;
            }
        }
        
        particleSystem.setupForces();
      //  particleSystem.setTimeStep(timeStep);
        
        float willow = originalBincenter+(sin(ofGetFrameNum()/uniqueSpeed)*uniqueWillow)-uniqueWillow/2;
        
        binCenter.x = willow;
        //binCenter.y = binCenter.y+ofSignedNoise(-10,10, ofGetElapsedTimef()*0.001);

        if(!drawBalls) {
            ofSetLineWidth(1);
            glBegin(GL_LINES); // need GL_LINES if you want to draw inter-particle forces
        }
        
        mesh.clear();
        for(int i = 0; i < particleSystem.size(); i++) {
            BinnedParticle& cur = particleSystem[i];
            // global force on other particles
            particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
            // forces on this particle
            cur.bounceOffWalls(0, 0, particleSystem.getWidth(), particleSystem.getHeight());
            cur.addDampingForce();
            
            
            mesh.addVertex(ofVec3f(particleSystem[i].x,particleSystem[i].y,particleNeighborhood*0.3));
            
        }
        
        
        
        if(!drawBalls) {
            glEnd();
        }
        // single-pass global forces
        particleSystem.addAttractionForce(binCenter.x, binCenter.y, particleSystem.getWidth() , centerAttraction);
        if(bRepelFrom) {
            for(int i = 0 ; i<repelFrom.size();i++)particleSystem.addRepulsionForce(repelFrom[i].x + padding, repelFrom[i].y + padding, 100, 1);
        }
        particleSystem.update(ofGetLastFrameTime());
        
        
        vbo.setVertexData(&mesh.getVertices()[0], (int)particleSystem.size(), GL_STATIC_DRAW);

        
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
#endif /* binnedSystem_h */
