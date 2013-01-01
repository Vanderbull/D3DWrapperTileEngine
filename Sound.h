//*******************************************************************
//* Namn: Rickard Skeppström
//* Personnr: 790930-xxxx
//* Klass: SP6
//* E-mail: rickard_skeppstrom@msn.com alt rickard.skeppstrom@powerhouse.net
//* Lab: Direct 3D wrapper
//*******************************************************************/

//#include "WaveDecoder.h"
#include <dsound.h>
#include <string>
#include <vector>

#include "dsutil.h"

using namespace std;


#define DSVOLUME_TO_DB(volume) ((DWORD)(-30*(100 - volume)))

class DSound
{
public:
	~DSound(void);

	// Pretty Singleton
	static DSound& getInstance() { static DSound pInstance; return pInstance;}

	// Methods for Creating and initiating a Direct3D device
	bool DSound_Create(int rate, int bits, int stereo);
	bool DSound_Init(HWND wndHandle);
	bool DSound_Lock(CWaveFile* wavFile);
	bool DSound_Play(int id);
	bool DSound_Stop(int id);
	bool DSound_ChangeVolume(int db, int id);
	bool DSound_ChangeFrequency(DWORD frequency);
	bool DSound_Unlock();
	bool DSound_Shutdown();

	bool LoadWaveToSoundBuffer(std::string wavFilename);

	int count_calls()
	{
		static int calls=0;
		return calls++;
	}

private:
	DSound(void);

	LPDIRECTSOUND8	m_lpSound;	//Directsound interface pointer

	LPDIRECTSOUNDBUFFER8 apDSBuffer[128];
	VOID*   pDSLockedBuffer; // Pointer to locked buffer memory
    DWORD   dwDSLockedBufferSize;    // Size of the locked DirectSound buffer
    DWORD   dwWavDataRead;    // Amount of data read from the wav file 

	CWaveFile *wavFile;

	DSBUFFERDESC dsbd;

	LPDIRECTSOUNDBUFFER	m_lpSoundBuffer; // Where the music file info will end up

	DSBUFFERDESC m_SoundBufferDesc;

	WAVEFORMATEX	m_SoundFormatDesc;

	int sound_id;
};