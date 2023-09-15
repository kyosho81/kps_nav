
#include <signal.h>


#include <iostream>
#include <fstream>
//#include <unistd.h>

#include <string>
#include <cassert>
#include "Comm.h"

#include "bag/bag.h"

bool brun = true; 


int main(int argc, char *argv[])
{
	cbag cb;
	std::string str_path;
	if ( argc > 1 ){
		str_path = argv[1];
	}
	F32 min_x = 0;
	F32 min_y = 0;
	F32 max_x = 0;
	F32 max_y = 0;
	SBAG sbg;
	while (cb.load_Bag(str_path,sbg)){
		min_x = cComm::Min( min_x, sbg.odom.x_);
		min_y = cComm::Min( min_y, sbg.odom.y_);
		max_x = cComm::Min( max_x, sbg.odom.x_);
		max_y = cComm::Min( max_y, sbg.odom.y_);
		
	}
	F32 dx = (max_x - min_x)/2;
	F32 dy = (max_y - min_y)/2;

	cbag cb2;
	while (cb.load_Bag(str_path,sbg)){
		sbg.odom.x_ = sbg.odom.x_ - dx;
		sbg.odom.y_ = sbg.odom.y_ - dy;
		cb2.save_one(sbg);
	}
	cb2.over();
}
