////////////////////////////////////////////////////////////////////////////////////////
// Creator: Rickard Skeppström
// Purpose: Winmain application entry point.
// Altered: 2008-03-10
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <windows.h>
#include <windowsx.h>
using namespace std;

#include "winmain.h"
#include "guicon.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

////////////////////////////////////////////////////////////////////////////////////////
// Creator: Rickard Skeppström
// Purpose: Wínmain function
// Altered: 2008-03-10
// Indata: HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
// Outdata: int, msg.wParam
////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	ZeroMemory(&wcxWnd_class, sizeof(WNDCLASSEX));

    wcxWnd_class.cbSize = sizeof(WNDCLASSEX);
    wcxWnd_class.style = CS_HREDRAW | CS_VREDRAW;
    wcxWnd_class.lpfnWndProc = (WNDPROC)WindowProc;
    wcxWnd_class.hInstance = hInstance;
    wcxWnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcxWnd_class.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
    wcxWnd_class.lpszClassName = "WindowClass";

    RegisterClassEx(&wcxWnd_class);

    hWnd = CreateWindowEx(NULL, 
		"WindowClass", 
		"Main window",
		WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW, 
		0, 
		0, 
		640,
		480,
		0, 
		0, 
		hInstance, 
		0);

	if(hWnd == 0)
	{
		return -1;
	}
	else
	{
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}

	RedirectIOToConsole();

    while(!bApp_done)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
			{
                break;
			}
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

////////////////////////////////////////////////////////////////////////////////////////
// Creator: Rickard Skeppström
// Purpose: Main message handler for the application
// Altered: 2008-03-10
// Indata: HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
// Outdata: DefWindowProc (hWnd, message, wParam, lParam)
////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_PAINT:
			{
				hdc = BeginPaint( hWnd, &ps );
				EndPaint( hWnd, &ps );
			}break;
		case WM_CHAR:
			{
			}break;
        case WM_DESTROY:
            {
                PostQuitMessage(0);
            }break;
		case WM_MOUSEMOVE:
			{
			}break;
        case WM_SIZE:
			{
			}break;

		case WM_LBUTTONUP:
			{
			}break;

        case WM_LBUTTONDOWN:
			{
			}break;
        case WM_KEYDOWN:
			{
				switch( LOWORD( wParam ))
				{
					case VK_ESCAPE:
						{	/*  Pressing esc quits */
							PostQuitMessage( 0 );
						}break;
				}break;
			}break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}