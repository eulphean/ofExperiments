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
  
  if (kinect != NULL){
    kinect->update();
    if( kinect->isFrameNew() ){
      // Load the next frame's texture into vector.
      depthTexture.loadData( kinect->getDepthPixels());
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Depth texture at 10,10.
  depthTexture.draw(10, 10);
  
  // Threshold panel.
  panel.draw();
}
