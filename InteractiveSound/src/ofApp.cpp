#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // Setup the receiver to receive data on the port.
  receive.setup(PORT);
  
  // Cap your frame rate.
  ofSetFrameRate(60);
  
  // Set black background.
  ofSetBackgroundColor(ofColor::white);
  
  // Load and play the track.
  track1.load("track.wav");
  track2.load("howtostillmind.mp3");
  track3.load("thiswillchangeyourmind.mp3");
  
  track1.setVolume(0.75f);
  track2.setVolume(0.75f);
  track3.setVolume(0.75f);
  
  track1.setLoop(true);
  track2.setLoop(true);
  track3.setLoop(true);
}

void ofApp::updateSound() {
  // x => Speed will decrease as we move farther in x - direction.
  float newSpeed = ofMap(mappedOsc.x, 30, ofGetWidth(), 1.0f, 0.5f, true);
  if (currentTrack != NULL) {
    currentTrack -> setSpeed(newSpeed);
  }
}

void ofApp::setCurrentTrackAndPlay(int val, ofSoundPlayer * newCurrentTrack) {
  if (val) {
    // Check if there is alread a currentTrack that's playing.
    // Stop that track.
    if (currentTrack != NULL) {
      currentTrack -> stop();
      currentTrack = NULL;
    }
    
    currentTrack = newCurrentTrack;
    currentTrack -> play();
  } else {
    
    // Stop the track if there is a valid current track.
    if (currentTrack != NULL) {
      currentTrack -> stop();
      currentTrack = NULL;
    }
  }
}

void ofApp::update(){
  // Read the data on oscController.
  while (receive.hasWaitingMessages()) {
    ofxOscMessage m;
    // Set the next message.
    #pragma warning(disable: WARNING_CODE)
    receive.getNextMessage(&m);
    
    // Get the current track.
    if (m.getAddress() == "/3/toggle1") {
      int val = m.getArgAsInt(0);
      setCurrentTrackAndPlay(val, &track1);
    }
    
    if (m.getAddress() == "/3/toggle2") {
      int val = m.getArgAsInt(0);
      setCurrentTrackAndPlay(val, &track2);
    }
    
    if (m.getAddress() == "/3/toggle3") {
      int val = m.getArgAsInt(0);
      setCurrentTrackAndPlay(val, &track3);
    }
    
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
  
  // Show the text
  ofDrawBitmapString("SYSTEM", 940, ofGetHeight()/2);
}
