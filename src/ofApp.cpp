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
    
    server.registerMethod("getSurveyAnswers", "Receive Survey Answers", this, &ofApp::getSurveyAnswers);
    
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
<<<<<<< HEAD
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
=======
    
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
            setUserText("question,4");
            break;
        case '5':
            setUserText("question,5");
            break;
        case '6':
            setUserText("question,6");
            break;
        case '7':
            setUserText("question,7");
            break;
        case 'b':
            setUserText("black");
            break;
        case 'w':
            setUserText("white");
            break;
        case 's':
            setUserText("start");
            break;
        case 'c':
            setUserText("image,/img/cat.gif");
            break;
        case 'f':
            sendFrame("wtf, how do I make a frame?");
            break;
>>>>>>> a1bb656563aeba69c02989d0100df41aeb8faedd
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
<<<<<<< HEAD
=======

void ofApp::sendFrame(string frame){
    //    ofxHTTP::WebSocketFrame frame;
    //    frame.
    server.webSocketRoute().broadcast(ofxHTTP::WebSocketFrame(frame));
}

>>>>>>> a1bb656563aeba69c02989d0100df41aeb8faedd
