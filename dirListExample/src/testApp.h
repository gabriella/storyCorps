#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
		
   // vector<string> testApp::ofxReadLines(string filename) ;

    string Minput;
		// we will have a dynamic number of images, based on the content of a directory:
		ofDirectory dir;
		vector<ofImage> images;
		int currentImage;
    vector<string> fileTxt ;
    ofVec2f loadData(string Minput);
    
    //ofxSVG map;
};

