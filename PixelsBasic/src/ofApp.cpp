#include "ofApp.h"

using namespace std;
//--------------------------------------------------------------
void ofApp::setup(){
  ofLoadImage(p, "image.png");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  for (int i = 0; i < p.size(); i++) {
    cout << p.size() << endl;
    cout << (int) p[i] << endl;
  }
}
