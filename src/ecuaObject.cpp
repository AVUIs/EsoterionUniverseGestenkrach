//
//  ecuaObject.cpp
//  EsoterionCarrotUniverseAlpha
//
//  Created by Borut Kumperscak on 7. 12. 14.
//
//

#include "ecuaObject.h"
#include "ofxOsc.h"

static ofxOscSender *sender = NULL;        //KX each obj same sender

ecuaObject::ecuaObject(ofVec3f _p) {
    setup(_p);
    if (sender==NULL) {
        sender = new ofxOscSender();
        sender->setup(HOST, PORT);
    }
}

ecuaObject::~ecuaObject() {
    if (sender!=NULL) {
        delete sender;
        sender = NULL;
    }
}

void ecuaObject::setup(ofVec3f _p, int _id) {

    objWarmth = ofRandom(360.0);
    objColor.setHsb(objWarmth, 255, 255);
    objSize = ofRandom(300.0);
    objSharpness = ofRandom(255);
    objOscillation = ofRandom(1.0);
    objAmplitude = ofRandom(1.0);
    pos = _p;
    id = _id;
    ball = new ofSpherePrimitive();

}

void ecuaObject::update() {
    curSize = objSize * objAmplitude * cos(ofGetElapsedTimef()*objOscillation);
    
    if (sender!=NULL) {
        ofxOscMessage m;
        
        m.setAddress("ecu");
        m.addIntArg(id);
        m.addFloatArg(objWarmth);
        m.addFloatArg(curSize);
        m.addFloatArg(objSharpness);
        m.addFloatArg(distToCenter);
        m.addFloatArg(distToCam);
        sender->sendMessage(m);
        
//        m.setAddress("/object/id");
//        m.addIntArg(id);
//        sender->sendMessage(m);
//        m.clear();
//        m.setAddress("/object/warmth");
//        m.addFloatArg(ofMap(objWarmth, 0, 128, 0.0, 1.0, true));
//        sender->sendMessage(m);
//        m.clear();
//        m.setAddress("/object/size");
//        m.addFloatArg(ofMap(objSize, 10, 300, 0.0, 1.0, true));
//        sender->sendMessage(m);
//        m.clear();
//        m.setAddress("/object/sharpness");
//        m.addFloatArg(ofMap(objSharpness, 2, 42, 0.0, 0.1, true));
//        sender->sendMessage(m);
//
//        m.clear();
//        m.setAddress("/object/distanceToCenter");
//        m.addFloatArg(distToCenter);
//        sender->sendMessage(m);
//        
//        m.clear();
//        m.setAddress("/object/distanceToCam");
//        m.addFloatArg(distToCam);
//        sender->sendMessage(m);
    }
}

void ecuaObject::draw() {
//    float spinX = sin(ofGetElapsedTimef()*.35f);
//    float spinY = cos(ofGetElapsedTimef()*.075f);
//    ofPushMatrix();
//    ofRotate(spinX, 1.0, 0.0, 0.0);
//    ofRotate(spinY, 0.0, 1.0, 0.0);
    objColor.setHsb(objWarmth, 255, 255, objSharpness);
    ofFill();
    ofSetColor(objColor);
    ball->setRadius(objSize);
    ball->setPosition(pos);
    
    //modify mesh with some noise
    float liquidness = 5;
    float amplitude = curSize/5.0;
    float speedDampen = 5;
    vector<ofVec3f>& verts = ball->getMesh().getVertices();
    for(unsigned int i = 0; i < verts.size(); i++){
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
    }
    ball->draw();

//    ofPopMatrix();
}

void ecuaObject::setWarmth(float _warmth) {
    objWarmth = _warmth;
}

void ecuaObject::setSize(int _size) {
    objSize = _size;
}

void ecuaObject::setSharpness(int _sharpness) {
    objSharpness = _sharpness;
}

void ecuaObject::setOscillation(float _oscillation) {
    objOscillation = _oscillation;
}

void ecuaObject::setParam(int _param, float _val) {
    switch (_param) {
        case 0:
        objWarmth = ofMap(_val, 0.0, 1.0, 0, 360, true);
        break;
        case 1:
        objSize = ofMap(_val, 0.0, 1.0, 10, 300, true);
        break;
        case 2:
        objSharpness = ofMap(_val, 0.0, 1.0, 0.0, 255.0, true);
        break;
        case 3:
        objOscillation = ofMap(_val, 0.0, 1.0, 0.0, 10.0, true);
        break;
        case 4:
        objAmplitude = ofMap(_val, 0.0, 1.0, 0.0, 1.0, true);
        break;
        default:
        break;
    }

}


float ecuaObject::getParam(int _param) {
    switch (_param) {
        case 0:
        return ofMap(objWarmth, 0, 360, 0.0, 1.0, true);
        case 1:
        return ofMap(objSize, 10, 300, 0.0, 1.0, true);
        case 2:
        return ofMap(objSharpness, 0.0, 255.0, 0.0, 1.0, true);
        case 3:
        return ofMap(objOscillation, 0.0, 10.0, 0.0, 1.0, true);
        case 4:
        return ofMap(objAmplitude, 0.0, 1.0, 0.0, 1.0, true);
        default:
        return 0;
    }
}

