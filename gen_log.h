// genereic log
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
#include <ddraw.h>

template <class ALog=int> class gen_log
{
	ALog data_;
	std::string text_;
	ofstream output_file;
	char t[256], d[256];
public:
	gen_log()
	{
		output_file.open("c++log.txt");
		output_file << "Log file started on " <<  _strdate( d ) << " at " << _strtime( t ) << endl;
		output_file.close();
		output_file.open("c++memlog.txt");
		output_file << "Memory Alloc / Dealloc Log file started on " << _strdate( d ) << " at " << _strtime( t ) << endl;
		output_file.close();
	}

	void Rectum(RECT r)
	{
		output_file.open("c++log.txt",ios::app);
		output_file << r.bottom << " " << r.left << " " << r.right << " " << r.top << endl;
		output_file.close();
	}

	void it(ALog mess)
	{
		output_file.open("c++log.txt",ios::app);
		output_file << __FILE__ << __LINE__ << " " << mess << " on " << _strdate( d ) << " at " << _strtime( t ) << endl;
		output_file.close();
	}

	void mit(ALog mess)
	{
		output_file.open("c++memlog.txt",ios::app);
		output_file << __FILE__ << __LINE__ << " " << mess << " on " << _strdate( d ) << " at " << _strtime( t ) << endl;
		output_file.close();
	}

	char* DDErrorString(HRESULT hr)
	{
		switch (hr)
		{
			case DD_OK:									return "DD_OK";
			case DDERR_ALREADYINITIALIZED:				return "DDERR_ALREADYINITIALIZED";
			case DDERR_BLTFASTCANTCLIP:					return "DDERR_BLTFASTCANTCLIP";
			case DDERR_CANNOTATTACHSURFACE:				return "DDERR_CANNOTATTACHSURFACE";
			case DDERR_CANNOTDETACHSURFACE:				return "DDERR_CANNOTDETACHSURFACE";
			case DDERR_CANTCREATEDC:					return "DDERR_CANTCREATEDC";
			case DDERR_CANTDUPLICATE:					return "DDERR_CANTDUPLICATE";
			case DDERR_CANTLOCKSURFACE:					return "DDERR_CANTLOCKSURFACE";
			case DDERR_CANTPAGELOCK:					return "DDERR_CANTPAGELOCK";
			case DDERR_CANTPAGEUNLOCK:					return "DDERR_CANTPAGEUNLOCK";
			case DDERR_CLIPPERISUSINGHWND:				return "DDERR_CLIPPERISUSINGHWND";
			case DDERR_COLORKEYNOTSET:					return "DDERR_COLORKEYNOTSET";
			case DDERR_CURRENTLYNOTAVAIL:				return "DDERR_CURRENTLYNOTAVAIL";
			case DDERR_DDSCAPSCOMPLEXREQUIRED:			return "DDERR_DDSCAPSCOMPLEXREQUIRED";
			case DDERR_DCALREADYCREATED:				return "DDERR_DCALREADYCREATED";
			case DDERR_DEVICEDOESNTOWNSURFACE:			return "DDERR_DEVICEDOESNTOWNSURFACE";
			case DDERR_DIRECTDRAWALREADYCREATED:		return "DDERR_DIRECTDRAWALREADYCREATED";
			case DDERR_EXCEPTION:						return "DDERR_EXCEPTION";
			case DDERR_EXCLUSIVEMODEALREADYSET:			return "DDERR_EXCLUSIVEMODEALREADYSET";
			case DDERR_EXPIRED:							return "DDERR_EXPIRED";
			case DDERR_GENERIC:							return "DDERR_GENERIC";
			case DDERR_HEIGHTALIGN:						return "DDERR_HEIGHTALIGN";
			case DDERR_HWNDALREADYSET:					return "DDERR_HWNDALREADYSET";
			case DDERR_HWNDSUBCLASSED:					return "DDERR_HWNDSUBCLASSED";
			case DDERR_IMPLICITLYCREATED:				return "DDERR_IMPLICITLYCREATED";
			case DDERR_INCOMPATIBLEPRIMARY:				return "DDERR_INCOMPATIBLEPRIMARY";
			case DDERR_INVALIDCAPS:						return "DDERR_INVALIDCAPS";
			case DDERR_INVALIDCLIPLIST:					return "DDERR_INVALIDCLIPLIST";
			case DDERR_INVALIDDIRECTDRAWGUID:			return "DDERR_INVALIDDIRECTDRAWGUID";
			case DDERR_INVALIDMODE:						return "DDERR_INVALIDMODE";
			case DDERR_INVALIDOBJECT:					return "DDERR_INVALIDOBJECT";
			case DDERR_INVALIDPARAMS:					return "DDERR_INVALIDPARAMS";
			case DDERR_INVALIDPIXELFORMAT:				return "DDERR_INVALIDPIXELFORMAT";
			case DDERR_INVALIDPOSITION:					return "DDERR_INVALIDPOSITION";
			case DDERR_INVALIDRECT:						return "DDERR_INVALIDRECT";
			case DDERR_INVALIDSTREAM:					return "DDERR_INVALIDSTREAM";
			case DDERR_INVALIDSURFACETYPE:				return "DDERR_INVALIDSURFACETYPE";
			case DDERR_LOCKEDSURFACES:					return "DDERR_LOCKEDSURFACES";
			case DDERR_MOREDATA:						return "DDERR_MOREDATA";
			case DDERR_NEWMODE:							return "DDERR_NEWMODE";
			case DDERR_NO3D:							return "DDERR_NO3D";
			case DDERR_NOALPHAHW:						return "DDERR_NOALPHAHW";
			case DDERR_NOBLTHW:							return "DDERR_NOBLTHW";
			case DDERR_NOCLIPLIST:						return "DDERR_NOCLIPLIST";
			case DDERR_NOCLIPPERATTACHED:				return "DDERR_NOCLIPPERATTACHED";
			case DDERR_NOCOLORCONVHW:					return "DDERR_NOCOLORCONVHW";
			case DDERR_NOCOLORKEY:						return "DDERR_NOCOLORKEY";
			case DDERR_NOCOLORKEYHW:					return "DDERR_NOCOLORKEYHW";
			case DDERR_NOCOOPERATIVELEVELSET:			return "DDERR_NOCOOPERATIVELEVELSET";
			case DDERR_NODC:							return "DDERR_NODC";
			case DDERR_NODDROPSHW:						return "DDERR_NODDROPSHW";
			case DDERR_NODIRECTDRAWHW:					return "DDERR_NODIRECTDRAWHW";
			case DDERR_NODIRECTDRAWSUPPORT:				return "DDERR_NODIRECTDRAWSUPPORT";
			case DDERR_NODRIVERSUPPORT:					return "DDERR_NODRIVERSUPPORT";
			case DDERR_NOEMULATION:						return "DDERR_NOEMULATION";
			case DDERR_NOEXCLUSIVEMODE:					return "DDERR_NOEXCLUSIVEMODE";
			case DDERR_NOFLIPHW:						return "DDERR_NOFLIPHW";
			case DDERR_NOFOCUSWINDOW:					return "DDERR_NOFOCUSWINDOW";
			case DDERR_NOGDI:							return "DDERR_NOGDI";
			case DDERR_NOHWND:							return "DDERR_NOHWND";
			case DDERR_NOMIPMAPHW:						return "DDERR_NOMIPMAPHW";
			case DDERR_NOMIRRORHW:						return "DDERR_NOMIRRORHW";
			case DDERR_NOMONITORINFORMATION:			return "DDERR_NOMONITORINFORMATION";
			case DDERR_NONONLOCALVIDMEM:				return "DDERR_NONONLOCALVIDMEM";
			case DDERR_NOOPTIMIZEHW:					return "DDERR_NOOPTIMIZEHW";
			case DDERR_NOOVERLAYDEST:					return "DDERR_NOOVERLAYDEST";
			case DDERR_NOOVERLAYHW:						return "DDERR_NOOVERLAYHW";
			case DDERR_NOPALETTEATTACHED:				return "DDERR_NOPALETTEATTACHED";
			case DDERR_NOPALETTEHW:						return "DDERR_NOPALETTEHW";
			case DDERR_NORASTEROPHW:					return "DDERR_NORASTEROPHW";
			case DDERR_NOROTATIONHW:					return "DDERR_NOROTATIONHW";
			case DDERR_NOSTEREOHARDWARE:				return "DDERR_NOSTEREOHARDWARE";
			case DDERR_NOSTRETCHHW:						return "DDERR_NOSTRETCHHW";
			case DDERR_NOSURFACELEFT:					return "DDERR_NOSURFACELEFT";
			case DDERR_NOT4BITCOLOR:					return "DDERR_NOT4BITCOLOR";
			case DDERR_NOT4BITCOLORINDEX:				return "DDERR_NOT4BITCOLORINDEX";
			case DDERR_NOT8BITCOLOR:					return "DDERR_NOT8BITCOLOR";
			case DDERR_NOTAOVERLAYSURFACE:				return "DDERR_NOTAOVERLAYSURFACE";
			case DDERR_NOTEXTUREHW:						return "DDERR_NOTEXTUREHW";
			case DDERR_NOTFLIPPABLE:					return "DDERR_NOTFLIPPABLE";
			case DDERR_NOTFOUND:						return "DDERR_NOTFOUND";
			case DDERR_NOTINITIALIZED:					return "DDERR_NOTINITIALIZED";
			case DDERR_NOTLOADED:						return "DDERR_NOTLOADED";
			case DDERR_NOTLOCKED:						return "DDERR_NOTLOCKED";
			case DDERR_NOTPAGELOCKED:					return "DDERR_NOTPAGELOCKED";
			case DDERR_NOTPALETTIZED:					return "DDERR_NOTPALETTIZED";
			case DDERR_NOVSYNCHW:						return "DDERR_NOVSYNCHW";
			case DDERR_NOZBUFFERHW:						return "DDERR_NOZBUFFERHW";
			case DDERR_NOZOVERLAYHW:					return "DDERR_NOZOVERLAYHW";
			case DDERR_OUTOFCAPS:						return "DDERR_OUTOFCAPS";
			case DDERR_OUTOFMEMORY:						return "DDERR_OUTOFMEMORY";
			case DDERR_OUTOFVIDEOMEMORY:				return "DDERR_OUTOFVIDEOMEMORY";
			case DDERR_OVERLAPPINGRECTS:				return "DDERR_OVERLAPPINGRECTS";
			case DDERR_OVERLAYCANTCLIP:					return "DDERR_OVERLAYCANTCLIP";
			case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:	return "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
			case DDERR_OVERLAYNOTVISIBLE:				return "DDERR_OVERLAYNOTVISIBLE";
			case DDERR_PALETTEBUSY:						return "DDERR_PALETTEBUSY";
			case DDERR_PRIMARYSURFACEALREADYEXISTS:		return "DDERR_PRIMARYSURFACEALREADYEXISTS";
			case DDERR_REGIONTOOSMALL:					return "DDERR_REGIONTOOSMALL";
			case DDERR_SURFACEALREADYATTACHED:			return "DDERR_SURFACEALREADYATTACHED";
			case DDERR_SURFACEALREADYDEPENDENT:			return "DDERR_SURFACEALREADYDEPENDENT";
			case DDERR_SURFACEBUSY:						return "DDERR_SURFACEBUSY";
			case DDERR_SURFACEISOBSCURED:				return "DDERR_SURFACEISOBSCURED";
			case DDERR_SURFACELOST:						return "DDERR_SURFACELOST";
			case DDERR_SURFACENOTATTACHED:				return "DDERR_SURFACENOTATTACHED";
			case DDERR_TESTFINISHED:					return "DDERR_TESTFINISHED";
			case DDERR_TOOBIGHEIGHT:					return "DDERR_TOOBIGHEIGHT";
			case DDERR_TOOBIGSIZE:						return "DDERR_TOOBIGSIZE";
			case DDERR_TOOBIGWIDTH:						return "DDERR_TOOBIGWIDTH";
			case DDERR_UNSUPPORTED:						return "DDERR_UNSUPPORTED";
			case DDERR_UNSUPPORTEDFORMAT:				return "DDERR_UNSUPPORTEDFORMAT";
			case DDERR_UNSUPPORTEDMASK:					return "DDERR_UNSUPPORTEDMASK";
			case DDERR_UNSUPPORTEDMODE:					return "DDERR_UNSUPPORTEDMODE";
			case DDERR_VERTICALBLANKINPROGRESS:			return "DDERR_VERTICALBLANKINPROGRESS";
			case DDERR_VIDEONOTACTIVE:					return "DDERR_VIDEONOTACTIVE";
			case DDERR_WASSTILLDRAWING:					return "DDERR_WASSTILLDRAWING";
			case DDERR_WRONGMODE:						return "DDERR_WRONGMODE";
			case DDERR_XALIGN:							return "DDERR_XALIGN";
		}
		
		return "Unknown Error";
	}
	~gen_log()
	{
	};
};