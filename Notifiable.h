#ifndef H_NOT
#define H_NOT
class Notifiable
{
public:
    virtual void notify() = 0;
	virtual void Exit() = 0;
	virtual void Enter() = 0;
	virtual void Execute() = 0;
};
#endif