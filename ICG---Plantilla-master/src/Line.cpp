#include "Line.h"
#include <iostream>
#include <math.h>
using namespace std;

CLine::CLine()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = LINE;
	canMove = false;
	vertexCount = 2;
}

CLine::~CLine()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CLine::display()
{
	glColor3fv(mColor);

	glBegin(GL_POINTS);

	int dx;
	int dy;
	float m;
	int x;
	int y;
	int endx;
	int endy;


	

	if (mVertices[1][0] < mVertices[0][0]) {

		x = mVertices[1][0];
		y = mVertices[1][1];
		endx = mVertices[0][0];
		endy = mVertices[0][1];

		dx = mVertices[0][0] - mVertices[1][0];
		dy = mVertices[0][1] - mVertices[1][1];

		//m = (mVertices[0][1] - mVertices[1][1]) / (mVertices[0][0] - mVertices[1][0]);
	}
	else {

		x = mVertices[0][0];
		y = mVertices[0][1];
		endx = mVertices[1][0];
		endy = mVertices[1][1];

		dx = mVertices[1][0] - mVertices[0][0];
		dy = mVertices[1][1] - mVertices[0][1];

		//m = (mVertices[1][1] - mVertices[0][1]) / (mVertices[1][0] - mVertices[0][0]);

	}


	if (y == endy) { //horizontal line

		for (x; x < endx; x++)	glVertex2i(x, y);
	}
	else {

		int d = dx - 2 * dy;
		glVertex2i(x, y);

		//if (m > 0 && m < 1) {
		if(dx > dy && dy > 0){

			int incE = -2 * dy;
			int incNE = 2 * (dx - dy);

			while (x < endx) {

				if (d <= 0) {
					d = d + incNE;
					y++;
				}
				else {
					d = d + incE;
				}
				x++;
				glVertex2i(x, y);

			}
		}
		//else if (m >= 1) {
		else if(dy > dx && dy > 0){

			int incN = 2 * dx;
			int incNE = 2 * (dx - dy);

			while (y < endy) {

				if (d < 0) {
					d = d + incN;
				}
				else {
					d = d + incNE;
					x++;
				}
				y++;
				glVertex2i(x, y);
			}
		}
		//else if (m < 0 && m >= -1) {
		else if(abs(dx) > abs(dy) && dy < 0){
			int incE = -2 * dy;
			int incSE = -2 * (dy + dx);

			while (x < endx) {

				if (d <= 0) {
					d = d + incE;
				}
				else {
					d = d + incSE;
					y--;
				}
				x++;
				glVertex2i(x, y);

			}
		}
		//else if (m < -1) {
		else if(abs(dy) > abs(dx) && dy < 0){
			int incS = -2 * dx;
			int incSE = -2 * (dx + dy);

			while (y > endy) {

				if (d > 0) {
					d = d + incS;
				}
				else {
					d = d + incSE;
					x++;
				}
				y--;
				glVertex2i(x, y);
			}

		}


	}

	

	glEnd();
}