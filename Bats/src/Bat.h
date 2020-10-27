#pragma once
#include "ofMain.h"

class Bat
{
public:

	Bat(vector<ofImage> *, int batRadius);
	Bat(vector<ofImage> * batImages, int batRadius, ofVec2f pos, ofVec2f velocity);

	void update(vector<Bat*> * , float a, float s, float b);
	void draw(bool debug);

private:

	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;

	int maxForce;
	int maxSpeed;
	int perceptionRadius = 100;

	void edges();
	void flock(vector<Bat*> * bats, float alignValue, float cohesionValue, float separationValue);

	ofVec2f alignment(vector<Bat*> * bats);
	ofVec2f cohesion(vector<Bat*> * bats);
	ofVec2f separation(vector<Bat*> * bats);

	vector<ofImage> * images;
	int currImage;
	int radius;

};

