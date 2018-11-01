//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_SILENT);

    ofx::HTTP::JSONRPCServerSettings settings;
    settings.setPort(8197);
    // Initialize the server.
    server.setup(settings);


    // Register RPC methods.
    server.registerMethod("get-text","Returns a random chunk of text to the client.",this, &ofApp::getText);

    server.registerMethod("set-text", "Sets text from the user.", this, &ofApp::setText);
    
    server.registerMethod("getSurveyAnswers", "Receive Survey Answers", this, &ofApp::getSurveyAnswers);
    
    server.registerMethod("setSurveyPage", "Change question for audience", this, &ofApp::setSurveyPage);
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

void ofApp::getSurveyAnswers(ofx::JSONRPC::MethodArgs& args){
    
    cout<<"Client Address: " + args.request().clientAddress().toString() + " Server Address: " + args.request().serverAddress().toString() <<endl;

}

void ofApp::setSurveyPage(ofx::JSONRPC::MethodArgs& args){
    
    cout<<"Client Address: " + args.request().clientAddress().toString() + " Server Address: " + args.request().serverAddress().toString() <<endl;
    
}

void ofApp::exit()
{
    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
}


void ofApp::keyPressed(int key){
    
    switch (key) {
        case '0':
            setUserText("question,0");
            break;
        case '1':
            setUserText("question,1");
            break;
        case '2':
            setUserText("question,2");
            break;
        case '3':
            setUserText("question,3");
            break;
        case '4':
            setUserText("black");
            break;
        case '5':
            setUserText("white");
            break;
        case '6':
            setUserText("start");
            break;
        case '7':
            setUserText("image,/img/cat.gif");
            break;
    }
}


void ofApp::getText(ofx::JSONRPC::MethodArgs& args)
{
    string current = args.params;
    // Set the result equal to the substring.
    if ( current != userText){
          args.result = userText;
    }
    ofLogVerbose("ofApp::getText") << args.result.dump(4);
    //cout<<"Client Address: " + args.request().clientAddress().toString() + " Server Address: " + args.request().serverAddress().toString() <<endl;

}


void ofApp::setText(ofx::JSONRPC::MethodArgs& args)
{

  // here the answer will be saved to json.
    ofLogVerbose("ofApp::setText") << args.params.dump(4);
}


std::string ofApp::getUserText() const
{
    std::unique_lock<std::mutex> lock(mutex);
    return userText;
}


void ofApp::setUserText(const std::string& text)
{
    std::unique_lock<std::mutex> lock(mutex);
    userText = text;
}

