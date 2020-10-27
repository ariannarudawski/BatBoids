#pragma once
#include "Bat.h"

#include "ofxGui.h"

class BatCloud
{
public:

	BatCloud(int initialNumBats);

	void update();
	void draw();
	void keyPressed(int key);

private:

	// bats

	vector<Bat*> bats;

	ofParameter<float> alignment;
	ofParameter<float> cohesion;
	ofParameter<float> separation;

	// drawing

	int batRadius = 100;
	vector<ofImage> batImages;

	ofParameter<ofColor> batColor;
	ofParameter<ofColor> backgroundColor;

	// debug

	bool debug = true;
	ofxPanel gui;
	ofParameterGroup mainGroup;
};

