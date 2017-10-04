#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
  
    // pdsp modules
    ofxPDSPEngine   engine;
  
    pdsp::Sampler       sampler0;
    pdsp::Sampler       sampler1;
    pdsp::Amp           amp0;
    pdsp::Amp           amp1;
  
    pdsp::SampleBuffer  sample;
    pdsp::ADSR          env;
  
    ofxPDSPTrigger envGate;
    ofxPDSPTrigger sampleTrig;
  
    pdsp::Decimator     decimator;

    ofxPanel gui;
    ofxPDSPValue        osc_decimator_ctrl;
    ofxPDSPValue        osc_noise_pitch_ctrl;
    ofxPDSPValue        osc_noise_bit_ctrl;
    ofParameterGroup    osc1_group;
  
    pdsp::BitNoise      noise;
};
