#ifndef H_CTILE_MANAGER
#define H_CTILE_MANAGER

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
using namespace std;
#include "Direct3DManager.h"
#include "winmain.h"
static Direct3DWrapper& DManager = Direct3DWrapper::getInstance();

class CTile
{
public:
	CTile()
	{
		bPlaced = false;
	};
	~CTile(){};
	void Set_clipping_rect(UINT uiX, UINT uiY, UINT uiSize)
	{
		rClipping_rect.bottom = uiY + uiSize;
		rClipping_rect.left = uiX;
		rClipping_rect.right = uiX + uiSize;
		rClipping_rect.top = uiY;
	};

	RECT Get_clipping_rect()
	{
		return rClipping_rect;
	};

	void Set_Texture(LPDIRECT3DTEXTURE9 lpTexture)
	{
		m_lpTexture = lpTexture;
	};

	LPDIRECT3DTEXTURE9 Get_texture()
	{
		return m_lpTexture;
	};

	void Set_position(UINT Pos_x, UINT Pos_y, UINT Pos_z)
	{
		m_sPosition.x = Pos_x;
		m_sPosition.y = Pos_y;
		m_sPosition.z = Pos_z;
	};

	void Set_center(UINT uiX, UINT uiY, UINT uiZ)
	{
		m_sCenter.x = uiX;
		m_sCenter.y = uiY;
		m_sCenter.z = uiZ;
	};
	void Update_position(int Change_x, int Change_y, int Change_z)
	{
		m_sPosition.x += Change_x;
		m_sPosition.y += Change_y;
		m_sPosition.z += Change_z;
	};

	D3DXVECTOR3 Get_position()
	{
		return m_sPosition;
	};

	void Draw()
	{
		RECT aSrc_rect;
		SetRect(&aSrc_rect,0,0,TILE_SIZE,TILE_SIZE);
		
		DManager.Draw(
			aSrc_rect, 
			m_lpTexture,
			m_sPosition,
			m_sCenter);
	};

	RECT rClipping_rect;
	D3DXVECTOR3 m_sPosition,m_sCenter;
	LPDIRECT3DTEXTURE9 m_lpTexture;
	bool bDrawable;
	bool bPlaced;
};

CTile cTile_map[100][100][100];
CTile cTile_player[16];
CTile cTile_player2[16];

class CTile_manager
{
public:
	~CTile_manager(){};
	CTile_manager()
	{
		uiScroll_Y = 0;
		uiScroll_X = 0;
		uiCurrent_scroll_X = 0;
		uiCurrent_scroll_Y = 0;
		uiLayers = 1;
		uiCurrent_layer = 1;
		m_bAdjust_to_scroll = true;
		uiTiles_to_draw = 0;
	};
	void Add_tile( LPDIRECT3DTEXTURE9 lpTexture )
	{
		cTile_map[0][0][0].Set_position(100,100,100);
		m_lpspritepic = lpTexture;
		m_lpTexture.push_back(m_lpspritepic);
	};
	LPDIRECT3DTEXTURE9 lpGet_Texture(unsigned int iID)
	{
		DManager.lpGet_Texture(0);
		if( iID < 0)
		{
			return 0;
		}

		if( ( m_lpTexture.size() >= 0 && iID < m_lpTexture.size() ) )
		{
			m_lpspritepic = m_lpTexture.at(iID);
			return m_lpspritepic;
		}
		return 0;
	};

	UINT uiGet_scroll_Y()
	{
		return uiScroll_Y;
	};

	UINT uiGet_scroll_X()
	{
		return uiScroll_X;
	};
	
	void Reset_scroll()
	{
		uiCurrent_scroll_X = 0;
		uiCurrent_scroll_Y = 0;
	};
	void Reset_current_X(UINT uiValue)
	{
		uiCurrent_scroll_X = uiValue;
	};
	void Reset_current_Y(UINT uiValue)
	{
		uiCurrent_scroll_Y = uiValue;
	};
	UINT uiSet_scroll_X(UINT uiScroll_change)
	{
		uiCurrent_scroll_X += uiScroll_change;
		return uiCurrent_scroll_X;
	}
	UINT uiSet_scroll_Y(UINT uiScroll_change)
	{
		uiCurrent_scroll_Y += uiScroll_change;
		return uiCurrent_scroll_Y;
	}
	UINT uiGet_current_scroll_Y()
	{
		return uiCurrent_scroll_Y;
	};

	UINT uiGet_current_scroll_X()
	{
		return uiCurrent_scroll_X;
	};
	
