#include "swarmParticle.h"
#include "defines.h"
//------------------------------------------------------------------
swarmParticle::swarmParticle(){
	attractPoints = NULL;
}



//------------------------------------------------------------------
void swarmParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void swarmParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x =  ofRandom(RES_W);
	pos.y = ofRandom(RES_H);
	
	vel.x = ofRandom(-1.9, 1.9);
	vel.y = ofRandom(-1.9, 1.9);
	
	frc   = ofPoint(0,0,0);
    
    //float r = ofRandom(1);
    //if(r>0.5)
    twoModes=1;
    //else twoModes = -1;

	scale = ofRandom(0.5, 3.0);
    
	drag  = ofRandom(0.75, 0.998);
    closestPt=ofPoint(500,500);
    closest = -1;
    closestDist = 9999999;
   // radius = int(ofRandom(2,10));
//    if( mode == PARTICLE_MODE_NOISE ){
//		drag  = ofRandom(0.97, 0.99);
//		vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
//	}else{
//		
//	}
}

//------------------------------------------------------------------
void swarmParticle::update(){

		
		if( attractPoints ){

            if(frameMod>0){
                //1 - find closest attractPoint
                closestPt;
                closest = -1;
                closestDist = 9999999;
                
                for(unsigned int i = 0; i < attractPoints->size(); i++){
                    
                    float lenSq = ( attractPoints->at(i)-pos ).lengthSquared();
                    
                    if(  lenSq < closestDist ){
                        closestDist = lenSq;
                        closest = i;
                    }
                }
            }
			
			//2 - if we have a closest point - lets calcuate the force towards it
			if( closest != -1 ){
				closestPt = attractPoints->at(closest);
                

				float dist = 1/b2InvSqrt(closestDist);
                //float dist = sqrt(closestDist);
                
				//in this case we don't normalize as we want to have the force proportional to distance 
				frc = closestPt - pos;
                frc *= 1;
				vel *= drag;
				 
				//lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
				if( dist < 300 && dist > 20  ){
                    
					vel += frc * 0.003;
				}else{
					//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.02, ofGetElapsedTimef()*0.2);
					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.02, ofGetElapsedTimef()*0.2);
					vel += frc * 0.4;
				}
				
			}
		
		}
   // }
		
	//}
	
	
	//2 - UPDATE OUR POSITION
	
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
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

//------------------------------------------------------------------
void swarmParticle::draw(){

//	if( mode == PARTICLE_MODE_ATTRACT ){
//		ofSetColor(255, 63, 180);
//	}
//	else if( mode == PARTICLE_MODE_REPEL ){
//		ofSetColor(208, 255, 63);
//	}
//	else if( mode == PARTICLE_MODE_NOISE ){
//		ofSetColor(99, 63, 255);
//	}
//	else if( mode == PARTICLE_MODE_NEAREST_POINTS ){
//		
//	}
    if(twoModes == 1)ofSetColor(103, 160, 237, 200);
    else ofSetColor(237, 160, 103, 200);
	ofDrawCircle(pos.x, pos.y, scale * 4.0);
    
    
}

