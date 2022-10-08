//---------------------------------------------------------
// file:	carlevel.c
// author:	Seetoh Wei Tung
// email:	seetoh.w@digipen.edu
//
// brief:	Contains the state for the car level
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>

double dt;
int carI; //Iterator to select which car you are
int totalCars = 3;
double carDiameter = 100;
double carRadius;
double highlightAlpha = 255;
double steerSpeed = 300; //300 degrees per second
double triangleYBound;
CP_Vector dirVec;
CP_Color triangleCol;
//Defining structure for the car.
typedef struct Car
{
	double mass;
	double force;
	double moveSpeed;
	double maxSpeed;
	double dir;
	double x;
	double y;
	CP_Color carColour;
} Car;
Car car[3];

//Function to create the car by specifying the values to populate using arguments.
Car create_car(double _x, double _y, double _mass, double _maxSpeed, CP_Color _carColour)
{
	Car ret;
	ret.x = _x;
	ret.y = _y;
	ret.mass = _mass;
	ret.maxSpeed = _maxSpeed;
	ret.carColour = _carColour;
	ret.dir = 0;
	ret.moveSpeed = 0;
	ret.force = 0;
	return ret;
}

void Car_Level_Init()
{
	carI = -1; //Which car is currently selected. -1 because the array is only 0-2
	carRadius = carDiameter / 2.0;
	triangleYBound = carRadius * 0.7;
	triangleCol = CP_Color_Create(255, 255, 255, 100);

	car[0] = create_car(100, 100, 5, 800, CP_Color_Create(255, 0, 0, 255)); //Red
	car[1] = create_car(250,250,8,650, CP_Color_Create(0, 255, 0, 255)); //Green
	car[2] = create_car(250,100,12,400, CP_Color_Create(0, 0, 255, 255)); //Blue
}

void Car_Level_Update()
{
	//Obtain delta time
	dt = CP_System_GetDt();
	//Clear the background and make it gray
	CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
	//Draw all cars
	for (int i = 0; i < totalCars; i++)
	{
		//Draw yellow highlight if this is the selected car
		if (i == carI)
		{
			//Set to yellow
			CP_Settings_Fill(CP_Color_Create(255, 255, 12, highlightAlpha));
			//Draw a slightly thicker circle on the currently selected car
			CP_Graphics_DrawCircle(car[i].x, car[i].y, carDiameter*1.1);
		}
		//Draw car circle body
		CP_Settings_Fill(car[i].carColour);
		CP_Graphics_DrawCircle(car[i].x, car[i].y, carDiameter);
		//Draw triangle
		CP_Settings_Fill(triangleCol);
		double triangleRearX = car[i].x - (carRadius * 0.7);
		CP_Graphics_DrawTriangleAdvanced(car[i].x+carRadius, car[i].y, triangleRearX, car[i].y - triangleYBound, triangleRearX, car[i].y + triangleYBound, car[i].dir);
		 
		//Player hovering over car
		if (MouseInCircle(car[i].x, car[i].y, carDiameter, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//Player clicks on the car
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				//Switch the currently selected car to the one clicked on
				carI = i;
			}
		}
	}
	//Obtain boolean values for all movement keys
	int drive = CP_Input_KeyDown(KEY_W);
	int reverse = CP_Input_KeyDown(KEY_S);
	int steerLeft = CP_Input_KeyDown(KEY_A);
	int steerRight = CP_Input_KeyDown(KEY_D);
	//Returns 1 when only steerRight is pressed, -1 when only steerLeft
	//and 0 when either both or none are pressed.
	double steer = steerRight - steerLeft;

	//Change the direction of the car based on the player's steering input
	//and steering speed.
	car[carI].dir += (steer * steerSpeed)*dt;
	//Ensure direction never exceeds 360 and never falls below 0
	car[carI].dir = Wrap((int)car[carI].dir,0,360);

	if (reverse) //Go backwards
		car[carI].force = -700;

	else if (drive) //Accelerate, add some force
		car[carI].force = 2000;

	else //Slow to a halt
	{
		car[carI].force = 0;
		//Reduces speed based on mass until it reaches 0
		car[carI].moveSpeed = Approach(car[carI].moveSpeed,0,car[carI].mass*80 * dt);
	}

	//Acceleration = Force / Mass
	double accel = car[carI].force / car[carI].mass;
	//Velocity += Acceleration x time
	car[carI].moveSpeed += accel * dt;
	//Clamping to upper and lower speed limit
	car[carI].moveSpeed = CP_Math_ClampFloat(car[carI].moveSpeed, -car[carI].maxSpeed/2.0, car[carI].maxSpeed);
	//Obtain angle/direction of the car in radians
	float radAngle = CP_Math_Radians(car[carI].dir);
	//Converting radian vector into direction vector
	CP_Vector dirVec = AngleToVector(radAngle);
	//Assigning velocity to a variable that's easier to call.
	double velocity = car[carI].moveSpeed;
	//Position += Velocity(direction vector) x time
	car[carI].x += dirVec.x * velocity*dt;
	car[carI].y += dirVec.y * velocity * dt;

	//Screen wrapping for x axis
	if (car[carI].x < 0)
		car[carI].x = windowWidth;
	else if (car[carI].x > windowWidth)
		car[carI].x = 0;
	//Screen wrapping for y axis
	if (car[carI].y < 0)
		car[carI].y = windowHeight;
	else if (car[carI].y > windowHeight)
		car[carI].y = 0;
	//The wrapping function produces some weird movement due to only
	//working with int values, hence I'm not using it here for wrapping
	//the position of my car.

	//Go back to main menu
	if (CP_Input_KeyDown(KEY_Q))
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
}

void Car_Level_Exit()
{

}
