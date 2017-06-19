#include "MyBox.h"
#include <gl\glut.h>
void MyBox::Draw()
{
	glRectf(m_x, m_y, m_x + m_width, m_y + m_height);
}

void MyBox::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	m_midX = m_x + (static_cast<GLfloat>(m_width) / 2);
	m_midY = m_y + (static_cast<GLfloat>(m_height) / 2);
}

bool MyBox::isCollide(MyBox * other) const
{
	if (isYcolided(other)&& isXcolided(other))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MyBox::isXcolided(MyBox * other) const
{
	if ((Abs(m_midX,other->GetMidX()))<m_radX+other->GetRadX())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MyBox::isYcolided(MyBox * other) const
{
	if ((Abs(m_midY, other->GetMidY()))<m_radY + other->GetRadY())
	{
		return true;
	}
	else
	{
		return false;
	}
}
