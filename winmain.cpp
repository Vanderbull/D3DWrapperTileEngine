////////////////////////////////////////////////////////////////////////////////////////
// Creator: Rickard Skeppström
// Purpose: Winmain application entry point.
// Altered: 2008-03-10
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <windows.h>
#include <windowsx.h>
using namespace std;

//#include "Direct3DManager.h"
#include "CTile_manager.h"
#include "CMouse.h"
#include "CKeyboard.h"
#include "winmain.h"
#include "guicon.h"
#include "CFont.h"
#include "CStatus.h"
UINT uiTexture_id = 0;
int uiScroll_X = 0;
int uiScroll_Y = 0;
UINT uiScroll_tile = 0;
UINT iTeam = 0;
static POINT pt; 
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
		WIDTH,
		HEIGHT,
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

	cTile_manager.Add_tile(DManager.lpGet_Texture(0));
	cTile_manager.Add_tile(DManager.lpGet_Texture(1));
	cTile_manager.Add_tile(DManager.lpGet_Texture(3));
	cTile_manager.Add_tile(DManager.lpGet_Texture(4));
	cTile_manager.Add_tile(DManager.lpGet_Texture(5));
	cTile_manager.Add_tile(DManager.lpGet_Texture(6));

	D3DXCreateSprite(DManager.GetDevice(), &d3dspt);
	cTile_manager.Init_map(0,0, 15, 27);
	cTile_manager.Init_player_tiles();
	cFont.Init(DManager.GetDevice(),"Arial");
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
		DManager.ClearScreen(255,255,255);
		DManager.StartScene();
		cTile_manager.sSet_center(0,0,0);
		cTile_manager.Map(0,0, 15, 27);
		//cTile_player[uiTexture_id].Set_Texture(cTile_manager.lpGet_Texture(1));
		//cTile_player[uiTexture_id].Draw();

		if( iTeam == 1 )
		{
			for(int h=0; h < 16; h++)
			{
				//cTile_player[h].Set_position(0,h*TILE_SIZE,0);
				//cTile_player[h].Set_center(0,0,0);
				cTile_player[h].Set_Texture(cTile_manager.lpGet_Texture(2));
				//cTile_player[h].Update_position(0,0,0);
				cTile_player[h].Draw();
			}

			for(int h= 0; h < 16; h++)
			{
				if( uiTexture_id == h)
				{
					//cTile_player[h].Set_position(0,h*TILE_SIZE,0);
					//cTile_player[h].Set_center(0,0,0);
					cTile_player[h].Set_Texture(cTile_manager.lpGet_Texture(0));
					//cTile_player[h].Update_position(uiScroll_tile,0,0);
					cTile_player[h].Draw();
					cTile_player[h].Set_Texture(cTile_manager.lpGet_Texture(1));
					cTile_player[h].Draw();
					cStatus[h].Print(h);
				}
			}
			
			DManager.StopScene();
			DManager.EndRender();
		}
		if( iTeam == 2 )
		{
			for(int h=0; h < 16; h++)
			{
				//cTile_player[h].Set_position(0,h*TILE_SIZE,0);
				//cTile_player[h].Set_center(0,0,0);
				cTile_player2[h].Set_Texture(cTile_manager.lpGet_Texture(2));
				//cTile_player[h].Update_position(0,0,0);
				cTile_player2[h].Draw();
			}

			for(int h= 0; h < 16; h++)
			{
				if( uiTexture_id == h)
				{
					//cTile_player[h].Set_position(0,h*TILE_SIZE,0);
					//cTile_player[h].Set_center(0,0,0);
					cTile_player2[h].Set_Texture(cTile_manager.lpGet_Texture(0));
					//cTile_player[h].Update_position(uiScroll_tile,0,0);
					cTile_player2[h].Draw();
					cTile_player2[h].Set_Texture(cTile_manager.lpGet_Texture(1));
					cTile_player2[h].Draw();
					cStatus[h].Print(h);
				}
			}
			d3dspt->End();
			DManager.StopScene();
			DManager.EndRender();
		}

		//cTile_manager.Init_cTile(0,0,0,128,128,0,TILE_SIZE,0);
		//cTile_manager.Create_cTile();
		
		//DManager.ClearScreen(255,255,255);
		//DManager.StartScene();
		//RECT aSrc_rect;
		//SetRect(&aSrc_rect,0,0,TILE_SIZE,TILE_SIZE);

		//cTile_manager.Reset_current_X(cTile_manager.uiGet_scroll_X());
		//cTile_manager.Reset_current_Y(cTile_manager.uiGet_scroll_Y());
		//for(int i = 0; i < 15; ++i)
		//{
		//	for(int y = 0; y < 26; ++y)
		//	{
		//		cTile_manager.vSet_position(cTile_manager.uiGet_scroll_X(),cTile_manager.uiGet_scroll_Y(),0);
		//		cTile_manager.vSet_center( cTile_manager.uiGet_current_scroll_X() + scroll,cTile_manager.uiGet_current_scroll_Y() + iScroll_y, 0);
		//		DManager.Draw(aSrc_rect, cTile_manager.lpGet_Texture(0),cTile_manager.vGet_position(),cTile_manager.vGet_center());
		//		cTile_manager.uiSet_scroll_Y(TILE_SIZE);
		//	}
		//	cTile_manager.Reset_current_Y(200);
		//	cTile_manager.uiSet_scroll_X(TILE_SIZE);
		//}
		//DManager.StopScene();
		//DManager.EndRender();
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
	PAINTSTRUCT ps; 
    HDC hdc; 
    RECT rc; 
    POINT aptStar[6] = {50,2, 2,98, 98,33, 2,33, 98,98, 50,2}; 

    switch(message)
    {
		case WM_CREATE:
			{
				RedirectIOToConsole();
				DManager.D3D_Create9();
				DManager.InitD3D_Device9(hWnd,false,WIDTH,HEIGHT);
				DManager.LoadTexture("sprites/Temple.png");
				DManager.LoadTexture("Sprites/grid.png");
				DManager.LoadTexture("Sprites/Temple.bmp");
				DManager.LoadTexture("Sprites/Temple2.png");
				DManager.LoadTexture("Sprites/goal.png");
				DManager.LoadTexture("Sprites/sideline.png");
				DManager.LoadTexture("Sprites/scrimmage.png");

				iTeam = 1;
			}
        case WM_PAINT:
			{
				hdc = BeginPaint( hWnd, &ps );
				GetClientRect(hWnd, &rc); 
				SetMapMode(hdc, MM_ANISOTROPIC); 
				SetWindowExtEx(hdc, 100, 100, NULL); 
				SetViewportExtEx(hdc, rc.right, rc.bottom, NULL); 
				Polyline(hdc, aptStar, 6); 
				EndPaint( hWnd, &ps );
			}break;
		case WM_CHAR:
			{
				switch( LOWORD( wParam ))
				{
					case 'a': uiScroll_X+=TILE_SIZE; break;
					case 'd': uiScroll_X-=TILE_SIZE; break;
					case 's': uiScroll_Y += TILE_SIZE; break;
					case 'w': uiScroll_Y -= TILE_SIZE; break;

					case '3': uiScroll_tile+=TILE_SIZE; cout << uiScroll_tile << endl;break;
					case '4': 
						if( uiScroll_tile != 0 )
						{
							uiScroll_tile-=TILE_SIZE; 
						}
						cout << uiScroll_tile << endl;break;
					case '+': cTile_manager.Add_layer(); break;
					case '-': cTile_manager.Remove_layer(); break;
					case 't': cTile_manager.Adjust_to_scrolling(false); break;
					case 'u': cTile_manager.Adjust_to_scrolling(true); break;
					case 'c': cTile_manager.Add_tile( DManager.lpGet_Texture(uiTexture_id) ); break;
				}
			}break;
        case WM_DESTROY:
            {
                PostQuitMessage(0);
            }break;
		case WM_MOUSEMOVE:
			{
				cMouse.Set_position(lParam);
				cMouse.Set_pSnap_pt(TILE_SIZE);

				if ( PtInRegion(cMouse.hrgn, cMouse.pt.x, cMouse.pt.y) )
				{
					cout << "cursor pos(" << cMouse.pt.x << "," << cMouse.pt.y << ")" << endl;
					if( iTeam == 1 )
					{
						if( cTile_player[uiTexture_id].bPlaced == false )
						cTile_player[uiTexture_id].Set_position(cMouse.pSnap_pt.x,cMouse.pSnap_pt.y,0);
					}
					if( iTeam == 2 )
					{
						cTile_player2[uiTexture_id].Set_position(cMouse.pSnap_pt.x,cMouse.pSnap_pt.y,0);
					}
				}
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
				SKeyb_data sKeyb_data = cKeyboard.Key_down(wParam,uiScroll_X,uiScroll_Y,iTeam, uiTexture_id);

				uiScroll_X = sKeyb_data.Scroller_x;
				uiScroll_Y = sKeyb_data.Scroller_y;
				iTeam = sKeyb_data.Team;
				uiTexture_id = sKeyb_data.Texture_id;
			}break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}