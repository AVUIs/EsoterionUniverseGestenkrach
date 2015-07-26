#include "ctrls.h"

ctrls::ctrls() {
    setup();
}

//--------------------------------------------------------------
void ctrls::setup(){
    //setupP();
    setupM();
}

void ctrls::setupP() {
    spacer = TWO_PI / amnt;

    for(int i= 0; i< amnt; i++){
        fadersPos.push_back(1);
        isTouched.push_back(false);
        xMax.push_back( size*scale * sin(i*spacer));//i*spacer; //
        yMax.push_back( size*scale * cos(i*spacer));
        xMin.push_back( innerCircle * sin(i*spacer)); //xMax-20;//
        yMin.push_back( innerCircle * cos(i*spacer));
        
        xPos.push_back( xMax[i] * 1.f);
        yPos.push_back( yMax[i] * 1.f);
        
        len.push_back(ofDist(xMin[i],yMin[i],xMax[i],yMax[i]));
    }
    //double the amount to use with secondary layer
    for(int i= 0; i< amnt; i++){
        fadersPos.push_back(1);
        isTouched.push_back(false);
        xMax.push_back( size*scale * sin(i*spacer));//i*spacer; //
        yMax.push_back( size*scale * cos(i*spacer));
        xMin.push_back( innerCircle * sin(i*spacer)); //xMax-20;//
        yMin.push_back( innerCircle * cos(i*spacer));
        
        xPos.push_back( xMax[i] * 1.f);
        yPos.push_back( yMax[i] * 1.f);
        
        len.push_back(ofDist(xMin[i],yMin[i],xMax[i],yMax[i]));
    }
}

void ctrls::setupM() {
    spacer = ofGetWidth()/2 / amnt;
    cout << "spacer = " << spacer << endl;
    for(int i=0; i< amnt; i++){
        fadersPos.push_back(1);
        isTouched.push_back(false);

        xMax.push_back( spacer/5 + i*spacer*scale);//i*spacer; //
        yMax.push_back( ofGetHeight()/2*scale);
        xMin.push_back( spacer + i*spacer*scale); //xMax-20;//
        yMin.push_back( ofGetHeight()*scale);
        
        xPos.push_back( xMax[i] * 1.f);
        yPos.push_back( yMax[i] * 1.f);
        
        len.push_back(ofDist(xMin[i],yMin[i],xMax[i],yMax[i]));
    }
    //double the amount to use with secondary layer
    for(int i= 0; i< amnt; i++){
        fadersPos.push_back(1);
        isTouched.push_back(false);

        xMax.push_back( spacer/5 + i*spacer*scale);//i*spacer; //
        yMax.push_back( ofGetHeight()/2*scale);
        xMin.push_back( spacer + i*spacer*scale); //xMax-20;//
        yMin.push_back( ofGetHeight()*scale);
        
        xPos.push_back( xMax[i] * 1.f);
        yPos.push_back( yMax[i] * 1.f);
        
        len.push_back(ofDist(xMin[i],yMin[i],xMax[i],yMax[i]));
    }
}

//--------------------------------------------------------------
void ctrls::update(ofVec3f screenPosition){
    screenPos = screenPosition;
    
//    for(int i = 0; i < amnt; i++){
////        float val = ofMap(   ofDist(mouseX,mouseY,xMin[i],yMin[i])+innerCircle   , 0, len[i], 0, 1);
////        ofMap(<#float value#>, <#float inputMin#>, <#float inputMax#>, <#float outputMin#>, <#float outputMax#>)
//    
////        val = ofMap (fadersPos[i], 0,1,0,len[i]);
////        ofMap(fadersPos[i], xMin, ofDist(xMax[i],yMax[i],xMin[i],yMin[i])+innerCircle, 0, 1);
//        
//       // float val = ofMap( fadersPos[i], 0, ofDist(xMax[i],xMin[i],xMin[i],yMin[i]));
//
//        xPos[i] = fadersPos[i] * xMax[i]+xMin[i];
//        yPos[i] = fadersPos[i] * yMax[i]+yMin[i];
//    }
    for(int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0); i++){
    xPos[i] = (xMax[i]-xMin[i])*fadersPos[i]+xMin[i];//(size-innerCircle)*scale * sin(i*spacer)*val;
    yPos[i] = (yMax[i]-yMin[i])*fadersPos[i]+yMin[i];//;(size-innerCircle)*scale * cos(i*spacer)*val;
    }
    
}
bool ctrls::getActive(){
    return active;
}
void ctrls::setActive(bool activ){
    active = activ;
}

