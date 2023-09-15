

#ifndef HINS_LE_DRIVER_H
#define HINS_LE_DRIVER_H

#include <string>
#include <vector>
#include <map>


#include "Comm/pattern_thread.h"

#include "sensor/hins_le/connection_address.h"
#include "sensor/hins_le/hins/protoc.h"

using namespace hins;
namespace hins
{
	class XingSongDriver;
}
class hins_le_driver
{
public:
    //! Initialize driver
    hins_le_driver();

    //! Cleanly disconnect in case of destruction
    ~hins_le_driver();

	bool init(std::string str_ip);
	void bind_pub( boost::function<void (float* range, unsigned int* intensity, int d_size)> fnc_pub_data);

	bool fnc_check();

    bool connect();

    //! Disconnect from the laserscanner and reset internal state
    void disconnect();

    //! Return connection status
    bool isConnected() {return is_connected_; }

	bool require_scan();

	
private:

	boost::function<void (float* range, unsigned int* intensity, int d_size)> fnc_pub_data_;

	float* f_range_;
	unsigned int* i_amplitude_;
	int i_size_;

	bool init_transfer_device();

	


	bool is_connected_;

private:
	//pattern_thread th_read_;
	


	
private:

	hins::XingSongDriver* p_xingsong_;

	std::string str_laser_ip_;
	int i_laser_port_;

	ConnectionAddress laser_conn_info_;
	XingSongLaserParam laser_param_;
	ShadowsFilterParam shadows_filter_param_;
	DisturbFilterParam disturb_filter_param_;

	HSGetAreaDataPackage command_;
};



#endif // HINS_LE_DRIVER_H
