

#include "Boid.h"
#include "IBoidBehaviour.h"

#define TAIL_SIZE 8

CBoid::CBoid()
{
}


CBoid::~CBoid()
{
}

void CBoid::prepare_update(std::vector<const CBoid*>& pboids, int nimg)
{
	if (m_pbehaviour != NULL)
		m_pbehaviour->prepare_update(this, pboids);
}

void CBoid::update()
{
	update_tail(m_position);

	m_position += m_speed;
	m_speed += m_accel;

	m_accel.set(0, 0);

	if (m_pbehaviour != NULL)
		m_pbehaviour->update(this);
}

void CBoid::update_tail(ofVec2f& p)
{
	m_tail.push_front(p);
	while (m_tail.size() > TAIL_SIZE)
		m_tail.pop_back();
}