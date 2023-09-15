
#include <signal.h>


#include <iostream>
#include <fstream>
//#include <unistd.h>

#include <string>
#include <cassert>
#include "Comm.h"


#include "Comm/gpio.h"

bool brun = true; 

gpio g_gpio ;

// A = 32*0 + pin(12)
// B = 32*1 
// C = 32*2 
// D = 32*3

#define GPIOA 32*0
#define GPIOB 32*1
#define GPIOC 32*2
#define GPIOD 32*3

#define DO1 GPIOB+8   //p1.4  GPIOB8  io:40
#define DO2 GPIOC+17  //p1.6  GPIOC17 io:81
#define DO3 GPIOB+24  //p1.20 GPIOB24 io:56
#define DO4 GPIOC+10  //p1.22 GPIOC10 io:74

#define DI01 GPIOB+30 //p1.27 GPIOB30 io:62
#define DI02 GPIOC+15 //p1.29 GPIOC15 io:79
#define DI03 GPIOB+31 //p1.31 GPIOB31 io:63
#define DI04 GPIOD+1  //p1.33 GPIOD1  io:97
#define DI05 GPIOC+13 //p1.35 GPIOC13 io:77
#define DI06 GPIOB+18 //p1.32 GPIOB18 io:50
#define DI07 GPIOC+16 //p1.30 GPIOC16 io:80
#define DI08 GPIOC+9  //p1.28 GPIOC9  io:73
#define DI09 GPIOC+12 //p1.26 GPIOC12 io:76
#define DI10 GPIOC+11 //p1.24 GPIOC11 io:75

void test_do_gpio(){

	//g_gpio.export_gpio(GPIOC12,true);
	//g_gpio.export_gpio(GPIOC9,true);
	//g_gpio.export_gpio(GPIOC16,true);

	for(int i = 0 ; i < 100 ; ++i){
	    g_gpio.set_gpio_on(DO2);
	    SLEEP(500);
	    g_gpio.set_gpio_off(DO2);
	    SLEEP(500);

	    g_gpio.set_gpio_on(DO3);
	    SLEEP(500);
	    g_gpio.set_gpio_off(DO3);
	    SLEEP(500);


	    g_gpio.set_gpio_on(DO4);
	    SLEEP(500);
	    g_gpio.set_gpio_off(DO4);
	    SLEEP(500);
	}
	

	//g_gpio.unexport_gpio(GPIOC12);
	//g_gpio.unexport_gpio(GPIOC9 );
	//g_gpio.unexport_gpio(GPIOC16);
	//exit(0);


}
void test_di_gpio(){


	g_gpio.export_gpio(74,false);
	int value = g_gpio.get_gpio(74);
	printf("get di:%d value:%d \n",74,value);
	g_gpio.unexport_gpio(74);

}

#define REBOOT_PIN 222

int main(int argc, char *argv[])
{
	test_do_gpio();
	
}
