#include "Notifiable.h"

class CStateMachine
{
public:
	
	void InitState(Notifiable* pNewState) 
	{
		pNewState->Enter();
		m_pnState = pNewState; 
	}

	void ChangeState(Notifiable* pNewState)
	{
		assert (m_pnState && pNewState);
		m_pnState->Exit();
		m_pnState = pNewState;
		m_pnState->Enter();		
	};

	void Update()
	{
		if(m_pnState)
		{
			m_pnState->Execute();
		}
	};

private:
	Notifiable* m_pnState;
};