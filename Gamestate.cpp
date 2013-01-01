#include "Gamestate.h"
CGamestate::CGamestate(){};
CGamestate::CGamestate( GameState GameStateInit )
{
   State = GameStateInit;
};
bool CGamestate::Init(){return true;};
bool CGamestate::Intro(){return true;};
bool CGamestate::Update()
{
	if(State == ::GS_INTRO)
	{
		Intro();
	}
	if(State == ::GS_HELP)
	{
		Help();
	}
	if(State == ::GS_MAINGAME)
	{
		Logic();
	}
	if(State == ::GS_MENU)
	{
		Menu();
	}
	if(State == ::GS_OPTIONS)
	{
		Options();
	}
	return true;
};
bool CGamestate::Input(){cout << "Input";return true;};
bool CGamestate::Logic(){cout << "Logic";return true;};
bool CGamestate::Draw_menu(){cout << "Draw_menu";return true;};
bool CGamestate::Draw(){cout << "Draw";return true;};
bool CGamestate::Menu(){cout << "Menu";return true;};
bool CGamestate::Options(){cout << "Options";return true;};
bool CGamestate::Help(){cout << "Help";return true;};
bool CGamestate::Shutdown(){cout << "Shutdown";return true;};

CGamestate::~CGamestate(){};