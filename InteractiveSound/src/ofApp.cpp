#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // Setup the receiver to receive data on the port.
  receive.setup(PORT);
  
  // Cap your frame rate.
  ofSetFrameRate(60);
  
  // Set black background.
  ofSetBackgroundColor(ofColor::black);
  
  // Load and play the track.
  track.load("track.wav");
  track.setVolume(0.75f);
  track.setLoop(true);
  track.play();
}

void ofApp::updateSound() {
  // x => track speed.
  float newSpeed = ofMap(mappedOsc.x, 0, ofGetWidth(), 0.5f, 2.0f);
  track.setSpeed(newSpeed);
  
  // y => track volume.
  float newVolume = ofMap(mappedOsc.y, 0, ofGetHeight(), 0.1f, 2.0f);
  track.setVolume(newVolume);
}

//--------------------------------------------------------------
void ofApp::update(){
  // Read the data on oscController.
  while (receive.hasWaitingMessages()) {
    ofxOscMessage m;
    // Set the next message.
    #pragma warning(disable: WARNING_CODE)
    receive.getNextMessage(&m);
    
    // Parse the values from XY pad.
    if (m.getAddress() == "/3/xy") {
      float oscX = m.getArgAsFloat(0);
      float oscY = m.getArgAsFloat(1);
      mappedOsc.x = ofMap(oscX, 0, 1, 0, ofGetWidth());
      mappedOsc.y = ofMap(oscY, 0, 1, 0, ofGetHeight());
      
      // Modify sound with this new osc input.
      updateSound();
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofDrawCircle(mappedOsc.x, mappedOsc.y, 30);
}
