

#include "ofApp.h"

//#include "ECURabbitObject.h"
#include "ecuaObject.h"

ofVec3f p;
bool zDown = false;
ofPoint movingVector;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofSetCircleResolution(100);
//    ofSetEscapeQuitsApp(false);
//    mesh.load("lofi-bunny.ply");
    
//    cout << cam.getTarget().getPosition() << endl;
    universe = new ECUUniverse();
//Borut    universe->addObject(new ecuaObject(ofVec3f(0, 0, -1000)));
    //    cam.disableMouseInput();
    
    //    cam.set
    
    ofSetSmoothLighting(true);
    pointLight2.setDiffuseColor( ofFloatColor(.3, .3, .3));
    pointLight2.setSpecularColor(ofFloatColor(10, 10, 10));
    pointLight2.setPosition(120, 80, 500);


    currentEditingObj = NULL;
    
//    ofAddListener(ofEvent::mousePressed, &control, control::mousePressed)
//    ofAddListener(ofEvents().mouseDragged , &control, &ctrls::mouseDragged);
//    ofAddListener(ofEvents().mousePressed, &control, &ctrls::mousePressed);
//    ofAddListener(ofEvents().mouseReleased, &control, &ctrls::mouseReleased);
//    ofAddListener(ofEvents().mouseScrolled, &control, &ctrls::mouseScrolled);

//    ofRegisterMouseEvents(control);

    showHelp = false;
    movingVector = ofPoint(0,0,0);
    
    //LEAP MOTION
    leap.open();
	leap.setupGestures();   // we enable our gesture detection here
    leap.setMappingX(-200, 200, 0, ofGetWidth());
    leap.setMappingY(50, 300, 0, ofGetHeight());
    min[0] = -50;
    min[1] = -50;
    min[2] = -50;
    min[3] = -50;
    min[4] = -50;
    max[0] = 0;
    max[1] = 0;
    max[2] = 0;
    max[3] = 0;
    max[4] = 0;
}

void ofApp::exit() {
    delete universe;
}

