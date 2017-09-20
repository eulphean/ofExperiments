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
    void setCurrentTrackAndPlay(int val, ofSoundPlayer * newCurrentTrack);
  
    ofxOscReceiver receive;
    ofVec2f mappedOsc;
    ofSoundPlayer track1;
    ofSoundPlayer track2;
    ofSoundPlayer track3;
  
    ofSoundPlayer *currentTrack = NULL;
};
