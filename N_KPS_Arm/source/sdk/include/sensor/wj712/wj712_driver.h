

#ifndef WJ712_DRIVER_H
#define WJ712_DRIVER_H

#include <string>
#include <vector>
#include <map>

#include "trans_dev/trans_dev.h"
#include "Comm/pattern_thread.h"

namespace wj_lidar{
	class wj_712_lidar_protocol;

}

class wj712_driver
{
public:
    //! Initialize driver
    wj712_driver();

    //! Cleanly disconnect in case of destruction
    ~wj712_driver();

	bool init(std::string str_ip, bool b_wj712_7200);
	void bind_pub( boost::function<void (float* range, float* intensity, int d_size)> fnc_pub_data);

    bool connect(const std::string hostname, int port = 2110 );

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
	//wj_712_lidar::wj_712_lidarConfig config_;
	wj_lidar::wj_712_lidar_protocol* protocol_;


};


#endif // WJ712_DRIVER_H
