#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    const int numOfPoints = 10;
    const int theta = 30;
    ofMesh mesh;
    int currentKey;
    ofImage img;
    bool save;
  
    vector<ofVec3f> bright;
    vector<ofVec3f> mids;
    vector<ofVec3f> dark;
  
    void keyPressed(int key);
};