//--------------------------------------------------------------
void ctrls::draw(){
    drawM();
}

void ctrls::drawP(){
    
    ofPushMatrix();
    ofTranslate(screenPos);
    ofSetColor(0,0,0);
    if (useTertiary) {
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(0, 0, 0);
        ofDrawEllipse(0,0,innerCircle*2,innerCircle*2);
        ofDrawLine(-innerCircle/2, -innerCircle/2, innerCircle/2, innerCircle/2);
        ofDrawLine(innerCircle/2, -innerCircle/2, -innerCircle/2, innerCircle/2);
    } else {
        ofSetLineWidth(2);
        ofNoFill();
        ofSetColor(0,0,0,200);
        if (useSecondary) ofSetColor(255,255,255,200);
        ofDrawEllipse(0,0,innerCircle*2,innerCircle*2);

        if (useSecondary) ofSetColor(255,255,255);
        for (int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0); i ++){
            //ofSetColor(255,0,0);
            
            float mouseDist = ofDist(mouseX, mouseY, xPos[i], yPos[i]);
            if(mouseDist < ballSize*2){
                ofFill();
                ofDrawEllipse(xPos[i],yPos[i],ballSize,ballSize);
            }
            
            if(touchedFader == i){
                ofSetColor(0,0,0,200);
                if (useSecondary) ofSetColor(255,255,255,200);
                ofDrawEllipse(xPos[i], yPos[i],ballSize*2, ballSize*2);
                ofDrawBitmapString(ofToString(fadersPos[touchedFader],2), -17, 5);
                ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
            }
            
            else{
                ofSetColor(0,0,0,100);
                if (useSecondary) ofSetColor(255,255,255,100);
                ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
            ofDrawBitmapString(ofToString(i), xMax[i], yMax[i]);
            }
            ofNoFill();
            //ofSetColor(255,100,100);
            
            ofDrawEllipse(xPos[i], yPos[i], ballSize,ballSize);
            ofDrawLine(xPos[i],yPos[i],xPos[(i+1)%amnt+(useSecondary?amnt:0)],yPos[(i+1)%amnt+(useSecondary?amnt:0)]);
        }
    }
    ofPopMatrix();
}

void ctrls::drawM(){
    ofSetColor(0,0,0);
    if (useTertiary) {
        ofNoFill();
        ofSetLineWidth(30);
        ofSetColor(255, 100, 100);
        ofDrawLine(ofGetWidth()/2-50, ofGetHeight()/2-50, ofGetWidth()/2+50, ofGetHeight()/2+50);
        ofDrawLine(ofGetWidth()/2+50, ofGetHeight()/2-50, ofGetWidth()/2-50, ofGetHeight()/2+50);
    } else {
        ofSetLineWidth(10);
        ofNoFill();
        ofSetColor(0,0,255,100);
        if (useSecondary) ofSetColor(0,255,0,100);
        for (int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0); i ++){
            //ofSetColor(255,0,0);
            
//            float mouseDist = ofDist(mouseX, mouseY, xPos[i], yPos[i]);
//            if(mouseDist < ballSize*2){
//                ofFill();
//                ofDrawEllipse(xPos[i],yPos[i],ballSize,ballSize);
//            }
            ofFill();
            ofSetColor(255,255,255,255);
            ofDrawLine(xMin[i],yPos[i],xMax[i], yPos[i]);
            
            if(touchedFader == i){
                ofFill();
                ofSetColor(255,255,255,200);
//                if (useSecondary) ofSetColor(255,255,255,200);
                ofDrawRectangle(xMin[i],yMin[i],xMax[i]-xMin[i], yMax[i]-yMin[i]);
                ofSetColor(255,255,255,255);
                ofDrawBitmapString(ofToString(i), xMax[i], yMax[i]);
            }
            
            else{
                ofFill();
                ofSetColor(200,200,255,100);
                if (useSecondary) ofSetColor(200,255,200,100);
                //ofDrawLine(xMin[i],yMin[i],xMax[i], yMax[i]);
                ofDrawRectangle(xMin[i],yMin[i],xMax[i]-xMin[i], yMax[i]-yMin[i]);
                ofSetColor(255,255,255,255);
                ofDrawBitmapString(ofToString(i), xMax[i], yMax[i]);
            }
            ofNoFill();
//            ofSetColor(0,0,255,100);
//            if (useSecondary) ofSetColor(0,255,0,100);
            
//            ofDrawEllipse(xPos[i], yPos[i], ballSize,ballSize);
//            ofDrawLine(xPos[i],yPos[i],xPos[(i+1)%amnt+(useSecondary?amnt:0)],yPos[(i+1)%amnt+(useSecondary?amnt:0)]);
        }
    }
}

