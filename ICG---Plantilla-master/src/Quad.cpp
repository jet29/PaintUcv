#include "Quad.h"

CQuad::CQuad()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = QUAD;
	fill = false;
	canMove = false;
	vertexCount = 2;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CQuad::display()
{
	


	int startx;
	int starty;
	int endx;
	int endy;


	if (mVertices[0][0] < mVertices[1][0]) {
		startx = floor(mVertices[0][0]);
		starty = floor(mVertices[0][1]);
		endx =  floor(mVertices[1][0]);
		endy = floor(mVertices[1][1]);
	}
	else {
		startx = floor(mVertices[1][0]);
		starty = floor(mVertices[1][1]);
		endx = floor(mVertices[0][0]);
		endy = floor(mVertices[0][1]);
	}

	if (starty < endy) {

		if (fill) {

			glColor3fv(mColor);

			glBegin(GL_POINTS);

			for (int y = starty; y < endy; y++) {
				for (int x = startx; x < endx; x++) {
					glVertex2i(x, y);
				}
			}

			glEnd();

			}


		glColor3fv(mColorBorder);

		glBegin(GL_POINTS);


		for (int i = starty; i < endy; i++) {
			glVertex2i(startx, i);

		}

		for (int i = starty; i < endy; i++) {
			glVertex2i(endx, i);
		}

		for (int i = startx; i < endx; i++) {
			glVertex2i(i, starty);
		}

		for (int i = startx; i < endx; i++) {
			glVertex2i(i, endy);
		}

		glEnd();
	
		

	}
	else
	{
		if (fill) {

			glColor3fv(mColor);

			glBegin(GL_POINTS);

			for (int y = endy; y < starty; y++) {
				for (int x = startx; x < endx; x++) {
					glVertex2i(x, y);
				}
			}

			glEnd();
		}

		glColor3fv(mColorBorder);

		glBegin(GL_POINTS); 

		for (int i = endy; i < starty; i++) {
			glVertex2i(startx, i);
		}

		for (int i = endy; i < starty; i++) {
			glVertex2i(endx, i);
		}

		for (int i = startx; i < endx; i++) {
			glVertex2i(i, starty);
		}

		for (int i = startx; i < endx; i++) {
			glVertex2i(i, endy);
		}

		glEnd();
		
		
	}
	

}
