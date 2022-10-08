#include "cprocessing.h"

//---------------------------------------------------------
// file:	main.c
// author:	Seetoh Wei Tung
// email:	seetoh.w@digipen.edu
//
// brief:	Car select game
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "carlevel.h"

int main(void)
{
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);

	CP_Engine_Run();
	return 0;
}
