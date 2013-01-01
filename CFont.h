#ifndef H_CFONT
#define H_CFONT

#include <sstream>
using namespace std;
class CFont
{
public:
	ID3DXFont *g_font;
	LPD3DXSPRITE m_lpSurface;
	std::string text;

	CFont()
	{
	}
	~CFont()
	{
		if( g_font != 0 )
		{
			g_font->Release();
			g_font = 0;
		}
	}

	bool Init(LPDIRECT3DDEVICE9 device, std::string Font)
	{
		D3DXCreateSprite(device, &m_lpSurface);
		if(FAILED(D3DXCreateFont( 
						device, 
						20, 
						0, 
						FW_BOLD, 
						0, 
						FALSE, 
						DEFAULT_CHARSET, 
						OUT_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, 
						DEFAULT_PITCH | FF_DONTCARE, 
						Font.c_str(), 
						&g_font )))
		{
			MessageBox(0,"Font init error","Direct3dwrapper",MB_OK);
			return false;
		}
		return true;
	}

	void Destroy()
	{
		if( g_font != 0 )
		{
			g_font->Release();
			g_font = 0;
		}
	}

	void Print( int x, int y, std::string txt_to_print )
	{
		text = txt_to_print;

		RECT location;
		SetRect(&location,x,y,WIDTH,HEIGHT);
	 
		g_font->DrawText(DManager.m_lpSprite, 
			text.c_str(), 
			-1, 
			&location, 
			0, 
			D3DCOLOR_ARGB(255,120,255,255) 
			);
	}
	
	void PrintInt(int x, int y, int value)
	{
		std::stringstream stream;
		stream << value;
		Print(x,y,stream.str());
	}

	void InitVolatileResources()
	{
	   //Init internal resources
	   g_font->OnResetDevice();
	}
	void FreeVolatileResources()
	{
	   //Free up some internal resources
	   g_font->OnLostDevice();
	}
};

CFont cFont;

#endif