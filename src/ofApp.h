//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxJSONRPC.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;
    void exit() override;
    void keyPressed(int key);
    void sendFrame(string frame);

    // Registered methods.
    void setText(ofx::JSONRPC::MethodArgs& args);
    void getSurveyAnswers(ofx::JSONRPC::MethodArgs& args);
    void setSurveyPage(string page, string extra = NULL);
    void getCurrentPage(ofx::JSONRPC::MethodArgs& args);


    bool is_number(const std::string& s);
    void ping();

    /// \brief The server that handles the JSONRPC requests.
    ofx::HTTP::JSONRPCServer server;

    /// \brief Set the user text in a thread-safe way.
    /// \param text the user text to set.
    void setUserText(const std::string& text);

private:
    // A custom logging channel to mirror all log messages to the web clients.
    // WebSocketLoggerChannel::SharedPtr loggerChannel;

    // This piece of text might be modified by multiple client threads.
    // Thus we must use a mutex to protect it during multi-threaded access.
    std::string userText;
    std::string jsonn;

    // We use a mutex to protect any variables that can be
    // modified by multiple clients. In our case, userText must be protected.
    // We mark the mutex as mutable so that it can be used in const functions.
    mutable std::mutex mutex;
    
    float fader = 0;
    std::string fadingText;

};
