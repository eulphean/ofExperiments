#include "ofApp.h"
#include "string.h"

using namespace std;

ofPoint center;

//--------------------------------------------------------------
void ofApp::setup(){
  // Read the decimal file and store it in memory.
  inputFile.open("music.txt");
  
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
  for (vector<int>::iterator it = decimals.begin(); it != decimals.end(); it++) {
    float hue = ofMap(*it, minDecimal, maxDecimal, 0, 255);
    ofSetColor(ofColor::fromHsb(hue, 255, 255));
    
    // Draw a line with a color represented by the hue.
    ofPoint from(center.x, center.y);
    ofPoint to(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
    ofDrawLine(from, to);
  }
}
