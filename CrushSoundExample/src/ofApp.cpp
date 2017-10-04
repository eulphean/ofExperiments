#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //-------------------GRAPHIC SETUP--------------
  ofBackground(0);
  ofSetFrameRate(30);
  
  //--------PATCHING-------
  sample.load("/Users/amaykataria/Documents/of_v0.9.8_osx_release/apps/Experiments/CrushSoundExample/bin/data/howtostillmind.mp3");
  
  // Sample 0, 1 are taking the sample buffer.
  sampler0.addSample( &sample, 0 );
  sampler1.addSample( &sample, 1 );
  
  // ADSR Trigger - Without this the sample wouldn't play.
  envGate >> env >> amp0.in_mod();
  env >> amp1.in_mod();
  
  osc_noise_pitch_ctrl >> noise.in_pitch();
  osc_noise_bit_ctrl >> noise.in_bits();
  
  noise * dB(-24.0f) >> amp0 >> engine.audio_out(0);
  noise * dB(-24.0f) >> amp1 >> engine.audio_out(1);
  
  sampleTrig >> sampler0 >> amp0 >> decimator >> engine.audio_out(0);
  sampleTrig >> sampler1 >> amp1 >> decimator >> engine.audio_out(1);
  
  // Control the frequency using the GUI.
  osc_decimator_ctrl >> decimator.in_freq();
  
  // Setup the GUI.
  gui.setup("Decimator");
  osc1_group.add( osc_decimator_ctrl.set( "decimator", 44100, 200, 50000) );
  osc1_group.add( osc_noise_pitch_ctrl.set( "pitch", -100.0f, 10.0f, 100.0f) );
  osc1_group.add( osc_noise_bit_ctrl.set( "bit", 6, 1, 12) );
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
