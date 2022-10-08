//---------------------------------------------------------
// file:	mainmenu.c
// author:	Seetoh Wei Tung
// email:	seetoh.w@digipen.edu
//
// brief:	Contains the state for the main menu
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "utils.h"
#include "carlevel.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

double dt;
float windowWidthCenter;
float windowHeightCenter;
float buttonWidth = 150.0;
float buttonHeight = 50.0;
float buttonX[2];
float buttonY[2];
//Character pointer for array storing the 2 button names
char* buttonName[] = {"Play","Exit"};
CP_Color buttonCol;
CP_Color buttonClick;
CP_Color buttonText;
CP_Font myFont;

void Main_Menu_Init()
{
	CP_System_SetFrameRate(60.0f); //Sets framerate to 60 FPS
	CP_System_SetWindowSize(windowWidth, windowHeight);

	// initialize settings
	CP_Settings_TextSize(35);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	myFont = CP_Font_GetDefault();
	//Get default button colour
	buttonCol = CP_Color_Create(255, 40, 100, 255);
	//Get button colour when hovered
	buttonClick = CP_Color_Create(128, 20, 51, 255);
	//Get text on button colour
	buttonText = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void Main_Menu_Update()
{
	windowWidthCenter = CP_System_GetWindowWidth() / 2.0f;
	windowHeightCenter = CP_System_GetWindowHeight() / 2.0f;

	buttonX[0] = windowWidthCenter;
	buttonY[0] = windowHeightCenter;

	buttonX[1] = windowWidthCenter;
	buttonY[1] = windowHeightCenter + 100;
	CP_Graphics_ClearBackground(CP_Color_Create(30, 30, 30, 255)); //Make gray background
	//Loop through both buttons
	for (int i = 0; i < 2; i++)
	{
		//Set the button colour to default button colour
		CP_Settings_Fill(buttonCol);
		//Check if mouse is within the button's boundaries
		if (MouseInRect(buttonX[i], buttonY[i], buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//Since mouse is hovering, change button colour to hover colour
			CP_Settings_Fill(buttonClick);
			//Player clicks on the button
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				switch (i)
				{
				case 0: //Play
					CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
					break;
				case 1: //Exit
					CP_Engine_Terminate();
					break;
				default:
					break;
				}
			}
		}
		//Draw all buttons
		CP_Graphics_DrawRect(buttonX[i], buttonY[i], buttonWidth, buttonHeight);
		CP_Font_Set(myFont);
		CP_Settings_Fill(buttonText);
		//Draw name of the button
		CP_Font_DrawText(buttonName[i], buttonX[i], buttonY[i]);
	}
}

void Main_Menu_Exit()
{
}
