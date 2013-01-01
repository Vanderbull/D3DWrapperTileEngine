#include "Notifiable.h"
class CButton
{
public:
    void click() 
	{ 
		if (m_pnOnClick) m_pnOnClick->notify(); 
	}
    void onClick(Notifiable* pn) 
	{ 
		m_pnOnClick = pn; 
	}
	void clickC(Notifiable* pn)
	{
		m_pnOnClick = pn;
		if (m_pnOnClick) m_pnOnClick->notify(); 
	}
private:
    Notifiable* m_pnOnClick;
};