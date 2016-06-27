#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(RES_W/PREVIEW,RES_H/PREVIEW,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    
    ofGLFWWindowSettings settings;
    settings.width = 400;
    settings.height = 800;
    ofCreateWindow(settings);
    
	ofRunApp(new ofApp());

}
