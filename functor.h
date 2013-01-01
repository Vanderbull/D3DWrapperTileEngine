//USAGE:
//PlayerAddStrengthNotifiable psn(&p);
//Buttoni addbutton;
//addbutton.onClick(&add_strength);
//mglayer mg;
//mglayNotifiable pn(&mg);
//CDStopNotifiable sn(&mg);
//Buttoni playButton;
//playButton.onClick(&pn);
//Buttoni stopButton;
//stopButton.onClick(&sn);
//stopButton.click();
#include <cassert>
#include "stacks.h"
#include "CStateMachine.h"
#include "Notifiable.h"
#include "CButton.h"
stacks stack_manager;

class CStateMachine;

class MenuGame
{
public:
	void play()
	{
		cout << "Playing the game" << endl;
	};
	void stop()
	{
		cout << "Stopping the Game" << endl;
	};
};

class MenuPlayNotifiable : public Notifiable
{
public:
    MenuPlayNotifiable(MenuGame* mg) : m_mg(mg) { }
    virtual void notify() { m_mg->play(); }
	virtual void Exit() {cout << "Exit MenuStopNotifiable" << endl; }
	virtual void Enter() { stack_manager.string_stack.push("Enter menu");cout << stack_manager.string_stack.top();cout << "Enter MenuPlayNotifiable" << endl; }
	virtual void Execute() { cout << "Execute MenuPlayNotifiable" << endl; }
private:
    MenuGame* m_mg;
};

class MenuStopNotifiable : public Notifiable
{
public:
    MenuStopNotifiable(MenuGame* mg) : m_mg(mg) { }
    virtual void notify() { m_mg->stop(); }
	virtual void Exit() { cout << "Exit MenuStopNotifiable" << endl; }
	virtual void Enter() { cout << "Enter MenuStopNotifiable" << endl; }
	virtual void Execute() { cout << "Execute MenuStopNotifiable" << endl; }
private:
    MenuGame* m_mg;
};

CStateMachine StateMachine;
MenuGame menu;
MenuPlayNotifiable Play_trigger(&menu);
MenuStopNotifiable Stop_trigger(&menu);
CButton PlayButton;
CButton StopButton;