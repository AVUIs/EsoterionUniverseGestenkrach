//
//  ECUBaseObject.h
//  esoterionUniverse
//
//  Created by Will Gallia on 06/12/2014.
//
//

#pragma once

#include "ofMain.h"

class ECUUniverse;

class ECUBaseObject {
public:
    ECUBaseObject() {
        
    }
    
    virtual ~ECUBaseObject() {}
    
    virtual void update() {}

    virtual void draw() {}
    
//    virtual void sendOSc();
    
    
    ofVec3f pos;
    int id;
    
    float distToCam;
    float distToCenter;
    
    ECUUniverse *universeRef;
    
};