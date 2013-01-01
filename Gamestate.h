#ifndef H_GAMESTATE
#define H_GAMESTATE

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <functional>
#include <iostream>
#include <algorithm>
using namespace std;

class d3d_manager;
class di_manager;
class DSound;

enum GameState{
	GS_INTRO, 
	GS_MAINGAME, 
	GS_MENU, 
	GS_OPTIONS, 
	GS_HELP};

class CGamestate
{
public:
	CGamestate();
	~CGamestate();
	CGamestate( GameState GameStateInit );
	bool Init();
	bool Intro();
	bool Update();
	bool Input();
	bool Logic();
	bool Draw_menu();
	bool Draw();
	bool Menu();
	bool Options();
	bool Help();
	bool Shutdown();

private:	
	GameState State;
};

#endif