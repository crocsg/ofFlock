#pragma once

#include <vector>
#include <ofVec2f.h>

class CVectorField2D
{
public:
	
	CVectorField2D::CVectorField2D()
	{

	}
	virtual CVectorField2D::~CVectorField2D()
	{

	}

	const CVectorField2D& operator=(const CVectorField2D& rfield)
	{
		m_col	=	rfield.m_col;
		m_row	=	rfield.m_row;
		m_scalex =	rfield.m_scalex;
		m_scaley =	rfield.m_scaley;
		m_ofx	=	rfield.m_ofx;
		m_ofy	=	rfield.m_ofy;

		m_field = rfield.m_field;
		
		return (*this);
	}
	
	int open(size_t fieldcol, size_t fieldrow)
	{
		if (m_field.size() > 0)
			return (-1);
		
		m_field.resize(fieldrow * fieldcol);

		m_col = fieldcol;
		m_row = fieldrow;

		return m_field.size();
	}

	
	void close()
	{
		m_field.clear();
		m_row = 0;
		m_col = 0;
	}

	void setup(std::function<ofVec2f(float worldx, float worldy)> &&param,
		const ofVec2f& scale, ofVec2f& offset)
	{
		setTranslateWorld2Field(offset);
		setScaleWorld2Field(scale);
		
		for (size_t y = 0; y < m_row; y++)
			for (size_t x = 0; x < m_col; x++)
			{
				float wx, wy;
				wx = (float)x / m_scalex;
				wy = (float)y / m_scaley;

				set(x, y, param(wx, wy));

			}
	}
	
	void set(size_t x, size_t y, ofVec2f v)
	{
		size_t of = vecpos(x, y);
		if (of < m_field.size())
			m_field[of] = v;
	}

	ofVec2f get(size_t x, size_t y) {
		size_t of = vecpos(x, y);
		return (of < m_field.size() ? m_field[of] : ofVec2f(0, 0));
	}

	void setScaleWorld2Field(float scalex, float scaley)
	{
		m_scalex = scalex;
		m_scaley = scaley;
	}

	void setTranslateWorld2Field(float ofx, float ofy)
	{
		m_ofx = ofx;
		m_ofy = ofy;
	}
	void setScaleWorld2Field(ofVec2f scale)
	{
		setScaleWorld2Field(scale.x, scale.y);
	}
	void setTranslateWorld2Field(ofVec2f of)
	{
		setTranslateWorld2Field(of.x, of.y);
	}

	size_t World2FieldX(float x)
	{
		int xf;
		xf = (size_t)((x + m_ofx) * m_scalex);
		
		if (xf < 0)				return 0;
		if (xf > (int) m_row)	return (m_row - 1);
		
		return ((size_t) xf);
	}

	size_t World2FieldY(float y)
	{
		int yf;
		yf = (size_t)((y + m_ofy) * m_scaley);

		if (yf < 0)				return 0;
		if (yf > (int) m_row)	return (m_row - 1);

		return ((size_t)yf);
	}

	void World2Field(const ofVec2f& p, size_t& xf, size_t& yf)
	{
		xf = World2FieldX(p.x);
		yf = World2FieldY(p.y);
	}

	ofVec2f getFieldVec(const ofVec2f& worldpos)
	{
		size_t xf, yf;
		
		World2Field(worldpos, xf, yf);
		
		return get(xf, yf);
	}

	ofVec2f getFieldVec(float worldx, float worldy)
	{
		return (getFieldVec(ofVec2f(worldx, worldy)));
	}

private:
	size_t vecpos(size_t x, size_t y)
	{
		size_t of = y * m_col + x;

		return (of < m_field.size() ? of : m_field.size() - 1);
	}

	size_t	m_col;		// number of columns
	size_t	m_row;		// number of rows
	float	m_scalex;	// scale from world to field
	float	m_scaley;	// scale from world to field
	float	m_ofx;		// offset x before scaling
	float	m_ofy;		// offset y before scaling

	std::vector<ofVec2f> m_field;
};