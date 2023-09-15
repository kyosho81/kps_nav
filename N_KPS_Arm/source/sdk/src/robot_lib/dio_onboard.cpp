#include <string.h>
#include <iostream>

#include "Comm.h"
#include "msg_pump/msg_pump.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "trans_dev/trans_dev.h"
#include "log/log_client.h"
#include "Comm/gpio.h"
#include "robot/dio_strategy.h"
#include "robot/dio_manage.h"

#include "robot/dio_onboard.h"


// A = 32*0 
// B = 32*1 
// C = 32*2 
// D = 32*3
#define GPIO_A 32*0
#define GPIO_B 32*1
#define GPIO_C 32*2
#define GPIO_D 32*3

#define DI_ONBOARD_00  GPIO_B + 30 //GPIOB30
#define DI_ONBOARD_01  GPIO_C + 15 //GPIOC15
#define DI_ONBOARD_02  GPIO_B + 31 //GPIOB31
#define DI_ONBOARD_03  GPIO_D + 1  //GPIOD1
#define DI_ONBOARD_04  GPIO_C + 13 //GPIOC13
#define DI_ONBOARD_05  GPIO_B + 18 //GPIOB18
#define DI_ONBOARD_06  GPIO_C + 16 //GPIOC16
#define DI_ONBOARD_07  GPIO_C + 9  //GPIOC9
#define DI_ONBOARD_08  GPIO_C + 12 //GPIOC12
#define DI_ONBOARD_09  GPIO_C + 11 //GPIOC11

#define DO_ONBOARD_00  GPIO_B + 8  //GPIOB8
#define DO_ONBOARD_01  GPIO_C + 17 //GPIOC17
#define DO_ONBOARD_02  GPIO_B + 24 //GPIOB24
#define DO_ONBOARD_03  GPIO_C + 10 //GPIOC10


dio_onboard::dio_onboard()
{
	std::cout<<"dio_onboard"<<std::endl;
}

dio_onboard::~dio_onboard()
{

}
bool dio_onboard::init(){

	return true;
}


bool dio_onboard::do_in_out()
{
	//////DI
	
	SDI sdi;
	get_di(sdi);
	std::map<std::string,SDI> m_dev_sdi;
	m_dev_sdi[DIO_DEV_ONBOARD] = sdi;
	dio_strategy::pub_fnc_sdi(m_dev_sdi);

	//////DO
	std::map<std::string, SDOAO> m_do_ao;
	DIO_MANAGE.get_sdo_ao(m_do_ao);
	auto it = m_do_ao.find(DIO_DEV_ONBOARD);
	if ( it != m_do_ao.end() ){
		SDOAO &sdo_ao = it->second;
		for ( int i = 0 ; i < MAX_DO; ++i){
			if ( sdo_ao.do_[i] > 0 ){
				gpio_.set_gpio_on(i);
			}else{
				gpio_.set_gpio_off(i);
			}
		}
	}

	return true;
}

bool dio_onboard::get_di(SDI &sdi)
{
	memset(&sdi,0,sizeof(SDI));
	U8 value = 0;
	value = gpio_.get_gpio(DI_ONBOARD_00);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_00,value);
	value = gpio_.get_gpio(DI_ONBOARD_01);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_01,value);
	value = gpio_.get_gpio(DI_ONBOARD_02);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_02,value);
	value = gpio_.get_gpio(DI_ONBOARD_03);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_03,value);
	value = gpio_.get_gpio(DI_ONBOARD_04);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_04,value);
	value = gpio_.get_gpio(DI_ONBOARD_05);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_05,value);
	value = gpio_.get_gpio(DI_ONBOARD_06);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_06,value);
	value = gpio_.get_gpio(DI_ONBOARD_07);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_07,value);
	value = gpio_.get_gpio(DI_ONBOARD_08);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_08,value);
	value = gpio_.get_gpio(DI_ONBOARD_09);
	dio_strategy::set_sdi(sdi,DI_ONBOARD_09,value);

	return true;
}


