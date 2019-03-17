#pragma once


#include <ofVec2f.h>
#include <ofAppRunner.h>

#include "IBoidBehaviour.h"
#include "Boid.h"

class CBoidBehaviourStd :
	public IBoidBehaviour
{
public:
	CBoidBehaviourStd();
	virtual ~CBoidBehaviourStd();


	// Inherited via IBoidBehaviour
	virtual void prepare_update(CBoid * pboid, std::vector<const CBoid*>& pboids) override;
	virtual void update(CBoid* pboid) override;
	virtual void set_screenSize(float xsize, float ysize) override;

private:
	ofVec2f	update_gravity(CBoid * pboid);
	ofVec2f	update_cohesion (CBoid* pboid, std::vector<const CBoid*>& boids);
	ofVec2f update_separation (CBoid* pboid, std::vector<const CBoid*>& boids);
	ofVec2f update_similarity(CBoid* pboid, std::vector<const CBoid*>& boids);
	void	update_hue (CBoid* pboid, std::vector<const CBoid*>& boids);

	void apply_limit(CBoid* pboid);

	float m_gravity_limit = 0.9;
	float m_gravity_factor = 0.21;
	float m_speed_limit = 10;
	ofVec2f m_gravity_center = ofVec2f(0, 0);

	float m_cohesion_limit = 0.9;
	float m_cohesion_factor = 0.19;
	float m_cohesion_distance = 64;
	
	float m_separation_limit = 1;
	float m_separation_distance = 10;
	float m_separation_factor = 2;

	float m_similarity_limit = 1;
	float m_similarity_distance = 32;
	float m_similarity_factor = 1.5;
				
	float m_screen_sizex;
	float m_screen_sizey;
};

