#pragma once

#include <vector>
#include "Boid.h"
#include "IBoidBehaviour.h"

class CBoidController
{
public:

	CBoidController () {}
	~CBoidController() {}

	void addBoid(CBoid&& boid);
	void update(int nparam);

	template<typename fdraw> void draw(fdraw f)
	{
		std::for_each(begin(m_boids), end(m_boids), f);
	}
	
	template<typename fdraw> void draw_slice(int nslice, fdraw f)
	{
		
		for (auto it = begin(m_boids); it != end(m_boids) - nslice; it += nslice)
		{
			f(it, it + nslice);
		}
	}

	CBoid build_boid(int n, float x, float y, float speed_limit, IBoidBehaviour* pbehaviour)
	{
		CBoid boid;
		boid.m_position.x = x;
		boid.m_position.y = y;
		boid.m_speed.x = ofRandomf() * speed_limit;
		boid.m_speed.y = ofRandomf() * speed_limit;
		boid.m_pbehaviour = pbehaviour;
		boid.m_group = 0;// n % 4;
		boid.m_hue = boid.m_target_hue = 0 + ((n%3)  * 12);

		return boid;
	}

	void set_screen_size(size_t dx, size_t dy)
	{
		m_screen_sizex = dx;
		m_screen_sizey = dy;
	}

private:

	// data
	std::vector<CBoid>			m_boids;
	std::vector<const CBoid*>	m_pboids;

	size_t						m_screen_sizex;
	size_t						m_screen_sizey;
};