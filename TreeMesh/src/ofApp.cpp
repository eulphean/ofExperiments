#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::white);
  img.load("tree.png");
  img.resize(400, 360);
  mesh.setMode(OF_PRIMITIVE_POINTS);
  ofEnableSmoothing();
  ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update(){
  int pixelSkip = 5;
  for (int x = 0; x < img.getWidth(); x += pixelSkip) {
    for (int y = 0; y < img.getHeight(); y += pixelSkip) {
      float brightness = img.getColor(x, y).getBrightness();
      if (brightness > 20) {
        glm::vec3 pos (x*2, y*2, 0);
        mesh.addVertex(pos);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  if (save) {
    ofBeginSaveScreenAsPDF(ofGetTimestampString() + ".pdf");
  }
  
  ofNoFill();
  ofSetColor(ofColor::black);
  
  int theta = 360/mesh.getVertices().size();
  for (int i = 0; i < mesh.getVertices().size(); i++) {
    glm::vec2 point(mesh.getVertices()[i].x, mesh.getVertices()[i].y);
    ofPushMatrix();
      ofTranslate(point);
      ofRotateZDeg(45);
      ofDrawRectangle(0, 0, 6, 6);
    ofPopMatrix();
  }
 
  if (save) {
    ofEndSaveScreenAsPDF();
    save = false;
  }
}

void ofApp::keyPressed(int key) {
  if (!save) {
    save = !save;
  }
}
