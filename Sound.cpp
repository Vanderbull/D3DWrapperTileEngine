/*******************************************************************
* Namn: Rickard Skeppström
* Personnr: 790930-xxxx
* Klass: SP6
* E-mail: rickard_skeppstrom@msn.com alt rickard.skeppstrom@powerhouse.net
* Lab: DSound wrapper
*******************************************************************/

#include ".\Sound.h"

/************************************************************************/
//Method:	DSound(void)
//Finished:	[]
//Purpose:	Initialize everything to a default state
/************************************************************************/
DSound::DSound(void)
{
 	ZeroMemory(&m_SoundFormatDesc, sizeof(m_SoundFormatDesc));

	m_SoundFormatDesc.cbSize			= 0;
	m_SoundFormatDesc.nAvgBytesPerSec	= m_SoundFormatDesc.nSamplesPerSec * m_SoundFormatDesc.nBlockAlign;
	m_SoundFormatDesc.nBlockAlign		= 1;
	m_SoundFormatDesc.nChannels			= 1;
	m_SoundFormatDesc.nSamplesPerSec	= 11025;
	m_SoundFormatDesc.wBitsPerSample	= 8;
	m_SoundFormatDesc.wFormatTag		= WAVE_FORMAT_PCM;

	
	m_SoundBufferDesc.dwBufferBytes		= 22050;
	m_SoundBufferDesc.dwFlags			= DSBCAPS_CTRLFREQUENCY | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	m_SoundBufferDesc.dwReserved		= 0;
	m_SoundBufferDesc.dwSize			= sizeof(m_SoundBufferDesc);
	m_SoundBufferDesc.lpwfxFormat		= &m_SoundFormatDesc;
}

/************************************************************************/
//Method:	~DSound()
//Finished:	[]
//Purpose:	
/************************************************************************/
DSound::~DSound()
{
	DSound_Shutdown();
}

/************************************************************************/
//Method:	DSound_Create()
//Finished:	[]
//Purpose:	
/************************************************************************/
bool DSound::DSound_Create(int rate, int bits, int channels)
{
	m_SoundFormatDesc.cbSize			= 0;
	m_SoundFormatDesc.nAvgBytesPerSec	= m_SoundFormatDesc.nSamplesPerSec * m_SoundFormatDesc.nBlockAlign;
	m_SoundFormatDesc.nBlockAlign		= 1;
	m_SoundFormatDesc.nChannels			= channels;
	m_SoundFormatDesc.nSamplesPerSec	= rate;
	m_SoundFormatDesc.wBitsPerSample	= bits;
	m_SoundFormatDesc.wFormatTag		= WAVE_FORMAT_PCM;

	CoInitialize(0);

	if(DirectSoundCreate8(0,&m_lpSound, 0) != DS_OK )
	{
		MessageBox(0,"DirectSoundCreate", "Error", MB_OK);
		return false;
	}
	else
	{
		return true;
	}
}

/************************************************************************/
//Method:	DSound_Init()
//Finished:	[]
//Purpose:	
/************************************************************************/
bool DSound::DSound_Init(HWND wndHandle)
{
	if(m_lpSound->SetCooperativeLevel(wndHandle,DSSCL_NORMAL) != DS_OK)
	{
		MessageBox(0,"SetCooperation level", "Error", MB_OK);
		return false;
	}
	else
	{
		return true;
	}
}

/************************************************************************/
//Method:	LoadWaveToSoundBuffer(std::string wavFilename, int ID)
//Finished:	[]
//Purpose:	Loading a file from disk into buffer
/************************************************************************/
bool DSound::LoadWaveToSoundBuffer(std::string wavFilename)
{
	sound_id = count_calls();

	wavFile = new CWaveFile();
	wavFile->Open((char*)wavFilename.c_str(), 0, WAVEFILE_READ );

	if( wavFile->GetSize() == 0 )
	{
		MessageBox(0, "Invalid file", "Error", MB_OK);
		return false;
	}

	ZeroMemory(&m_SoundBufferDesc, sizeof(m_SoundBufferDesc));

	ZeroMemory( &m_SoundBufferDesc, sizeof(DSBUFFERDESC) );
	m_SoundBufferDesc.dwBufferBytes		= wavFile->GetSize();
	m_SoundBufferDesc.dwFlags			= //DSBCAPS_STICKYFOCUS |
										  DSBCAPS_CTRLVOLUME |
										  //DSBCAPS_CTRLPAN | 
										  DSBCAPS_CTRLFREQUENCY |
										  DSBCAPS_CTRLFX |
										  //DSBCAPS_STATIC | 
										  DSBCAPS_LOCSOFTWARE;
	m_SoundBufferDesc.dwReserved		= 0;
	m_SoundBufferDesc.dwSize			= sizeof(DSBUFFERDESC);
	m_SoundBufferDesc.guid3DAlgorithm	= GUID_NULL;
	m_SoundBufferDesc.lpwfxFormat		= wavFile->m_pwfx;

	LPDIRECTSOUNDBUFFER pTempBuffer = 0;
	HRESULT hr = m_lpSound->CreateSoundBuffer( &m_SoundBufferDesc, &pTempBuffer, 0 );
	if(FAILED(hr))
	{
		MessageBox(0,"Unable to create sound buffer", "ERROR", MB_OK);
	}

	pTempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&apDSBuffer[sound_id]);

	pTempBuffer->Release();

