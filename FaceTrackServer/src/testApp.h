#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "ofxNetwork.h"

class testApp : public ofBaseApp{
    private:
        ofVideoGrabber camera;
        ofImage image;
        ofxCvHaarFinder finder;
        int msec;

	public:
		void setup();
		void netWorksetup();
		void update();
		void netWorkupdate(string senndData);
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofImage img;

		// NetWork
		ofxTCPServer TCP;

		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;

		vector <string> storeText;

};
