#ifndef _KEYBOARD_KYOSHO_20150909_
#define _KEYBOARD_KYOSHO_20150909_


#include <termios.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "MyDefine.h"

#define KEYCODE_W 0x77
#define KEYCODE_A 0x61
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64
#define KEYCODE_E 0x65
#define KEYCODE_L 0x6c

#define KEYCODE_Q 0x72

#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_W_CAP 0x57
#define KEYCODE_E_CAP 0x45
#define KEYCODE_L_CAP 0x4c

#define KEYCODE_Q_CAP 0x52

class keyboard
{
public:
	keyboard();
	~keyboard();

	bool keyboardLoop(double dt,F32 &x ,F32 &a,bool bstop);
	void close();
protected:
private:

	int kfd;
	struct termios cooked,raw;
	struct pollfd ufd;
	bool done;

	double walk_vel_;
	double run_vel_;
	double yaw_rate_;
	double yaw_rate_run_;

	double vx_tmp;
	double vw_tmp;

	bool dirty;
	int speed;
	int turn;


	F32 sx_;
	F32 sy_;
	F32 sa_;

	void init();


};


#endif//_KEYBOARD_KYOSHO_20150909_