/*	for (int i=0; i < 128; i++)
	{
		if(m_lpSound->DuplicateSoundBuffer( m_lpSoundBuffer[0], &apDSBuffer[0] ) != DS_OK)
		{
				MessageBox(0,"Unable to create sound buffer", "ERROR", MB_OK);
		}
	}
*/
	DSound_Lock(wavFile);

    // Reset the wave file to the beginning
    if( FAILED(wavFile->ResetFile()) )
	{
		MessageBox(0,"Unable to reset the file to beginning","Error", MB_OK);
	}

	// Read the wave file
    if( FAILED(wavFile->Read( (BYTE*) pDSLockedBuffer,
                  dwDSLockedBufferSize, 
                  &dwWavDataRead) ) )
	{
		MessageBox(0,"Reading wavefile","Error", MB_OK);
		return false;
	}
	
	// Check to make sure the wav file is not empty
    if( dwWavDataRead == 0 )
    {
        // Wav is blank, so just fill with silence
        FillMemory( (BYTE*) pDSLockedBuffer, 
                    dwDSLockedBufferSize, 
                    (BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
    }
    else if( dwWavDataRead < dwDSLockedBufferSize )
    {
	    // Don't repeat the wav file, just fill in silence 
        FillMemory( (BYTE*) pDSLockedBuffer + dwWavDataRead, 
                   dwDSLockedBufferSize - dwWavDataRead, 
                   (BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
    }

	DSound_Unlock();

	// Clean up
	delete wavFile;

	return 0;
}
/************************************************************************/
//Method:	DSound_Lock()
//Finished:	[X]
//Purpose:	Locking the sound buffer
/************************************************************************/
bool DSound::DSound_Lock(CWaveFile* wavFile)
{
	if(apDSBuffer[sound_id] == 0)
	{
		return false;
	}
	if(apDSBuffer[sound_id]->Lock( 0, wavFile->GetSize(), &pDSLockedBuffer, &dwDSLockedBufferSize, 0, 0, 0L ) != DS_OK)
	{
		MessageBox(0,"Unable to lock the buffer", "ERROR", MB_OK);
		return false;
	}

	return true;
}

/************************************************************************/
//Method:	DSound_Unlock()
//Finished:	[]
//Purpose:	Unlocking the soundbuffer 
/************************************************************************/
bool DSound::DSound_Unlock()
{
    // Unlock the buffer, we don't need it anymore.
    if(apDSBuffer[sound_id]->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, 0, 0 ) != DS_OK)
	{
		MessageBox(0,"*Unable to stop the sound", "Error",MB_OK);
		return false;
	}

	return true;
}

/************************************************************************/
//Method:	DSound_Play()
//Finished:	[]
//Purpose:	Playing the sound
/************************************************************************/
bool DSound::DSound_Play(int id)
{
  // Describe the effect.
  DSEFFECTDESC dsEffect;
  memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
  dsEffect.dwSize = sizeof(DSEFFECTDESC);
  dsEffect.dwFlags = 0;
  dsEffect.guidDSFXClass = GUID_DSFX_STANDARD_ECHO;

  LPDIRECTSOUNDBUFFER8 pBuffer8;
  apDSBuffer[id]->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer8);

  pBuffer8->SetFX(1, &dsEffect, 0);

  pBuffer8->Release();

	if( ( apDSBuffer[id]->Play(0,0,DSBPLAY_LOOPING) != DS_OK) )
	{
		MessageBox(0,"Unable to play sound", "Error",MB_OK);
		return false;
	}
	else
	{
		apDSBuffer[id]->Play(0,0,DSBPLAY_LOOPING);
		return true;
	}
}

/************************************************************************/
//Method:	DSound_Stop()
//Finished:	[]
//Purpose:	Stop the sound playing
/************************************************************************/
bool DSound::DSound_Stop(int id)
{
	if( ( apDSBuffer[id]->Stop() != DS_OK) )
	{
		MessageBox(0,"Unable to stop sound", "Error",MB_OK);
		return false;
	}
	else
	{
		apDSBuffer[id]->Stop();
		return true;
	}
}

/************************************************************************/
//Method:	DSound_ChangeVolume()
//Finished:	[]
//Purpose:	Change the volume of the sound
/************************************************************************/
bool DSound::DSound_ChangeVolume(int db, int id)
{
	if(!(apDSBuffer[id]->SetVolume(DSVOLUME_TO_DB(db))))
	{
		MessageBox(0,"Unable to change volume", "Error",MB_OK);
		return false;
	}
	else
	{
		return true;
	}
}

/************************************************************************/
//Method:	DSound_ChangeFrequency(DWORD frequency)
//Finished:	[]
//Purpose:	Change the frequency of the sound
/************************************************************************/
bool DSound::DSound_ChangeFrequency(DWORD frequency)
{
	if(frequency < 100 || frequency > 100000)
	{
		MessageBox(0,"Frequency to high or to low", "Error",MB_OK);
		return false;
	}
	else
	{
		apDSBuffer[sound_id]->SetFrequency(frequency);
	}

	return true;
}


/************************************************************************/
//Method:	DSound_Shutdown()
//Finished:	[]
//Purpose:	Release everything that have been allocated during run
/************************************************************************/
bool DSound::DSound_Shutdown()
{
	if(m_lpSound != 0)
	{
		m_lpSound->Release();
		m_lpSound = 0;
	}

	return true;
}