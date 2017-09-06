#include "ofApp.h"

int numOfLines = 40;
ofPoint center;
//--------------------------------------------------------------
void ofApp::setup(){
  ofEnableSmoothing();
  ofBackground(ofColor::ghostWhite);
}

//--------------------------------------------------------------
void ofApp::update(){
  center.x = ofGetWidth()/2;
  center.y = ofGetHeight()/2;
}

void ofApp::stripePattern() {
  ofSetLineWidth(2);
  ofSetColor(ofColor::black);
  ofSetCircleResolution(100);
  for(int i =-numOfLines; i<numOfLines; i++){
    ofPushMatrix();
    ofTranslate(i * 20, 0);
    ofScale(15,20);
    ofRotate(i * 5);
    ofDrawLine(0, -100, 0, 100);
    ofNoFill();
    ofDrawCircle(0, 10, 10, 10);
    ofPopMatrix();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofPushMatrix();
  ofTranslate(center.x, center.y);
  stripePattern();
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
