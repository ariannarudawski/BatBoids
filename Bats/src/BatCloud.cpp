#include "BatCloud.h"

BatCloud::BatCloud(int initialNumBats)
{
	// params

	mainGroup.setName("BATS");

	mainGroup.add(alignment.set("alignment", 0.5f, 0.0f, 1.0f));
	mainGroup.add(cohesion.set("cohesion", 0.225f, 0.0f, 1.0f));
	mainGroup.add(separation.set("separation", 0.5f, 0.0f, 1.0f));

	mainGroup.add(batColor.set("bat color", ofColor(255)));
	mainGroup.add(backgroundColor.set("background color", ofColor(10, 0, 26)));

	gui.setup(mainGroup);

	// load bat pngs

	for (int i = 1; i <= 8; ++i)
	{
		ofImage bat;
		bat.load("bats/bat_" + ofToString(i) + ".png");
		bat.resize(batRadius, batRadius);
		batImages.push_back(bat);
	}

	// create bats

	for (int i = 0; i < initialNumBats; ++i)
	{
		bats.push_back(new Bat(&batImages, batRadius));
	}
}


void BatCloud::update()
{
	for (Bat* bat : bats)
	{
		bat->update(&bats, alignment, cohesion, separation);
	}
}

void BatCloud::draw()
{
	ofBackground(backgroundColor.get());

	ofSetColor(batColor.get());
	for (Bat* bat : bats)
	{
		bat->draw(debug);
	}

	if (debug)
	{
		gui.draw();
	}
}

void BatCloud::keyPressed(int key)
{
	switch (key)
	{
	case 'd':
	case 'D':
		debug = !debug;
		break;
	}
}
