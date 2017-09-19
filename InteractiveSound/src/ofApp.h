#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// Update the port after setting the right port through TouchOSC.
#define PORT 8000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void updateSound();
  
    ofxOscReceiver receive;
    ofVec2f mappedOsc;
    ofSoundPlayer track;
};
