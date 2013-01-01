class Button {
public:
	enum BState {
		  Pressed,
		  None,
		  Hoover,
		  Disabled,
		  Drag
	   };

   // Declare two constructors: a default constructor,
   //  and a constructor that sets the cardinal and
   //  suit value of the new card.
   Button();
   Button( int ButtonInit, BState BStateInit, RECT texcoords, LPD3DXSPRITE spr )
   {
	   ID = ButtonInit;
	   state = BStateInit;
	   cardinalValue = 0;
	   tex_clipped = texcoords;
	   d3dspt = spr;
   };

   // Get and Set functions.
   int   GetCardinal();          // Get cardinal value of card.
   int   SetCardinal();          // Set cardinal value of card.
   BState  GetBState()
   {
	   return state;
   };              // Get suit of card.
   void  SetBState(BState new_bstate)
   {
	   state = new_bstate;
   }; // Set suit of card.
   char *NameOf();               // Get string representation of card.
	// this draws a portion of the specified texture
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, float x, float y, int a)
	{
		D3DXVECTOR3 center(0.0f, 0.0f, 0.0f), position(x, y, 0.0f);
		d3dspt->Draw(texture, &tex_clipped, &center, &position, D3DCOLOR_ARGB(a,255, 255, 255));

		return;
	}
private:
	LPD3DXSPRITE d3dspt;
	
	BState  state;
	int cardinalValue;
	int ID;
	RECT tex_clipped;
};

// Define a postfix increment operator for Suit.
inline Button::BState operator++( Button::BState &rs, int ) {
   return rs = (Button::BState)(rs + 1);
}

// http://technet.microsoft.com/en-us/library/2dzy4k6e(VS.80).aspx