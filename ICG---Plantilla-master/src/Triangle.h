#pragma once

#include "Figure.h"

class CTriangle : public CFigure
{
public:
	CTriangle();
	CTriangle(const CFigure*);
	~CTriangle();
	void display();
};

