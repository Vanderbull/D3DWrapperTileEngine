//*******************************************************************
//* Namn: Rickard Skeppström
//* Personnr: 790930-xxxx
//* Klass: SP6
//* E-mail: rickard_skeppstrom@msn.com alt rickard.skeppstrom@powerhouse.net
//* Lab: Direct 3D wrapper
//*******************************************************************/

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
using namespace std;

class Direct3DWrapper
{
public:
	~Direct3DWrapper(void);

	// Pretty Singleton
	static Direct3DWrapper& getInstance() { static Direct3DWrapper pInstance; 
return pInstance;}

	// Methods for Creating and initiating a Direct3D device
	bool D3D_Create9();
	bool InitD3D_Device9(HWND wndHandle, bool Fullscreen, int Width, int Height);
	int LoadTexture(LPCSTR filename);
	int CreateTexture();

	void Render(IDirect3DSurface9* srcSurface, const RECT *srcRect, HWND wndHandle, double angle);
	void RotateTexture(int turn);
	void ScaleTexture(float scale);
	void StartScene();
	void StopScene();

	void MakeSprite(double angle);

	bool ClearScreen(int Red, int Green, int Blue );
	void EndRender(void);
	void Shutdown(void);
	int Texture_id();
	LPDIRECT3DDEVICE9 GetDevice();

private:
	Direct3DWrapper(void);

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
};

