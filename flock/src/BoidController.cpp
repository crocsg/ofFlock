#include "BoidController.h"


void CBoidController::addBoid(CBoid&& boid)
{
	m_boids.push_back(boid);
	
	// update reference pointer vector
	// 
	m_pboids.clear();
	for_each(begin(m_boids), end(m_boids), [this](CBoid& b) {this->m_pboids.push_back(&b); });
}

void CBoidController::update(int nparam)
{
	std::for_each(begin(m_boids), end(m_boids), [this](CBoid&b) {
		b.prepare_update(this->m_pboids, 0);
		b.update();
	});
}
