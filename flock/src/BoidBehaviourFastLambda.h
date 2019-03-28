#pragma once

#include <ofVec2f.h>
#include <ofAppRunner.h>

#include "IBoidBehaviour.h"
#include "Boid.h"
#include "VectorField.h"

class CBoidTheadTrunk
{
public:

private:
	
	
	std::vector<const CBoid*> m_neighbour_pop;
	std::vector<const CBoid*> m_cohesion_pop;
	std::vector<const CBoid*> m_similarity_pop;
	std::vector<const CBoid*> m_separation_pop;
};

class CBoidBehaviourFastLambda :
	public IBoidBehaviour
{
public:
	CBoidBehaviourFastLambda();
	virtual ~CBoidBehaviourFastLambda();

	// Inherited via IBoidBehaviour
	virtual void prepare_update(CBoid* pboid, std::vector<const CBoid*>& pboids) override;
	virtual void update(CBoid* pboid) override;
	virtual void set_screenSize(float xsize, float ysize) override;

	CVectorField2D& get_vec_field() {
		return m_vecfield;
	}

private:
	ofVec2f	update_gravity(CBoid * pboid);
	ofVec2f	update_cohesion(CBoid* pboid, std::vector<const CBoid*>& boids);
	ofVec2f update_separation(CBoid* pboid, std::vector<const CBoid*>& boids);
	ofVec2f update_similarity(CBoid* pboid, std::vector<const CBoid*>& boids);
	
	
	void build_dist_cache(CBoid * pboid, std::vector<const CBoid*>& pboids);
	void apply_limit(CBoid* pboid);

	float m_gravity_limit = 0.9;
	float m_gravity_factor = 0.7;
	float m_speed_limit = 10;
	ofVec2f m_gravity_center = ofVec2f(0, 0);

	float m_cohesion_limit =1;
	float m_cohesion_factor = 0.25;
	float m_cohesion_distance = 64;

	float m_separation_limit = 2;
	float m_separation_distance = 16;
	float m_separation_factor = 1.5;

	float m_similarity_limit = 1;
	float m_similarity_distance = 48;
	float m_similarity_factor = 1;

	float m_screen_sizex;
	float m_screen_sizey;

	CVectorField2D	m_vecfield;

	class CBehaviourData
	{
	public:
		std::vector<const CBoid*> m_neighbour_pop;
		std::vector<const CBoid*> m_cohesion_pop;
		std::vector<const CBoid*> m_similarity_pop;
		std::vector<const CBoid*> m_separation_pop;
	};

	std::vector<CBehaviourData> m_data;
	
	static std::vector<const CBoid*> m_neighbour_pop;
	static std::vector<const CBoid*> m_cohesion_pop;
	static std::vector<const CBoid*> m_similarity_pop;
	static std::vector<const CBoid*> m_separation_pop;

	
};

