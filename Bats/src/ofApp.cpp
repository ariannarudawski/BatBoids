#include "ofApp.h"

void ofApp::setup()
{
	batCloud = new BatCloud(50);
}

void ofApp::update()
{
	batCloud->update();
}

void ofApp::draw()
{
	batCloud->draw();
}

void ofApp::keyPressed(int key)
{
	batCloud->keyPressed(key);

	switch (key)
	{
	case 'f':
	case 'F':
		ofToggleFullscreen();
		break;
	}
}

void ofApp::windowResized(int w, int h)
{

}


