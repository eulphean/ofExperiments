#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //--------PATCHING-------
  
  // Default output for the oscillator is out_saw. Multiplying with a
  // a float number changes the loudness of the signal.
  osc.out_sine() * 0.25f >> engine.audio_out(0);
  osc.out_sine() * 0.50f >> engine.audio_out(1);
  
  // This changes the pitch of the sin wave.
  // 80.0f >> osc.in_pitch();
  
  // Use a LFO to modulate the sine wave.
  lfo.out_triangle() >> osc.in_pitch();
  
  //------------SETUPS AND START AUDIO-------------
  engine.listDevices();
  engine.setDeviceID(1); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup( 44100, 512, 3);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  float pitch = ofMap(x, 0, ofGetWidth(), 48.0f, 72.0f);
  float lfoFreq = ofMap(y, 0, ofGetHeight(), 1.5f, 0.25f);
  pitch >> osc.in_pitch();
  lfoFreq >> lfo.in_freq();
}
