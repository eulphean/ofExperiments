#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
  ofPoint center; 
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
  
    vector<int> rotAngles;
    vector<ofColor> recColors;
    vector<ofBlendMode> blendModes;
};
