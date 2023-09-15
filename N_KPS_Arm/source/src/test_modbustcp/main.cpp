
#include <stdlib.h>
#include "Comm/Rand.hpp"

#include "trans_dev.h"
#include "Comm.h"
#include <iostream>
#include <fstream>

//

#include "trans_dev/modbus_tcp.h"

int main(int argc, char *argv[])
{
	
	modbus_tcp_clt* p_modbus_tcp_clt = new modbus_tcp_clt();
	p_modbus_tcp_clt->init("127.0.0.1",9000);

	while(1){
		SDI sdi;
		U16 add = 0x0000;
		U16 count = 8;
		p_modbus_tcp_clt->read_coil(sdi,add,count);
		SLEEP(1000);
		
		SDO sdo;
		memset(&sdo,0,sizeof(SDO));
		for (int i = 0 ; i < 8 ; ++i){
			sdo.id_[i] = i;
			sdo.do_[i] = i;
			sdo.used_++;
		}
		p_modbus_tcp_clt->write_mut_coil(add,sdo);
		SLEEP(1000);

		add = 0x1000;
		SAO sao;
		memset(&sao,0,sizeof(SAO));
		for (int i = 0 ; i < 8 ; ++i){
			sao.id_[i] = i;
			sao.ao_[i] = i + 0xff;
			sao.used_++;
		}
		p_modbus_tcp_clt->write_mut_reg(add,sao);
		SLEEP(1000);

		add = 0x2000;
		SAI sai;
		memset(&sai,0,sizeof(SAI));
		p_modbus_tcp_clt->read_holding_reg(sai,add,8);
		
	}
}