//--------------------------------------------------------------
void ctrls::keyPressed(int key){

}

//--------------------------------------------------------------
void ctrls::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ctrls::mouseMoved(int x, int y){
    
    mouseX = x-screenPos.x;
    mouseY = y-screenPos.y;
    
}

//--------------------------------------------------------------
void ctrls::mouseDragged(int x, int y, int button){
    mouseX = x-screenPos.x;
    mouseY = y-screenPos.y;
    
//    float mouseDownX = mouseX - downX;
//    float mouseDownY = mouseY - downY;
    
    for(int i = (useSecondary?amnt:0); i < amnt+(useSecondary?amnt:0);i++){
        if(touchedFader == i){
            
            float zeroDist = ofDist(mouseX,mouseY,0,0);
            if(dragged && zeroDist > innerCircle){
  //              cout<<ofDist(mouseX,mouseY,xMin[i],yMin[i])+innerCircle<<endl;
                
                float val = ofMap(   ofDist(mouseX,mouseY,xMin[i],yMin[i])   , 0, len[i], -0.05, 1);
                
                val = ofClamp(val,0,1);
//                cout<<len[i]<<"  "<<val<<endl;
                
//                xPos[i] = (xMax[i]-xMin[i])*val+xMin[i];//(size-innerCircle)*scale * sin(i*spacer)*val;
//                yPos[i] = (yMax[i]-yMin[i])*val+yMin[i];//;(size-innerCircle)*scale * cos(i*spacer)*val;
                
                fadersPos[i] = val;
            }
        }
    }
}

//--------------------------------------------------------------
void ctrls::mousePressed(int x, int y, int button){
    dragged = true;
    downX=mouseX;//x-screenPos.x;
    downY=mouseY;//y-screenPos.y;
    
    for(int i = 0; i<amnt; i++){
        float mouseDist = ofDist(mouseX, mouseY, xPos[i+(useSecondary?amnt:0)], yPos[i+(useSecondary?amnt:0)]);

        if( mouseDist < ballSize*2){
            
            float zeroDist = ofDist(mouseX,mouseY,0,0);
            
            if(dragged && zeroDist > innerCircle){
                touchedFader = i+(useSecondary?amnt:0);
                //cout << "TOUCHED FADER: " << touchedFader << endl;
            }
        }

    }
    
    if(ofDist(downX,downY,0,0) < innerCircle){
        active = 0;
    }
}

bool ctrls::deleteObject(int x, int y, int button) {
    downX=mouseX;
    downY=mouseY;
    if(useTertiary && ofDist(downX,downY,0,0) < innerCircle) {
        active = 0;
        return true;
    }
    return false;
}

void ctrls::deleteObjectNow() {
    active = 0;
}

void ctrls::setFaderVal(int _fader, float _val) {
    if (_fader<amnt) {
        fadersPos[_fader+(useSecondary?amnt:0)] = _val;
    }
}

void ctrls::checkTouchedFaderX(int _x) {
    for (int i = 0; i<amnt; i++) {
        if (i*spacer - _x < spacer) touchedFader = i;
    }
}

void ctrls::setTouchedFaderVal(float _val) {
    if (touchedFader > -1) fadersPos[touchedFader+(useSecondary?amnt:0)] = _val;
}

//--------------------------------------------------------------
void ctrls::mouseReleased(int x, int y, int button){
    dragged = false;
    touchedFader = -1;
}

//--------------------------------------------------------------
void ctrls::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ctrls::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ctrls::dragEvent(ofDragInfo dragInfo){
    
}