#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
    ofSpherePrimitive sphere;
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    ofMaterial material;
    
    float posx;
    float posx2;
    float posx3;
    float posy;
    float posy2;
    float posy3;
    float lft;
    
	ofVideoGrabber cam;
	ofxCv::ObjectFinder finder;
	ofImage sunglasses;
    
    
};
