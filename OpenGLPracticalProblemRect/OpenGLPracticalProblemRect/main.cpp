#include <Windows.h>
#include <gl/glut.h>
#include <vector>
#include <random>
#include "MyBox.h"

GLfloat window_w;
GLfloat window_h;

std::vector<MyBox*> boxes;

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.f, 0.f, 0.f);

	for (auto box : boxes)
	{
		box->Draw();
	}

	glutSwapBuffers();
}

void CheckWindow(GLfloat &rectStartX, GLfloat &rectStartY, GLsizei &rectSizeX,GLsizei &rectSizeY, GLfloat &xstep, GLfloat &ystep)
{
	if (rectStartX > window_w - rectSizeX || rectStartX < -window_w)
	{
		xstep = -xstep;
	}

	if (rectStartY > window_h - rectSizeY || rectStartY < -window_h)
	{
		ystep = -ystep;
	}

	if (rectStartX > window_w - rectSizeX)
	{
		rectStartX = window_w - rectSizeX - 1;
	}

	if (rectStartX < -window_w)
	{
		rectStartX = -window_w + 1;
	}

	if (rectStartY > window_h - rectSizeY)
	{
		rectStartY = window_h - rectSizeY - 1;
	}

	if (rectStartY < -window_h)
	{
		rectStartY = -window_h + 1;
	}
}

void CheckBoxes(MyBox* box)
{
	for (auto otherBox : boxes)
	{
		if (otherBox == box)
		{
			continue;
		}

		if (!box->isCollide(otherBox))
		{
			continue;
		}

		auto otherBoxLeft = otherBox->GetX();
		auto otherBoxRight = otherBoxLeft + otherBox->GetWidth();
		auto otherBoxBottom = otherBox->GetY();
		auto otherBoxTop = otherBoxBottom + otherBox->GetHeight();

		if (box->GetXStep() * otherBox->GetXStep() < 0)
		{
			auto xstep = box->GetXStep();
			box->SetXStep(-xstep);
			xstep = otherBox->GetXStep();
			otherBox->SetXStep(-xstep);
		}

		if (box->GetYStep() * otherBox->GetYStep() < 0)
		{
			auto ystep = box->GetYStep();
			box->SetYStep(-ystep);
			ystep = otherBox->GetYStep();
			otherBox->SetYStep(-ystep);
		}

		if (box->GetX()<otherBoxLeft&&box->GetX() > otherBoxLeft - box->GetWidth())
		{
			box->SetPosition(otherBoxLeft - box->GetWidth(), box->GetY());
		}
		else if (box->GetX() <otherBoxRight&&box->GetX() < otherBoxLeft)
		{
			box->SetPosition(otherBoxRight, box->GetY());
		}

		if (box->GetY()<otherBoxBottom&&box->GetY() > otherBoxBottom - box->GetHeight())
		{
			box->SetPosition(box->GetX(), box->GetY() - box->GetHeight());
		}
		else if (box->GetY() < otherBoxTop&& box->GetY()<otherBoxBottom)
		{
			box->SetPosition(box->GetX(), otherBoxTop);
		}
	}
}


void TimerFunction(int value)
{
	for (auto box : boxes)
	{
		auto boxStartX = box->GetX();
		auto boxStartY = box->GetY();
		auto boxSizeX = box->GetWidth();
		auto boxSizeY = box->GetHeight();
		auto xstep = box->GetXStep();
		auto ystep = box->GetYStep();

		CheckBoxes(box);

		CheckWindow(boxStartX, boxStartY, boxSizeX, boxSizeY, xstep, ystep);

		box->SetXStep(xstep);
		box->SetYStep(ystep);

		boxStartX += box->GetXStep();
		boxStartY += box->GetYStep();

		box->SetPosition(boxStartX, boxStartY);
		
	}
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void SetupRC()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		window_w = 100.f;
		window_h = 100.f*h / w;
		glOrtho(-100.f, 100.f, -window_h, window_h, 1.f, -1.f);
	}
	else
	{
		window_w = 100.f*w / h;
		window_h = 100.f;
		glOrtho(-window_w, window_w, -100.f, 100.f, 1.f, -1.f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void main()
{
	std::random_device rng;

	for (int i = 0; i < 4; ++i)
	{
		auto num =static_cast<float>(rng() % 20);

		float x = -400 + i*200;
		float y = -400 + i*200;
		float xstep = num/10;

		boxes.emplace_back(new MyBox(x, y, num+10, num+10, xstep, xstep));
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("OpenGLPracticalProblemRect");
	glutDisplayFunc(Render);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(2000, TimerFunction, 1);
	SetupRC();

	glutMainLoop();

	for each(auto rect in boxes)
	{
		delete rect;
	}
}