/*******************************************************************
* Namn: Rickard Skeppström
* Personnr: 790930-xxxx
* Klass: SP6
* E-mail: rickard_skeppstrom@msn.com alt rickard.skeppstrom@powerhouse.net
* Lab: Direct input wrapper
*******************************************************************/

#include ".\Direct3DManager.h"

/*******************************************************************
* Method:	Direct3DWrapper(ok)
* Purpose:	Set everything to a default NULL state
*******************************************************************/
Direct3DWrapper::Direct3DWrapper(void)
{
	m_lpD3D_Object = 0;
	m_lpd3dDevice = 0;
	m_lpspritepic = 0;
	m_lpSprite = 0;
}

LPDIRECT3DDEVICE9 Direct3DWrapper::GetDevice()
{
	return m_lpd3dDevice;
}
/************************************************************************/
//Method:	~Direct3DWrapper(ok)
//Purpose:	Destructor calling shutdown to release resources
/************************************************************************/
Direct3DWrapper::~Direct3DWrapper(void)
{
	Shutdown();
}

/************************************************************************/
//Method:	D3D_Create9
//Purpose:	Initializes DirectInput for use with the device
/************************************************************************/
bool Direct3DWrapper::D3D_Create9()
{
	if (NULL == ( m_lpD3D_Object = Direct3DCreate9(D3D_SDK_VERSION) ) )
	{
		return false;
	}

	return true;
}

/************************************************************************/
//Method:	InitD3D_Device9
//Purpose:	Initializes DirectInput devices
/************************************************************************/
bool Direct3DWrapper::InitD3D_Device9(HWND wndHandle, bool Fullscreen, int 
Width, int Height)
{
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed =true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferWidth = Width;
	d3dpp.hDeviceWindow = wndHandle;

	m_lpD3D_Object->CreateDevice(D3DADAPTER_DEFAULT,
								 D3DDEVTYPE_HAL,
								 wndHandle,
								 D3DCREATE_MIXED_VERTEXPROCESSING,
								 &d3dpp,
								 &m_lpd3dDevice );

	ZeroMemory(&m_lpSprite,sizeof(m_lpSprite));

	if(FAILED(D3DXCreateSprite(m_lpd3dDevice, &m_lpSprite)))
	{
		MessageBox(NULL,"Error", "Create sprite", MB_OK);
	}

	m_lpd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
	m_lpd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_lpd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
	m_lpd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	D3DXMatrixIdentity(&m_result);
	return true;
}

int Direct3DWrapper::Texture_id()
{
	static int id=0;
	id++;
	return id;
}

void Direct3DWrapper::RotateTexture(int turn)
{
	D3DXMatrixRotationZ(&m_rotate, D3DXToRadian(turn));
	D3DXMatrixMultiply(&m_result, &m_result, &m_rotate);
}

void Direct3DWrapper::ScaleTexture(float scale)
{
	D3DXMatrixScaling(&m_scale, scale, scale, scale);
	D3DXMatrixMultiply(&m_result, &m_result, &m_scale);
}

int Direct3DWrapper::LoadTexture(LPCSTR filename)
{
	if(FAILED(D3DXCreateTextureFromFileEx(
		m_lpd3dDevice, 
		filename, 
		0, 
		0, 
		0, 
		0,
        D3DFMT_A8R8G8B8, 
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT,
        D3DX_DEFAULT, 
		D3DCOLOR_XRGB(255, 0, 255), 
		NULL, 
		NULL, 
		&m_lpspritepic)))
	{
		MessageBox(0,"Error","Loading Texture from file", MB_OK);
	}

	m_lpTexture.push_back(m_lpspritepic);

	return m_lpTexture.size();
}

int Direct3DWrapper::CreateTexture()
{
	if(FAILED(D3DXCreateTexture(m_lpd3dDevice,512,512,D3DX_DEFAULT, 0,D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_lpspritepic)))
	{
		MessageBox(0,"Error","Loading Texture from file", MB_OK);
	}


	D3DLOCKED_RECT lock_Rect;
	m_lpspritepic->LockRect(0,&lock_Rect,0,0);
	unsigned char* pData=(unsigned char*)lock_Rect.pBits;
	for (int y=0; y<20;y++){
		for (int x=0;x<20;x++){
			pData[x*4+0]=0xFF;
			pData[x*4+1]=0xFF;
			pData[x*4+2]=0xFF;
			pData[x*4+3]=0xFF;
		}
		pData+=lock_Rect.Pitch;
	}
	m_lpspritepic->UnlockRect(0);
	m_lpTexture.push_back(m_lpspritepic);
	return 0;
}

