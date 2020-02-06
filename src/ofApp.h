//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#pragma once
//Load the addons and libraries needed to build the app
#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxTextSuite.h"
#include "../findButton.h"
#include <string>
#include <sstream>

//States the namespaces for coding
using namespace ofxTwitter;
using namespace std;

class ofApp : public ofBaseApp
{
public:
	//Useful
	void setup();
	void draw();

	//Came with app generation
	//Receives tweets found from client.search()
	void onStatus(const ofxTwitter::Status& status);
	//Unneeded
	void onError(const ofxTwitter::Error& error);
	void onException(const std::exception& exception);
	void onMessage(const ofJson& json);
	//Used to search twitter for tweets containing a string
	ofxTwitter::SearchClient client;
	//Used to determine if any tweets have been found and counts them
	uint64_t count = 0;
	//Unused
	uint64_t countMissed = 0;

	//My functions
	//Draws page according to pageID
	void getPage(char pageID);
	//Reads user input from keyboard and executes accordingly
	void keyPressed(int key);
	//Reads user input from mouse and executes accordingly
	void mousePressed(int x, int y, int button);
	//Used to find tweets
	void getQuery(string queryStr);

	//My variables
	//Background colour
	ofColor colour1;
	//fonts
	ofTrueTypeFont titleTXT, subheadTXT, mainTXT, btnTXT, minorTXT;

	//Strings 
	//Takes user input
	string searchInp = "";
	//Used for search query
	string searchStr = "";
	//Sting for user input year, month, day so can be typed and limited
	string pDYear, pDMonth, pDDay;
	//used to display tweets
	stringstream tweets;

	//sets up two text boxes to wrap the tweets inside
	//tweetsDiv for pages that take user input
	//exTweetsDiv for example pages
	ofxTextBlock tweetsDiv, exTweetsDiv;

	//integers
	//counts how many characters remaining to type for user input
	int charRem = 19;
	//sets the Y position for tweetsDiv so can be moved via arrow keys
	int divY = 500;
	//sets the Y position for exTweetsDiv so can be moved via arrow keys
	int exDivY = 240;
	//input integers for search date
	int sDay, sMonth, sYear;
	//real day, month, year to compare with search dates
	int rDay, rMonth, rYear;
	//Check day, month, year values for minimum search crit
	int cDayN, cMonthN;

	//Used to control the switch and page display
	char pageID;

	//Booleans for displaying tweets on each page
	bool displayFSTweets = false;
	bool displayHashTweets = false;
	bool displayDateTweets = false;
	bool displayLocTweets = false;
	bool displayPopTweets = false;
	bool display6NTweets = false;
	bool displayERTweets = false;
	bool displayPopRTweets = false;
	bool displayDateBSTweets = false;
	bool displayPopBSUTweets = false;
	bool displayUserTweets = false;

	//booleans to check whether a valid date has been input
	bool validDate = false;
	bool futureDate = false;
	
	//Used to control the input on date page into each box
	bool inpDDay = true;
	bool inpDMonth = false; 
	bool inpDYear = false;

	//Buttons
	//Home Page
	ofRectangle rectFs;
	findButton btnFs;
	ofRectangle rectOpt1;
	findButton btnOpt1;
	ofRectangle rectOpt2;
	findButton btnOpt2;
	ofRectangle rectOpt3;
	findButton btnOpt3;
	ofRectangle rectOpt4;
	findButton btnOpt4;
	ofRectangle rectOpt5;
	findButton btnOpt5;
	ofRectangle rectMore;
	findButton btnMore;

	//More page
	ofRectangle rectFsM;
	findButton btnFsM;
	ofRectangle rectOpt1M;
	findButton btnOpt1M;
	ofRectangle rectOpt2M;
	findButton btnOpt2M;
	ofRectangle rectOpt3M;
	findButton btnOpt3M;
	ofRectangle rectOpt4M;
	findButton btnOpt4M;
	ofRectangle rectOpt5M;
	findButton btnOpt5M;
	ofRectangle rectOpt6M;
	findButton btnOpt6M;
	ofRectangle rectOpt7M;
	findButton btnOpt7M;
	ofRectangle rectOpt8M;
	findButton btnOpt8M;
	ofRectangle rectOpt9M;
	findButton btnOpt9M;
	ofRectangle rectOpt10M;
	findButton btnOpt10M;

	//Free search page
	findButton btnFSearch;
	ofRectangle rectFSearch;

	//Hashtag search page
	findButton btnHashSearch;
	ofRectangle rectHashSearch;

	//Date search page
	findButton btnDateSearch;
	ofRectangle rectDateSearch;
	//ofRectangle areas for date boxes
	ofRectangle pDYBox, pDMBox, pDDBox;

	//User search page
	findButton btnUserSearch;
	ofRectangle rectUserSearch;

	//Location search page
	ofRectangle rectBath;
	ofRectangle rectNY;
	ofRectangle rectHelsinki;
	ofRectangle rectTokyo;

	//Popular tweets with word page
	findButton btnPopSearch;
	ofRectangle rectPopSearch;

	//Other;
	ofRectangle rectHome;
	findButton btnHome;
	ofRectangle rectMore2;
	findButton btnMore2;
};