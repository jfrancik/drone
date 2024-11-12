#include "stdafx.h"
#include "MyGame.h"
#include <iostream>

CMyGame game;
CGameApp app;

int main(int argc, char* argv[])
{
	app.OpenConsole();
	
	cout << endl << "War of Drones" << endl << endl;
	cout << "Find the enemy using cockpit instruments." << endl;
	cout << "The arrows show direction relative to the drone's course and not to the screen!" << endl;
	cout << "Use Left and Right Ctrl keys to shoot (or Left Ctrl and Alt)" << endl;
	cout << "A/Left Arrow and D/Right Arrow to navigate." << endl ;
	cout << "DEBUG: Left Alt + Z and X to reveal the vectors." << endl << endl;

	app.OpenWindow(1024, 768, "War of Drones");
	//app.OpenFullScreen(800, 600, 24);
	app.SetClearColor(CColor::White());
	app.Run(&game);
	return(0);
}
