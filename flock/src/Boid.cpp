

#include "Boid.h"
#include "IBoidBehaviour.h"


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
	
	m_position += m_speed;
	m_speed += m_accel;

	m_accel.set(0, 0);

	if (m_pbehaviour != NULL)
		m_pbehaviour->update(this);
}