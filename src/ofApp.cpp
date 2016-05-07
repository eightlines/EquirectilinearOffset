#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(0);
    
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("800k");
    vidRecorder.setAudioCodec("mp3");
    vidRecorder.setAudioBitrate("192k");
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    
    gui.setup();
    gui.add(offset.setup("offset", 640, 0, 1280));
}

void ofApp::update() {
    if (isFileLoaded) {
        video1.update();
        video2.update();
    }
}

void ofApp::draw() {
    if (isFileLoaded) {
        fbo.begin();
        ofClear(0, 0);
        video1.draw(offset, 0);
        video2.draw(offset - video1.getWidth(), 0);
        
        
        fbo.end();

        fbo.draw(0, 0);
        
        ofPixels pix;
        fbo.readToPixels(pix);
        vidRecorder.addFrame(pix);
        
        if (!hideGui) gui.draw();
    } else {
        ofDrawBitmapStringHighlight("Drag & Drop Equirectilinear File into Window", 20, 20);
    }
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
    video1.load(dragInfo.files[0]);
    video2.load(dragInfo.files[0]);
    video1.setLoopState(OF_LOOP_NONE);
    video2.setLoopState(OF_LOOP_NONE);
    fbo.allocate(video1.getWidth(), video1.getHeight());
    isFileLoaded = true;
    vidRecorder.setup(dragInfo.files[0] + ofGetTimestampString() + ".MP4", video1.getWidth(), video1.getHeight(), 30);
    vidRecorder.start();
    video1.play();
    video2.play();
}

void ofApp::keyReleased (int key) {
    if (key == 'h') hideGui = !hideGui;
}

void ofApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args) {
    cout << "Video file is now complete." << endl;
    vidRecorder.setPaused(true);
    vidRecorder.close();
}

void ofApp::exit() {
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    vidRecorder.close();
}
