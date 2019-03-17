#pragma once



#ifndef _IBOIDBEAVIOUR_H
#define _IBOIDBEAVIOUR_H

#include <vector>

class CBoid;

class IBoidBehaviour
{
public:

	IBoidBehaviour()
	{
	}

	virtual ~IBoidBehaviour()
	{
	}

	virtual void prepare_update(CBoid* pboid, std::vector<const CBoid*>& pboids) = 0;
	virtual void update(CBoid* pboid) = 0;
	virtual void set_screenSize(float xsize, float ysize) = 0;

	static const std::string    PARAM_COHESION_RANGE;// = "cohesion_range";
	static const std::string    PARAM_COHESION_FACTOR;// = "cohesion_factor";
	
	static const std::string    PARAM_GRAVITY_FACTOR;// = "cohesion_factor";
	static const std::string    PARAM_GRAVITY_RANGE;// = "cohesion_factor";

	static const std::string    PARAM_SEPARATION_FACTOR;// = "cohesion_factor";
	static const std::string    PARAM_SEPARATION_RANGE;// = "cohesion_factor";

	static const std::string    PARAM_SIMILARITY_FACTOR;// = "cohesion_factor";
	static const std::string    PARAM_SIMILARITY_RANGE;// = "cohesion_factor";

		
};



#endif // _IBOIDBEAVIOUR_H
