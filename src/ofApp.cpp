//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"

std::string jsonn;

void ofApp::setup()
{
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_SILENT);
    ofx::HTTP::JSONRPCServerSettings settings;
    settings.setPort(8197);
    // Initialize the server.
    server.setup(settings);


    // Register RPC methods.
    
    server.registerMethod("get-survey-answers", "Receive Survey Answers", this, &ofApp::getSurveyAnswers);
    
    server.registerMethod("get-current-page", "On Startup, get the current page", this, &ofApp::getCurrentPage);

    // Start the server.
    server.start();

    // Launch a browser with the address of the server.
    ofLaunchBrowser(server.url());
}


void ofApp::draw()
{
    ofBackground(255);
    ofDrawBitmapStringHighlight("Open the URL: " + server.url(), 14, 18);
    ofDrawBitmapStringHighlight(userText, 14, 42, ofColor::yellow, ofColor::red);
    
    fader = ofClamp(fader - 10, 0, 255);
    ofDrawBitmapStringHighlight(fadingText,
                                ofGetWidth() / 2 - 25,
                                ofGetHeight() / 2,
                                ofColor(0, fader),
                                ofColor(255, fader));
}

void ofApp::ping()
{
    ofLogVerbose("ofApp::ping") << "Ping'd";
}

void ofApp::getSurveyAnswers(ofx::JSONRPC::MethodArgs& args){
    
    cout<<"Client Address: " + args.request().clientAddress().toString() + " Server Address: " + args.request().serverAddress().toString() <<endl;
    std::cout << "Received: " << args.params.dump(4) << endl;
  // here the answer will be saved to json.

}

void ofApp::setSurveyPage(string page, string extra ){
    jsonn = "{\"jsonrpc\":\"no\",\"page\":\"" + page + "\",\"extra\":\"" + extra + "\"}";
    server.webSocketRoute().broadcast(ofx::HTTP::WebSocketFrame(jsonn));
    std::cout << "Broadcast page: " << page << ", " << extra << endl;
}

void ofApp::exit()
{
    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
}


void ofApp::keyPressed(int key){
    string page="none";
    string extra;
    if ( 47 < key && key < 58 ) {
                page = "questions";
                extra = key;
    } else {
        switch (key) {
            case 'b':
                page= "black";
                break;
            case 'w':
                page = "white";
                break;
            case 's':
                page = "start";
                break;
            case 'c':
                page = "image";
                extra = "/img/cat.gif";
                break;
        }
    }
    if ( page == "none"){
        ofLogVerbose("ofApp::keyPressed") << "The key pressed does not correspond to any page";
    } else {
        setSurveyPage(page,extra);
    }
}

void ofApp::setText(ofx::JSONRPC::MethodArgs& args)
{
  // here the answer will be saved to json.
    ofLogVerbose("ofApp::setText") << args.params.dump(4);
    std::cout << "received: " << args.params.dump(4) << endl;
}

void ofApp::getCurrentPage(ofx::JSONRPC::MethodArgs& args)
{
    args.result = jsonn;
    cout<<"Client: " + args.request().clientAddress().toString() + " asked for currentPage." <<endl;

}

void ofApp::setUserText(const std::string& text)
{
    std::unique_lock<std::mutex> lock(mutex);
    userText = text;
}

void ofApp::sendFrame(string frame){
    //    ofxHTTP::WebSocketFrame frame;
    //    frame.
    server.webSocketRoute().broadcast(ofxHTTP::WebSocketFrame(frame));
}
