#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
   
    
   // videoBack.load("test_v1.mp4");
 //   videoFront.load("forest/visual_v1_alpha.mov");
  //  videoBack.setLoopState(OF_LOOP_NORMAL);

   // videoFront.play();
   // videoBack.play();
    ofSetVerticalSync(false);  
    
    trees.load("bubbles.jpg");
    
    group.setName("FazerParticles");
    parameters.setName("offsetControl");

    ofParameterGroup one,two,three,four;
    one.setName("one");
    two.setName("two");
    three.setName("three");
    four.setName("four");
    
    one.add(offSet1X.set("offSet1X",0,-100,900));
    one.add(offSet1Y.set("offSet1Y",0,-500,500));
    one.add(scale1.set("scale1",0,3,0));
    // this overlap is always 0.
    two.add(offSet2X.set("offSet2X",0,700,1700));
    two.add(offSet2Y.set("offSet2Y",0,-500,500));
    two.add(scale2.set("scale2",0,3,0));
    
    two.add(overLap1.set("overLap1",0,-700,700));
   
    three.add(offSet3X.set("offSet3X",0,1500,2500));
    three.add(offSet3Y.set("offSet3Y",0,-500,500));
    three.add(scale3.set("scale3",0,3,0));
    
    three.add(overLap2.set("overLap2",0,-700,700));
    
    four.add(offSet4X.set("offSet4X",0,2300,3300));
    four.add(offSet4Y.set("offSet4Y",0,-500,500));
    four.add(scale4.set("scale4",0,3,0));
    
    four.add(overLap3.set("overLap3",0,-700,700));
    
    parameters.add(numAttractionP.set("numAttraction",5,1,20));
    
    visualControl.setName("visuals");
    visualControl.add(swarm.set("swarm", true));
    visualControl.add(cluster.set("clusters", true));
    visualControl.add(perlin.set("perlin", false));
    visualControl.add(bUserParticles.set("bUserParticles", false));
   
    visualControl.add(bBox2d.set("bBox2d", true));
    visualControl.add(b2bBounce.set("b2bBounce",0.5,0,3));
    visualControl.add(drawAnimals.set("drawVideoLoops", false));
    
    ofParameterGroup colorControl;
    colorControl.add(clusterRange1.set("background",ofColor(255,255), ofColor(0,0),ofColor(255)));
    colorControl.add(swarmColor.set("swarmnBox2dColor",ofColor(255,255), ofColor(0,0),ofColor(255)));
    colorControl.add(clusterRange2.set("cluster color",ofColor(255,255), ofColor(0,0),ofColor(255)));
    
    parameters.add(one);
    parameters.add(two);
    parameters.add(three);
    parameters.add(four);
    group.add(parameters);
    group.add(visualControl);
    group.add(colorControl);

    gui.setup(group);
    gui.loadFromFile("settings.xml");
    
    
    // osc receiver setup:
    for(int i = 0; i<4;i++){
        ofxOscReceiver rec = *new ofxOscReceiver;
        int port = 8001+i;
        rec.setup(port);
        receivers.push_back(rec);
    }
    
    //15 blob limit for each kinect:
    blobs.resize(4);
    for(int i = 0; i< blobs.size();i++){
        blobs[i].resize(15);
    }
    
    for(int i = 0; i<5;i+=4){
        ofImage img = *new ofImage;
        img.load("trees/puutyved-0"+ofToString(i+1)+".png");
        theTrees.push_back(img);
    }

    
    pointSplineFbo.allocate(RES_W,RES_H);
    pointSplineFbo.begin();
    ofClear(0);
    pointSplineFbo.end();
    
    finalRender.allocate(RES_W,RES_H);
    finalRender.begin();
    ofClear(0);
    finalRender.end();
    

    sparkImg.allocate(128,128, GL_RGBA);
    ofDisableArbTex();
     ofLoadImage(sparkImg, "dot.png");
    ofEnableArbTex();
    
    solid.allocate(128,128, GL_RGBA);
    ofDisableArbTex();
    ofLoadImage(solid, "solid.png");
    ofEnableArbTex();
    
    pointSpline.load("shader/shader");
 

    // swarms
    int num = SWARM_NUM;
    swarmParticles.assign(num, swarmParticle());
    for(unsigned int i = 0; i < swarmParticles.size(); i++){
        swarmParticles[i].setAttractPoints(&attractPoints);;
        swarmParticles[i].reset();
        swarmParticles[i].frameMod=&frameMod;
        pointSizes.push_back(ofRandom(5, 10));
        
    }
    
    for(int i = 0; i< 25; i++){
        burstingBubbles b = *new burstingBubbles;
        busting.push_back(b);
        busting.back().setup(ofPoint(i*(RES_W/25),800), 400, "animals/1.mov", "animals/2.mov", &attractPoints);
      
    }

    // perlin
    for(unsigned int i = 0; i < PERLIN_NUM; i++){
        PerlinParticle p;
        perlinParticles.push_back(p);
        perlinParticles.back().setup(&attractPoints);
    }
    
    //cluster / binned sys
    for(int i = 0 ; i<CLUSTER_NUM; i++){
        binnedSystem b;
        clusters.push_back(b);
        clusters.back().setup(ofVec2f((RES_W/(CLUSTER_NUM+1))*(i+1),ofRandom(100, RES_H-100)), ofRandom(100,220), ofRandom(10,60), ofColor(ofRandom(clusterRange1->r,clusterRange2->r),ofRandom(clusterRange1->g,clusterRange2->g),ofRandom(clusterRange1->b,clusterRange2->b)));
        clusters.back().attractPoints = &attractPoints;
        clusters.back().tree = &theTrees[int(ofRandom(theTrees.size()))];
    }

    
