#pragma once

#include <functional>
#include "BoidBehaviourFastLambda.h"


std::vector<const CBoid*> CBoidBehaviourFastLambda::m_neighbour_pop;
std::vector<const CBoid*> CBoidBehaviourFastLambda::m_cohesion_pop;
std::vector<const CBoid*> CBoidBehaviourFastLambda::m_similarity_pop;
std::vector<const CBoid*> CBoidBehaviourFastLambda::m_separation_pop;

CBoidBehaviourFastLambda::CBoidBehaviourFastLambda()
{
	m_vecfield.open(1920 * 2, 1080 * 2);
	m_vecfield.setup([](float x, float y)->ofVec2f 
	{
		ofVec2f g = ofVec2f(1920/4 - x, 1080/2 - y);
		ofVec2f g2 = ofVec2f((1920 - 1920 / 4)  - x, (1080 - 1080 / 2)  - y);

		//g += g2 * 0.8;
		g.normalize();
		//g.y += 2 * sin(x*PI / 720);
		//g.x = 1;
		g.normalize();
		return (g);
	}, 
		ofVec2f(2, 2), ofVec2f(0, 0));
}


CBoidBehaviourFastLambda::~CBoidBehaviourFastLambda()
{
}



void CBoidBehaviourFastLambda::build_dist_cache(CBoid* pboid, std::vector<const CBoid*>& pboids)
{
	float dist2 = m_cohesion_distance * m_cohesion_distance;
	
	m_neighbour_pop.resize(pboids.size());
	m_cohesion_pop.resize(pboids.size());
	m_similarity_pop.resize(pboids.size());
	m_separation_pop.resize(pboids.size());

	// filter neighbour
	dist2 = m_cohesion_distance * m_cohesion_distance;
		
	auto it = std::copy_if(begin(pboids), end(pboids), begin(m_cohesion_pop), [dist2, pboid](const CBoid* pb) {
		return pboid->m_position.squareDistance(pb->m_position) < dist2 ? true : false;
	});
	m_cohesion_pop.resize(std::distance(begin(m_cohesion_pop), it));

	// filter similarity distance
	dist2 = m_similarity_distance * m_similarity_distance;
	it = std::copy_if(begin(m_cohesion_pop), end(m_cohesion_pop), begin(m_similarity_pop), [dist2, pboid](const CBoid* pb) {
		return pboid->m_position.squareDistance(pb->m_position) < dist2 ? true : false;
	});
	m_similarity_pop.resize(std::distance(begin(m_similarity_pop), it));
	
	// filter separation distance
	dist2 = m_separation_distance * m_separation_distance;
	it = std::copy_if(begin(m_similarity_pop), end(m_similarity_pop), begin(m_separation_pop), [dist2, pboid](const CBoid* pb) {
		return pboid->m_position.squareDistance(pb->m_position) < dist2 ? true : false;
	});
	m_separation_pop.resize(std::distance(begin(m_separation_pop), it));

#if 0
	// filter cohesion distance
	dist2 = m_similarity_distance * m_similarity_distance;
	std::remove_if(begin(m_cohesion_pop), end(m_cohesion_pop), [dist2, pboid](CBoid* pb)->bool {
		return pboid->m_position.squareDistance(pb->m_position) >= dist2 ? true : false;
	});

	// filter similarity distance
	dist2 = m_separation_distance * m_separation_distance;
	std::remove_if(begin(m_similarity_pop), end(m_similarity_pop), [dist2, pboid](CBoid* pb)->bool {
		return pboid->m_position.squareDistance(pb->m_position) >= dist2 ? true : false;
	});

	// filter separation distance
	std::remove_if(begin(m_similarity_pop), end(m_similarity_pop), [dist2, pboid](CBoid* pb)->bool {
		return pboid->m_position.squareDistance(pb->m_position) == 0 ? true : false;
	});
#endif
}


