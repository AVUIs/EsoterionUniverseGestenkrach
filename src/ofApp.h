#pragma once

#include "ofMain.h"

#include "ECUUniverse.h"
#include "ctrls.h"
#include "ofxLeapMotion.h"

enum {
    CREATING, CREATED
};

class ECUBaseObject;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
        void mouseScrolled(float x, float y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void checkObjectSelected(int x, int y);
    
    ofLight pointLight2;

    
    void createObject();
    ECUBaseObject *currentEditingObj;
    
    
    ECUUniverse *universe;
    ctrls control;
    bool creatingObject;
    
    ofMesh mesh;
//    ofEasyCam cam;
    int curObj;
    
    bool showHelp;
    
    ofxLeapMotion leap;
	vector <ofxLeapMotionSimpleHand> simpleHands;
    int min[5];
    int max[5];
};
