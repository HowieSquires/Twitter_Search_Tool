#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//Sets the window size to a 1080p
	ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context
	//Launches the ofApp
	ofRunApp(new ofApp());

}