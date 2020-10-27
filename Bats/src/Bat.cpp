#include "Bat.h"

Bat::Bat(vector<ofImage> * batImages, int batRadius)
{
	this->position.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	this->velocity.set(ofRandom(365), ofRandom(365));
	this->acceleration.set(0, 0);

	this->maxForce = 1;
	this->maxSpeed = 4;

	this->images = batImages;
	this->currImage = ofRandom(this->images->size());
	radius = batRadius;
}

Bat::Bat(vector<ofImage>* batImages, int batRadius, ofVec2f pos, ofVec2f velocity)
{
	this->position.set(pos);
	this->position.set(ofRandom(2, 4));
	this->acceleration.set(0, 0);

	this->maxForce = 1;
	this->maxSpeed = 4;

	this->images = batImages;
	this->currImage = ofRandom(this->images->size());
	radius = batRadius;
}

void Bat::update(vector<Bat*> * bats, float a,  float c, float s)
{
	// update edges

	edges();

	// perform flocking evaluations

	flock(bats, a, c, s);
	position += velocity;
	velocity += acceleration;
	velocity.rescale(ofRandom(2, 4));
	velocity.limit(maxSpeed);
	acceleration.set(0, 0);

	// update flap image

	if (ofGetFrameNum() % 3 == 0)
	{
		++currImage;
		if (currImage == this->images->size())
			currImage = 0;
	}
}

void Bat::draw(bool debug)
{
	ofPushMatrix();
	ofTranslate(position);
	ofRotateRad(atan2(velocity.y,  velocity.x) + (PI * 0.5f));

	(*images)[currImage].draw(-radius * 0.5f, -radius * 0.5f);

	ofPopMatrix();
}

void Bat::edges()
{
	if (this->position.x > ofGetWidth() + radius) {
		this->position.x = -radius;
	}
	else if (this->position.x < -radius) {
		this->position.x = ofGetWidth() + radius;
	}
	if (this->position.y > ofGetHeight() + radius) {
		this->position.y = -radius;
	}
	else if (this->position.y < -radius) {
		this->position.y = ofGetHeight() + radius;
	}
}

void Bat::flock(vector<Bat*> * bats, float alignValue, float cohesionValue, float separationValue)
{
	ofVec2f a = alignment(bats) * alignValue;
	ofVec2f c = cohesion(bats) * cohesionValue;
	ofVec2f s = separation(bats) * separationValue;

	acceleration += (a + c + s);
}

ofVec2f Bat::alignment(vector<Bat*> * bats)
{
	ofVec2f steering;
	int total = 0;

	for (Bat * other : *bats)
	{
		float d = this->position.distance(other->position);

		if (other != this && d < perceptionRadius) 
		{
			steering += other->velocity;
			total++;
		}
	}
	if (total > 0) 
	{
		steering /= total;
		steering.rescale(this->maxSpeed);
		steering -= this->velocity;
		steering.limit(this->maxForce);
	}
	return steering;
}

ofVec2f Bat::cohesion(vector<Bat*> * bats)
{
	ofVec2f steering;
	int total = 0;

	for (Bat * other : *bats)
	{
		float d = this->position.distance(other->position);

		if (other != this && d < (perceptionRadius * 2))
		{
			steering += other->position;
			total++;
		}
	}

	if (total > 0) 
	{
		steering /= total;
		steering -= position;
		steering.rescale(maxSpeed);
		steering -= velocity;
		steering.limit(maxForce);
	}
	return steering;
}

ofVec2f Bat::separation(vector<Bat*> * bats)
{
	ofVec2f steering;
	int total = 0;

	for (Bat * other : *bats)
	{
		float d = this->position.distance(other->position);

		if (other != this && d < perceptionRadius) 
		{
			ofVec2f diff = this->position - other->position;
			diff /= (d * d);
			steering += diff;
			total++;
		}
	}

	if (total > 0) 
	{
		steering /= total;
		steering.rescale(maxSpeed);
		steering -= velocity;
		steering.limit(maxForce);
	}

	return steering;
}
