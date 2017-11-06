#pragma once

#include "ofMain.h"
#include "ofxDelaunay2D.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    void keyPressed(int key);

    ofImage img;
    ofMesh mesh;
    bool save = true;
};
