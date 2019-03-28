#pragma once
#include <vector>
#include <iterator>

#include "ofMain.h"

#include "Boid.h"
#include "BoidBehaviourStd.h"
#include "BoidBehaviourFastLambda.h"
#include "BoidController.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		

protected:
		
		bool				m_draw_vfield;
		
		IBoidBehaviour*		m_pbehaviour;
		CBoidController		m_boids;

		// boids
		void updateBoid();
		void drawBoid();

		
		
		
};
