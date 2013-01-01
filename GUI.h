struct Texture
{
	int left,top,right,bottom;
};

struct widget 
{
	int what;
	int left,top,right,bottom;
	Texture* textures[4];
	int state;
};

class GUI {
public:
	enum GUIState {
		  Pressed,
		  None,
		  Hoover,
		  Disabled,
		  Drag
	   };

   GUI();
   GUI( int GUIInit, GUIState GUIStateInit, RECT texcoords )
   {
	   ID = GUIInit;
	   state = GUIStateInit;
	   UIObject = texcoords;
   };

   GUIState  GetGUIState()
   {
	   return state;
   };

   void  SetGUIState(GUIState new_bstate)
   {
	   state = new_bstate;
   };

   RECT GetLoc()
   {
	   return UIObject;
   };

   char *NameOf(){};
	   
private:

	RECT UIObject;
	GUIState  state;
	int ID;
};

// Define a postfix increment operator for Suit.
inline GUI::GUIState operator++( GUI::GUIState &rs, int ) {
   return rs = (GUI::GUIState)(rs + 1);
}

// http://technet.microsoft.com/en-us/library/2dzy4k6e(VS.80).aspx