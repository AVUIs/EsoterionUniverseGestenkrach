#pragma once

#include "ofMain.h"

class ctrls : public ofBaseApp {
public:
    ctrls();

    void setup();
    void setupP();
    void setupM();
    void update(ofVec3f screenPosition);
    void draw();
    void drawP();
    void drawM();
    bool getActive();
    void setActive(bool activ);
    bool deleteObject(int x, int y, int button = 0);
    void deleteObjectNow();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void setFaderVal(int _fader, float _val);
    void checkTouchedFaderX(int _x);
    void setTouchedFaderVal(float _val);

    int amnt = 5;
    float size = 100;
    float scale = 1.;
    float spacer = 1.;
    float ballSize = 15;
    float faderPos= 0.5;
    float innerCircle = 20;
    int touchedFader = -1;
    ofVec3f screenPos;
    
    bool active;
    vector<float> xMax;//i*spacer; //
    vector<float> yMax ;
    vector<float> xMin ; //xMax-20;//
    vector<float> yMin ;
    vector<float> len;
    vector<float> xPos ;
    vector<float> yPos ;
    
    vector<float> fadersPos;
    vector<bool>isTouched;
    
    int downX=0;
    int downY=0;
    
    bool dragged = false;
    
    bool useSecondary = false;
    bool useTertiary = false;
};