//--------------------------------------------------------------
void ofApp::update(){
    universe->update();
    if(control.getActive()==false){
        currentEditingObj = NULL;
    }
    if(currentEditingObj != NULL ) {
            control.update(universe->cam.worldToScreen((currentEditingObj)->pos));
        for (int i = 0; i < control.amnt; i++) {
//            cout<<control.fadersPos[i]<<endl;
        }
    }
    
    //Leapmotion ctrl
    simpleHands = leap.getSimpleHands();
    
    
    for(int i = 0; i < simpleHands.size(); i++){
//        cout << simpleHands[i].handPos.x << " " << simpleHands[i].handPos.y << " " << simpleHands[i].handPos.z << endl;

        
        //HAND 1 = navigate / grab object
        if (currentEditingObj == NULL && simpleHands[0].isRight) {
            universe->pos.x+= simpleHands[0].handNormal.x*5;
            universe->pos.z+= -simpleHands[0].handNormal.z*20;
            universe->pos.y+= (simpleHands[0].handPos.y-ofGetHeight()/2)*0.01;
            movingVector = ofPoint(simpleHands[0].handNormal.x*10, (simpleHands[0].handPos.y-ofGetHeight()/2)*0.1);
            if (simpleHands[0].pinchStrength>0.8) {
                checkObjectSelected(ofGetWidth()/2, ofGetHeight()/2);
                if (currentEditingObj == NULL) keyPressed('a');
            }
        } else if (simpleHands[0].isRight) {
            if (simpleHands[0].pinchStrength<0.1) checkObjectSelected(ofGetWidth()/2, ofGetHeight()/2);
        }
        
        //HAND 2 = edit params
        if (simpleHands.size()>1 && simpleHands[0].isRight && currentEditingObj != NULL) {
            //blablabla
            if (simpleHands[0].handPos.y>ofGetHeight()/3*2) {
                control.useSecondary=true;
                control.useTertiary=false;
            } else if (simpleHands[0].handPos.y>ofGetHeight()/3) {
                control.useSecondary=false;
                control.useTertiary=false;
            } else {
                control.useSecondary=false;
                control.useTertiary=true;
            }
            
            control.checkTouchedFaderX(simpleHands[1].handPos.x);
            
//            for(int j = 0; j < simpleHands[1].fingers.size(); j++){
//                int intVal = simpleHands[i].fingers[j].pos.y - simpleHands[i].fingers[j].base.y;
//                
//                float val = ofMap(intVal, min[i], max[i], -0.05, 1);
//                val = ofClamp(val,0,1);
//                
//                control.setFaderVal(j, val);
//            }

            control.setTouchedFaderVal(ofMap(simpleHands[1].handPos.y, ofGetHeight()/3,ofGetHeight()/3*2,0.0,1.0,true));
            if (simpleHands[1].sphereRadius<50) {
//                if (control.deleteObject(ofGetWidth()/2, ofGetHeight()/2, 0)) {
//                    universe->deleteObject(currentEditingObj);
//                    currentEditingObj == NULL;
//                }
            }
        }
    }
    
  //  if (simpleHands.size()==0) currentEditingObj=NULL;
    
    if (currentEditingObj!=NULL) {
        for (int i = 0; i < control.amnt; i++) {
            currentEditingObj->setParam(i, control.fadersPos[i]);
            universe->saved = false;
            //if we found an object, set the of the control to the object so there is no jump
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    ofShowCursor();
    ofBackgroundGradient(ofColor(100), ofColor(0));
    //ofBackground(0, 0, 0);
    
    ofSetColor(255);
    
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight2.enable();
    
    universe->draw();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    if(currentEditingObj != NULL) {
        control.draw();
    }
    
    if (universe->objects.size()==0 || showHelp) {
        ofSetColor(255);
        ofDrawBitmapString("KEY\n\nA = Add objects\nS = Save universe\nL = Load universe\nTwo-finger mouse drag = move arround\nZ + mouse drag = Hold to move in Z direction\nClick on object = Show GUI\nCmd-Click = Secondary GUI\nAlt-Click = Tertiary GUI\n0 = Armageddon\nH = Show this help", ofGetWidth()/2 - 100, 30);
    }
    
    ofSetColor(255,0,0);
    ofDrawBitmapString(universe->saved?"SAVED":"NOT SAVED", 10, 10);
    
    ofPushStyle();
    ofSetLineWidth(5);
    ofSetColor(255, 255, 255,50);
    for (int i=0; i<simpleHands.size(); i++) {
        ofSetLineWidth(10);
        ofDrawLine(simpleHands[i].handPos.x, 0, simpleHands[i].handPos.x, ofGetHeight());
        ofDrawLine(0, (ofGetHeight()-simpleHands[i].handPos.y), ofGetWidth(), (ofGetHeight()-simpleHands[i].handPos.y));
        ofDrawCircle(simpleHands[i].handPos.x, (ofGetHeight()-simpleHands[i].handPos.y), (1-simpleHands[i].pinchStrength)*50);
        ofSetLineWidth(2);
        if (i==0) ofDrawLine(simpleHands[i].handPos.x, (ofGetHeight()-simpleHands[i].handPos.y),
                             simpleHands[i].handPos.x + movingVector.x*10, (ofGetHeight()-simpleHands[i].handPos.y) + movingVector.y*10);
    }
    ofNoFill();
    ofDrawLine(0, ofGetHeight()/3, ofGetWidth(), ofGetHeight()/3);
    ofDrawLine(0, ofGetHeight()/3*2, ofGetWidth(), ofGetHeight()/3*2);
//    ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
    ofSetLineWidth(5);
    if (universe->findEditObject(ofGetWidth()/2, ofGetHeight()/2)!=NULL) ofSetColor(255, 255, 255,200);
    ofDrawLine(ofGetWidth()/2-75, ofGetHeight()/2-75, ofGetWidth()/2-25, ofGetHeight()/2-25);
    ofDrawLine(ofGetWidth()/2+25, ofGetHeight()/2+25, ofGetWidth()/2+75, ofGetHeight()/2+75);
    ofDrawLine(ofGetWidth()/2-75, ofGetHeight()/2+75, ofGetWidth()/2-25, ofGetHeight()/2+25);
    ofDrawLine(ofGetWidth()/2+25, ofGetHeight()/2-25, ofGetWidth()/2+75, ofGetHeight()/2-75);
//    ofCircle(ofGetWidth()/2, ofGetHeight()/2, 50);
    ofPopStyle();
}



void ofApp::createObject() {
    
    if(currentEditingObj != NULL) {
        //we are now going to turn off, this means that we need to place the object in
        currentEditingObj = NULL;
    }

    else {

        ECUBaseObject *obj = new ecuaObject(ofVec3f(universe->pos.x, universe->pos.y, universe->pos.z-1000));
        currentEditingObj = obj;
        universe->addObject(obj);
        for (int i = 0; i < control.amnt; i++) {
            control.fadersPos[i] = currentEditingObj->getParam(i);
        }
    }
    
//    creatingObject = !creatingObject;
}

#define KEY(k, f) if(key == (k)) { (f); }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key=='s' || key =='l') currentEditingObj=NULL;
    
    KEY('z', zDown = true)
    
    KEY('a', createObject())

    KEY('s', universe->save());

    KEY('l', universe->load());

    KEY('h', showHelp =!showHelp);

    KEY('d', universe->debug = !universe->debug);

    KEY('0', universe->clearUniverse());
    
    KEY(OF_KEY_COMMAND, control.useSecondary=true);
    KEY(OF_KEY_ALT, control.useTertiary=true);
    //cout << "current pos = " << universe->pos << endl;
    //cout << "there are " << universe->objects.size() << " objects" << endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    KEY('z', zDown = false);
    KEY(OF_KEY_COMMAND, control.useSecondary=false);
    KEY(OF_KEY_ALT, control.useTertiary=false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    control.mouseMoved(x, y);
}

ofVec3f downPosition;
ofQuaternion downOrientation;

//float mouseRange = 0;

void ofApp::mouseDragged(int x, int y, int button) {
    if (currentEditingObj!=NULL) {
        control.mouseDragged(x, y, button);
        
        for (int i = 0; i < control.amnt; i++) {
            currentEditingObj->setParam(i, control.fadersPos[i]);
            universe->saved = false;
            //if we found an object, set the of the control to the object so there is no jump
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(float x, float y) {
    if (zDown) {
        universe->pos.z+= -y;
    }
    else {
        universe->pos.x-= x;
        universe->pos.y+= y;
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    mouseRange = mouseX;
    checkObjectSelected(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    control.mouseReleased(x, y, button);
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

void ofApp::checkObjectSelected(int x, int y) {
    downPosition = universe->cam.getPosition(); // ofCamera::getGlobalPosition();
   // cout << "cam pos = " << downPosition << endl;
    downOrientation = universe->cam.getOrientationQuat(); // ofCamera::getGlobalOrientation();
    
    if(currentEditingObj != NULL && control.deleteObject(x, y, 0)) {
        universe->deleteObject(currentEditingObj);
        currentEditingObj == NULL;
    } else {
        control.mousePressed(x, y, 0);
        if(currentEditingObj == NULL) {
            currentEditingObj = universe->findEditObject(x, y);
            if (currentEditingObj != NULL) {
                control.setActive(1);
                //if we found an object, set the of the control to the object so there is no jump
                for (int i = 0; i < control.amnt; i++) {
                    control.fadersPos[i] = currentEditingObj->getParam(i);
                }
            }
        }
    }
}
