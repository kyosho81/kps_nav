

#ifndef WJ719_DRIVER_H
#define WJ719_DRIVER_H

#include <string>
#include <vector>
#include <map>


#include "Comm/pattern_thread.h"


namespace wj_lidar{
	class vanjee_719_lidar_protocol;
}
class Async_Client9;
class udp_driver;

class wj719_driver
{
public:
    //! Initialize driver
    wj719_driver();

    //! Cleanly disconnect in case of destruction
    ~wj719_driver();

	bool init(std::string str_ip, bool b_wj719_10800);
	void bind_pub( boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data);

	bool fnc_check();

    bool connect();

    //! Disconnect from the laserscanner and reset internal state
    void disconnect();

    //! Return connection status
    bool isConnected() {return is_connected_; }

	void require_scan();

  

private:


	bool init_transfer_device();

	


	bool is_connected_;

private:
	//pattern_thread th_read_;
	


	
private:

	//wj_lidar::wj_712_lidar_protocol* protocol_;
	std::string str_laser_ip_;
	std::string str_host_ip_;
	int i_laser_port_;
	int i_host_port_;

	wj_lidar::vanjee_719_lidar_protocol *protocol_net_;
	Async_Client9* tcp_drv_;
	udp_driver* udp_drv_;
	int communication_mode_;
	
	uint8_t XOR_check(uint8_t *Buf,uint8_t start,uint8_t end,uint8_t len);
};



#endif // WJ719_DRIVER_H
