#pragma once
extern int windowWidth;
extern int windowHeight;

int MouseInRect(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int MouseInCircle(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
union CP_Vector AngleToVector(float radian_angle);
double Wrap(int val, double min, double max);
double Approach(double a, double b, double amount);
