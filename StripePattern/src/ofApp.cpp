#include "ofApp.h"

using namespace std;

int numOfLines = 60;
bool screenShot = false;
int maxLength = 250;
int defaultLength = 100;
bool useConstantLength = true;

ofPoint center;
//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(7);
  ofEnableSmoothing();
  ofSetBackgroundColor(ofColor::black);
  
  int bufferSize = 256;
  
  left.assign(bufferSize, 0.0);
  right.assign(bufferSize, 0.0);
  volHistory.assign(400, 0.0);
  
  smoothedVol = 0.0;
  scaledVol	= 0.0;
  
  // Setup audio stream.
  ofSoundStreamSetup(0, 2, this, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
  center.x = ofGetWidth()/2;
  center.y = ofGetHeight()/2;
  
  //lets scale the vol up to a 0-1 range
  scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
  
  //lets record the volume into an array
  volHistory.push_back( scaledVol );
  
  //if we are bigger the the size we want to record - lets drop the oldest value
  if( volHistory.size() >= 400 ){
    volHistory.erase(volHistory.begin(), volHistory.begin()+1);
  }
  
  scaledVol *= 100.0;
  
  if (scaledVol > 2) {
    useConstantLength = false;
  } else {
    useConstantLength = true;
  }
}

void drawLine() {
  // Potentially read this line from some real time data.
  float length;
  float hue;
  
  if (useConstantLength) {
    length = defaultLength;
    hue = ofMap(ofGetHeight(), 0, ofGetHeight(), 0, 255);
  } else {
    length = ofRandom(0, ofGetHeight());
    hue = ofMap(length, 0, ofGetHeight(), 0, 255);
  }
  
  ofSetColor(ofColor::fromHsb(hue, 255, 255));
  ofDrawLine(0, length, 0, -length);
}

void drawCircle() {
  float rand = ofRandom(0, 10);
  ofNoFill();
  ofDrawCircle(0, 0, rand);
}

void drawTriangle() {
  ofDrawTriangle(50,10,10,40,90,40);
}

void ofApp::stripePattern() {
  ofSetLineWidth(2);
  ofSetColor(ofColor::black);
  ofSetCircleResolution(100);
  for(int i =-numOfLines; i<numOfLines; i++){
    // Stack the current coordinate system.
    ofPushMatrix();
    ofTranslate(i * 20, 0);

    // Draw lines along the base curve.
    drawLine();
    //drawCircle();
    
    // Reset the coordinate system.
    ofPopMatrix();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  if (screenShot) {
    ofBeginSaveScreenAsPDF(ofGetTimestampString()+".pdf", false);
  }
  
  if (scaledVol > 5) {
    cout << "Current audio is " << scaledVol;
  }
  
  ofPushMatrix();
  ofTranslate(center.x, center.y);
  stripePattern();
  ofPopMatrix();
}

void ofApp::audioIn(ofSoundBuffer & input) {
  float curVol = 0.0;
  
  // samples are "interleaved" (Left, Right, Left, Right)
  int numCounted = 0;
  
  //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
  for (int i = 0; i < input.getNumFrames(); i++){
    left[i]	= input[i*2]*0.5;
    right[i]= input[i*2+1]*0.5;
    
    curVol += left[i] * left[i];
    curVol += right[i] * right[i];
    numCounted+=2;
  }
  
  //this is how we get the mean of rms :)
  curVol /= (float)numCounted;
  
  // this is how we get the root of rms :)
  curVol = sqrt( curVol );
  
  smoothedVol *= 0.93;
  smoothedVol += 0.07 * curVol;
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
  ofImage img;
  img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
  img.save(ofGetTimestampString() + ".png");
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
