#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    ofxPanel panel;
    ofxKinectV2 * kinect;
    ofTexture depthTexture;
};
