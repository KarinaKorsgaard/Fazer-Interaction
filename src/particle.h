//
//  particle.h
//  blobReceiverTest
//
//  Created by Karina Jensen on 08/06/16.
//
//

#ifndef particle_h
#define particle_h

class Particle {
public:
    ofVec2f pos;
    ofVec2f vel;
    int age;
    ofColor col;
    int radius;
    ofVec2f acc;
    bool isDead;
    ofMesh mesh;
    void setup(ofVec2f _pos){
        //ofRandom(_pos.x-10,_pos.x+10),ofRandom(_pos.y-10,_pos.y+10)
        pos = ofVec2f(_pos);
        vel = ofVec2f(0,0.3);
        age = 0;
        acc = ofVec2f(0,0.2);
        isDead = false;
    }
    

    void update(){
       
        vel+=acc;
        age++;
        if(age > 15){
            isDead = true;
        }
        pos+=vel;
    
    }
    void draw(){

       // ofDrawCircle(pos, 2);
    }
};


#endif /* particle_h */
