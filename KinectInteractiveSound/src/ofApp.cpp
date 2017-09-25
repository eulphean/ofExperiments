#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  //Uncomment for verbose info from libfreenect2
  //ofSetLogLevel(OF_LOG_VERBOSE);
    
  ofBackground(30, 30, 30);
  
  // See if we have a valid Kinect hooked to the system.
  ofxKinectV2 tmp;
  vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();
  
  panel.setup("", "settings.xml", 10, 100);
  
  // Modify this if there are multiple Kinects hooked into the system.
  if (deviceList.size() > 0) {
    kinect = new ofxKinectV2();
    kinect -> open(deviceList[0].serial);
    panel.add(kinect->params);
  }
  
  // Load track.
  track1.load("howtostillmind.mp3");
  track1.setVolume(0.75f);
  track1.setLoop(true);
  
  // Start playing the track.
  // TODO: Hook it up with Touch OSC later.
  track1.play();
  
  panel.loadFromFile("settings.xml");
}

void ofApp::updateSound() {
  float newSpeed = ofMap(avgBrightness, 150, 165, 1.0f, 0.3f, true);
  track1.setSpeed(newSpeed);
}

//--------------------------------------------------------------
void ofApp::update(){
  int sumX = 0;
  int sumY = 0;
  int numPixels = 0;
  int sumBrightness = 0;
  
  if (kinect != NULL){
    kinect->update();
    if( kinect->isFrameNew() ){
      
      // Get depth pixels.
      ofPixels pixels = kinect -> getDepthPixels();
      
      // Create the texture from Kinect pixels.
      depthTexture.loadData(pixels);
      int height = depthTexture.getHeight();
      int width = depthTexture.getWidth();
      
      for (int x = 0; x < width; x += pixelSkip) {
        for (int y = 0; y < height; y += pixelSkip) {
          int pixelIndex = x + y * width;
          // Check if the brightness of this pixel is greater than my
          // minimum brightness.
          int pixelVal = (int) pixels[pixelIndex];
          if (pixelVal > 100) {
            sumX += x;
            sumY += y;
            sumBrightness += pixels[pixelIndex];
            numPixels++;
          }
        }
      }
      
      if (numPixels != 0) {
        // Calculate average pixel values.
        avgX = sumX / numPixels;
        avgY = sumY / numPixels;
        avgBrightness = sumBrightness / numPixels;
        // Update the sound.
        updateSound();
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Depth texture at 10,10.
  depthTexture.draw(0, 0);
  
  ofPushStyle();
  
  // Draw a small circle at (avgX, avgY)
  ofSetColor(ofColor::purple);
  ofFill();
  ofDrawCircle(avgX, avgY, 20);
  ofDrawBitmapString(avgBrightness, ofGetWidth()/2, ofGetHeight()/2);
  
  ofPopStyle();
  
  // Change the sound based on avgBrightness.
  // Map the brightness to speed of the sound.
  
  // Threshold panel.
  panel.draw();
}
