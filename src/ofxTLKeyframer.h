/*
 *  THISKeyframeEditor.h
 *  THIS_Editor
 *
 *  Created by Jim on 6/26/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofRange.h"
#include "ofxTween.h"
#include "ofxTLElement.h"

typedef struct
{
	int id;
	ofRectangle bounds;
	string name;
	ofxEasing* easing;
} EasingFunction;

typedef struct
{
	int id;
	ofRectangle bounds;
	string name;
	ofxTween::ofxEasingType type;
} EasingType;

typedef struct
{
	EasingFunction* easeFunc;
	EasingType* easeType;
	ofVec2f position; // x is value, y is time, all 0 - 1.0
} ofxTLKeyframe;

class ofxTLKeyframer : public ofxTLElement
{
  public:	
	ofxTLKeyframer();
	~ofxTLKeyframer();

	virtual void setup();
	virtual void draw();

	//main function to get values out of the timeline
	virtual float sampleTimelineAt(float percent);
	
	virtual void mousePressed(ofMouseEventArgs& args);
	virtual void mouseMoved(ofMouseEventArgs& args);
	virtual void mouseDragged(ofMouseEventArgs& args);
	virtual void mouseReleased(ofMouseEventArgs& args);
		
	virtual void keyPressed(ofKeyEventArgs& args);

	virtual void save();
	virtual void load();
	
	virtual void reset();
	virtual void clear();
	
  private:
	ofxTLKeyframe* firstkey;
	ofxTLKeyframe* lastkey;
	ofVec2f grabOffset;
	vector<ofxTLKeyframe*> keyframes;

	
	bool keyframeIsInBounds(ofxTLKeyframe* key);
	
	ofxTLKeyframe* selectedKeyframe;
	int selectedKeyframeIndex;
	ofVec2f keyframeGrabOffset;
	float minBound; //TODO: replace with range
	float maxBound;
	
	void updateKeyframeSort();
	ofxTLKeyframe* keyframeAtScreenpoint(ofVec2f p, int& selectedIndex);
	bool screenpointIsInBounds(ofVec2f screenpoint);
	ofVec2f coordForKeyframePoint(ofVec2f keyframePoint);
	ofVec2f keyframePointForCoord(ofVec2f coord);
		
	//easing dialog stuff
	ofVec2f easingWindowPosition;
	bool drawingEasingWindow;
	vector<EasingFunction*> easingFunctions;
	vector<EasingType*> easingTypes;
	float easingBoxWidth;
	float easingBoxHeight;
	float easingWindowSeperatorHeight;
	
	void initializeEasings();
	ofxTLKeyframe* newKeyframe(ofVec2f point);
};