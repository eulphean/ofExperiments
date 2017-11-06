// Author: Amay Kataria
// Date: 10/28/2017
// Description: Mesh experiments with openFrameworks.

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(ofColor::white);
  mesh.enableIndices();
  ofSetCircleResolution(70);
  ofEnableSmoothing();
  
  save = false;
}

//--------------------------------------------------------------
void ofApp::update(){
  
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (save) {
    ofBeginSaveScreenAsPDF(ofGetTimestampString() + ".pdf");
  }
  
  ofSetColor(ofColor::black);
  
  if (currentKey == 50) {
    ofPushMatrix();
      ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    // Draw vertices.
    for (int i = 0; i < mesh.getVertices().size(); i++) {
      glm::vec3 vertex = mesh.getVertices()[i];
      ofPushMatrix();
        ofTranslate(vertex);
        ofSetColor(ofColor::white);
        ofFill();
        ofDrawCircle(0, 0, 20);
      ofPopMatrix();
    }
    mesh.drawWireframe();
    
    ofPopMatrix();
  }
  
  if (currentKey == 49) {
    // Draw vertices.
    for (int i = 0; i < mesh.getVertices().size(); i++) {
      glm::vec3 vertex = mesh.getVertices()[i];
      ofPushMatrix();
        ofTranslate(vertex);
        ofSetColor(ofColor::white);
        ofFill();
        ofDrawCircle(0, 0, 10);
      ofPopMatrix();
    }
    mesh.draw();
  }
  
  if (currentKey == 51) {
    for (int i = 0; i < bright.size(); i++) {
      ofVec3f position = bright[i];
      ofFill();
      ofDrawTriangle(position.x-8, position.y, position.x+8, position.y, position.x, position.y -8);
    }
    
    for (int i = 0; i < mids.size(); i++) {
      ofVec3f position = mids[i];
      ofFill();
      ofDrawCircle(position, 5);
    }
    
    for (int i = 0; i < dark.size(); i++) {
      ofVec3f position = dark[i];
      ofNoFill();
      ofDrawRectangle(position, 10, 10);
    }
  }
  
  if (currentKey == 52) {
      mesh.draw();
      img.draw(0, 0);
  }
  
  if (save) {
    ofEndSaveScreenAsPDF();
    save = false;
  }
}

void ofApp::keyPressed(int key) {
  if (bright.size() > 0) {
    bright.clear();
  }
  
  if (mids.size() > 0) {
    mids.clear();
  }
  
  if (dark.size() > 0) {
    dark.clear();
  }
  
  if (mesh.hasVertices()) {
    mesh.clear();
  }
  
  switch(key) {
    
    // Create a random set of 2D vertices
    case 49 : {
      currentKey = 49;
      mesh.setMode(OF_PRIMITIVE_TRIANGLES);
      // Add a set of random points as vertices.
      for (int i = 0; i < numOfPoints; i++) {
        glm::vec3 vertex (ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0);
        mesh.addVertex(vertex);
      }
      
      for (int i = 0; i < numOfPoints; i++) {
        // From.
        mesh.addIndex(i);
        
        for (int j = 0; j < 2; j++) {
          // Calculate To.
          int randomIdx = ofRandom(numOfPoints);
          while (randomIdx == i) {
            randomIdx = ofRandom(numOfPoints);
          }
          // Add to the mesh.
          mesh.addIndex(randomIdx);
        }
      }
     
      break;
    }
      
    case 50 : {
      currentKey = 50;
      mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
      float radiusArr[3] = { 165.0, 265.0, 365.0 };
      
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 360; j = j + theta) {
          glm::vec3 vertex(radiusArr[i] * cos(ofDegToRad(j)), radiusArr[i] * sin(ofDegToRad(j)), 0);
          mesh.addVertex(vertex);
        }
      }
      break;
    }
    
    case 51 : {
      currentKey = 51;
      img.load("bowie.png");
      img.setImageType(OF_IMAGE_GRAYSCALE);
      img.resize(300, 220);
      int pixelSkip = 5;
      
      for (int x=0; x < img.getWidth() ; x = x + pixelSkip) {
        for (int y=0; y< img.getHeight(); y = y + pixelSkip) {
          float brightness = img.getColor(x, y).getBrightness();
          ofVec3f pos(x*2, y*2, 0);
          if (brightness >= 150) {
            bright.push_back(pos);
          } else if (brightness >= 75 && brightness < 150) {
            mids.push_back(pos);
          } else {
            dark.push_back(pos);
          }
        }
      }
      break;
    }
    
    case 52: {
      currentKey = 52;
      img.load("tree.png");
      //img.resize(400, 38000);
      mesh.setMode(OF_PRIMITIVE_POINTS);
      
      int pixelSkip = 5;
      for (int x=0; x < img.getWidth() ; x = x + pixelSkip) {
        for (int y=0; y< img.getHeight(); y = y + pixelSkip) {
          float brightness = img.getColor(x, y).getBrightness();
          if (brightness < 100) {
            ofVec3f pos(x, y, 0);
            mesh.addVertex(pos);
          }
        }
      }
      break;
    }
    
    // If you want to save the file.
    case 115: {
      if (!save) {
        save = !save;
      }
      break;
    }
  }
}
