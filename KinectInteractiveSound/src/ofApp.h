#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define PORT 8000

class ofApp : public ofBaseApp{

	public:
    const int pixelSkip = 3;
    const int minBrightness = 2500;

		void setup();
		void update();
		void draw();
  
  void updateSound();
  
    ofxPanel panel;
    ofxKinectV2 * kinect;
    ofTexture depthTexture;
  
    float avgX;
    float avgY;
    float avgBrightness;
  
  
    void setCurrentTrackAndPlay(int val, ofSoundPlayer * newCurrentTrack);
    
    ofxOscReceiver receive;
    ofVec2f mappedOsc;
    ofSoundPlayer *currentTrack = NULL;
  
    ofSoundPlayer track1;
    ofSoundPlayer track2;
    ofSoundPlayer track3;
};
