class CMouse
{
public:
	CMouse()
	{

	};
	~CMouse(){};

	bool Set_position(LPARAM lParam)
	{
		pt.x = (LONG) LOWORD(lParam); 
		pt.y = (LONG) HIWORD(lParam);
		return true;
	}
	
	bool Set_pSnap_pt(unsigned int iTile_size)
	{
		pSnap_pt.x=((pt.x+iTile_size/2)/iTile_size)*iTile_size;  //take advantage of integer division truncation
		pSnap_pt.y=((pt.y+iTile_size/2)/iTile_size)*iTile_size;

		if( pSnap_pt.x < 0 )
		{
			pSnap_pt.x = 0;
		}
		if( pSnap_pt.x > TILE_SIZE*14 )
		{
			pSnap_pt.x = TILE_SIZE*14;
		}
		if( pSnap_pt.y < 0 )
		{
			pSnap_pt.y = 0;
		}
		if( pSnap_pt.y > TILE_SIZE*14 ) // here there should occure some kind of scrolling action
		{
			pSnap_pt.y = TILE_SIZE*14;
		}
		hrgn = CreateRectRgn(pSnap_pt.x,pSnap_pt.y,pSnap_pt.x + iTile_size,pSnap_pt.y+iTile_size);
		return true;
	}

	POINT pt;
	POINT pSnap_pt;
	HRGN hrgn;
};

CMouse cMouse;