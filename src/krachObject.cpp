//
//  krachObject.cpp
//  esoterionUniverse
//
//  Created by Borut Kumperscak on 25/07/2015.
//
//

#include "krachObject.h"

krachObject::krachObject() {
}

krachObject::~krachObject() {
    krach->free();
    krach = NULL;
}

void krachObject::setup() {
    krach = new ofxSCSynth("krach1");
    krach->create();
}

void krachObject::update() {
}

void krachObject::setParam(int _param, float _val) {
    switch (_param) {
        case 0:
        krach->set("val4", _val);
        break;
        case 1:
        {
            //SYNTH SELECTION HERE
            int numSynths = 3;   //num X of synth defs krach1..krachX
            string selectedSynth;
            for (int i=0; i<numSynths; i++) {
                if (_val < (i+1)*(1.0/numSynths)) {
                    selectedSynth = "krach" + ofToString(i+1);
                    break;
                }
            }
            cout << "selectedSynth " << selectedSynth << endl;
            krach->free();
            krach = new ofxSCSynth(selectedSynth);
            krach->create();
            break;
        }
        case 2:
        //AMP/VOL HERE
        krach->set("val1", _val);
        break;
        case 3:
        //if not normalized in krad do something like ofMap(_val, 0.0, 1.0, 0, 255, true);
        krach->set("val2", _val);
        break;
        case 4:
        krach->set("val3", _val);
        break;
        default:
        break;
    }
}

float krachObject::getParam(int _param) {
}
