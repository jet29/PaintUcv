#include "Ellipse.h"
#include "math.h"

CEllipse::CEllipse()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = ELLIPSE;
	fill = false;
	canMove = false;
	vertexCount = 2;
}

CEllipse::~CEllipse()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CEllipse::display()
{
	

	int a;
	int b;
	if (mVertices[0][0] < mVertices[1][0]) {
		a = (mVertices[1][0] - mVertices[0][0]) / 2;
	}
	else {
		a = (mVertices[0][0] - mVertices[1][0]) / 2;
	}

	if (mVertices[0][1] < mVertices[1][1]) {

		b = (mVertices[1][1] - mVertices[0][1]) / 2;
	}
	else {
		b = (mVertices[0][1] - mVertices[1][1]) / 2;
	}

	int centerx = (mVertices[1][0] + mVertices[0][0]) / 2;
	int centery = (mVertices[1][1] + mVertices[0][1]) / 2;
	int d = b * (4 * b - 4 * a*a) + a * a;

	int x = 0;
	int y = b;

	glVertex2i(abs(a) + centerx,centery);
	glVertex2i(-abs(a) + centerx,centery);
	glVertex2i(centerx, abs(b) + centery);
	glVertex2i(centerx, -abs(b) + centery);

	//pinto el centro
	glColor3fv(mColor);

	glBegin(GL_POINTS);

	if (fill) {

		for (int i = centerx - a; i < centerx + a; i++) {
			glVertex2i(i, centery);
		}
	}

	glEnd();

	//modalidad1
	while (b*b * 2 * (x + 1) < a*a*(2 * y - 1)) {

		if (d < 0) {
			d += 4 * (b*b*(2*x+3));
		}
		else {
			d += 4 * (b*b*(2 * x + 3) + a * a*(-2 * y + 2));
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
		x++;

		glColor3fv(mColorBorder);

		glBegin(GL_POINTS);


		glVertex2i(x + centerx, y + centery);
		glVertex2i(-x + centerx, y + centery);
		glVertex2i(x + centerx, -y + centery);
		glVertex2i(-x + centerx, -y + centery);

		glEnd();
	}

	//modalidad2
	d = b * b*(4 * x*x + 4 * x + 1) + a * a*(4 * y*y - 8 * y + 4) - 4 * a*a*b*b;

	while (y > 0) {
		if (d < 0) {
			d = d + 4 * (b*b*(2 * x + 2) + a * a *(-2 * y + 3));
			x++;

			
		}
		else {
			d = d + 4 * a*a*(-2 * y + 3);
		}

		glColor3fv(mColor);

		glBegin(GL_POINTS);
		if (fill) {
			for (int i = -x; i < x; i++) {
				glVertex2i(i + centerx, y + centery);
				glVertex2i(i + centerx, -y + centery);
			}
		}
		glEnd();

		glColor3fv(mColorBorder);

		glBegin(GL_POINTS);

		y--;
		glVertex2i(x + centerx, y + centery);
		glVertex2i(-x + centerx, y + centery);
		glVertex2i(x + centerx, -y + centery);
		glVertex2i(-x + centerx, -y + centery);

		glEnd();
	}

	glEnd();
}