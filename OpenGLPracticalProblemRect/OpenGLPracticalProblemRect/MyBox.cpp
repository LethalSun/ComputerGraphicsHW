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
	if (m_x < other->m_x + other->m_width &&
		m_x > other->m_x - m_width)
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
	if (m_y < other->m_y + other->m_height &&
		m_y > other->m_y - m_height)
	{
		return true;
	}
	else
	{
		return false;
	}
}
