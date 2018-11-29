#include "Circle.h"
#include "math.h"

CCircle::CCircle()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CIRCLE;
	fill = false;
	canMove = false;
	vertexCount = 2;
}

CCircle::~CCircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCircle::display()
{


	int r = sqrt(pow(mVertices[1][0] - mVertices[0][0], 2) + pow(mVertices[1][1] - mVertices[0][1], 2));
	int x = 0;
	int y = r;
	int d = 1 - r;
	int centerx = mVertices[0][0];
	int centery = mVertices[0][1];

	glColor3fv(mColorBorder);

	glBegin(GL_POINTS);
	glVertex2i(centerx, centery + r);
	glVertex2i(centerx, centery - r);
	glVertex2i(centerx - r, centery);
	glVertex2i(centerx + r, centery);
	glEnd();


	glColor3fv(mColor);

	glBegin(GL_POINTS);
	if (fill) {

		for (int i = centerx - r; i < centerx + r; i++) {
			glVertex2i(i, centery);
		}
	}
	glEnd();

	while (y > x) {

		x++;

		int incE = 2 * x + 3;
		int incSE = 2 * (x - y) + 5;

		if (d < 0) {
			d += incE;
		}
		else {
			d += incSE;
			y--;


			glColor3fv(mColor);

			glBegin(GL_POINTS);
			if (fill) {
				for (int i = -x; i < x; i++) {
					glVertex2i(i + centerx, y + centery);
					glVertex2i(i + centerx, -y + centery);
				}


			}
			glEnd();
		}


		glColor3fv(mColor);

		glBegin(GL_POINTS);

		if (fill) {

			for (int i = -y; i < y; i++) {
				glVertex2i(i + centerx, x + centery);
				glVertex2i(i + centerx, -x + centery);
			}

		}

		glEnd();

		glColor3fv(mColorBorder);

		glBegin(GL_POINTS);
		glVertex2i(x + centerx, y + centery);
		glVertex2i(-x + centerx, y + centery);
		glVertex2i(x + centerx, -y + centery);
		glVertex2i(-x + centerx, -y + centery);
		glVertex2i(y + centerx, x + centery);
		glVertex2i(-y + centerx, x + centery);
		glVertex2i(y + centerx, -x + centery);
		glVertex2i(-y + centerx, -x + centery);

		glEnd();


	}
}

