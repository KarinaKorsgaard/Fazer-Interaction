#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxAutoReloadedShader.h"
#include "ofxBox2d.h"
#include "ofxSyphon.h"
#include "ofxSvg.h"

#include "defines.h"


#include "swarmParticle.h"
#include "binnedSystem.h"
#include "perlinParticle.h"

#include "videoLoops.h"

#include "ParticleSystemSpawnTexture.h"

class CustomParticle : public ofxBox2dCircle {
    
public:
    int age=0;
    float radius;
    CustomParticle() {
        radius = getRadius();
    }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<ofxOscReceiver>receivers;
    vector<vector<ofPolyline>>blobs;
    
    int binnedReset;

    float					time;
    float					timeStep;

    vector<ofVec3f>			spawnPositions;
    ofPixels				maskPixels;

    ParticleSystemSpawnTexture	spawnParticles;
    
    bool					drawGui;
    bool bDebug = true;

    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameterGroup visualControl;
    ofParameterGroup group;
    ofParameter<float>offSet1X,offSet2X,offSet3X,offSet4X,b2bBounce;
    ofParameter<float>offSet1Y,offSet2Y,offSet3Y,offSet4Y;
    ofParameter<float>scale1,scale2,scale3,scale4;
    ofParameter<int>smoothe;
    ofParameter<int>resample;
    ofParameter<int>numAttractionP,attractionPointOverlap;
    ofParameter<int>overLap1,overLap2,overLap3;
    ofParameter<bool>swarm,cluster,perlin,bUserParticles,bBox2d,simplify, drawAnimals;
    ofParameter<ofColor>swarmColor;
    ofParameter<ofColor>clusterRange1;
    ofParameter<ofColor>clusterRange2;
    
    // POINTS IN BLOBS!
    vector <ofPoint> attractPoints;
    
    // swarming Particles
    vector <swarmParticle> swarmParticles;
    void resetParticles();
    
    // perlin Particles
    vector <PerlinParticle> perlinParticles;
   
    //clusters
    vector<binnedSystem>clusters;
    binnedSystem backgroundCluster;
    vector<ofImage>theTrees;
    
    
    ofFbo pointSplineFbo;
    ofTexture sparkImg;
    ofTexture solid;
    ofTexture dot;
    ofxAutoReloadedShader pointSpline;
    
    // swarm mesh and vbo
    ofMesh mesh;
    ofVbo vbo;
    vector<int>pointSizes;
    
    //box 2 d mesh and vbo
    ofMesh meshBox2D;
    ofVbo vboBox2D;
    
    ofFbo finalRender;
    ofxSyphonServer syphon;


    //box 2 d;
    ofxBox2d                             box2d;
    vector <shared_ptr<CustomParticle> > customParticles;
    vector <shared_ptr<ofxBox2dCircle> >  circles;
    vector <shared_ptr<ofxBox2dEdge> >   edges;
    vector <shared_ptr<ofxBox2dPolygon> > polyShapes;
    
    
    //inverse sqrt
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
    
    ofImage trees;
    vector<burstingBubbles> busting;
    int frameMod;

    ofVideoPlayer videoBack;
    ofVideoPlayer videoFront;
    

    

    
   
};
