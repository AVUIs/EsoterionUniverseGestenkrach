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
    synthName = "krach1";
    krach = new ofxSCSynth(synthName);
    krach->create();
}

void krachObject::update() {
}

void krachObject::setParam(int _param, float _val) {
    switch (_param) {
        case 0:
        krach->set("val4", ofMap(_val, 0.0, 1.0, 0, 100, true));
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
            if (selectedSynth != synthName) {
                synthName = selectedSynth;
                krach->free();
                krach = NULL;
                krach = new ofxSCSynth(selectedSynth);
                cout << "CREATED SYNTH " << selectedSynth << endl;
                krach->create();
            }
            break;
        }
        case 2:
        //AMP/VOL HERE
        krach->set("val1", ofMap(_val, 0.0, 1.0, 0, 100, true));
        break;
        case 3:
        //if not normalized in krad do something like ofMap(_val, 0.0, 1.0, 0, 255, true);
        krach->set("val2", ofMap(_val, 0.0, 1.0, 0, 100, true));
        break;
        case 4:
        krach->set("val3", ofMap(_val, 0.0, 1.0, 0, 100, true));
        break;
        default:
        break;
    }
}

void krachObject::setPan(float _val) {
    krach->set("pan", _val);
  //  cout << "PAN: " << _val << endl;
}

void krachObject::setAmp(float _val) {
    krach->set("amp", _val);
}


float krachObject::getParam(int _param) {
}