void CBoidBehaviourFastLambda::prepare_update(CBoid * pboid, std::vector<const CBoid*>& pboids)
{
	build_dist_cache(pboid, pboids);


	//cout << m_cohesion_pop.size() << " " << m_similarity_pop.size() << endl;
	ofVec2f grav = update_gravity(pboid);
	ofVec2f cohesion = update_cohesion(pboid, m_cohesion_pop);
	ofVec2f similarity = update_similarity(pboid, m_similarity_pop);
	ofVec2f separation = update_separation(pboid, m_separation_pop);
	

	pboid->m_accel = grav * m_gravity_factor + 
		cohesion * m_cohesion_factor + 
		separation * m_separation_factor + 
		similarity * m_similarity_factor;

	apply_limit(pboid);
}

void CBoidBehaviourFastLambda::update(CBoid* pboid)
{
	
	pboid->m_position.x = ofWrap(pboid->m_position.x, 0, m_screen_sizex);
	pboid->m_position.y = ofWrap(pboid->m_position.y, 0, m_screen_sizey);

	
}

ofVec2f CBoidBehaviourFastLambda::update_gravity(CBoid * pboid)
{
#if 1
	ofVec2f g = m_vecfield.getFieldVec(pboid->m_position);
#else
	ofVec2f g = m_gravity_center - pboid->m_position;
	g.normalize();
#endif
	g *= m_gravity_limit;
	return (g);
}

ofVec2f CBoidBehaviourFastLambda::update_cohesion(CBoid * pboid, std::vector<const CBoid*>& boids)
{
	ofVec2f cohesion(0, 0);
	int cnt = 0;
	for (auto it = boids.begin(); it != boids.end(); ++it)
	{
		if (pboid->m_group != (*it)->m_group)
			continue;
		if (pboid == (*it))
			continue;
		
		cohesion += (*it)->m_position - pboid->m_position;
		cnt++;
	}
	if (cnt > 0)
		cohesion /= (float) cnt;
	//cohesion.normalize();
	//cohesion *= m_cohesion_limit;
	cohesion.limit(m_cohesion_limit);
	return (cohesion);
}

ofVec2f CBoidBehaviourFastLambda::update_separation(CBoid * pboid, std::vector<const CBoid*>& boids)
{
	ofVec2f separation(0, 0);
	int cnt = 0;
	for (auto it = boids.begin(); it != boids.end(); it++)
	{
		if (pboid == (*it))
			continue;
		
		separation += pboid->m_position - (*it)->m_position;
		separation += ofVec2f(ofRandomf() * m_separation_factor / 5.,
			ofRandomf() * m_separation_factor / 5.);
		cnt++;
	}
	//separation.normalize();
	//separation *= m_separation_limit;
	separation.limit(m_separation_limit);
	return (separation);
}

ofVec2f CBoidBehaviourFastLambda::update_similarity(CBoid * pboid, std::vector<const CBoid*>& boids)
{
	ofVec2f similarity(0, 0);
	float hue = 0;
	int cnt = 0;
	int cnt_hue = 0;
	for (auto it = boids.begin(); it != boids.end(); it++)
	{

		if (pboid == (*it))
			continue;
				
		if (pboid->m_group == (*it)->m_group)
		{
			similarity += (*it)->m_speed;
			cnt++;
		}

		if (pboid->m_group != (*it)->m_group)
		{
			hue += (*it)->m_target_hue;
			cnt_hue++;
		}
		
	}
	if (cnt > 0)
	{
		similarity /= (float)cnt;

		similarity -= pboid->m_speed;
		//similarity.normalize();
		//similarity *= m_separation_limit;
		similarity.limit(m_separation_limit);

	}
	if (cnt_hue > 0)
	{
		
		hue /= (float)cnt_hue;
		//hue = 25;
		hue = (9. * pboid->m_hue + hue) / 10;
		pboid->m_hue = hue;
		
	}
	else
	{
		pboid->m_hue = (9. * pboid->m_hue + pboid->m_target_hue) / 10.;
	}

	//return (ofVec2f(0, 0));
	return (similarity);
}


void CBoidBehaviourFastLambda::apply_limit(CBoid * pboid)
{
	pboid->m_accel.limit(m_speed_limit / 5);
	pboid->m_speed.limit(m_speed_limit);
}

void CBoidBehaviourFastLambda::set_screenSize(float xsize, float ysize)
{
	m_gravity_center = ofVec2f(xsize / 2, ysize / 2);
	m_screen_sizex = xsize;
	m_screen_sizey = ysize;
}


