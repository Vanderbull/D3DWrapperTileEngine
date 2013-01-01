#include <cassert>
#include "stacks.h"
#include "CStateMachine.h"
#include "Notifiable.h"
#include "CButton.h"
#include "CMenu.h"
stacks stack_manager;

class CStateMachine;

class MenuPlayNotifiable : public Notifiable
{
public:
    MenuPlayNotifiable(CMenu* mg) : m_mg(mg) {}
    virtual void notify() 
	{ 
		m_mg->play(); 
	}
	virtual void Exit() 
	{
		cout << "Exited Play mode" << endl; 
	}
	virtual void Enter() 
	{ 
		stack_manager.string_stack.push("Play");
		cout << "Entered Play mode" << endl; 
	}
	virtual void Execute() 
	{
		m_mg->play(); 
		cout << "Running in Play mode" << endl; 
	}
private:
    CMenu* m_mg;
};

class MenuOptionsNotifiable : public Notifiable
{
public:
	MenuOptionsNotifiable(CMenu* mg) : m_mg(mg) {}
	virtual void notify()
	{
	}
	virtual void Exit()
	{
	}
	virtual void Enter()
	{
	}
	virtual void Execute()
	{
		m_mg->stop();
	}
private:
	CMenu* m_mg;
};

class MenuCreditsNotifiable : public Notifiable
{
public:
	MenuCreditsNotifiable(CMenu* mg) : m_mg(mg) {}
	virtual void notify()
	{
	}
	virtual void Exit()
	{
	}
	virtual void Enter()
	{
	}
	virtual void Execute()
	{
		m_mg->stop();
	}
private:
	CMenu* m_mg;
};

class MenuCreatePlayerNotifiable : public Notifiable
{
public:
	MenuCreatePlayerNotifiable(CMenu* mg) : m_mg(mg) {}
	virtual void notify()
	{
	}
	virtual void Exit()
	{
	}
	virtual void Enter()
	{
	}
	virtual void Execute()
	{
		m_mg->stop();
	}
private:
	CMenu* m_mg;
};

class MenuStopNotifiable : public Notifiable
{
public:
    MenuStopNotifiable(CMenu* mg) : m_mg(mg) {}
    virtual void notify() 
	{ 
		m_mg->stop(); 
	}
	virtual void Exit() 
	{ 
		cout << "Exited Stop mode" << endl; 
	}
	virtual void Enter() 
	{ 
		cout << "Entered Stop mode" << endl; 
	}
	virtual void Execute() 
	{
		m_mg->stop(); 
		//cout << "Running in Stop mode" << endl; 
	}
private:
    CMenu* m_mg;
};

CStateMachine MenuStateMachine;
CMenu menu;
MenuPlayNotifiable Play_trigger(&menu);
MenuOptionsNotifiable Options_trigger(&menu);
MenuCreditsNotifiable Credits_trigger(&menu);
MenuCreatePlayerNotifiable CreatePlayer_trigger(&menu);
MenuStopNotifiable Stop_trigger(&menu);
CButton PlayButton;
CButton StopButton;
CButton OptionsButton;