#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
  ofPoint center;
  
  float rotateAngle = 0;
  float elapsedTime;
  float scale = 0;
};
