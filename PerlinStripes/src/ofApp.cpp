// Author: Amay Kataria
// Description: Stripe pattern with perlin noise.
// Date: 9/25/2017

#include "ofApp.h"

int maxLines = 60;
int offset = 10;
int lineHeight = 100;
int scaleFactor = 5;
int rotateFactor = 360;
//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::black);
  ofSetFrameRate(60);
  ofSetCircleResolution(80);
  
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
  
  elapsedTime = ofGetElapsedTimef();
  // ofSignedNoise value is between -1 to 1
  rotateAngle = ofSignedNoise(elapsedTime) * scaledVol;
  scale = ofSignedNoise(elapsedTime) * scaledVol * 5;
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw all the lines using translate, push and pop matrix.
  
  ofPushMatrix();
  ofTranslate(center.x, center.y);
  
  int radius = 0;
  
  for (int x = -400; x <= 400; x++) {
    ofPushMatrix();
      ofTranslate(x * offset, 0);
      ofRotateZDeg(x * 3);
      ofScale(scale, scale);
      ofColor hue = ofColor::fromHsb(ofRandom(255), 255, 255);
      ofSetColor(hue);
      ofSetLineWidth(2);
      ofDrawLine(x, -lineHeight, x, lineHeight);
      ofNoFill();
      ofSetLineWidth(1.5);
      /*if (x % 2 == 0) {
        ofFill();
        radius = 10;
      } else {
        ofNoFill();
        radius = 20;
      }*/
     // ofNoFill();
      ofDrawCircle(x, 0, scaledVol);
    ofPopMatrix();
  }
  
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

