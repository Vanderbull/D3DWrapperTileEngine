#include "CFont.h"
class CStatus
{
public:
	CStatus()
	{

	};
	~CStatus(){};

	void Print(int iPlayer_id)
	{
		cFont.Print(WIDTH-64,HEIGHT-256,"Adam");
		cFont.PrintInt(WIDTH-64,HEIGHT-192,100);
		cFont.Print(WIDTH-64,HEIGHT-128,"Blocker");
		cFont.PrintInt(WIDTH-64,HEIGHT-64,iPlayer_id);
	}
};

CStatus cStatus[16];