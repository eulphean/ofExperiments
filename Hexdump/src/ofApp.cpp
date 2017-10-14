#include "ofApp.h"
#include "string.h"

using namespace std;

ofPoint center;
int length = 20;

// Starting counter is 10,10
// Calculate how many rectangles can fit on the screen

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::black);
  
  // Read the decimal file and store it in memory.
  inputFile1.open("imageZipConverted.txt");
  inputFile2.open("imageConverted.txt");
  
  string stringDec;
  
  // Set the max and min to arbitrarily large numbers.
  maxDecimal = -9999;
  minDecimal = 9999;
  
  if (inputFile2.is_open())
  {
    while (getline(inputFile1, stringDec))
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
      
      decimals1.push_back(decimal);
    }
    
    // Close the file
    inputFile2.close();
    cout << "Success: File read successfully.";
  } else {
    cout << "Unable to open this file." << endl;
  }
//  
//  if (inputFile2.is_open())
//  {
//    while (getline(inputFile2, stringDec))
//    {
//      // Convert string to decimal and push into the vector.
//      int decimal = stoi(stringDec);
//      
//      // Calculate maxima.
//      if (decimal > maxDecimal) {
//        maxDecimal = decimal;
//      }
//      
//      // Calculate minima.
//      if (decimal < minDecimal) {
//        minDecimal = decimal;
//      }
//      
//      decimals2.push_back(decimal);
//    }
//    
//    // Close the file
//    inputFile2.close();
//    cout << "Success: File read successfully.";
//  } else {
//    cout << "Unable to open this file." << endl;
//  }
  
    // Allocate new pixels.
    pixels.allocate(512, 512, 1);
  
    int s = 0;
    // Iterate through the pixels.
    for (int x = 0; x < pixels.getWidth(); x++)
    {
      for (int y = 0; y < pixels.getHeight(); y++)
      {
        int red = decimals1[s];

        // Create a color.
        ofColor color(red, 0, 0);
        
        // Set the color at the current position.
        pixels.setColor(x, y, color);
        
        s = s + 1;
      }
    }
    
    // Save our image.
    //ofSaveImage(pixels, "myImage.png");
    
    // Load our pixels into a texture.
    texture.loadData(pixels);
}

//--------------------------------------------------------------
void ofApp::update() {
  center.x = ofGetWidth()/2;
  center.y = ofGetHeight()/2;
}

//--------------------------------------------------------------
void ofApp::draw(){
  //cam.begin();
  
  // TODO: Control this with a GUI handle
  //int numOfSamples = decimals1.size();
  
  
  // Go through numOfSample and for every three samples, plot them on
  // x, y, z
  /*ofVec3f origin (0, 0, 0);
  for (int i = 0; i < numOfSamples; i=i+3) {
    ofVec3f position(decimals1[i]*5, decimals1[i+1]*5, decimals1[i+2]*5);
    ofPushMatrix();
      ofTranslate(position);
      //ofSetColor(ofColor(decimals[i], decimals[i+1], decimals[i+2]));
      ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
      ofFill();
      ofDrawLine(origin, position);
      //ofDrawBox(2);
    ofPopMatrix();
  }*/
  
  /*
    ofVec3f start(decimals1[0], decimals1[1], decimals1[2]);
    myPath.moveTo(start);
    
    for (int i = 3; i < numOfSamples; i=i+2) {
      ofVec3f vertex(decimals1[i]*10, decimals1[i+1]*10, decimals1[i+2]*10);
      ofPushMatrix();
        ofTranslate(vertex);
        ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
        ofFill();
        ofDrawBox(30);
      ofPopMatrix();
      myPath.lineTo(vertex);
    }
    
    myPath.setColor(ofColor::white);
    myPath.setFilled(false);
    myPath.setStrokeWidth(2);
    myPath.draw();
  */
  /*numOfSamples = decimals2.size();
  // Go through numOfSample and for every three samples, plot them on
  // x, y, z
  for (int i = 0; i < numOfSamples; i=i+3) {
    ofVec3f position(decimals2[i]*2, decimals1[i+1]*5, decimals1[i+2]*5);
    ofPushMatrix();
    ofTranslate(position-1000);
    //ofSetColor(ofColor(decimals[i], decimals[i+1], decimals[i+2]));
    ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
    ofFill();
    ofDrawBox(2);
    ofPopMatrix();
  }*/
  
  //cam.end();
  //ofPushMatrix();
  //ofScale(10, 10);
  texture.draw(ofGetWidth()/2, ofGetHeight()/2);
  //ofPopMatrix();
}
