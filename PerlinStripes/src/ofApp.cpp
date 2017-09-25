#include "ofApp.h"

int maxLines = 60;
int offset = 10;
int lineHeight = 100;
int scaleFactor = 15;
int rotateFactor = 360;
//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::white);
  ofSetFrameRate(60);
  ofSetCircleResolution(80);
}

//--------------------------------------------------------------
void ofApp::update(){
  center.x = ofGetWidth()/2;
  center.y = ofGetHeight()/2;
  
  elapsedTime = ofGetElapsedTimef();
  // ofSignedNoise value is between -1 to 1
  rotateAngle = ofSignedNoise(elapsedTime) * rotateFactor;
  scale = ofSignedNoise(elapsedTime) * scaleFactor;
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw all the lines using translate, push and pop matrix.
  
  ofPushMatrix();
  ofTranslate(center.x, center.y);
  
  for (int x = -400; x <= 400; x++) {
    ofPushMatrix();
      ofTranslate(x * offset, 0);
      ofRotate(x * 3);
      ofScale(scale, scale);
      ofSetColor(ofColor::black);
      ofSetLineWidth(2);
      ofDrawLine(x, -lineHeight, x, lineHeight);
      ofNoFill();
      ofSetLineWidth(1.5);
      ofDrawCircle(x, 0, 10);
    ofPopMatrix();
  }
  
  ofPopMatrix();
}
