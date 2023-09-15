#include "../Comm/Comm.h"
#include "trans_dev/trans_dev.h"

#include "trans_dev/can_socket.h"

boost::mutex can_socket::mu_rec_;
std::map<int,boost::function<void(SCanframe)>> can_socket::m_fnc_;

can_socket::can_socket()
{
	
	sock_ = 0;

	rec_ = 0;
}

can_socket::~can_socket()
{
	close_device();
}

bool can_socket::open_device()
{
	std::system("ip link set can0 down");
	std::system("sudo ip link set can0 type can bitrate 500000");
	std::system("ip link set can0 up");
	//th_run_.run_thread(boost::bind(&can_tcp::th_read,this));

	

#ifdef WIN32
#else
	int buffer_len = sizeof(struct can_frame);

	if(rec_){
		delete[] rec_;
		rec_ = 0;
	}
	rec_ = new U8[buffer_len + 1];
	memset(rec_ , 0 , buffer_len + 1 );

	struct sockaddr_can addr;
	struct can_frame frame;
	
	int nbytes;
	//int i;
	struct ifreq ifr;


	sock_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if( sock_ == -1){
		fprintf(stderr, "can socket error:%s\n\a", strerror(errno));
		exit(1);
	}

	strcpy(ifr.ifr_name, "can0" );
	ioctl( sock_, SIOCGIFINDEX, &ifr);

	bzero(&addr, sizeof(struct sockaddr_can));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	bind( sock_, (struct sockaddr *)&addr, sizeof(addr));
	//struct can_filter {
	//	canid_t can_id;
	//	canid_t can_mask;
	//};

	//#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
	//#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
	//#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */
	//can_filter rfilter[1];
	//rfilter[0].can_id   = 0x0;
	//rfilter[0].can_mask = CAN_SFF_MASK;
	//rfilter[1].can_id   = 0x200;
	//rfilter[1].can_mask = 0x700;
	//setsockopt(sock_, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
	
	int i_size = m_can_id_.size();
	std::cout<<"can_id size:"<<i_size<<std::endl;
	can_filter* p_can_filter = new can_filter[i_size];
	memset(p_can_filter, 0 , sizeof(can_filter)*i_size );
	
	int i = 0;
	auto it = m_can_id_.begin();	
	for(  ; it != m_can_id_.end() ; ++it ){
		
		p_can_filter[i].can_id   = it->first;	
		p_can_filter[i++].can_mask = CAN_SFF_MASK;
	}
	setsockopt(sock_, SOL_CAN_RAW, CAN_RAW_FILTER, p_can_filter, sizeof(can_filter)*i_size);
	delete[] p_can_filter;
	p_can_filter = 0;

	int  ret;

	/* Set up the AIO request */
	bzero( (char *)&m_aiocb_, sizeof(struct aiocb) );
	m_aiocb_.aio_fildes = sock_;
	m_aiocb_.aio_buf = rec_;
	m_aiocb_.aio_nbytes = buffer_len;
	m_aiocb_.aio_offset = 0;

	/* Link the AIO request with a thread callback */
	m_aiocb_.aio_sigevent.sigev_notify = SIGEV_THREAD;
	
	std::cout<<"begin bind read callback!"<<std::endl;
	//boost::function<void(sigval_t)> fnc = boost::bind(&can_socket::read_callback,this,_1);
	//typedef void (*pointer_to_func)(sigval_t);
	m_aiocb_.aio_sigevent.sigev_notify_function =  read_callback;//*fnc.target<pointer_to_func>();
	m_aiocb_.aio_sigevent.sigev_notify_attributes  = NULL;
	m_aiocb_.aio_sigevent.sigev_value.sival_ptr = &m_aiocb_;

	boost::mutex::scoped_lock lock(mu_rec_);
	m_fnc_[sock_] = boost::bind(&can_socket::fnc_read,this,_1);

	std::cout<<"begin read"<<std::endl;
	ret = aio_read( &m_aiocb_ );

#endif

	return true;
}

bool can_socket::close_device()
{
	//std::system("ip link set can0 down");
	return true;
}

bool can_socket::send(U32 can_index, SCanframe data, U8 send_type){
	
#ifdef WIN32
	return false;
#else
	int ret = 0;

	can_frame frame;
	memset(&frame,0,sizeof(can_frame));

	frame.can_id = data.can_id_;
	frame.can_dlc = data.len_;
	memcpy( frame.data, data.data_ , frame.can_dlc);

	ret = write(sock_, &frame, sizeof(struct can_frame));
	if (ret < 0){
		fprintf(stderr, "can socket write error:%s\n\a", strerror(errno));
		return false;
	}
	if(ret < sizeof(struct can_frame)){
		fprintf(stderr, "can socket write incomplete CAN frame\n\a");
		return false;
	}
	return true;
#endif

}
bool can_socket::send(U32 can_index, std::vector<SCanframe> &frame_list, U8 send_type){

#ifdef WIN32
	return false;
#else
	int i_size = frame_list.size();
	if (i_size < 1){
		return false;
	}

	bool b_send_ok = true;
	for ( int i = 0 ; i < frame_list.size() ; ++i ){
		if( !send(can_index,frame_list[i],send_type)){
			b_send_ok = false;
		}
	}

	return b_send_ok;
#endif

}
bool can_socket::read(U32 can_index, std::vector<SCanframe> &frame_list){

#ifdef WIN32
	return false;
#else
 	frame_list.clear();
	if ( can_index == 0 ){
		SCanframe frame;
		while( can0_list_.size() > 0){
			can0_list_.get(frame);
			frame_list.push_back(frame);
		}
		if (frame_list.size() > 0){
			return true;
		}
	}
	return false;
#endif
}
void can_socket::fnc_read(SCanframe frame){
	can0_list_.put(frame);	
}
#ifdef WIN32
void can_socket::read_callback(int sigval){};
#else
void can_socket::read_callback(sigval_t sigval){

	struct aiocb *req;

	req = (struct aiocb *)sigval.sival_ptr;
	int ret = 0;


	/* Did the request complete? */
	if (aio_error( req ) == 0) {

		/* Request completed successfully, get the return status */
		ret = aio_return( req );

		can_frame frame;
		memcpy(&frame,(U8*)req->aio_buf,sizeof(can_frame));

		SCanframe read;
		memset(&read,0,sizeof(SCanframe));
		read.can_id_ = frame.can_id;
		read.len_ = frame.can_dlc;
		memcpy( read.data_ , frame.data , read.len_);
		
		boost::mutex::scoped_lock lock(mu_rec_);
		auto it = m_fnc_.find(req->aio_fildes);
		if( it != m_fnc_.end()){
			it->second(read);
			//std::cout<<"call back send!"<<std::endl;
		}
		
		//can0_list_.put(read);

		ret = aio_read(req);
		//std::cout<<"read over"<<std::endl;
	}

	return;
}
#endif
