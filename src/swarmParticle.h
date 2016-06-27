#pragma once
#include "ofMain.h"


class swarmParticle{

	public:
		swarmParticle();
		
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
    
    int twoModes;
       // int radius;
    bool repel;
    
    ofPoint closestPt;
    int closest = -1;
    float closestDist = 9999999;
		
    vector <ofPoint> * attractPoints;
   
    int* frameMod;
    /// This is a approximate yet fast inverse square-root.
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