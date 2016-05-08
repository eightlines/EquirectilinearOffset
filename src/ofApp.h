#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxVideoRecorder.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyReleased (int key);
    void dragEvent(ofDragInfo dragInfo);
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
    void exit();
    void playButtonPressed();
private:
    ofVideoPlayer video1, video2;
    ofFbo fbo;
    bool isFileLoaded = false;
    bool hideGui = false;
    ofxPanel gui;
    ofxFloatSlider offset;
    ofxButton playToggle;
    ofxVideoRecorder vidRecorder;
};
