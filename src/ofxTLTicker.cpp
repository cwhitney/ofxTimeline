/*
 *  ofxTLTicker.cpp
 *  timelineExample
 *
 *  Created by Jim on 7/19/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#include "ofxTLTicker.h"

ofxTLTicker::ofxTLTicker() 
:	isFrameBased(false),	
	durationInFrames(0),
	durationInSeconds(0),
	framerate(25),
	curHoverFrame(-1)
{
	//default constructor
	hovering = false;
}

ofxTLTicker::~ofxTLTicker(){
}

void ofxTLTicker::setup(){
	enable();
}

void ofxTLTicker::draw(){
	
	ofPushStyle();
	
	if(isFrameBased){
		
		curStartFrame = ofMap(zoomBounds.min, 0, 1.0, 0, durationInFrames);
		curEndFrame = ofMap(zoomBounds.max, 0, 1.0, 0, durationInFrames);
		curHoverFrame = ofMap(ofGetMouseX(), totalDrawRect.x, totalDrawRect.x+totalDrawRect.width, curStartFrame, curEndFrame, true);
		framesInView = curEndFrame-curStartFrame;
	
		float framesPerPixel = framesInView / totalDrawRect.width;
		int frameStepSize = 1;
		
		/*
		if(framesPerPixel > 10){
			frameStepSize = 10;
		}
		else if(framesPerPixel > 1){
		}
		else {
			frameStepSize = 1;			
		}
		*/
		
		for(int i = curStartFrame; i <= curEndFrame; i++){
			float x = ofMap(i, curStartFrame, curEndFrame, totalDrawRect.x, totalDrawRect.x+totalDrawRect.width, true);
			ofSetColor(200, 180, 40);
			float heightMultiplier = 0.0;
			if(i % 10 == 0){
				ofSetLineWidth(3);
				heightMultiplier = .5;
			}
			else {
				heightMultiplier = .75;
				ofSetLineWidth(1);
			}
			
			ofLine(x, bounds.y+bounds.height*heightMultiplier, x, bounds.height);
		}
			
		/*
		//draw tickers with frame numbers
		float d = bounds.width/(float)durationInFrames; //using a float results in uneven spread of keyframes
		 ofSetColor(200, 180, 40);
		int counter = 0;
		for (float i = bounds.x; i < bounds.width; i+=d){
			ofLine(i, bounds.y, i, bounds.y+bounds.height);
			if(counter%10 == 0){
				ofSetLineWidth(3);
				ofLine(i, bounds.y+bounds.height*.85, i, bounds.height);
				ofSetLineWidth(1);
			}
			counter++;
		}
		 */
		
		//highlite current mouse position
		if(hovering){
			ofEnableAlphaBlending();
			//draw background rect
			ofSetColor(0);
			
			string text = ofToString(curHoverFrame);
			int textH = 10;
			int textW = (text.size()+1)*7;
			ofRect(ofGetMouseX(), bounds.y+bounds.height-textH, textW, textH);
			ofSetColor(200, 180, 40);
			ofDrawBitmapString(text, ofGetMouseX()+5, bounds.y+bounds.height);
			
			//draw playhead line
			ofSetColor(255, 0, 0, 150);
			ofSetLineWidth(1);
			ofLine(ofGetMouseX(), 0, ofGetMouseX(), totalDrawRect.height);
		}
	}
	else {
		//draw tickers with time
	}

	ofNoFill();
	ofSetColor(200, 180, 40);
	ofRect(bounds);
	
	ofPopStyle();
	
}

void ofxTLTicker::setDuration(int frames){
	isFrameBased = true;
	durationInFrames = frames;
	durationInSeconds = 1.0*frames/framerate;
}

void ofxTLTicker::setDuration(float seconds){
	isFrameBased = false;
	durationInSeconds = seconds;
	durationInFrames = seconds*framerate;
}

void ofxTLTicker::setFrameRate(int _framerate){
	framerate = _framerate;
	
	//TODO: maintain duration
	if(isFrameBased){
		
	}
	else{
	}
}
	
void ofxTLTicker::mouseDragged(ofMouseEventArgs& args){
	updateHover(args);
	//TODO update time, trigger an event?
}

void ofxTLTicker::mouseMoved(ofMouseEventArgs& args){
	updateHover(args);
}

void ofxTLTicker::mousePressed(ofMouseEventArgs& args){

}

void ofxTLTicker::mouseReleased(ofMouseEventArgs& args){
}

void ofxTLTicker::setTotalDrawRect(ofRectangle drawRect){
	totalDrawRect = drawRect;
}


void ofxTLTicker::updateHover(ofMouseEventArgs& args){
	ofVec2f mousePos(args.x - totalDrawRect.x, args.y - totalDrawRect.y); //necessary or are mouse positions already mapped to the right region?
	hovering = mousePos.x > 0 && mousePos.x < totalDrawRect.width && mousePos.y > 0 && mousePos.y < totalDrawRect.height;
}
