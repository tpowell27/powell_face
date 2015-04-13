#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	finder.setup("haarcascade_frontalface_alt2.xml");
	finder.setPreset(ObjectFinder::Fast);
	finder.getTracker().setSmoothingRate(.3);
	cam.initGrabber(640, 480);
	sunglasses.loadImage("sunglasses.png");
	ofEnableAlphaBlending();
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    material.setShininess( 120 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    ofSetSphereResolution(24);
    sphere.setRadius(65);
    
    posx = 0.5;
    posx2 = 0.5;
    posx3 = 0.5;
    posy = 0.15;
    posy2 = 0.15;
    posy3 = -0.15;
    lft = 0.01;
}

void ofApp::update() {
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
	cam.update();
	if(cam.isFrameNew()) {
		finder.update(cam);
	}
    
    posx+=lft;
    posx2-=lft;
    posy+=lft;
    posy2-=lft;
    if((posx>=0.9)||(posx<=0.4)){
        lft*=-1;
    }
    if((posx2>=0.6)||(posx2<=0.1)){
        lft*=-1;
    }
    if((posx3>=0.6)||(posx3<=-0.6)){
        lft*=-1;
    }
    if((posy>=0.25)||(posy<=0.05)){
        lft*=-1;
    }
    if((posy2>=0.25)||(posy2<=0.05)){
        lft*=-1;
    }
    if((posy3>=-0.25)||(posy3<=0)){
        lft*=-1;
    }
}

void ofApp::draw() {
	cam.draw(0, 0);
    ofEnableDepthTest();
    
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    
    material.begin();
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
        
	for(int i = 0; i < finder.size(); i++) {
		ofRectangle object = finder.getObjectSmoothed(i);
		sunglasses.setAnchorPercent(.5, .5);
		float scaleAmount = .90 * object.width / sunglasses.getWidth();
		ofPushMatrix();
		ofTranslate(object.x + object.width * 1.75 * posx, object.y + object.height * posy);
		ofScale(scaleAmount, scaleAmount);
		sphere.draw();
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(object.getPosition());
		ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
		ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
		ofPopMatrix();
	}
    
    for(int i = 0; i < finder.size(); i++) {
        ofRectangle object = finder.getObjectSmoothed(i);
        sunglasses.setAnchorPercent(.5, .5);
        float scaleAmount = .90 * object.width / sunglasses.getWidth();
        ofPushMatrix();
        ofTranslate(object.x + object.width * 0 * posx2, object.y + object.height * posy2);
        ofScale(scaleAmount, scaleAmount);
        sphere.draw();
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(object.getPosition());
        ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
        ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
        ofPopMatrix();
    }

    for(int i = 0; i < finder.size(); i++) {
        ofRectangle object = finder.getObjectSmoothed(i);
        sunglasses.setAnchorPercent(.5, .5);
        float scaleAmount = .90 * object.width / sunglasses.getWidth();
        ofPushMatrix();
        ofTranslate(object.x + object.width * 1 * posx3, object.y + object.height * posy3);
        ofScale(scaleAmount, scaleAmount);
        sphere.draw();
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(object.getPosition());
        ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
        ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
        ofPopMatrix();
    }
}

//888-288-3282
