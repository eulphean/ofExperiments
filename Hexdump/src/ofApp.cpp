#include "ofApp.h"
#include "string.h"

using namespace std;

ofPoint center;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::black);
  
  // Read the decimal file and store it in memory.
  inputFile.open("audioDecimal.txt");
  
  string stringDec;
  
  // Set the max and min to arbitrarily large numbers.
  maxDecimal = -9999;
  minDecimal = 9999;
  
  if (inputFile.is_open())
  {
    while (getline(inputFile, stringDec))
    {
      // Convert string to decimal and push into the vector. 
      int decimal = stoi(stringDec);
      
      // Calculate maxima.
      if (decimal > maxDecimal) {
        maxDecimal = decimal;
      }
      
      // Calculate minima.
      if (decimal < minDecimal) {
        minDecimal = decimal;
      }
      
      decimals.push_back(decimal);
    }
    
    // Close the file
    inputFile.close();
    cout << "Success: File read successfully.";
  } else {
    cout << "Unable to open this file." << endl;
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  center.x = ofGetWidth()/2;
  center.y = ofGetHeight()/2;
}

//--------------------------------------------------------------
void ofApp::draw(){
  cam.begin();
  
  // Ask Chris if there is a way to print this.
  // TODO: Control this with a GUI handle
  int numOfSamples = decimals.size();
  
  // Go through numOfSample and for every three samples, plot them on
  // x, y, z
  for (int i = 0; i < numOfSamples; i=i+3) {
    ofVec3f position(decimals[i] * 10, decimals[i+1] * 10, decimals[i+2] * 10);
    ofPushMatrix();
      ofTranslate(position);
      ofSetColor(ofColor(decimals[i], decimals[i+1], decimals[i+2]));
      ofFill();
      ofDrawBox(2);
    ofPopMatrix();
  }
  
  cam.end();
}
