#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    // Input file.
    ofFile inputFile;
    vector<int> decimals;
  
    // Maximum and minimum.
    int maxDecimal;
    int minDecimal;
  
    // 3D Camera
    ofEasyCam cam;
};
