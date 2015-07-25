#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//--------------------------------------------------------------
	// Create a SuperCollider synth with default parameters
	// and spawn it on the server.
	//--------------------------------------------------------------
	synth = new ofxSCSynth("sine_harmonic");
	synth->create();

	//--------------------------------------------------------------
	// Load up a buffer with a sound file, and route its playback
	// to an fx unit via a 2-channel audio bus.
	//--------------------------------------------------------------
	buffer = new ofxSCBuffer();
	buffer->read(ofToDataPath("bell.aif", true));

	bus = new ofxSCBus(2);

	playbuf = new ofxSCSynth("playbuf_1");
	playbuf->set("bufnum", buffer->index);
	playbuf->set("outbus", bus->index);

	delay = new ofxSCSynth("fx_delay");
	delay->set("wet", 0.4);
	delay->set("delaytime", 0.4);
	delay->set("decaytime", 4);
	delay->set("inbus", bus->index);
	delay->set("outbus", 0);
	delay->addToTail();

	//--------------------------------------------------------------
	// Drawing setup
	//--------------------------------------------------------------
	ofBackground(0, 20, 50);
	ofSetBackgroundAuto(true);

    //Set framerate
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    //LEAP MOTION SETUP
	ofSetLogLevel(OF_LOG_VERBOSE);

    leap.open();
	leap.setupGestures();   // we enable our gesture detection here

}

//--------------------------------------------------------------
void ofApp::update(){

    //LEAP SENSOR DETECTION GETS UPDATED
    leap.updateGestures();  // check for gesture updates
	leap.markFrameAsOld();	//IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.

}

ofApp::~ofApp()
{
	//--------------------------------------------------------------
	// Free synths and buffers when we're done - otherwise
	// they'll hang about on SC server, occupying CPU and memory.
	//--------------------------------------------------------------
	synth->free();
	delay->free();
	buffer->free();
	bus->free();

}
//--------------------------------------------------------------
void ofApp::draw(){



	 /* Leap iGesture Key
     --------------------------------
     1 = Screen Tap
     2 = Key Tap
     3 = Swipe Right
     4 = Swipe Left
     5 = Swipe Down
     6 = Swipe Up
     7 = Swipe Forward
     8 = Swipe Backward (towards yourself)
     9 = Circle Left (counter-clockwise)
     10 = Circle Right (clockwise)
     --------------------------------
     */

    string msg;

    switch (leap.iGestures) {
        case 1:
            msg = "Screen Tap";
            msg += "\nPosition: "+ofToString(leap.screenTapPosition);
            break;

        case 2:
            msg = "Key Tap";
            msg += "\nPosition: " + ofToString(leap.keyTapPosition);
            synth->set("freq", leap.keyTapPosition[0] + 240);
            synth->set("amp", 0.8);
            break;

        case 3:
            msg = "Swipe Right";
            msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;

        case 4:
            msg = "Swipe Left";
            msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;

        case 5:
            msg = "Swipe Down";
            msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;

        case 6:
            msg = "Swipe Up";
            msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;

        case 7:
            msg = "Swipe Forward";
            msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;

        case 8:
            msg = "Swipe Backwards";
            msg += "\nSwipe Speed mm/s: " + ofToString(leap.swipeSpeed) + "\nDuration sec's: "+ofToString(leap.swipeDurationSeconds);
            break;

        case 9:
            msg = "Circle Left";
            msg += "\nCircle Radius: " + ofToString(leap.circleRadius) + "\nCircle Center: "+ofToString(leap.circleCenter);
            break;

        case 10:
            msg = "Circle Right";
            msg += "\nCircle Radius: " + ofToString(leap.circleRadius) + "\nCircle Center: "+ofToString(leap.circleCenter);
            break;

        default:
            msg = "Waiting for hand movement...";
            break;
    }

    ofSetColor(255);
    ofDrawBitmapString(msg, 20, 20);  // let's draw our message to the screen

    //ofEnableAlphaBlending();
    ofSetColor(0, 20, 50, 2);
  	ofFill();
  	ofRect(0, 0, ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    //--------------------------------------------------------------
	// Modulate synth params based on mouse position.
	//--------------------------------------------------------------

	if (button == 0)
	{
		synth->set("freq", x + 40);
		synth->set("amp", 1.0f - (float) y / ofGetHeight());
		synth->set("pan", (float) x / ofGetHeight() - 0.5f);

		ofSetColor(255, 255, 255, 100);
		ofCircle(x, y, 10 * (1.0 - (float) y / ofGetHeight()));
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    synth->set("amp", 0.1f);

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}

//--------------------------------------------------------------
void ofApp::exit(){
    leap.close();  // let's close down Leap and kill the controller
}
