#include "Triangle.h"
#include "Utils.h"
#include <cmath>
#include <math.h>
#include <iostream>
using namespace std;

CTriangle::CTriangle()
{
	mVertices = new float*[3];
	for (int i = 0; i < 3; ++i)
		mVertices[i] = new float[2];

	mType = TRIANGLE;
	fill = false;
	canMove = false;
	vertexCount = 3;
}

CTriangle::CTriangle(const CFigure* figure){
	*this = figure;
}

CTriangle::~CTriangle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CTriangle::display()
{

	glColor3fv(mColorBorder);

	glBegin(GL_POINTS);

	DrawLine(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1]);
	
	DrawLine(mVertices[0][0], mVertices[0][1], mVertices[2][0], mVertices[2][1]);
	DrawLine(mVertices[2][0], mVertices[2][1], mVertices[1][0], mVertices[1][1]);

	glEnd();

	glColor3fv(mColor);

	glBegin(GL_POINTS);

	if (fill) {

		//finding the lowest, mid upper point
		int indexL = 0;
		int indexU = 0;
		int indexM = 0;
		int lowest = mVertices[0][1];
		int greatest = mVertices[0][1];

		for (int i = 0; i < vertexCount; i++)
		{
			if (mVertices[i][1] > greatest) {
				indexU = i;
				greatest = mVertices[i][1];
			}

			if (mVertices[i][1] < lowest) {
				indexL = i;
				lowest = mVertices[i][1];
			}
		}

		for (int i = 0; i < vertexCount; i++) {
			if (i != indexU && i != indexL) {
				indexM = i;
				break;
			}
		}

		float m1 = (mVertices[indexU][1] - mVertices[indexL][1]) / (mVertices[indexU][0] - mVertices[indexL][0]); //right
		float m2 = (mVertices[indexU][1] - mVertices[indexM][1]) / (mVertices[indexU][0] - mVertices[indexM][0]); //left
		float m3 = (mVertices[indexM][1] - mVertices[indexL][1]) / (mVertices[indexM][0] - mVertices[indexL][0]); //botton

		if (mVertices[indexM][0] > mVertices[indexL][0]) {
			int y = -1;

			for (y = ceil(mVertices[indexL][1]); y < floor(mVertices[indexM][1]); y++) {
				int xstart = ceil((y / m1) - (mVertices[indexL][1] / m1) + mVertices[indexL][0]);
				int xend = floor((y / m3) - (mVertices[indexL][1] / m3) + mVertices[indexL][0]);
				for (int x = xstart; x < xend; x++) {
					glVertex2i(x, y);
				}
			}

			for(y; y < floor(mVertices[indexU][1]); y++)
			{
				int xstart = ceil((y / m1) - (mVertices[indexL][1] / m1) + mVertices[indexL][0]);
				int xend = floor((y / m2) - (mVertices[indexM][1] / m2) + mVertices[indexM][0]);
				for (int x = xstart; x < xend; x++) {
					glVertex2i(x, y);
				}
			}

		}
		else {

			int y = -1;

			for (y = ceil(mVertices[indexL][1]); y < floor(mVertices[indexM][1]); y++) {
				int xend = ceil((y / m1) - (mVertices[indexL][1] / m1) + mVertices[indexL][0]);
				int xstart = floor((y / m3) - (mVertices[indexL][1] / m3) + mVertices[indexL][0]);
				for (int x = xstart; x < xend; x++) {
					glVertex2i(x, y);
				}
			}

			for (y; y < floor(mVertices[indexU][1]); y++)
			{
				int xend = ceil((y / m1) - (mVertices[indexL][1] / m1) + mVertices[indexL][0]);
				int xstart = floor((y / m2) - (mVertices[indexM][1] / m2) + mVertices[indexM][0]);
				for (int x = xstart; x < xend; x++) {
					glVertex2i(x, y);
				}
			}



		}


	}
    
	glEnd();
}

