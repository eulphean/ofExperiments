#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
    const skipPixel = 5;
    const minBrightness = 2500;

		void setup();
		void update();
		void draw();
  
    ofxPanel panel;
    ofxKinectV2 * kinect;
    ofTexture depthTexture;
  
    float avgX;
    float avgY;
    float avgBrightness; 
};
