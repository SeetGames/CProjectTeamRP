//---------------------------------------------------------
// file:	game.c
// author:	Seetoh Wei Tung
// email:	seetoh.w@digipen.edu
//
// brief:	Contains the state for the gameplay loop
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

void Game_Init()
{
	
}

void Game_Update()
{
	//Obtain delta time
	dt = CP_System_GetDt();
	//Clear the background and make it gray
	CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
}

void Game_Exit()
{

}
