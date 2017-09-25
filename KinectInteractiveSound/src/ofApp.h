#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

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
  
    ofSoundPlayer track1; 
};
