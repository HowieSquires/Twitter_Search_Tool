#pragma once
#include "ofMain.h"

//This is a class to create the find buttons for my Twitter app
class findButton
{
public:
	//variables used to make the buttons
	ofRectangle areaID;
	ofTrueTypeFont mainTXT;
	int xPos;
	int yPos;

	//called within ofApp.cpp -> setup() 
	void setup(ofRectangle btnName, int x, int y) {
		//load font
		mainTXT.load("LGCafe.ttf", 34);
		//name ofRectangle, xPos, yPos to the passed value
		areaID = btnName;
		xPos = x;
		yPos = y;
	}

	//Called to draw a button with "Find" on it
	void drawFind() {
		//sets color of the rectangle
		ofSetColor(255);
		//sets the area of the ofRectangle
		areaID.set(xPos, yPos, 200, 75);
		//draws a rectangle inside the ofRectangle area
		ofDrawRectangle(areaID);
		ofSetColor(0);
		//draws the "Find!" string over the button
		mainTXT.drawString("Find!", xPos + (mainTXT.stringWidth("Find!") / 2), yPos + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		ofSetColor(255);
	}

	//same as drawFind() except text changes to "Home!"
	void drawHome() {
		ofSetColor(255);
		areaID.set(xPos, yPos, 200, 75);
		ofDrawRectangle(areaID);
		ofSetColor(0);
		mainTXT.drawString("Home!", xPos + (mainTXT.stringWidth("Find!") / 2), yPos + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		ofSetColor(255);
	}

	//same as drawFind() except text changes to "More!"
	void drawMore() {
		ofSetColor(255);
		areaID.set(xPos, yPos, 200, 75);
		ofDrawRectangle(areaID);
		ofSetColor(0);
		mainTXT.drawString("More!", xPos + (mainTXT.stringWidth("Find!") / 2), yPos + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		ofSetColor(255);
	}

	findButton();
	~findButton();
};