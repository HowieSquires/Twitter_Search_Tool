//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

//Connects page with code on page ofApp.h
#include "ofApp.h"
//Shortcut to not writing ofxTwitter::... for any twitter addon code
using namespace ofx::Twitter;

//Function runs on first app execution
void ofApp::setup()
{
	//Came with project generation
	//Sets frame rate of the app
	ofSetFrameRate(30);

	// Easily register for all search events.
	client.registerSearchEvents(this);

	// First we load credentials from a file. These can also be loaded manually
	// using the ofxTwitter::Credentials constructor.
	//
	// Developers must get their credentials after creating an app at
	// https://apps.twitter.com
	//Loads credentials from data folder
	client.setCredentialsFromFile("credentials.json");

	// Set the polling interval for 6 seconds.
	client.setPollingInterval(6000);

	//My content
	//Set the starting page to 'h' = home
	pageID = 'h';

	//Sets colour variable to use for background
	colour1.set(104, 226, 255);

	//Clears the tweets stringstream
	tweets.str("");

	//Sets rel date variables to the value of the current day
	rDay = ofGetDay();
	rMonth = ofGetMonth();
	rYear = ofGetYear();

	//fonts -> Some aren't used but here for future development
	titleTXT.load("LGCafeBold.ttf", 54);
	subheadTXT.load("LGCafeBold.ttf", 44);
	mainTXT.load("LGCafe.ttf", 34);
	btnTXT.load("LGCafe.ttf", 28);
	minorTXT.load("LGCafe.ttf", 24);
	ofSetLineWidth(4.0f);
	//tweets text boxes
	tweetsDiv.init("LGCafe.ttf", 34);
	exTweetsDiv.init("LGCafe.ttf", 34);

	//Buttons
	btnHome.setup(rectHome, 10, 10);
	btnMore2.setup(rectMore2, 220, 10);
	//Home page Buttons
	btnFs.setup(rectFs, ofGetWidth() / 2 - 50, 385);
	btnOpt1.setup(rectOpt1, 10, 630);
	btnOpt2.setup(rectOpt2, 10, 780);
	btnOpt3.setup(rectOpt3, 10, 930);
	btnOpt4.setup(rectOpt4, ofGetWidth() / 2 - 50, 630);
	btnOpt5.setup(rectOpt5, ofGetWidth() / 2 - 50, 780);
	btnMore.setup(rectMore, ofGetWidth() / 2 - 50, 930);
	//More page buttons
	btnFsM.setup(rectFsM, 10, 190 + 50);
	btnOpt1M.setup(rectOpt1M, 10, 190 + 195);
	btnOpt2M.setup(rectOpt2M, 10, 190 + 335);
	btnOpt3M.setup(rectOpt8M, 10, 190 + 475);
	btnOpt4M.setup(rectOpt3M, 10, 190 + 620);
	btnOpt5M.setup(rectOpt4M, 10, 190 + 765);
	btnOpt6M.setup(rectOpt5M, ofGetWidth() / 2 - 50, 190 + 195);
	btnOpt7M.setup(rectOpt6M, ofGetWidth() / 2 - 50, 190 + 335);
	btnOpt8M.setup(rectOpt7M, ofGetWidth() / 2 - 50, 190 + 475);
	btnOpt9M.setup(rectOpt9M, ofGetWidth() / 2 - 50, 190 + 620);
	btnOpt10M.setup(rectOpt10M, ofGetWidth() / 2 - 50, 190 + 765);
	//Free search page button
	btnFSearch.setup(rectFSearch, ofGetWidth() / 2 - 50, 210);
	//Hashtag search page button
	btnHashSearch.setup(rectHashSearch, ofGetWidth() / 2 + 10, 210);
	//Date search page button
	btnDateSearch.setup(rectDateSearch, 1060, 210);
	pDYBox.set(870, 210, 150, 75);
	pDMBox.set(530, 210, 150, 75);
	pDDBox.set(150, 210, 150, 75);
	//User search page
	btnUserSearch.setup(rectUserSearch, 980, 210);
	//Location search page
	rectBath.set(10, 210, 400, 75);
	rectNY.set(450, 210, 400, 75);
	rectHelsinki.set(890, 210, 400, 75);
	rectTokyo.set(1330, 210, 400, 75);
	//Popular tweets with word page
	btnPopSearch.setup(rectPopSearch, ofGetWidth() / 2 - 50, 210);
}

//Function loops throughout the app run time
void ofApp::draw()
{
	//My Content
	//Sets app background
	ofBackground(colour1);
	//Calls the getPage() function and passes the pageID variable
	getPage(pageID);
}

//When the app receives tweets from the Twitter API they are controlled here
void ofApp::onStatus(const ofxTwitter::Status& status)
{	
	//Counts the amount of tweets received
	count++;
	//Puts the received twets into the tweets stringstream with username of the tweet
	tweets << "New tweet from @" << status.user()->screenName() << ": " << status.text() << "<br/><br/>";
	//If the tweets received are from searches of pages a, g, d, j, i or f, they are wrapped in the tweetsDiv textbox
	//Else they are wrapped in the exTweetsDiv textbox
	if (pageID == 'a' || pageID == 'g' || pageID == 'd' || pageID == 'j' || pageID == 'i' || pageID == 'f' || pageID == 's') {
		tweetsDiv.setHtmlText(tweets.str());
		tweetsDiv.wrapTextX(ofGetWidth() - 20);
	}
	else {
		exTweetsDiv.setHtmlText(tweets.str());
		exTweetsDiv.wrapTextX(ofGetWidth() - 20);
	}
	
	//Unused but possible use in future development
	//ofLogNotice("ofApp::onStatus") << "Text: " << status.text();
	//ofLogNotice("ofApp::onStatus") << "Coordinates: " << (status.coordinates() ? ofToString(status.coordinates()) : "NONE");
	//ofLogNotice("ofApp::onStatus") << "Place: " << (status.place() ? ofToString(status.place()->fullName()) : "NONE");
}

