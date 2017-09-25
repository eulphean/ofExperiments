#include "ofApp.h"

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
  
  panel.loadFromFile("settings.xml");
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
      
      for (int i = 0; i <= height; i += pixelSkip) {
        for (int j = 0; j <= width; j += pixelSkip) {
          const pixelIndex = i + j * height;
          // Check if the brightness of this pixel is greater than my
          // minimum brightness.
          if (pixels[pixelIndex] > minBrightness) {
            sumX += i;
            sumY += j;
            sumBrightness += pixels[pixelIndex];
            numPixels++;
          }
        }
      }
      
      // Calculate average pixel values.
      avgX = sumX / numPixels;
      avgY = sumY / numPixels;
      avgBrightness = sumBrightness / numPixels;
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Depth texture at 10,10.
  depthTexture.draw(10, 10);
  
  // Draw a small circle at (avgX, avgY)
  ofSetColor(ofColor::purple);
  ofFill();
  ofDrawCircle(avgX, avgY, 5);
  
  // Change the sound based on avgBrightness.
  // Map the brightness to speed of the sound.
  
  // Threshold panel.
  panel.draw();
}