//    // animals; // class is not included, but still in src folder:
//    string path = "animals";
//    ofDirectory dir(path);
//    //only show png files
//    dir.allowExt("png");
//    dir.listDir();
//    
//    for(int i = 0; i<dir.size();i++){
//        Animal anAnimal;
//        theAnimals.push_back(anAnimal);
//        theAnimals.back().setupFromFile(dir.getPath(i),ofVec2f(i*300,0));
//    }
//    animalShader.load("shader/animal");
//    animalRender.allocate(RES_W,RES_H,GL_RGBA);
//    animalRender.begin();
//    ofClear(0);
//    animalRender.end();
    

    //box2d setup
    box2d.init();
    box2d.setGravity(0, 0.1);
    box2d.createGround(0, RES_H, RES_W, RES_H);
    box2d.setFPS(30.0);
    box2d.registerGrabbing();
    
    // Box2d
//    box2d.init();
//    box2d.setGravity(0, 10);
//    box2d.createGround(0, RES_H, RES_W, RES_H);
//    box2d.setFPS(30.0);

    
    int texSize = 100;
    spawnParticles.init( texSize ); // number of particles is (texSize * texSize)
    time = 0.0f;
    timeStep = 1.0f / 60.0f;
    
    drawGui = true;

    
    
    syphon.setName("FazerParticles");
}

