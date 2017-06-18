#pragma once
#include <windows.h>
#include <gl/glut.h>

class MyBox
{
public:
	MyBox(GLfloat x, GLfloat y, GLsizei width, GLsizei height, GLfloat xStep, GLfloat yStep)
		:m_x(x), m_y(y), m_width(width), m_height(height), m_xStep(xStep), m_yStep(yStep)
	{
		m_x = m_x;
		m_y;
		m_width;
		m_height;
		m_xStep;
		m_yStep;
	}
	~MyBox() = default;

	void Draw();

	GLfloat GetX()
	{ 
		return m_x; 
	}
	GLfloat GetY()
	{
		return m_y; 
	}
	void SetXStep(GLfloat value)
	{
		m_xStep = value; 
	}
	void SetYStep(GLfloat value)
	{ 
		m_yStep = value; 
	}
	GLfloat GetXStep()
	{ 
		return m_xStep;
	}
	GLfloat GetYStep()
	{
		return m_yStep; 
	}
	GLsizei GetWidth()
	{
		return m_width; 
	}
	GLsizei GetHeight()
	{
		return m_height;
	}

	void SetPosition(float x, float y);

	bool isCollide(MyBox* other) const;

private:

	bool isXcolided(MyBox* other)const;
	bool isYcolided(MyBox* other)const;

	GLfloat m_x;
	GLfloat m_y;
	GLsizei m_width;
	GLsizei m_height;
	GLfloat m_xStep;
	GLfloat m_yStep;
};

