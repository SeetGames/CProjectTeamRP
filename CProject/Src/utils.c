//---------------------------------------------------------
// file:	utils.c
// author:	Seetoh Wei Tung
// email:	seetoh.w@digipen.edu
//
// brief:	Contains the utility functions for other source
//			files.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include <math.h>

int windowWidth = 1920;
int windowHeight = 1080;

int CircleInRect(float circle_x, float circle_y, float circle_diameter, float rect_x, float rect_y, float rect_width, float rect_height)
{

}

// will check if a point is within a rectangular area.
int MouseInRect(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float half_width = area_width / 2;
	float half_height = area_height / 2;
	//If x is within x1 & x2 and y is within y1 & y2, return true.
	if (fabs(click_x - area_center_x) < half_width && fabs(click_y - area_center_y) < half_height)
		return 1;
	return 0;
}

//Will check if a point is within a circle.
int MouseInCircle(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float radius = diameter / 2.0;
	if (CP_Math_Distance(circle_center_x, circle_center_y, click_x, click_y) < radius)
		return 1;
	return 0;
}

//Converts an angle with respect to x-axis to a 2D vector that is rotated
//counter-clockwise from x-axis.
//@param radian_angle represents the angle with respect to the x-axis in radian
CP_Vector AngleToVector(float radian_angle)
{
	double _x = cos(radian_angle);
	double _y = sin(radian_angle);
	CP_Vector ret = CP_Vector_Set(_x, _y);
    return ret;
}

/*Wraps value to min when it exceeds max.
Likewise, wraps to max when value exceeds min.
Examples:
angle += 5; //Constantly rotating 5 degrees
angle = Wrap(angle, 0, 360);
angle will reset back to 0 once it exceeds 360*/
double Wrap(int value, double min, double max)
{
	// Returns the value wrapped, values over or under will be wrapped around
	if (value % 1 == 0)
	{
		while (value > max || value < min)
		{
			if (value > max)
				value += min - max - 1;
			else if (value < min)
				value += max - min + 1;
		}
		return(value);
	}
	else
	{
		double vOld = value + 1;
		while (value != vOld)
		{
			vOld = value;
			if (value < min)
				value = max - (min - value);
			else if (value > max)
				value = min + (value - max);
		}
		return(value);
	}
}

/*Moves "a" towards "b" by "amount and returns the result.
Nice because it will not overshoot "b" and works in both directions
Examples:
  alpha = Approach(alpha, 1, 0.1);*/
double Approach(double a, double b, double amount)
{
	if (a < b)
	{
		a += amount;
		if (a > b)
			return b;
	}
	else
	{
		a -= amount;
		if (a < b)
			return b;
	}
	return a;
}
