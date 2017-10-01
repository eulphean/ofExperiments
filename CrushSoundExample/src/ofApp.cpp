#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //-------------------GRAPHIC SETUP--------------
  ofBackground(0);
  ofSetFrameRate(30);
  
  //--------PATCHING-------
  sample.load("/Users/amaykataria/Documents/of_v0.9.8_osx_release/apps/Experiments/CrushSoundExample/bin/data/howtostillmind.mp3");
  
  //sampler0 >> amp0 >> fader0;
  //sampler1 >> amp1 >> fader1;
  
  
  sampler0.addSample( &sample, 0 );
  sampler1.addSample( &sample, 1 );
  
  // ADSR Trigger - Without this the sample wouldn't play.
  envGate >> env >> amp0.in_mod();
  env >> amp1.in_mod();
  
  sampleTrig >> sampler0 >> amp0 >> decimator >> engine.audio_out(0);
  sampleTrig >> sampler1 >> amp1 >> decimator >> engine.audio_out(1);
  
  // Control the frequency using the GUI.
  osc_decimator_ctrl >> decimator.in_freq();
  
  // Setup the GUI.
  gui.setup("Decimator");
  osc1_group.add( osc_decimator_ctrl.set( "decimal", 44100, 200, 50000) );
  gui.add( osc1_group );
  gui.setPosition(5, 5);

  //------------SETUPS AND START AUDIO-------------
  engine.listDevices();
  engine.setDeviceID(1); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!
  engine.setup( 44100, 512, 3);
  
  // Trigger the sample.
  sampleTrig.trigger(1.0f);
  envGate.trigger(1.0f);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
