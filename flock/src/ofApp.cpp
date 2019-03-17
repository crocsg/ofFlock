#include "ofApp.h"

#define NB_BOID 800*3
#define BOID_MAX_SPEED 10

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofSetFrameRate(60);
		
	//m_pbehaviour = new CBoidBehaviourStd();
	m_pbehaviour = new CBoidBehaviourFastLambda();
	for (int i = 0; i < NB_BOID; i++)
	{
		// TODO: make something for speed_limit and build_boid
		m_boids.addBoid(m_boids.build_boid(i,
			ofGetWidth() / 2 + ofRandomf() * ofGetWidth() / 4,
			ofGetHeight() / 2 + ofRandomf() * ofGetHeight() / 4, BOID_MAX_SPEED,  m_pbehaviour));
	}

	m_boids.set_screen_size(ofGetWidth(), ofGetHeight());
	m_pbehaviour->set_screenSize(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(ofColor::black);
		
	updateBoid();
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::white);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 10, 10);

	drawBoid();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/*
	if ('c' == key)
	{
		std::for_each(begin(m_boids), end(m_boids), [](CBoid& boid) {
			boid.m_hue = 250;
		});
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	m_boids.set_screen_size(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::updateBoid()
{
	m_boids.update((int) ofGetFrameNum());
	

	//cout << m_boids[0].get_hue() << endl;
}

void ofApp::drawBoid()
{
	auto stddraw = [](CBoid& boid)
	{
		ofColor c;
		c.setHsb(boid.get_hue(), 255, 255, 128);
		ofSetColor(c);
		ofDrawCircle(boid.m_position.x, boid.m_position.y, 2);
		ofDrawLine(boid.m_position, boid.m_position + boid.m_speed.normalized() * 8);
	};

	auto filldraw = [](CBoid& boid)
	{
		ofColor c;
		c.setHsb(boid.get_hue() + 10, 255, 255, 128);
		ofSetColor(c);
		ofDrawCircle(boid.m_position.x, boid.m_position.y, 2);
		ofDrawLine(boid.m_position, boid.m_position + boid.m_speed * 2);
	};

	auto slicedrawcircle = [](std::vector<CBoid>::iterator begin, std::vector<CBoid>::iterator end)
	{
		ofColor c;
		c.setHsb(begin->get_hue(), 200, 200, 200);
		ofSetColor(c);
		ofVec2f center = { 0,0 };
		int i = 0;
		for (auto it = begin; it != end - 1; it++)
		{
			center += it->get_position();
			i++;
		}
		center /= (float)i;// (std::distance(begin, end) + 5);

		ofDrawCircle(center, center.distance(begin->get_position()));
		
	};


	auto slicedrawspline = [](std::vector<CBoid>::iterator begin, std::vector<CBoid>::iterator end)
	{
		ofColor c;
		c.setHsb(begin->get_hue(), 200, 200, 200);
		ofSetColor(c);
		ofVec2f center = { 0,0 };

		for (auto it = begin; it != end - 1; it++)
		{
			
		}
		

		

	};


	ofNoFill();
	ofSetCircleResolution(90);
	m_boids.draw(filldraw);
	//m_boids.draw_slice(3, slicedrawcircle);
}


