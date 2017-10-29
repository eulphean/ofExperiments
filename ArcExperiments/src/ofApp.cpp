#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofPath curve;  
	ofPoint p(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);  
	curve.arc(p, 300, 300, 0, 210);  
	//curve.arcNegative(p, 200, 200, 210, 0);
	curve.close();  
	curve.setArcResolution(60);  
	ofColor c(255, 0,0);  
	curve.setFillColor(c);  
	curve.setFilled(true);  
	curve.draw();
}
