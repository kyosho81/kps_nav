
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <signal.h>

#include "Comm/Comm.h"
#include "log/log_client.h"
#include "log/log_server.h"
#include "pf/merge_tf.h"

merge_tf mt;
SPos odom;
SPos amcl;

boost::mutex mu_str;
std::vector<std::string> vs;
bool b_run = false;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	b_run = false;

	SLEEP(500);


	return;
}

void th_run(){

	b_run = true;

	while(b_run)
	{
		std::string s;
		{
			boost::mutex::scoped_lock sc(mu_str);
			if (vs.size() > 0)
			{
				s = vs[0];
				vs.clear();
			}
		}
		
		std::vector<std::string> v_res;
		cComm::SplitString(s," ",v_res);
		if (v_res.size() > 0)
		{
			if( v_res[0] == "a" ){
				amcl.x_ += 0.03;
				mt.adjusting_tf(amcl,odom,true);
			}else if( v_res[0] == "s"){
				SAMCL_CONFIDENCE confidence;
				confidence.amcl_confidence_ = 1;
				confidence.b_amcl_confidence_ = true;
				mt.update_confidence(confidence);
				amcl.x_ += 0.6;
				mt.adjusting_tf(amcl,odom);
			}else if( v_res[0] == "d"){
				SAMCL_CONFIDENCE confidence;
				confidence.amcl_confidence_ = 0.9;
				confidence.b_amcl_confidence_ = true;
				mt.update_confidence(confidence);
				amcl.x_ += 0.81;
				mt.adjusting_tf(amcl,odom);
			}else if( v_res[0] == "f"){
				SAMCL_CONFIDENCE confidence;
				confidence.amcl_confidence_ = 0.2;
				confidence.b_amcl_confidence_ = false;
				mt.update_confidence(confidence);
				amcl.x_ += 0.81;
				mt.adjusting_tf(amcl,odom);
			}
		}

		////////////////
		odom.x_ += 0.1;
		SPOS_CONFIDENCE conf_pos; 
		memset(&conf_pos,0,sizeof(SPOS_CONFIDENCE));
		mt.get_pos_after_tf(conf_pos,odom);
		amcl = conf_pos.pos_;
		std::cout<<"confidence:"<<conf_pos.confidence_.amcl_confidence_<<" pos x:"<<conf_pos.pos_.x_<<" y:"<<conf_pos.pos_.y_<<" a:"<<conf_pos.pos_.th_<<std::endl;
		SLEEP(100);
	}
}

int main(int argc, char* argv[]){

	::signal(SIGINT, shutdown);

	memset(&odom,0,sizeof(SPos));
	memset(&amcl,0,sizeof(SPos));

	std::string str;

	boost::thread th(&th_run);
	std::cout<<"press a will set new amcl pos with x += 0.03"<<std::endl;
	while(std::getline(std::cin,str)){
		std::cout<<"press a will set new amcl pos with x += 0.03"<<std::endl;
		boost::mutex::scoped_lock sc(mu_str);
		vs.push_back(str);
	}
	
}