//************************************************************************/
//Method:	Draw
//Purpose:	This is a testing function to the render method.
/************************************************************************/
void Direct3DWrapper::Draw(RECT sDraw_rect, LPDIRECT3DTEXTURE9 angle, D3DXVECTOR3 vPos, D3DXVECTOR3 vCenter)
{
	m_lpSprite->Draw(angle, &sDraw_rect, &vCenter, &vPos, D3DCOLOR_XRGB(255, 255, 255));
}

//************************************************************************/
//Method:	MakeSprite
//Purpose:	This is a testing function to the render method.
/************************************************************************/
void Direct3DWrapper::MakeSprite(double angle)
{
	m_lpd3dDevice->SetTexture(0, m_lpspritepic);

	D3DXMATRIX Position;
	D3DXMatrixTranslation(&Position, 100.0f, 100.0f, 0.0f);
	m_lpd3dDevice->SetTransform(D3DTS_WORLD, &m_result);

	m_lpSprite->Draw(m_lpspritepic, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));}

/************************************************************************/
//Method:	ClearScreen
//Purpose:	Clear screen with a specific color
/************************************************************************/
bool Direct3DWrapper::ClearScreen(int Red, int Green, int Blue)
{
	//Clears screen to a specific color, Here we need some more error checking
	// and before this part there should be controlls checking that there is
	// a device available.
	m_lpd3dDevice->Clear(0, NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0f,0);
	return true;
}

/************************************************************************/
//Method:	StartScene
//Purpose:	Starts the rendering
/************************************************************************/
void Direct3DWrapper::StartScene()
{
	m_lpd3dDevice->BeginScene();
	m_lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixIdentity(&m_result);
}

/************************************************************************/
//Method:	StartScene
//Purpose:	Starts the rendering
/************************************************************************/
void Direct3DWrapper::StopScene()
{
	m_lpSprite->End();
	m_lpd3dDevice->EndScene();
}

/************************************************************************/
//Method:	Render
//Purpose:	Here is where the writing to the Backbuffer is being done.
/************************************************************************/
void Direct3DWrapper::Render(IDirect3DSurface9* srcSurface, const RECT *srcRect, HWND wndHandle, double angle)
{
	m_lpspritepic->GetLevelDesc(0, &m_surface_desc);

	// Holding the xy coordinates for the center of the sprite
	D3DXVECTOR2 spriteCentre=D3DXVECTOR2(m_surface_desc.Width/2.0f, m_surface_desc.Height/2.0f);

	// Screen position of the sprite
	D3DXVECTOR2 trans=D3DXVECTOR2(50.0f,80.0f);

	// Rotate based on the time passed
	float rotation=0.0f;//timeGetTime()/500.0f;

	D3DXVECTOR2 scaling(2.0f,2.0f);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&m_result,NULL,0.0,&scaling,&spriteCentre,rotation,&trans);

	m_lpd3dDevice->SetTexture(0, m_lpspritepic);
	m_lpd3dDevice->SetTransform(D3DTS_WORLD, &m_result);
	m_lpSprite->Draw(m_lpspritepic, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

/************************************************************************/
//Method:	EndRender
//Purpose:	Last part in the rendering, it simply flips the backbuffer
//			to screen.
/************************************************************************/
void Direct3DWrapper::EndRender(void)
{
	m_lpd3dDevice->Present(NULL,NULL,NULL,NULL);
}

/************************************************************************/
//Method:	Shutdown
//Purpose:	Shuts down and releases Direct3D device, right now it have
//			a bit to many calls. Have to sort out what should be left
/************************************************************************/
void Direct3DWrapper::Shutdown(void)
{
	for(int i=0; i < m_lpTexture.size(); i++)
	{
		m_lpTexture.at(i)->Release();
	}
	
	m_lpTexture.clear();

	if(m_lpSprite != 0)
		m_lpSprite->Release();
	if ( m_lpd3dDevice != 0)
		m_lpd3dDevice->Release();
	if ( m_lpD3D_Object != 0)
		m_lpD3D_Object->Release();
}

LPDIRECT3DTEXTURE9 Direct3DWrapper::lpGet_Texture(int iID)
{
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
}
