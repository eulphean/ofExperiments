#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::white);
  ofSetFrameRate(60);
  
  // Initialize the vector.
  rotAngles = { 0, 50, 100, 150 };
  recColors = { ofColor::red, ofColor::green, ofColor:: black, ofColor::orange };
  blendModes = { OF_BLENDMODE_ALPHA, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN };
}

//--------------------------------------------------------------
void ofApp::update(){
  center.x = ofGetWidth() / 2;
  center.y = ofGetHeight() / 2;
  
  // Update rotation angles.
  for (int i = 0; i < rotAngles.size(); i++) {
    rotAngles[i] = rotAngles[i] + i + 1;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  
  ofPushMatrix();
    ofTranslate(center.x, center.y);
    for (int i = 0; i < rotAngles.size(); i++) {
        ofPushMatrix();
          ofRotateZ(rotAngles[i]);
          ofSetColor(recColors[i]);
          ofEnableBlendMode(blendModes[i]);
          ofDrawRectangle(0, 0, center.x, center.y);
        ofPopMatrix();
    }
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
