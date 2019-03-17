#include "BoidBehaviourStd.h"


CBoidBehaviourStd::CBoidBehaviourStd()
{
}


CBoidBehaviourStd::~CBoidBehaviourStd()
{
}

void CBoidBehaviourStd::prepare_update(CBoid * pboid, std::vector<const CBoid*>& pboids)
{
	
	ofVec2f grav = update_gravity(pboid);
	ofVec2f cohesion = update_cohesion(pboid, pboids);
	ofVec2f separation = update_separation(pboid, pboids);
	ofVec2f similarity = update_similarity(pboid, pboids);

	pboid->m_accel = grav * m_gravity_factor + cohesion * m_cohesion_factor + separation * m_separation_factor + similarity * m_similarity_factor;

	apply_limit(pboid);
}

void CBoidBehaviourStd::update(CBoid* pboid)
{
	pboid->update();
	pboid->m_position.x = ofWrap(pboid->m_position.x, 0, m_screen_sizex);
	pboid->m_position.y = ofWrap(pboid->m_position.y, 0, m_screen_sizey);
}

ofVec2f CBoidBehaviourStd::update_gravity(CBoid * pboid)
{
	
	ofVec2f g = m_gravity_center - pboid->m_position;
	g.normalize();
	g *= m_gravity_limit;
	return (g);
}

ofVec2f CBoidBehaviourStd::update_cohesion(CBoid * pboid, std::vector<const CBoid*>& pboids)
{
	ofVec2f cohesion(0, 0);
	int cnt = 0;
	for (auto it = pboids.begin(); it != pboids.end(); ++it)
	{
		if (pboid->m_group != (*it)->m_group)
			continue;
		if (pboid == (*it))
			continue;
		float dist = pboid->m_position.squareDistance((*it)->m_position);

		if (dist <= m_cohesion_distance * m_cohesion_distance && dist > m_similarity_distance * m_similarity_distance)
		{
			cohesion += (*it)->m_position - pboid->m_position;
		}
	}
	cohesion.normalize();
	cohesion *= m_cohesion_limit;
	return (cohesion);
}

ofVec2f CBoidBehaviourStd::update_separation(CBoid * pboid, std::vector<const CBoid*>& boids)
{
	ofVec2f separation(0, 0);
	int cnt = 0;
	for (auto it = boids.begin(); it != boids.end(); it++)
	{
		if (pboid == (*it))
			continue;
		float dist = pboid->m_position.squareDistance((*it)->m_position);

		if (dist <= m_separation_distance * m_separation_distance)
		{
			separation += pboid->m_position - (*it)->m_position;
			cnt++;
		}
	}
	separation += ofVec2f(ofRandomf() * m_separation_factor / 5.,
				ofRandomf() * m_separation_factor / 5.);
	separation.normalize();
	separation *= m_separation_limit;
	return (separation);
}

ofVec2f CBoidBehaviourStd::update_similarity(CBoid * pboid, std::vector<const CBoid*>& boids)
{
	ofVec2f similarity(0, 0);
	float hue = 0;
	int cnt = 0;
	int cnt_hue = 0;
	for (auto it = boids.begin(); it != boids.end(); it++)
	{
		
		if (pboid == (*it))
			continue;
		float dist = pboid->m_position.squareDistance((*it)->m_position);

		if (dist <= m_similarity_distance * m_similarity_distance && dist > m_separation_distance * m_separation_distance)
		{
			if (pboid->m_group == (*it)->m_group)
			{
				similarity += (*it)->m_speed;
				cnt++;
			}

			if (pboid->m_group != (*it)->m_group)
			{
				hue += (*it)->m_hue;
				cnt_hue++;
			}
		}
	}
	if (cnt > 0)
	{
		similarity /= (float)cnt;
		
		similarity -= pboid->m_speed;
		similarity.normalize();
		similarity *= m_separation_limit;
			
	}
	if (cnt_hue > 0)
	{
		hue /= (float)cnt_hue;
		hue = (5. * pboid->m_hue + hue) / 6;
		pboid->m_hue = hue;
	}
	else
	{
		pboid->m_hue = (25. * pboid->m_hue + pboid->m_target_hue) / 26.;
	}

	//return (ofVec2f(0, 0));
	return (similarity);
}

void CBoidBehaviourStd::update_hue(CBoid * pboid, std::vector<const CBoid*>& boids)
{
}

void CBoidBehaviourStd::apply_limit(CBoid * pboid)
{
	pboid->m_accel.limit(m_speed_limit/5);
	pboid->m_speed.limit(m_speed_limit);
}

void CBoidBehaviourStd::set_screenSize(float xsize, float ysize)
{
	m_gravity_center = ofVec2f(xsize / 2, ysize / 2);
	m_screen_sizex = xsize;
	m_screen_sizey = ysize;
}

