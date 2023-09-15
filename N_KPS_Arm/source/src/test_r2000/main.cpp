
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Acc.h"
#include "Comm/Rand.hpp"
#include "Comm.h"
#include "Comm/MyDefine.h"

#include "Comm/tollage.h"
#include "Comm/file.h"
#include "sensor/R2000/r2000_driver.h"
#include "sensor/laser_filter/laser_filter_ex.h"

pepperl_fuchs::R2000Driver* driver_ = 0;
int g_scan_frequency = 10;
int g_samples_per_scan = 8400;
SLaser_Ex g_laser_ex;

laser_filter_ex filter;

void init_filter(SLaser_Ex &laser_ex,int samples_per_scan){
	
	laser_ex.frame_dt_ = 0.1;
	laser_ex.range_min_ = 0.01;
	laser_ex.range_max_ = 20.0;

	if (driver_)
	{
		laser_ex.frame_dt_ = 1 / std::atof(driver_->getParametersCached().at("scan_frequency").c_str());
		laser_ex.range_min_ = std::atof(driver_->getParametersCached().at("radial_range_min").c_str());
		laser_ex.range_max_ = std::atof(driver_->getParametersCached().at("radial_range_max").c_str());
	}

	laser_ex.start_angle_ = -M_PI;
	laser_ex.dx_ = 0.2;
	laser_ex.dy_ = 0;
	Config::getConfig("dev_laser_dx",laser_ex.dx_);
	Config::getConfig("dev_laser_dy",laser_ex.dy_);
	laser_ex.resolution_ = 2*M_PI/float(samples_per_scan);
	laser_ex.stamp_ = 0;
	laser_ex.used_ = samples_per_scan;

	memset(laser_ex.seg_,0,sizeof(U8)*LASER_COUNT_EX);
	memset(laser_ex.data_,0,sizeof(F32)*LASER_COUNT_EX);
	memset(laser_ex.intensities_,0,sizeof(U32)*LASER_COUNT_EX);

	filter.init_laser_para(laser_ex);

}

bool connect(const std::string &scanner_ip,const bool &b_8400 = true )
{
	if (driver_)
	{
		driver_->stopCapturing();
		SDelete(driver_);
	}
	
	// Connecting to laser range finder
	//-------------------------------------------------------------------------
	driver_ = new pepperl_fuchs::R2000Driver();
	std::cout << "Connecting to scanner at " << scanner_ip << " ... ";
	if( driver_->connect(scanner_ip,80) )
		std::cout << "OK" << std::endl;
	else
	{
		std::cout << "FAILED!" << std::endl;
		std::cerr << "Connection to scanner at " << scanner_ip << " failed!" << std::endl;
		return false;
	}

	// Setting, reading and displaying parameters
	//-------------------------------------------------------------------------
	if (b_8400)
	{
		g_scan_frequency = 10;
		g_samples_per_scan = 8400;
	}else{
		g_scan_frequency = 25;
		g_samples_per_scan = 720;
	}
	driver_->setScanFrequency(g_scan_frequency);
	driver_->setSamplesPerScan(g_samples_per_scan);

	auto params = driver_->getParameters();
	std::cout << "Current scanner settings:" << std::endl;
	std::cout << "============================================================" << std::endl;
	std::map<std::string, std::string>::const_iterator cit = params.begin();
	for ( ; cit != params.end() ; ++cit )
	{
		std::cout << cit->first << " : " << cit->second << std::endl;
	}
	std::cout << "============================================================" << std::endl;

	init_filter(g_laser_ex,g_samples_per_scan);
	// Start capturing scanner data
	//-------------------------------------------------------------------------
	std::cout << "Starting capturing: ";
	if( driver_->startCapturingTCP() )
		std::cout << "OK" << std::endl;
	else
	{
		std::cout << "FAILED!" << std::endl;
		return false;
	}
	return true;
}


int main(int argc, char **argv)
{
	std::cout << "Hello world!" << std::endl;

	connect("192.168.1.100",false);

	while(1){

		if( !driver_->isCapturing() )
		{
			std::cout << "ERROR: Laser range finder disconnected. Trying to reconnect..." << std::endl;
			while( !connect("192.168.1.100") )
			{
				std::cout << "ERROR: Reconnect failed. Trying again in 2 seconds..." << std::endl;
				SLEEP(2000);
			}
		}
		auto scandata = driver_->getFullScan();
		if( scandata.amplitude_data.empty() || scandata.distance_data.empty() )
			break;
		
		int icount = scandata.distance_data.size();
		if(icount > LASER_COUNT_EX){
			icount = LASER_COUNT_EX;
		}
		
		g_laser_ex.used_ = 0;

 		for( std::size_t i=0; i < icount; i++ )
 		{
			
 			g_laser_ex.data_[i] = float(scandata.distance_data[i])/1000.0f;
 			g_laser_ex.intensities_[i] = scandata.amplitude_data[i];
			g_laser_ex.used_++;
 		}
		filter.filter_used(g_laser_ex);
		//std::cout<<"g_laser_ex.used_:"<<g_laser_ex.used_<<std::endl;
	}

	std::cout << "Trying to stop capture" << std::endl;
	std::cout << "Stopping capture: " << driver_->stopCapturing() << std::endl;
	std::cout << "Goodbye world!" << std::endl;
	return 0;



	// 		for (int s = 0; s < 1000; s++)
	// 		{
	// 			SLEEP(1000);
	// 			int scans_captured = 0;
	// 			int scans_available = driver.getFullScansAvailable();
	// 			for (int i = 0; i < scans_available; i++)
	// 			{
	// // 				auto scandata = driver.getScan();
	//  				scans_captured++;
	// 				auto scandata = driver.getFullScan();
	// 				std::cout<<"amplitude_data:"<<scandata.amplitude_data.size()<<" distance_data:"<<scandata.distance_data.size()<<std::endl;
	//  				if( scandata.amplitude_data.empty() || scandata.distance_data.empty() )
	//  					continue;
	// 
	// 			}
	// 			std::cout << "Received " << scans_captured << " from scanner" << std::endl;
	// 		}
}