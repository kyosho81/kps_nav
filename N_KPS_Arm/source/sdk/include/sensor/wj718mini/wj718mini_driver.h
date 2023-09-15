

#ifndef WJ718_MINI_DRIVER_H
#define WJ718_MINI_DRIVER_H

#include <string>
#include <vector>
#include <map>

#include "trans_dev/trans_dev.h"
#include "Comm/pattern_thread.h"


namespace wj_lidar{
	class Vanjee718MiniLidarProtocol;
}


class wj718mini_driver
{
public:
    //! Initialize driver
    wj718mini_driver();

    //! Cleanly disconnect in case of destruction
    ~wj718mini_driver();

	bool init(std::string str_ip);
	void bind_pub( boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data);

	bool connect(const std::string hostname, int port = 6050 );

	//! Disconnect from the laserscanner and reset internal state
	void disconnect();

	//! Return connection status
	bool isConnected() {return is_connected_; }

	void require_scan();

  

private:

	bool init_transfer_device();

	std::string str_ip_;

	cTransferDevice* pTransferDevice_;
	cConnPara conn_para_;

	bool is_connected_;

private:

	pattern_thread th_read_;
	bool fnc_read();
	U8* uc_read_data_;
	int i_read_len_;

	
private:

	
	wj_lidar::Vanjee718MiniLidarProtocol *protocol_net_;


	uint8_t XOR_check(uint8_t *Buf,uint8_t start,uint8_t end,uint8_t len);
};



#endif // WJ718_MINI_DRIVER_H
