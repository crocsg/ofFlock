#pragma once

#ifndef __BOID_H
#define __BOID_H

#include <deque>
#include <ofVec2f.h>
#include <ofColor.h>


class IBoidBehaviour;

class CBoid
{
public:
	CBoid();
	virtual ~CBoid();

public:
	void prepare_update(std::vector<const CBoid*>& pboids, int n);
	void update();
	void update_tail(ofVec2f& pos);

public:
	const ofVec2f&	get_position()	{ return m_position; }
	const ofVec2f&	get_speed()		{ return m_speed; }
	const ofVec2f&	get_accel()		{ return m_accel; }
	float			get_hue()		{ return m_hue; }
	int				get_group()		{ return m_group; }

	void setBoidBehaviour(IBoidBehaviour* pbeav) { m_pbehaviour = pbeav; }
	IBoidBehaviour* getBoidBehaviour(void) { return m_pbehaviour; }

public:
	ofVec2f m_position;
	ofVec2f m_speed;
	ofVec2f m_accel;
	int		m_group;

	float	m_hue;
	float	m_target_hue;
	
	std::deque<ofVec2f> m_tail;

	IBoidBehaviour* m_pbehaviour;
	
	
};

#endif __BOID_H