//If Twitter API runs into an error, this function is called
void ofApp::onError(const ofxTwitter::Error& error)
{
	ofLogError("ofApp::onError") << "Error: " << error.code() << " " << error.message();
}

//If Twitter API runs into an exception, this function is called
void ofApp::onException(const std::exception& notice)
{
	ofLogError("ofApp::onException") << "Exception: " << notice.what();
}

//If Twitter API receives a message, this function is called
void ofApp::onMessage(const ofJson& json)
{
	// This is the raw message json and is ignored here.
}

//draws GUI for each page
void ofApp::getPage(char pageID) {
	switch (pageID) {
	//Home page
	case 'h':
		//top section -> intro text
		mainTXT.drawString("Welcome to your Twitter Search tool! By using this app you'll be able to search for tweets \nthrough free searching or by predefined searches such as \"Rugby\" by date, Tweets \nmentioning a user or #6Nations2018!", 10, 170);
		//free search sub title
		subheadTXT.drawString("Free Search:", 10, 350);
		ofDrawLine(10, 370, 10 + subheadTXT.stringWidth("Free Search:"), 370);
		//Search bar
		ofDrawRectangle(10, 385, ofGetWidth() / 2 - 100, 75);
		ofSetColor(0);
		//Draws user input string over text box
		mainTXT.drawString(searchInp, 50, 435);
		ofSetColor(255);
		//Tells user the amount of chacters left -> Based on amount of 'W' can fit in the box
		minorTXT.drawString(to_string(charRem) + " Remaining of 19", 50, 490);
		//Draws find button object
		btnFs.drawFind();
		//Menu
		ofSetColor(255);
		//Menu sub title
		subheadTXT.drawString("Menu:", 10, 570);
		ofDrawLine(10, 590, 10 + subheadTXT.stringWidth("Menu:"), 590);
		//Loads find buttons and text for the menu which lead to corresponding page on mouse click
		btnOpt1.drawFind();
		mainTXT.drawString("Search by hashtag...", 260, 630 + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt2.drawFind();
		mainTXT.drawString("Search \"Rugby\" by date...", 260, 780 + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt3.drawFind();
		mainTXT.drawString("Search tweets with a user...", 260, 930 + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt4.drawFind();
		mainTXT.drawString("Search \"Rugby\" within a location...", (ofGetWidth() / 2 - 50) + 250, 630 + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt5.drawFind();
		mainTXT.drawString("Most popular tweets with a word...", (ofGetWidth() / 2 - 50) + 250, 780 + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnMore.drawMore();
		mainTXT.drawString("More Options", (ofGetWidth() / 2 - 50) + 250, 930 + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		break;
	//More page
	case 'm':
		//Home button top left
		btnHome.drawHome();
		//Sub title
		subheadTXT.drawString("More Options:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("More Options:"), 190);
		btnFsM.drawFind();
		//Buttons with text 
		mainTXT.drawString("Free search...", 260, (190 + 50) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt1M.drawFind();
		mainTXT.drawString("Search by hashtag...", 260, (190 + 195) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt2M.drawFind();
		mainTXT.drawString("#6Nations2018...", 260, (190 + 335) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt3M.drawFind();
		mainTXT.drawString("Search tweets with a user......", 260, (190 + 475) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt4M.drawFind();
		mainTXT.drawString("@EnglandRugby...", 260, (190 + 620) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt5M.drawFind();
		mainTXT.drawString("Search \"Rugby\" by date...", 260, (190 + 765) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt6M.drawFind();
		mainTXT.drawString("Most popular tweets with a word...", (ofGetWidth() / 2 - 50) + 250, (190 + 195) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt7M.drawFind();
		mainTXT.drawString("Most popular tweets with \"Rugby\"...", (ofGetWidth() / 2 - 50) + 250, (190 + 335) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt8M.drawFind();
		mainTXT.drawString("Search \"Rugby\" within a location...", (ofGetWidth() / 2 - 50) + 250, (190 + 475) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt9M.drawFind();
		mainTXT.drawString("Search \"Bath Spa\" by date...", (ofGetWidth() / 2 - 50) + 250, (190 + 620) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		btnOpt10M.drawFind();
		mainTXT.drawString("Most popular tweets \"@BathSpaSU\"...", (ofGetWidth() / 2 - 50) + 250, (190 + 765) + (75 - mainTXT.stringHeight("Find!") / 2) - 5);
		break;
	//Free search page
	case 's':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (displayFSTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if(displayFSTweets && count == 0){
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please enter another search term and click [Find!]", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please enter a search term and click [Find!]", 10, 500);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Free search:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Free search:"), 190);
		//Search Bar
		ofDrawRectangle(10, 210, ofGetWidth() / 2 - 100, 75);
		ofSetColor(0);
		mainTXT.drawString(searchInp, 50, 260);
		ofSetColor(255);
		minorTXT.drawString(to_string(charRem) + " Remaining of 19", 50, 315);
		btnFSearch.drawFind();
		//Subtitle 
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);		
		break;
	//Hashtag page
	case 'a':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		//Display Tweets 
		if (displayHashTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if (displayHashTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please enter another search term and click [Find!]", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please enter a search term and click [Find!]", 10, 500);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Search by hashtag:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Search by hashtag:"), 190);
		//Search Bar
		subheadTXT.drawString("#", 10, 260);
		ofDrawRectangle(60, 210, ofGetWidth() / 2 - 100, 75);
		ofSetColor(0);
		mainTXT.drawString(searchInp, 120, 260);
		ofSetColor(255);
		minorTXT.drawString(to_string(charRem) + " Remaining of 19", 120, 315);
		btnHashSearch.drawFind();
		//Subtitle 
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);
		break;
	//#6Nations2018 page
	case 'b':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (display6NTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			exTweetsDiv.drawLeft(10, exDivY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 260);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 240);
		}
		else if (display6NTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found at this time, \n Please try again later!", 10, 240);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please wait for #SixNations results to load...", 10, 240);
		}
		//Rest of page
		//Home and more buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Sub title
		subheadTXT.drawString("#6Nations2018:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("#SixNations:"), 190);
		break;
	//@EnglandRugby page
	case 'c':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (displayERTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			exTweetsDiv.drawLeft(10, exDivY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 260);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 240);
		}
		else if (displayERTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found at this time, \n Please try again later!", 10, 240);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please wait for #SixNations results to load...", 10, 240);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("@EnglandRugby:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("@EnglandRugby:"), 190);
		break;
	//"Rugby" by date page
	case 'd':
		//Display Tweets if valid date and count is more than 0
		//Display "Not within 7 days" message
		//Display "Can't search future message
		//Displays "please enter data" message
		if (displayDateTweets && validDate && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if (displayDateTweets && validDate && !futureDate && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please enter another date and click [Find!]", 10, 500);
		}
		else if (displayDateTweets && !validDate && !futureDate) {
			mainTXT.drawString("Sorry date input is not within 7 days! \n Please enter another date and click [Find!]", 10, 500);
		}
		else if (displayDateTweets && !validDate && futureDate) {
			mainTXT.drawString("Sorry cannot search tweets from the future! \n Please enter another date and click [Find!]", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please enter a search term and click [Find!]", 10, 500);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Search \"Rugby\" by date (within 7 days):", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Search \"Rugby\" by date (within 7 days):"), 190);
		//Date Search Bars
		//Day
		subheadTXT.drawString("Day:", 10, 260);
		ofDrawRectangle(pDDBox);
		ofSetColor(0);
		mainTXT.drawString(pDDay, 170, 260);
		ofSetColor(255);
		//Month
		subheadTXT.drawString("Month:", 320, 260);
		ofDrawRectangle(pDMBox);
		ofSetColor(0);
		mainTXT.drawString(pDMonth, 550, 260);
		ofSetColor(255);
		//Year
		subheadTXT.drawString("Year:", 700, 260);
		ofDrawRectangle(pDYBox);
		ofSetColor(0);
		mainTXT.drawString(pDYear, 890, 260);
		ofSetColor(255);
		//Find button
		btnDateSearch.drawFind();
		//Subtitle 
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);
		break;
	//Popular tweets with "Rugby" 
	case 'e':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (displayPopRTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			exTweetsDiv.drawLeft(10, exDivY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 260);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 240);
		}
		else if (displayPopRTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found at this time, \n Please try again later!", 10, 240);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please wait for \"Rugby\" results to load...", 10, 240);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Most popular tweets with \"Rugby\":", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Most popular tweets with \"Rugby\":"), 190);
		break;
	//"Bath Spa" By date
	case 'f':
		//Display Tweets if valid date and count is more than 0
		//Display "Not within 7 days" message
		//Display "Can't search future message
		//Displays "please enter data" message
		if (displayDateBSTweets && validDate && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if (displayDateBSTweets && validDate && !futureDate && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please enter another date and click [Find!]", 10, 500);
		}
		else if (displayDateBSTweets && !validDate && !futureDate) {
			mainTXT.drawString("Sorry date input is not within 7 days! \n Please enter another date and click [Find!]", 10, 500);
		}
		else if (displayDateBSTweets && !validDate && futureDate) {
			mainTXT.drawString("Sorry cannot search tweets from the future! \n Please enter another date and click [Find!]", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please enter a search term and click [Find!]", 10, 500);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Search \"Bath Spa\" by date (within 7 days):", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Search \"Bath Spa\" by date (within 7 days):"), 190);
		//Date Search Bars
		//Day
		subheadTXT.drawString("Day:", 10, 260);
		ofDrawRectangle(pDDBox);
		ofSetColor(0);
		mainTXT.drawString(pDDay, 170, 260);
		ofSetColor(255);
		//Month
		subheadTXT.drawString("Month:", 320, 260);
		ofDrawRectangle(pDMBox);
		ofSetColor(0);
		mainTXT.drawString(pDMonth, 550, 260);
		ofSetColor(255);
		//Year
		subheadTXT.drawString("Year:", 700, 260);
		ofDrawRectangle(pDYBox);
		ofSetColor(0);
		mainTXT.drawString(pDYear, 890, 260);
		ofSetColor(255);
		//Find button
		btnDateSearch.drawFind();
		//Subtitle 
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);
		break;
	//Search tweets with user page
	case 'g':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (displayUserTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if (displayUserTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please enter another search term and click [Find!]", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please enter a search term and click [Find!]", 10, 500);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Search tweets with a user:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Search tweets with a user:"), 190);
		//Search Bar
		subheadTXT.drawString("@", 10, 260);
		ofDrawRectangle(80, 210, ofGetWidth() / 2 - 100, 75);
		ofSetColor(0);
		mainTXT.drawString(searchInp, 140, 260);
		ofSetColor(255);
		minorTXT.drawString(to_string(charRem) + " Remaining of 19", 140, 315);
		//Find button
		btnUserSearch.drawFind();
		//Results
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);
		break;
	//Display "Rugby" tweets from location
	case 'i':
		if (displayLocTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if (displayLocTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please chose another [location] above!", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please click a [location] above!", 10, 500);
		}
		//Rest of page
		//Top buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Search \"Rugby\" within a location:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Search \"Rugby\" within a location:"), 190);
		//Location buttons
		//Bath
		ofSetColor(255);
		ofDrawRectangle(rectBath);
		ofSetColor(0);
		subheadTXT.drawString("Bath", rectBath.getX() + ((rectBath.getWidth() / 2) - (subheadTXT.stringWidth("Bath") / 2)), 270);
		ofSetColor(255);
		//New York
		ofDrawRectangle(rectNY);
		ofSetColor(0);
		subheadTXT.drawString("New York", rectNY.getX() + ((rectNY.getWidth() / 2) - (subheadTXT.stringWidth("New York") / 2)), 270);
		ofSetColor(255);
		//Helsinki
		ofDrawRectangle(rectHelsinki);
		ofSetColor(0);
		subheadTXT.drawString("Helsinki", rectHelsinki.getX() + ((rectHelsinki.getWidth() / 2) - (subheadTXT.stringWidth("Helsinki") / 2)), 270);
		ofSetColor(255);
		//Tokyo
		ofDrawRectangle(rectTokyo);
		ofSetColor(0);
		subheadTXT.drawString("Tokyo", rectTokyo.getX() + ((rectTokyo.getWidth() / 2) - (subheadTXT.stringWidth("Tokyo") / 2)), 270);
		//Results
		ofSetColor(255);
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);
		break;
	//Popular tweets with word page
	case 'j':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (displayPopTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			tweetsDiv.drawLeft(10, divY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 485);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 475);
		}
		else if (displayPopTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no results found! \n Please enter another search term and click [Find!]", 10, 500);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please enter a search term and click [Find!]", 10, 500);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Most popular tweets with a word:", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Most popular tweets with a word:"), 190);
		//Search Bar
		ofDrawRectangle(10, 210, ofGetWidth() / 2 - 100, 75);
		ofSetColor(0);
		mainTXT.drawString(searchInp, 50, 260);
		ofSetColor(255);
		minorTXT.drawString(to_string(charRem) + " Remaining of 19", 50, 315);
		btnPopSearch.drawFind();
		//Subtitle 
		subheadTXT.drawString("Results:", 10, 425);
		ofDrawLine(10, 445, 10 + subheadTXT.stringWidth("Results:"), 445);
		break;
	//Popular tweets with "@BathSpaSU" page
	case 'k':
		//Display Tweets if bool is true and count is more than 0
		//Else if bool is true but no tweets found display "No tweets" message
		//Else display text if bool is false
		if (displayPopBSUTweets && count > 0) {
			//Output tweets
			ofSetColor(255);
			exTweetsDiv.drawLeft(10, exDivY);
			//Prevent tweets from drawing over top of page
			ofSetColor(colour1);
			ofDrawRectangle(0, 0, ofGetWidth(), 260);
			ofSetColor(255);
			//Instruct user
			minorTXT.drawString("(Use UP and DOWN arrows to scroll)", 10, 240);
		}
		else if (displayPopBSUTweets && count == 0) {
			//If no search term is returned this will display
			mainTXT.drawString("Sorry no popular @BathSpaSU tweets found at this time, \n Please try again later!", 10, 240);
		}
		else {
			//If no search term is entered this will display
			mainTXT.drawString("Please wait for \"Rugby\" results to load...", 10, 240);
		}
		//Rest of page
		//Home and More page buttons
		btnHome.drawHome();
		btnMore2.drawMore();
		//Title
		subheadTXT.drawString("Most popular tweets with \"@BathSpaSU\":", 10, 170);
		ofDrawLine(10, 190, 10 + subheadTXT.stringWidth("Most popular tweets with \"@BathSpaSU\":"), 190);
		break;
	//If for some reason none of the above pages are selected, the user can still return to home or more pages
	//Shouldn't occur at all
	default:
		btnHome.drawHome();
		btnMore2.drawMore();
		break;
	}

	//Displays title on all screens
	ofSetColor(255);
	titleTXT.drawString("Twitter Search", (ofGetWidth() / 2) - (titleTXT.stringWidth("Twitter Search") / 2), titleTXT.stringHeight("Twitter Search") + 20);
	ofDrawLine(ofGetWidth() / 2 - 235, 90, ofGetWidth() / 2 + 235, 90);
}

//Function thats called when user presses a keyboard key
void ofApp::keyPressed(int key) {
	//Learned to control from: //https://forum.openframeworks.cc/t/text-input-creating-words-by-entering-and-showing-on-screen/2846/3
	//Key codes taken from: http://www.expandinghead.net/keycode.html
	//Switch for user input to be controlled conditioned to the page they're on
	switch (pageID) {
	//Home page
	case 'h':
		//If key is 8 (Backspace) and string size is more than 0, delete last character in string
		//Add one to the remaining characters variable
		if (key == 8 && searchInp.size() > 0) {
			searchInp = searchInp.substr(0, searchInp.size() - 1);
			charRem++;
		}
		//If any other key and string size is less than 19, add it it to end of string
		//Minus one from remaining characters
		else if (key >= 32 && key <= 126 && searchInp.size() < 19) {
			searchInp.append(1, (char)key);
			charRem--;
		}
		break;
	//Free Search page
	case 's':
		//If key is 8 (Backspace) and string size is more than 0, delete last character in string
		//Add one to the remaining characters variable
		if (key == 8 && searchInp.size() > 0) {
			searchInp = searchInp.substr(0, searchInp.size() - 1);
			charRem++;
		}
		//If any other key and string size is less than 19, add it it to end of string
		//Minus one from remaining characters
		else if (key >= 32 && key <= 126 && searchInp.size() < 19) {
			searchInp.append(1, (char)key);
			charRem--;
		}
		//If up key, move divY downwards
		else if (key == OF_KEY_UP && displayFSTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayFSTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//Hastag page
	case 'a':
		//If key is 8 (Backspace) and string size is more than 0, delete last character in string
		//Add one to the remaining characters variable
		if (key == 8 && searchInp.size() > 0) {
			searchInp = searchInp.substr(0, searchInp.size() - 1);
			charRem++;
		}
		//If any other key and string size is less than 19, add it it to end of string
		//Minus one from remaining characters
		else if (key >= 32 && key <= 126 && searchInp.size() < 19) {
			searchInp.append(1, (char)key);
			charRem--;
		}
		//If up key, move divY downwards
		else if (key == OF_KEY_UP && displayHashTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayHashTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//#6Nations2018 page
	case 'b':
		//If up key, move divY downwards
		if (key == OF_KEY_UP && display6NTweets) {
			exDivY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && display6NTweets && divY <= 500) {
			exDivY += 10;
		}
		break;
	//@EnglandRugby page
	case 'c':
		//If up key, move divY downwards
		if (key == OF_KEY_UP && displayERTweets) {
			exDivY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayERTweets && divY <= 500) {
			exDivY += 10;
		}
		break;
	//"Rugby" By date
	case 'd':
		//If day input bool is true add characters to this pDDay string
		if (inpDDay) {
			//If string size is 0, only allow numbers 0-3
			if (pDDay.size() <= 0 && key >= 48 && key <= 51) {
				pDDay.append(1, (char)key);
			}
			//If string size is 1 and first number is 0, only allow 1-9
			else if (pDDay.size() == 1 && atoi(pDDay.c_str()) == 0 && key >= 49 && key <= 57) {
				pDDay.append(1, (char)key);
			}
			//If string size is 1 and first number is 1 or more, only allow 0-9
			else if (pDDay.size() == 1 && atoi(pDDay.c_str()) >= 1 && atoi(pDDay.c_str()) <= 2 && key >= 48 && key <= 57) {
				pDDay.append(1, (char)key);
			}
			//If string size is 1 and first number is 3, only allow 0 or 1
			else if (pDDay.size() == 1 && atoi(pDDay.c_str()) == 3 && key >= 48 && key <= 49) {
				pDDay.append(1, (char)key);
			}
			//If key is 8 (Backspace) and string size is more than 0, delete last character in string
			//Add one to the remaining characters variable
			else if (key == 8 && pDDay.size() > 0) {
				pDDay = pDDay.substr(0, pDDay.size() - 1);
			}
		}
		//If month input bool is true add characters to this pDMonth string
		else if (inpDMonth) {
			//If string size is 0 and key is 0 or 1 append key
			if (pDMonth.size() <= 0 && key >= 48 && key <= 49) {
				pDMonth.append(1, (char)key);
			}
			//If string size is 1, first number is 0, allow numbers 0-9
			else if (pDMonth.size() == 1 && atoi(pDMonth.c_str()) == 0 && key >= 49 && key <= 57) {
				pDMonth.append(1, (char)key);
			}
			//If string size is 1, first number is 1, allow numbers 0-2
			else if (pDMonth.size() == 1 && atoi(pDMonth.c_str()) == 1 && key >= 48 && key <= 50) {
				pDMonth.append(1, (char)key);
			}
			//If key is 8 (Backspace) and string size is more than 0, delete last character in string
			//Add one to the remaining characters variable
			else if (key == 8 && pDMonth.size() > 0) {
				pDMonth = pDMonth.substr(0, pDMonth.size() - 1);
			}
		}
		//If year input bool is true add characters to this pDYear string
		else if (inpDYear) {
			//If string is 3 or less characters and key is 0-9, append it
			if (pDYear.size() <= 3 && key >= 48 && key <= 57) {
				pDYear.append(1, (char)key);
			}
			//If key is 8 (Backspace) and string size is more than 0, delete last character in string
			//Add one to the remaining characters variable
			else if (key == 8 && pDYear.size() > 0) {
				pDYear = pDYear.substr(0, pDYear.size() - 1);
			}
		}
		//If up key, move divY downwards
		if (key == OF_KEY_UP && displayDateTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayDateTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//Popular tweets with "Rugby" page
	case 'e':
		//If up key, move divY downwards
		if (key == OF_KEY_UP && displayPopRTweets) {
			exDivY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayPopRTweets && divY <= 500) {
			exDivY += 10;
		}
		break;
	case 'f':
		//Same as page 'd' key inputs
		if (inpDDay) {
			if (pDDay.size() <= 0 && key >= 48 && key <= 51) {
				pDDay.append(1, (char)key);
			}
			else if (pDDay.size() == 1 && atoi(pDDay.c_str()) == 0 && key >= 49 && key <= 57) {
				pDDay.append(1, (char)key);
			}
			else if (pDDay.size() == 1 && atoi(pDDay.c_str()) >= 1 && atoi(pDDay.c_str()) <= 2 && key >= 48 && key <= 57) {
				pDDay.append(1, (char)key);
			}
			else if (pDDay.size() == 1 && atoi(pDDay.c_str()) == 3 && key >= 48 && key <= 49) {
				pDDay.append(1, (char)key);
			}
			else if (key == 8 && pDDay.size() > 0) {
				pDDay = pDDay.substr(0, pDDay.size() - 1);
			}
		}
		else if (inpDMonth) {
			if (pDMonth.size() <= 0 && key >= 48 && key <= 49) {
				pDMonth.append(1, (char)key);
			}
			else if (pDMonth.size() == 1 && atoi(pDMonth.c_str()) == 0 && key >= 49 && key <= 57) {
				pDMonth.append(1, (char)key);
			}
			else if (pDMonth.size() == 1 && atoi(pDMonth.c_str()) == 1 && key >= 48 && key <= 50) {
				pDMonth.append(1, (char)key);
			}
			else if (key == 8 && pDMonth.size() > 0) {
				pDMonth = pDMonth.substr(0, pDMonth.size() - 1);
			}
		}
		else if (inpDYear) {
			if (pDYear.size() <= 3 && key >= 48 && key <= 57) {
				pDYear.append(1, (char)key);
			}
			else if (key == 8 && pDYear.size() > 0) {
				pDYear = pDYear.substr(0, pDYear.size() - 1);
			}
			else if (key == 8 && pDYear.size() > 2) {
				pDYear = pDYear.substr(0, pDYear.size() - 1);
			}
		}
		//If up key, move divY downwards
		if (key == OF_KEY_UP && displayDateBSTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayDateBSTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//Tweets with a user page
	case 'g':
		//If key is 8 (Backspace) and string size is more than 0, delete last character in string
		//Add one to the remaining characters variable
		if (key == 8 && searchInp.size() > 0) {
			searchInp = searchInp.substr(0, searchInp.size() - 1);
			charRem++;
		}
		//If any other key and string size is less than 19, add it it to end of string
		//Minus one from remaining characters
		else if (key >= 32 && key <= 126 && searchInp.size() < 19) {
			searchInp.append(1, (char)key);
			charRem--;
		}
		//If up key, move divY downwards
		else if (key == OF_KEY_UP && displayUserTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayUserTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//"Rugby by location page
	case 'i':
		//If up key, move divY downwards
		if (key == OF_KEY_UP && displayLocTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayLocTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//Popular tweets with word page
	case 'j':
		//If key is 8 (Backspace) and string size is more than 0, delete last character in string
		//Add one to the remaining characters variable
		if (key == 8 && searchInp.size() > 0) {
			searchInp = searchInp.substr(0, searchInp.size() - 1);
			charRem++;
		}
		//If key is a letter and string size is less than 19, add it it to end of string
		//Minus one from remaining characters
		else if ((((key >= 65) && (key <= 90)) || ((key >= 97) && (key <= 122))) && searchInp.size() < 19) {
			searchInp.append(1, (char)key);
			charRem--;
		}
		//If up key, move divY downwards
		else if (key == OF_KEY_UP && displayPopTweets) {
			divY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayPopTweets && divY <= 500) {
			divY += 10;
		}
		break;
	//Popular tweets with "@BathSpaSU" page
	case 'k':
		//If up key, move divY downwards
		if (key == OF_KEY_UP && displayPopBSUTweets) {
			exDivY -= 10;
		}
		//If down key, move divY upwards
		else if (key == OF_KEY_DOWN && displayPopBSUTweets && divY <= 500) {
			exDivY += 10;
		}
		break;
	//If any other page is called by critial error and key is pressed display text
	default:
		mainTXT.drawString("Sorry, error has occured, please restart the program", 10, 210);
		break;
	}	
}

//Builds search query function
void ofApp::getQuery(string queryStr) {
	//Make twitter query
	SearchQuery query("");
	query.setQuery(queryStr);
	query.setLanguage("en");
	//If pages j, e, or k add result type to popular
	if (pageID == 'j' || pageID == 'e' || pageID == 'k') {
		query.setResultType(ofxTwitter::SearchQuery::ResultType::POPULAR);
	}
	//Searches for the query and returns tweets to onStatus()
	client.search(query);
}

//runs when a mouse button is pressed
void ofApp::mousePressed(int x, int y, int button) {
	switch (pageID) {
	//Home page
	case 'h':
		//If mouse clicked inside Find button
		if (btnFs.areaID.inside(x, y)) {
			//Sets pageID to s for Free Search page
			pageID = 's';
			//Clears tweet count
			count = 0;
			//If input has been entered creates a search query
			if (searchInp.size() > 0) {
				tweets.str("");
				searchStr = searchInp;
				getQuery(searchStr);
				displayFSTweets = true;
			}
			else {
				displayFSTweets = false;
			}
		}
		//If mouse click inside any other page button, goes to that page
		if (btnOpt1.areaID.inside(x, y)) {
			pageID = 'a';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt2.areaID.inside(x, y)) {
			pageID = 'd';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt3.areaID.inside(x, y)) {
			pageID = 'g';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt4.areaID.inside(x, y)) {
			pageID = 'i';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt5.areaID.inside(x, y)) {
			pageID = 'j';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnMore.areaID.inside(x, y)) {
			pageID = 'm';
			charRem = 19;
		}
		break;
	//More page
	case 'm':
		//Home button goes to home page
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		//Other buttons go to corresponding pages
		if (btnFsM.areaID.inside(x, y)) {
			pageID = 's';
			count = 0;
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt1M.areaID.inside(x, y)) {
			pageID = 'a';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt2M.areaID.inside(x, y)) {
			pageID = 'b';
			searchInp = "";
			tweets.str("");
			count = 0;
			searchStr = "#6Nations2018";
			getQuery(searchStr);
			display6NTweets = true;
		}
		if (btnOpt3M.areaID.inside(x, y)) {
			pageID = 'g';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt4M.areaID.inside(x, y)) {
			pageID = 'c';
			searchInp = "";
			tweets.str("");
			count = 0;
			searchStr = "@EnglandRugby";
			getQuery(searchStr);
			displayERTweets = true;
		}
		if (btnOpt5M.areaID.inside(x, y)) {
			pageID = 'd';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt6M.areaID.inside(x, y)) {
			pageID = 'j';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt7M.areaID.inside(x, y)) {
			pageID = 'e';
			searchInp = "";
			tweets.str("");
			count = 0;
			searchStr = "Rugby";
			getQuery(searchStr);
			displayPopRTweets = true;
		}
		if (btnOpt8M.areaID.inside(x, y)) {
			pageID = 'i';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt9M.areaID.inside(x, y)) {
			pageID = 'f';
			searchInp = "";
			tweets.str("");
			charRem = 19;
		}
		if (btnOpt10M.areaID.inside(x, y)) {
			pageID = 'k';
			searchInp = "";
			tweets.str("");
			count = 0;
			searchStr = "@BathSpaSU";
			getQuery(searchStr);
			displayPopBSUTweets = true;
		}
		else {

		}
		break;
	//Free search page
	case 's':
		//Home or more buttons go to their pages
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			charRem = 19;
			divY = 500;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			charRem = 19;
			divY = 500;
		}
		//Find button
		if (btnFSearch.areaID.inside(x, y)) {
			//resets tweet count
			count = 0;
			//If user has input values creates query
			if (searchInp.size() > 0) {
				tweets.str("");
				searchStr = searchInp;
				getQuery(searchStr);
				displayFSTweets = true;
			}
			else {
				displayFSTweets = false;
			}
		}
		break;
	//Hashtag page
	case 'a':
		//Home and more buttons go to their pages
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			charRem = 19;
			divY = 500;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			charRem = 19;
			divY = 500;
		}
		//Find button
		if (btnHashSearch.areaID.inside(x, y)) {
			//Resets tweet count
			count = 0;
			//If user has input values, creates query
			if (searchInp.size() > 0) {
				tweets.str("");
				searchStr = string("#").append(searchInp);
				getQuery(searchStr);
				displayHashTweets = true;
			}
			else {
				displayHashTweets = false;
			}
		}
		break;
	//#6Nations2018 page
	case 'b':
		//Home and more buttons go to their pages
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			display6NTweets = false;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			display6NTweets = false;
		}
		break;
	//@EnglandRugby page
	case 'c':
		//Home and more buttons go to their pages
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			displayERTweets = false;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			displayERTweets = false;
		}
		break;
	//"Rugby" by date
	case 'd':
		//Home and more buttons go to their pages
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			displayDateTweets = false;
			pDDay = "";
			pDMonth = "";
			pDYear = "";
			charRem = 19;
			divY = 500;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			displayDateTweets = false;
			pDDay = "";
			pDMonth = "";
			pDYear = "";
			charRem = 19;
			divY = 500;
		}
		//If mouse click on day input box
		if (pDDBox.inside(x, y)) {
			//Day bool is true means key presses will add to day string
			inpDDay = true;
			inpDMonth = false;
			inpDYear = false;
		}
		//If mouse click on month input box
		if (pDMBox.inside(x, y)) {
			//Month bool is true means key presses will add to month string
			inpDMonth = true;
			inpDDay = false;
			inpDYear = false;
		}
		//If mouse click on year input box
		if (pDYBox.inside(x, y)) {
			//Year bool is true means key presses will add to Year string
			inpDYear = true;
			inpDDay = false;
			inpDMonth = false;
		}
		//If find button clicked
		if (btnDateSearch.areaID.inside(x, y)) {
			//Tweet count reset
			count = 0; 
			//If user has input values into all input boxes
			if (atoi(pDDay.c_str()) > 0 && atoi(pDMonth.c_str()) > 0 && atoi(pDYear.c_str()) > 0) {
				tweets.str("");
				displayDateTweets = true;
				//Search day, month, year integers = day, month, year input strings
				sDay = atoi(pDDay.c_str());
				sMonth = atoi(pDMonth.c_str());
				sYear = atoi(pDYear.c_str());

				//Sets minimum check dates according to real date
				//Doesn't work for February
				if (rDay <= 7) {
					cDayN = 30 - (7 - rDay);
					cMonthN = rMonth - 1;
				}
				else {
					cDayN = rDay - 7;
					cMonthN = rMonth;
				}
				//Checks if user input is within 7 days then makes query
				if ((((sDay <= cDayN) && (sMonth > cMonthN)) || ((sDay >= cDayN) && (sMonth >= cMonthN))) &&
				(((sDay >= rDay) && (sMonth < rMonth)) || ((sDay <= rDay) && (sMonth <= rMonth))) && sYear == rYear) {
					//Make query
					SearchQuery query("Rugby");
					query.setUntil(sYear, sMonth, sDay);
					query.setLanguage("en");
					client.search(query);
					validDate = true;
					futureDate = false;
				}
				//Checks if input date is from future
				else if (((sDay > rDay) && (sMonth >= rMonth) && (sYear >= rYear)) || 
					((sDay <= rDay) && (sMonth > rMonth) && (sYear >= rYear)) || sYear > rYear) {
					futureDate = true;
					validDate = false;
				}
				//Else if invalid date
				else {
					futureDate = false;
					validDate = false;
				}
			}
			else {
				displayDateTweets = false;
			}
		}
		break;
	//Popular tweets with "Rugby" page
	case 'e':
		//Home and more buttons leading to their page
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			displayPopRTweets = false;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			displayPopRTweets = false;
		}
		break;
	//"Bath Spa" by date
	case 'f':
		//Home and more buttons
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			displayDateBSTweets = false;
			pDDay = "";
			pDMonth = "";
			pDYear = "";
			divY = 500;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			displayDateBSTweets = false;
			pDDay = "";
			pDMonth = "";
			pDYear = "";
			divY = 500;
		}
		//Same as page D
		if (pDDBox.inside(x, y)) {
			inpDDay = true;
			inpDMonth = false;
			inpDYear = false;
		}
		if (pDMBox.inside(x, y)) {
			inpDMonth = true;
			inpDDay = false;
			inpDYear = false;
		}
		if (pDYBox.inside(x, y)) {
			inpDYear = true;
			inpDDay = false;
			inpDMonth = false;
		}
		if (btnDateSearch.areaID.inside(x, y)) {
			count = 0;
			//Search bar Find Button function here
			if (atoi(pDDay.c_str()) > 0 && atoi(pDMonth.c_str()) > 0 && atoi(pDYear.c_str()) > 0) {
				tweets.str("");
				displayDateBSTweets = true;
				sDay = atoi(pDDay.c_str());
				sMonth = atoi(pDMonth.c_str());
				sYear = atoi(pDYear.c_str());

				if (rDay <= 7) {
					cDayN = 30 - (7 - rDay);
					cMonthN = rMonth - 1;
				}
				else {
					cDayN = rDay - 7;
					cMonthN = rMonth;
				}

				if ((((sDay <= cDayN) && (sMonth > cMonthN)) || ((sDay >= cDayN) && (sMonth >= cMonthN))) &&
					(((sDay >= rDay) && (sMonth < rMonth)) || ((sDay <= rDay) && (sMonth <= rMonth))) && sYear == rYear) {
					//Make query
					SearchQuery query("\"Bath Spa\"");
					query.setUntil(sYear, sMonth, sDay);
					query.setLanguage("en");
					client.search(query);
					validDate = true;
					futureDate = false;
				}
				else if (((sDay > rDay) && (sMonth >= rMonth) && (sYear >= rYear)) ||
					((sDay <= rDay) && (sMonth > rMonth) && (sYear >= rYear))) {
					futureDate = true;
					validDate = false;
				}
				else {
					futureDate = false;
					validDate = false;
				}
			}
			else {
				displayDateBSTweets = false;
			}
		}
	//Tweets with user page
	case 'g':
		//Home and more buttons
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			charRem = 19;
			divY = 500;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			charRem = 19;
			divY = 500;
		}
		//Find button
		if (btnUserSearch.areaID.inside(x, y)) {
			//Tweets count reset
			count = 0;
			//If user has input values, creates query
			if (searchInp.size() > 0) {
				tweets.str("");
				searchStr = string("@").append(searchInp);
				getQuery(searchStr);
				displayUserTweets = true;
			}
			else {
				displayUserTweets = false;
			}
		}
		break;
	//"Rugby" By location
	case 'i':
		//Home and more buttons
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			charRem = 19;
			divY = 500;
			displayLocTweets = false;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			divY = 500;
			displayLocTweets = false;
		}
		//If user selects "Bath" creates query by Bath long, lat and radius
		if (rectBath.inside(x, y)) {
			tweets.str("");
			SearchQuery query("");
			query.setQuery("Rugby");
			query.setLanguage("en");
			query.setGeoCode(51.375470, -2.438925, 10, ofxTwitter::SearchQuery::UNITS_MILES);
			client.search(query);
			displayLocTweets = true;
		}
		//If user selects "New York" creates query by New York long, lat and radius
		if (rectNY.inside(x, y)) {
			tweets.str("");
			SearchQuery query("");
			query.setQuery("Rugby");
			query.setLanguage("en");
			query.setGeoCode(40.723458, -73.996172, 10, ofxTwitter::SearchQuery::UNITS_MILES);
			client.search(query);
			displayLocTweets = true;
		}
		//If user selects "Helsinki" creates query by Helsinki long, lat and radius
		if (rectHelsinki.inside(x, y)) {
			tweets.str("");
			SearchQuery query("");
			query.setQuery("Rugby");
			query.setLanguage("en");
			query.setGeoCode(60.168390, 24.940651, 10, ofxTwitter::SearchQuery::UNITS_MILES);
			client.search(query);
			displayLocTweets = true;
		}
		//If user selects "Tokyo" creates query by Tokyo long, lat and radius
		if (rectTokyo.inside(x, y)) {
			tweets.str("");
			SearchQuery query("");
			query.setQuery("Rugby");
			query.setLanguage("en");
			query.setGeoCode(35.699008, 139.770542, 10, ofxTwitter::SearchQuery::UNITS_MILES);
			client.search(query);
			displayLocTweets = true;
		}
		break;
	//Popular tweets with word
	case 'j':
		//Home and More buttons
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			charRem = 19;
			divY = 500;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			charRem = 19;
			divY = 500;
		}
		//Find button
		if (btnPopSearch.areaID.inside(x, y)) {
			//tweet count reset
			count = 0;
			//If user has input values, creates query
			if (searchInp.size() > 0) {
				tweets.str("");
				searchStr = searchInp;
				getQuery(searchStr);
				displayPopTweets = true;
			}
			else {
				displayPopTweets = false;
			}
		}
		break;
	//@BathSpaSU page
	case 'k':
		//Home and More buttons
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			displayPopBSUTweets = false;
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
			searchInp = "";
			tweets.str("");
			count = 0;
			exDivY = 240;
			displayPopBSUTweets = false;
		}
		break;
	//If critical error leads to a page
	default:
		//Home and More buttons
		if (btnHome.areaID.inside(x, y)) {
			pageID = 'h';
			searchInp = "";
			tweets.str("");
		}
		if (btnMore2.areaID.inside(x, y)) {
			pageID = 'm';
		}
		break;
	}
}