	D3DXVECTOR3 sSet_position(UINT uiX, UINT uiY, UINT uiZ)
	{
		sPosition.x = uiX;
		sPosition.y = uiY;
		sPosition.z = uiZ;
		return sPosition;
	};
	D3DXVECTOR3 sGet_position()
	{
		return sPosition;
	};
	D3DXVECTOR3 sSet_center(UINT uiX, UINT uiY, UINT uiZ)
	{
		sCenter.x = uiX;
		sCenter.y = uiY;
		sCenter.z = uiZ;
		return sCenter;
	};
	D3DXVECTOR3 sGet_center()
	{
		return sCenter;
	};
	D3DXVECTOR3 sSet_vTile(UINT uiX, UINT uiY, UINT uiZ)
	{
		sCenter.x = uiX;
		sCenter.y = uiY;
		sCenter.z = uiZ;
		return sCenter;
	};
	D3DXVECTOR3 sGet_vTile()
	{
		return sCenter;
	};

	void Init_map(int iScroll_X, int iScroll_Y,UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Set_position(x*TILE_SIZE + iScroll_X,y*TILE_SIZE + iScroll_Y,0);
				cTile_map[x][y][0].Set_center(0,0,0);
				if(y == 0 || y == 26)
					cTile_map[x][y][0].Set_Texture(lpGet_Texture(3));
				else
					if( x < 3 || x > 11 )
					{
						cTile_map[x][y][0].Set_Texture(lpGet_Texture(4));
					}
					else
						if( y > 13 && y < 16 && x > 2 && x < 12 )
						{
							cTile_map[x][y][0].Set_Texture(lpGet_Texture(5));
						}
					else
					{
						cTile_map[x][y][0].Set_Texture(lpGet_Texture(0));
					}
			}
		}
	}
	void Map(int iScroll_X, int iScroll_Y,UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Draw();
			}
		}
	}

	void Scroll_map_down(UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Update_position(0,TILE_SIZE,0);
			}
		}
		for( int iID = 0; iID < 16; ++iID )
		{
			cTile_player[iID].Update_position(0,TILE_SIZE,0);
			cTile_player2[iID].Update_position(0,TILE_SIZE,0);
		}
	}
	void Scroll_map_up(UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Update_position(0,-TILE_SIZE,0);
			}
		}
		for( int iID = 0; iID < 16; ++iID )
		{
			cTile_player[iID].Update_position(0,-TILE_SIZE,0);
			cTile_player[iID].Update_position(0,-TILE_SIZE,0);
		}
	}
	void Scroll_map_left(UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Update_position(-TILE_SIZE,0,0);
			}
		}
		for( int iID = 0; iID < 16; ++iID )
		{
			cTile_player[iID].Update_position(-TILE_SIZE,0,0);
			cTile_player[iID].Update_position(-TILE_SIZE,0,0);
		}
	}
	void Scroll_map_right(UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Update_position(TILE_SIZE,0,0);
			}
		}
		for( int iID = 0; iID < 16; ++iID )
		{
			cTile_player[iID].Update_position(TILE_SIZE,0,0);
			cTile_player[iID].Update_position(TILE_SIZE,0,0);
		}
	}
	void Show_bottom_pitch(UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Update_position(0,-TILE_SIZE*12,0);
			}
		}
	}
	void Show_top_pitch(UINT uiMap_width, UINT uiMap_height)
	{
		for(UINT x = 0; x < uiMap_width; ++x)
		{
			for(UINT y = 0; y < uiMap_height; ++y)
			{
				cTile_map[x][y][0].Update_position(0,TILE_SIZE*12,0);
			}
		}
	}
	// Need some sort of integer map for selecting tile type
	void Draw_map(int iScroll_X, int iScroll_Y,UINT uiMap_width, UINT uiMap_height, UINT uiTexture_id)
	{
		RECT aSrc_rect;
		SetRect(&aSrc_rect,0,0,TILE_SIZE,TILE_SIZE);

		for( UINT uiDraw_layer = 0; uiDraw_layer < uiLayers; uiDraw_layer++ )
		{
			Reset_current_X(uiGet_scroll_X());
			Reset_current_Y(uiGet_scroll_Y());

			for(UINT x = 0; x < uiMap_width; ++x)
			{
				for(UINT y = 0; y < uiMap_height; ++y)
				{
					sSet_position(
						sCenter.x + uiGet_current_scroll_X() + iScroll_X,
						sCenter.y + uiGet_current_scroll_Y() + iScroll_Y,
						0);

					if( uiDraw_layer > 1 )
					{
						uiTexture_id++;
					}
					DManager.Draw(
						aSrc_rect, 
						lpGet_Texture(uiTexture_id),
						sGet_position(),
						sGet_center());

					uiSet_scroll_Y(TILE_SIZE);
				}
				Reset_current_Y(0);
				uiSet_scroll_X(TILE_SIZE);
			}
		}
	};

	void Draw(int iPosition_x, int iPosition_y, UINT uiTexture_id)
	{
		Set_to_draw( iPosition_x,iPosition_y, uiTexture_id );
		RECT aSrc_rect;
		SetRect(&aSrc_rect,0,0,TILE_SIZE,TILE_SIZE);

		if( !m_bAdjust_to_scroll )
		{
			sSet_position(
				sCenter.x + iPosition_x,
				sCenter.y + iPosition_y,
				0);
		}

		if( m_bAdjust_to_scroll )
		{
			sSet_position(
				sCenter.x + iPosition_x + m_uiDistort_x,
				sCenter.y + iPosition_y + m_uiDistort_y,
				0);
		}
		
		DManager.Draw(
			aSrc_rect, 
			lpGet_Texture(uiTexture_id),
			sGet_position(),
			sGet_center());
	};

	UINT Get_current_layer()
	{
		return uiCurrent_layer;
	};

	UINT Add_layer()
	{
		uiLayers++;
		uiCurrent_layer++;
		return uiLayers;
	};

	UINT Remove_layer()
	{
		if( uiLayers > 1 )
		{
			uiLayers--;
			uiCurrent_layer--;
			return uiLayers;
		}
		return -1;
	};

	UINT uiDistort(UINT uiDistort_x, UINT uiDistort_y)
	{
		m_uiDistort_x = uiDistort_x;
		m_uiDistort_y = uiDistort_y;
		return 0;
	};

	void Adjust_to_scrolling( bool bAdjust_to_scroll )
	{
		m_bAdjust_to_scroll = bAdjust_to_scroll;
	};

	void Set_to_draw( int iPosition_x, int iPosition_y, UINT uiTexture_id )
	{
		D3DXVECTOR3 sTile(iPosition_x,iPosition_y, uiTexture_id);
		vTile[uiTiles_to_draw] = sTile;
		uiTiles_to_draw++;
	}
	void Reset_uiTiles_to_draw()
	{
		uiTiles_to_draw = 0;
	}

	// New create function for cTile object
	void Init_cTile(UINT uiX, UINT uiY, UINT uiZ, 
					 UINT uiPos_x, UINT uiPos_y, UINT uiPos_z, 
					 UINT uiSize, UINT uiTexture_id )
	{
		cInit_Tile.Set_center(uiX,uiY,uiZ);
		cInit_Tile.Set_position(uiPos_x,uiPos_y,uiPos_z);
		cInit_Tile.Set_clipping_rect(uiX,uiY,uiSize);
		cInit_Tile.Set_Texture( DManager.lpGet_Texture(uiTexture_id) );
	}
	void Create_cTile()
	{
		cTiler.push_back(cInit_Tile);
	}

	void Init_player_tiles()
	{
		for(int h= 0; h < 16; h++)
		{
			cTile_player[h].Set_position(h*TILE_SIZE,0,0);
			cTile_player[h].Set_center(0,0,0);
			cTile_player[h].Set_Texture(lpGet_Texture(0));
			
			cTile_player2[h].Set_position(h*TILE_SIZE,0,0);
			cTile_player2[h].Set_center(0,0,0);
			cTile_player2[h].Set_Texture(lpGet_Texture(0));
		}
	}



private:
	
	LPDIRECT3D9					m_lpD3D_Object;	// Direct3D object

	LPDIRECT3DDEVICE9			m_lpd3dDevice;	// Direct3D device

	LPDIRECT3DTEXTURE9			m_lpspritepic;

	std::vector <LPDIRECT3DTEXTURE9>		m_lpTexture;

	LPD3DXSPRITE				m_lpSprite;

	D3DXMATRIX					m_rotate;
	D3DXMATRIX					m_translate;
	D3DXMATRIX					m_scale;
	D3DXMATRIX					m_result;

	D3DSURFACE_DESC				m_surface_desc;
		
	UINT uiScroll_Y;
	UINT uiScroll_X;
	UINT uiCurrent_scroll_X;
	UINT uiCurrent_scroll_Y;
	UINT m_uiDistort_x;
	UINT m_uiDistort_y;
	UINT uiLayers;
	UINT uiCurrent_layer;
	D3DXVECTOR3 sPosition,sCenter;
	D3DXVECTOR3 vTile[1000];
	bool m_bAdjust_to_scroll;
	UINT uiTiles_to_draw;
	std::vector<CTile> cTiler;
	CTile cInit_Tile;
};

CTile_manager cTile_manager;

#endif