//--------------------------------------------------------------
void ofApp::update(){

    frameMod = ofGetFrameNum()%2;

    vector<float>ofsetlistX;
    ofsetlistX={offSet1X,offSet2X,offSet3X,offSet4X};
    
    vector<float>ofsetlistY;
    ofsetlistY={offSet1Y,offSet2Y,offSet3Y,offSet4Y};
    
    vector<float>scaleList;
    scaleList={scale1,scale2,scale3,scale4};


    for(int r = 0; r<receivers.size();r++){
        while(receivers[r].hasWaitingMessages()){
            
            
            ofxOscMessage msg;
            receivers[r].getNextMessage(msg);
            
            
            
            if(msg.getAddress()=="/numPeople"){
              
             //   cout<<"numppl"+ ofToString(msg.getArgAsInt(0))<<endl;
                for(int i=msg.getArgAsInt(0);i<blobs[r].size();i++){
                    blobs[r][i].clear();
                    
                }
               
                //cout<<"blob r "+ ofToString(blobs[r].size())<<endl;
            }
            
            if(msg.getNumArgs()>3){
                int pointCloudIndx=0;
                pointCloudIndx = ofToInt(ofSplitString(msg.getAddress(),"/")[1]);
              
              //  cout<<"point cl "+ ofToString(pointCloudIndx)<<endl;
       
                if(pointCloudIndx<blobs[r].size()){
                    blobs[r][pointCloudIndx].clear();
    
                    for(int  i = 0 ; i< msg.getNumArgs();i+=2){
                        
                        ofVec2f pt;
                        pt.x= msg.getArgAsFloat(i)*scaleList[r] + ofsetlistX[r];
                        pt.y= msg.getArgAsFloat(i+1)*scaleList[r] + ofsetlistY[r];;
                        
                        blobs[r][pointCloudIndx].addVertex(pt);
                        
                    }
                    if(blobs[r][pointCloudIndx].size()>0) blobs[r][pointCloudIndx].addVertex(blobs[r][pointCloudIndx].getVertices()[0]);

                }
            }
           //  cout<<"blob r "+ ofToString(blobs[r].size())<<endl;
        }
    }
    
    // find overlapping users: from overlapping tracking stuff... / not sure this will work
//    for(int i = 0 ; i<users.size();i++){
//        users[i].userExists = true;
//        for(int u = 0 ; u<users.size();u++){
//            if(i!=u){
//                if(users[i].receiverNum!= users[u].receiverNum){
//                    if(users[i].pos.distance(users[u].pos)  < 30){
//                        users[u].userExists = false;
//                    }
//                }
//            }
//        }
//    }
    
    
//    for (vector<User>::iterator it=users.begin(); it!=users.end();)    {
//        it->update();
//        if(it->isDead())
//            it = users.erase(it);
//        else
//            ++it;
//    }
//
    if(bDebug){

        blobs[0][0].clear();
        //testPoly
        ofPolyline line;
        float i = 0;
        while (i < TWO_PI ) { // make a heart
            float r = (2-2*sin(i) + sin(i)*sqrt(abs(cos(i))) / (sin(i)+1.4)) * -80;
            float x = ofGetWidth()/2 + cos(i) * r;
            float y = ofGetHeight()/2 + sin(i) * r;
            line.addVertex(ofVec2f(x+offSet1X,y+offSet1Y));
            i+=0.005*HALF_PI*0.5;
        }
        
        while (i < TWO_PI ) { // make a heart
            float r = (2-2*sin(i) + sin(i)*sqrt(abs(cos(i))) / (sin(i)+1.4)) * -80;
            float x = ofGetWidth()/2 + cos(i) * r;
            float y = ofGetHeight()/2 + sin(i) * r;
            line.addVertex(ofVec2f(x+20,y+20));
            i+=0.005*HALF_PI*0.5;
        }
        
        line.close(); // close the shape
        
        blobs[0][0]=line;
    }
    
    
     //make attraction points from blobs:
  //  if(frameMod==0){ //make new attraction point every second frame
        attractPoints.clear();
        
        vector<int>overLaps;
        overLaps={0,overLap1,overLap2,overLap3};
        
        for(int i = 0; i<blobs.size();i++){
            for(int u = 0; u<blobs[i].size();u++){
                
                ofPolyline p=blobs[i][u];
                
                if(p.size()>0){
                    attractPoints.push_back(p.getCentroid2D());
                    for( int pt = 0; pt < p.getVertices().size(); pt+=numAttractionP) {
                        if(p.getVertices().at(pt).x>overLaps[i]+ofsetlistX[i])attractPoints.push_back(p.getVertices().at(pt));
                        
                    }
                }
            }
        }

    // add mouse interaction on debug
    if(bDebug)attractPoints.push_back(ofPoint((RES_W/ofGetWidth() ) * mouseX, (RES_W/ofGetWidth())*mouseY));
    if(bUserParticles){
        time += timeStep;
        
        spawnPositions.clear();
        for(int i = 0; i<blobs.size();i++){
            for(int u = 0; u<blobs[i].size();u++){
                ofPolyline poly = blobs[i][u].getResampledByCount(50);
                
                
                for( int p = 0; p < poly.getVertices().size(); p++) {
                    ofVec3f spawnPos;
                    spawnPos.x = ofMap( poly.getVertices()[p].x + ofRandom(-5,5), 0, RES_W, -1.,1. );
                    spawnPos.y = ofMap( poly.getVertices()[p].y + ofRandom(-5,5), 0, RES_H,  -1., 1.);
                    spawnPos.z = ofMap( poly.getVertices()[p].x, 0, RES_W, -0.2, 0.2 );
                    
                    spawnPositions.push_back( spawnPos );
                }
                
            }
        }
        
        int tmpIndex = 0;
        if(spawnPositions.size()>0){
            for( int y = 0; y < spawnParticles.textureSize; y++ )
            {
                for( int x = 0; x < spawnParticles.textureSize; x++ )
                {
                    ofVec3f spawnPos;
                    
                    spawnPos = spawnPositions.at( (int)ofRandom(spawnPositions.size()-1) );
                    
                    spawnParticles.spawnPosBuffer.getPixels()[ (tmpIndex * 3) + 0 ] = spawnPos.x;
                    spawnParticles.spawnPosBuffer.getPixels()[ (tmpIndex * 3) + 1 ] = spawnPos.y;
                    spawnParticles.spawnPosBuffer.getPixels()[ (tmpIndex * 3) + 2 ] = spawnPos.z;
                    
                    tmpIndex++;
                }
            }
            
            spawnParticles.spawnPosTexture.loadData( spawnParticles.spawnPosBuffer );
            
        }
        spawnParticles.update(time,timeStep);
        
    }
    
    if(drawAnimals)for(int i = 0 ; i< busting.size();i++)busting[i].update();
    
    if(bBox2d){
       
        for(auto c:customParticles){if(c->age>600)c->alive=false;}
        ofRemove(customParticles, ofxBox2dBaseShape::shouldRemove);
        
        if(frameMod==1){ // make new edge every second frame
            edges.clear();
            polyShapes.clear();

            for(int i = 0; i<blobs.size();i++){
                for(int u = 0; u<blobs[i].size();u++){

                    ofPolyline drawing = blobs[i][u];
                    if(drawing.size()>2 && drawing.getBoundingBox().getArea()>15){
                        
                        drawing.setClosed(true);
                        drawing = drawing.getResampledByCount(60);
                        
                        // save the outline of the shape
                        
                        shared_ptr<ofxBox2dPolygon> poly = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);


                        poly->addVertices(drawing.getVertices());
                        poly->setPhysics(1.0, 0.3, 0.3);
                        poly->triangulatePoly();
                        poly.get()->create(box2d.getWorld());
                        polyShapes.push_back(poly);
                        
                        
//                        shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
//                        for (int d=0; d<drawing.size(); d++) {
//                            edge.get()->addVertex(drawing[d]);
//                        }
//                      //  poly.setPhysics(1, .2, 1);  // uncomment this to see it fall!
//                        edge.get()->create(box2d.getWorld());
//                        edges.push_back(edge);
                        
                    }
                }
            }
          
        }
//        // add bubbles randomly
        if(ofRandom(1)<0.1){
            customParticles.push_back(shared_ptr<CustomParticle>(new CustomParticle));
            CustomParticle * p = customParticles.back().get();
            float r = ofRandom(25, 40);		// a random radius 4px - 20px
            p->setPhysics(ofRandom(0.1,0.5), b2bBounce ,ofRandom(1,5));
            p->setup(box2d.getWorld(), ofRandom(0,RES_W), ofRandom(100,RES_H-100), r);
            p->radius=p->getRadius();
            p->setVelocity(ofRandom(-0.5,0.5), ofRandom(-0.5,0.5));
   
        }
        
//        // add some circles every so often
//        if((int)ofRandom(0, 10) == 0) {
//            shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
//            circle->setPhysics(0.3, 0.5, 0.1);
//            circle->age=0;
//            circle->setup(box2d.getWorld(),ofRandom(RES_W), -20, ofRandom(10, 20));
//            circles.push_back(circle);
//        }
       
        box2d.update();
//
//        // remove shapes offscreen
//
        // ofRemove(polyShapes, shouldRemove);
        // box2d mesh
        
        meshBox2D.clear();
        for(auto c:customParticles){
            c->age++;
            meshBox2D.addVertex(ofVec3f(float(c->getPosition().x),float(c->getPosition().y),float(c->radius/2.8)));
        }

        // load to vbo for pointspline replacement
        vboBox2D.setVertexData(&meshBox2D.getVertices()[0], customParticles.size(), GL_STATIC_DRAW);
    }

    

    if(swarm){
        mesh.clear();
        for(unsigned int i = 0; i < swarmParticles.size(); i++){
            swarmParticles[i].update();
            //pointSizes[i] += sin(ofGetElapsedTimef() *10) -5;
            mesh.addVertex(ofVec3f(swarmParticles[i].pos.x,swarmParticles[i].pos.y,pointSizes[i] ));
        }
        vbo.setVertexData(&mesh.getVertices()[0], SWARM_NUM, GL_STATIC_DRAW);
    }
    
    if(cluster){
        for(int i = 0 ; i< clusters.size();i++){
            clusters[i].update();
        }
    }
    if(perlin){
        for(unsigned int i = 0; i < perlinParticles.size(); i++){
            perlinParticles[i].update();
        }
    }

    //pointspline replacement
    if(cluster||swarm||bBox2d){
        pointSplineFbo.begin();
        ofClear(0, 0);
        glDepthMask(GL_FALSE);
        ofEnablePointSprites();
        ofEnableAlphaBlending();
        
        
        pointSpline.begin();
        pointSpline.setUniform1f("varyByColor", 0.);
        
        if(swarm){

            // bind the texture so that when all the points
            // are drawn they are replace with our dot image
            pointSpline.setUniform3f("col", float(swarmColor->r), float(swarmColor->g), float(swarmColor->b));
            solid.bind();
            vbo.draw(GL_POINTS, 0, (int)SWARM_NUM);
            solid.unbind();
           
        }

        
        if(bBox2d){
         //   pointSpline.setUniform1f("varyByColor", 1.);
            pointSpline.setUniform3f("col", float(swarmColor->r), float(swarmColor->g), float(swarmColor->b));
            // bind the texture so that when all the points
            // are drawn they are replace with our dot image
            solid.bind();
            vboBox2D.draw(GL_POINTS, 0, (int)customParticles.size());
            solid.unbind();
            pointSpline.setUniform1f("varyByColor", 0.);
           
        }
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        pointSpline.setUniform1f("varyByColor", 1.);
        if(cluster){
            for(int i = 0 ; i< clusters.size();i++){
                
                pointSpline.setUniform3f("col", float(clusterRange2->r+clusters[i].r), float(clusterRange2->g+clusters[i].g), float(clusterRange2->b+clusters[i].b));

                sparkImg.bind();
                clusters[i].vbo.draw(GL_POINTS, 0, (int)clusters[i].particleSystem.size());
                sparkImg.unbind();
                
                
            }
        }
        
        pointSpline.end();
        
        glDepthMask(GL_TRUE);
        
        pointSplineFbo.end();
    
        ofDisablePointSprites();
        ofDisableBlendMode();
        ofDisableAlphaBlending();
    }

    
    
    // final render
    finalRender.begin();
    ofClear(0);
    
    ofEnableAlphaBlending();

    ofBackground(clusterRange1);
    //videoBack.draw(0, 0, RES_W, RES_H);
   // trees.draw(0, 0, RES_W, RES_H);


    ofSetColor(0);
    for( int i = 0; i < blobs.size(); i++) {
        for( int u = 0; u < blobs[i].size(); u++) {
            
             blobs[i][u].draw();

        }
    }
    
    ofSetColor(255);
    if(cluster){
        for(auto c:clusters)c.drawTree();
    }
    ofSetColor(255);
    
    if(drawAnimals){
        for(int i = 0 ; i< busting.size();i++)busting[i].draw();
    }
    
    
    if(cluster||swarm||bBox2d){
        pointSplineFbo.draw(0,0);
    }


    
    if(perlin){
        for(auto p: perlinParticles)p.draw();
    }
 
    
    if(bUserParticles)spawnParticles.draw();
 
    if(bDebug){
        ofSetColor(255,255,0);
        ofDrawCircle( attractPoints.back() ,10);
        ofSetLineWidth(4);
        ofSetColor(255,255,0,200);
        ofDrawRectangle(offSet2X, 0, overLap1, RES_H);
        ofDrawRectangle(offSet3X, 0, overLap2, RES_H);
        ofDrawRectangle(offSet4X, 0, overLap3, RES_H);
        
        ofSetColor(ofColor::red);
        ofDrawLine(offSet1X, 0, offSet1X, RES_H);
        ofDrawLine(offSet2X, 0, offSet2X, RES_H);
        ofDrawLine(offSet3X, 0, offSet3X, RES_H);
        ofDrawLine(offSet4X, 0, offSet4X, RES_H);
        
        ofSetColor(ofColor::green);
        ofDrawLine(0, offSet1Y, RES_W, offSet1Y);
        ofDrawLine(0, offSet2Y, RES_W, offSet2Y);
        ofDrawLine(0, offSet3Y, RES_W, offSet3Y);
        ofDrawLine(0, offSet4Y, RES_W, offSet4Y);
        
        for(int i=0; i<polyShapes.size(); i++) {
            polyShapes[i]->draw();
            
            //ofCircle(polyShapes[i]->getPosition(), 3);
        }

    }
    
    finalRender.end();

    syphon.publishTexture(&finalRender.getTexture());
    
}



//--------------------------------------------------------------
void ofApp::draw(){
  //  ofDrawRectangle(300, 300, RES_W/10, RES_H/10);
    if(bDebug){
        
        
       // particles.drawGui();
       
        ofSetWindowTitle(ofToString(ofGetFrameRate()));
    }
    if( drawGui )
    {
        spawnParticles.drawGui();
         gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='d')bDebug = !bDebug;
    if(key=='s')drawGui = !drawGui;
//    if( key == '1'){
//        currentMode = PARTICLE_MODE_ATTRACT;
//        currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
//    }
//    if( key == '2'){
//        currentMode = PARTICLE_MODE_REPEL;
//        currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
//    }
//    if( key == '3'){
//        currentMode = PARTICLE_MODE_NEAREST_POINTS;
//        currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
//    }
//    if( key == '4'){
//        currentMode = PARTICLE_MODE_NOISE;
//        currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
//        resetParticles();
//    }	
//    
//    if( key == ' ' ){
//        resetParticles();
//    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(binnedReset>CLUSTER_NUM)binnedReset=0;
    clusters[binnedReset].binCenter.x=(x-300)*10;
    clusters[binnedReset].binCenter.y=(y-300)*10;
    binnedReset++;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


