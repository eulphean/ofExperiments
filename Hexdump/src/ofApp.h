#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    // Input file.
    ofFile inputFile1;
    ofFile inputFile2;
    vector<int> decimals1;
    vector<int> decimals2;
  
    // Maximum and minimum.
    int maxDecimal;
    int minDecimal;
  
    // 3D Camera
    ofEasyCam cam;
};
