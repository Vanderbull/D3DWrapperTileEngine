////////////////////////////////////////////////////////////////////////////////////////
// Creator: Rickard SKeppström
// Purpose: Winmain the entry point for the application.
// Altered: 2008-03-10
////////////////////////////////////////////////////////////////////////////////////////

#ifndef H_WINMAIN
#define H_WINMAIN

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
// include the DirectX Library files
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define HEIGHT 960
#define WIDTH 1280
unsigned int TILE_SIZE = 64;
HWND hWnd;
WNDCLASSEX wcxWnd_class;
bool bApp_done;
MSG msg;
HDC hdc;
PAINTSTRUCT ps;
LPD3DXSPRITE d3dspt;

#endif