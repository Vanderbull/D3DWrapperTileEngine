struct SKeyb_data
{
	int Scroller_x;
	int Scroller_y;
	int Team;
	int Texture_id;
};

class CKeyboard
{
public:
	CKeyboard()
	{

	};
	~CKeyboard(){};

	SKeyb_data Key_down(WPARAM wParam, int uiScroll_X, int uiScroll_Y, int iTeam, int uiTexture_id)
	{
		sKeyb_data.Scroller_x = uiScroll_X;
		sKeyb_data.Scroller_y = uiScroll_Y;
		sKeyb_data.Team = iTeam;
		sKeyb_data.Texture_id = uiTexture_id;

				switch( LOWORD( wParam ))
				{
					case VK_LEFT: 
						cTile_manager.Scroll_map_left(15,27);
						break;
					case VK_UP: 
						cTile_manager.Scroll_map_up(15,27);
						break;
					case VK_RIGHT:
						cTile_manager.Scroll_map_right(15,27);
						break;
					case VK_DOWN:
						cTile_manager.Scroll_map_down(15,27);
						break;
					case VK_NUMPAD1: /* move down left */ break;
					case VK_NUMPAD2: 
						uiScroll_Y = TILE_SIZE;
						if( iTeam == 1 )
							cTile_player[uiTexture_id].Update_position(0,uiScroll_Y,0);
						else
							cTile_player2[uiTexture_id].Update_position(0,uiScroll_Y,0);
						break;
					case VK_NUMPAD3: /* move down right */ break;
					case VK_NUMPAD4: 
						uiScroll_X = -TILE_SIZE;
						if( iTeam == 1 )
						cTile_player[uiTexture_id].Update_position(uiScroll_X,0,0);
						else
							cTile_player2[uiTexture_id].Update_position(uiScroll_X,0,0);
						break;
					case VK_NUMPAD5: TILE_SIZE -= 32; /* nothing */ break;
					case VK_NUMPAD6: 
						uiScroll_X = TILE_SIZE;
						if( iTeam == 1 )
						cTile_player[uiTexture_id].Update_position(uiScroll_X,0,0);
						else
							cTile_player2[uiTexture_id].Update_position(uiScroll_X,0,0);
						break;
					case VK_NUMPAD7: /* move up left */ break;
					case VK_NUMPAD8: 
						uiScroll_Y = -TILE_SIZE;
						if( iTeam == 1 )
						cTile_player[uiTexture_id].Update_position(0,uiScroll_Y,0);
						else
							cTile_player2[uiTexture_id].Update_position(0,uiScroll_Y,0);
						break;
					case VK_NUMPAD9: /* move up right */ break;
					case VK_ADD:
						cTile_player[uiTexture_id].bPlaced = true;
						uiTexture_id++; 
						cout << uiTexture_id << endl; break; 
						break;
					case VK_SUBTRACT:
						if( uiTexture_id != 0 )
						{
							uiTexture_id--; 
						}
						cout << uiTexture_id << endl; break;
						break;
					case VK_RETURN:
						if( iTeam == 1 )
						{
							cTile_manager.Show_bottom_pitch(15, 27);
							iTeam = 2;
							Sleep(100);
							uiTexture_id = 0;
						}							
						else
						{
							cTile_manager.Show_top_pitch(15, 27);
							iTeam = 1;
							Sleep(100);
							uiTexture_id = 0;
						}
						break;
					case VK_ESCAPE:
						{	/*  Pressing esc quits */
							PostQuitMessage( 0 );
						}break;
				}
				
				sKeyb_data.Scroller_x = uiScroll_X;
				sKeyb_data.Scroller_y = uiScroll_Y;
				sKeyb_data.Team = iTeam;
				sKeyb_data.Texture_id = uiTexture_id;

				return sKeyb_data;
	}

	SKeyb_data sKeyb_data;
};

CKeyboard cKeyboard;