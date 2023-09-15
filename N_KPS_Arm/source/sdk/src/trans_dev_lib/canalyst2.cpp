#include "../Comm/Comm.h"
#include "Comm/TimerDiff.h"

#include "trans_dev/canalyst2.h"

#pragma comment(lib,"ControlCAN")

canalyst2::canalyst2()
{

}

canalyst2::~canalyst2()
{
	close_device();
}

bool canalyst2::open_device()
{
	std::cout<<"canalyst2::open_device"<<std::endl;
	VCI_BOARD_INFO pInfo;//

	if(VCI_OpenDevice(VCI_USBCAN2,0,0)==1)//
	{
		printf(">>open deivce success!\n");//
	}else
	{
		printf(">>open deivce error!\n");
		return false;
	}
	if(VCI_ReadBoardInfo(VCI_USBCAN2,0,&pInfo)==1)//
	{
		printf(">>Get VCI_ReadBoardInfo success!\n");

		//printf(" %08X", pInfo.hw_Version);printf("\n");
		//printf(" %08X", pInfo.fw_Version);printf("\n");
		//printf(" %08X", pInfo.dr_Version);printf("\n");
		//printf(" %08X", pInfo.in_Version);printf("\n");
		//printf(" %08X", pInfo.irq_Num);printf("\n");
		//printf(" %08X", pInfo.can_Num);printf("\n");
		printf(">>Serial_Num:%c", pInfo.str_Serial_Num[0]);
		printf("%c", pInfo.str_Serial_Num[1]);
		printf("%c", pInfo.str_Serial_Num[2]);
		printf("%c", pInfo.str_Serial_Num[3]);
		printf("%c", pInfo.str_Serial_Num[4]);
		printf("%c", pInfo.str_Serial_Num[5]);
		printf("%c", pInfo.str_Serial_Num[6]);
		printf("%c", pInfo.str_Serial_Num[7]);
		printf("%c", pInfo.str_Serial_Num[8]);
		printf("%c", pInfo.str_Serial_Num[9]);
		printf("%c", pInfo.str_Serial_Num[10]);
		printf("%c", pInfo.str_Serial_Num[11]);
		printf("%c", pInfo.str_Serial_Num[12]);
		printf("%c", pInfo.str_Serial_Num[13]);
		printf("%c", pInfo.str_Serial_Num[14]);
		printf("%c", pInfo.str_Serial_Num[15]);
		printf("%c", pInfo.str_Serial_Num[16]);
		printf("%c", pInfo.str_Serial_Num[17]);
		printf("%c", pInfo.str_Serial_Num[18]);
		printf("%c", pInfo.str_Serial_Num[19]);printf("\n");

		printf(">>hw_Type:%c", pInfo.str_hw_Type[0]);
		printf("%c", pInfo.str_hw_Type[1]);
		printf("%c", pInfo.str_hw_Type[2]);
		printf("%c", pInfo.str_hw_Type[3]);
		printf("%c", pInfo.str_hw_Type[4]);
		printf("%c", pInfo.str_hw_Type[5]);
		printf("%c", pInfo.str_hw_Type[6]);
		printf("%c", pInfo.str_hw_Type[7]);
		printf("%c", pInfo.str_hw_Type[8]);
		printf("%c", pInfo.str_hw_Type[9]);printf("\n");

		printf(">>Firmware Version:V");
		printf("%x", (pInfo.fw_Version&0xF00)>>8);
		printf(".");
		printf("%x", (pInfo.fw_Version&0xF0)>>4);
		printf("%x", pInfo.fw_Version&0xF);
		printf("\n");	
	}else
	{
		printf(">>Get VCI_ReadBoardInfo error!\n");
		return false;
	}

	//
	VCI_INIT_CONFIG config;
	config.AccCode=0;
	config.AccMask=0xFFFFFFFF;
	config.Filter=1;//

	if(!get_baud_rate( config.Timing0, config.Timing1, baud_rate_)){
		std::cout<<"canalyst2 baud rate error!"<<baud_rate_<<std::endl;
		return false;
	}
	//config.Timing0 =0x03;/*125 Kbps  0x03  0x1C*/
	//config.Timing1=0x1C;
	
	
	config.Mode=0;//

	if(VCI_InitCAN(VCI_USBCAN2,0,0,&config)!=1)
	{
		printf(">>Init CAN1 error\n");
		VCI_CloseDevice(VCI_USBCAN2,0);
	}

	if(VCI_StartCAN(VCI_USBCAN2,0,0)!=1)
	{
		printf(">>Start CAN1 error\n");
		VCI_CloseDevice(VCI_USBCAN2,0);

	}

	if(VCI_InitCAN(VCI_USBCAN2,0,1,&config)!=1)
	{
		printf(">>Init can2 error\n");
		VCI_CloseDevice(VCI_USBCAN2,0);

	}
	if(VCI_StartCAN(VCI_USBCAN2,0,1)!=1)
	{
		printf(">>Start can2 error\n");
		VCI_CloseDevice(VCI_USBCAN2,0);

	}

	th_run_.run_thread(boost::bind(&canalyst2::th_read,this));

	return true;
}

bool canalyst2::close_device()
{

	th_run_.destory_thread();

	std::cout<<"canalyst2::close_device"<<std::endl;

	VCI_ResetCAN(VCI_USBCAN2, 0, 0);//can1
	SLEEP(100);
	VCI_ResetCAN(VCI_USBCAN2, 0, 1);//can2
	SLEEP(100);
	VCI_OpenDevice(VCI_USBCAN2,0,0);
	SLEEP(100);
	VCI_CloseDevice(VCI_USBCAN2,0);//
	SLEEP(2000);

	std::cout<<"canalyst2::close_device over!"<<std::endl;

	return true;
}

bool canalyst2::reset_driver()
{

	VCI_ResetCAN(VCI_USBCAN2, 0, 0);//can1
	SLEEP(100);
	VCI_ResetCAN(VCI_USBCAN2, 0, 1);//can2
	SLEEP(100);

	return true;
}

bool canalyst2::get_baud_rate( U8 &t0 , U8 &t1, S32 baud_rate)
{
	if(baud_rate == 125000){
		t0 = 0x03;
		t1 = 0x1C;
	}
	else if(baud_rate == 250000){
		t0 = 0x01;
		t1 = 0x1C;
	}
	else if(baud_rate == 500000){
		t0 = 0x00;
		t1 = 0x1C;
	}
	else if(baud_rate == 800000){
		t0 = 0x00;
		t1 = 0x16;
	}
	else if(baud_rate == 1000000){
		t0 = 0x00;
		t1 = 0x14;
	}else{
		return false;
	}
	return true;
}

bool canalyst2::th_read()
{
	int i_rec_len0 = 0;
	int i_rec_len1 = 0;

	{
		boost::mutex::scoped_lock lock(mu_rw_0_);
		i_rec_len0 = VCI_Receive(VCI_USBCAN2,0,0,rec_data0_,10,100);
	}
	{
		boost::mutex::scoped_lock lock(mu_rw_1_);
		i_rec_len1 = VCI_Receive(VCI_USBCAN2,0,1,rec_data1_,10,100);
	}
	
	for(int i = 0; i < i_rec_len0 ; ++i ){
		if( check_rec_can_id(rec_data0_[i].ID) )
		{
			SCanframe frame;
			frame.can_id_ = rec_data0_[i].ID ;
			frame.len_ = rec_data0_[i].DataLen;

			for(int j = 0; j < frame.len_; j++)
			{
				frame.data_[j] = rec_data0_[i].Data[j];
			}
			can0_list_.put(frame);
			if (fnc_call_back_){
				fnc_call_back_(frame);
			}
// 			if ( (frame.can_id_ & 0x180) == 0x180){
// 				int id = frame.can_id_ & ~0x180;
// 				S32 pos = 0;
// 				memcpy(&pos,frame.data_,4);
// 				std::cout<<"id"<<id<<" stamp:"<<cTimerDiff::get_now_ms()<<" pos:"<<pos<<std::endl;
// 			}
		}
	}

	for(int i = 0; i < i_rec_len1 ; ++i ){
		if( check_rec_can_id(rec_data1_[i].ID) )
		{
			SCanframe frame;
			frame.can_id_ = rec_data1_[i].ID ;
			frame.len_ = rec_data1_[i].DataLen;

			for(int j = 0; j < frame.len_; j++)
			{
				frame.data_[j] = rec_data1_[i].Data[j];
			}
			can1_list_.put(frame);
		}
	}

	SLEEP(20);

	return true;
}
bool canalyst2::send(U32 can_index, SCanframe data, U8 send_type){

	VCI_CAN_OBJ can_data;
	can_data.ID = data.can_id_;
	can_data.DataLen = data.len_;
	can_data.TimeStamp  = 0x00;
	can_data.TimeFlag = 0x00;
	can_data.SendType = send_type;   //
	can_data.RemoteFlag = 0x00;     //
	can_data.ExternFlag = 0x00;     //
	can_data.Reserved[0]= 0x00;
	can_data.Reserved[1]= 0x00;
	can_data.Reserved[2]= 0x00;

	for(int i = 0;i<data.len_;i++){
		can_data.Data[i] = data.data_[i];
	}
	//std::cout<<"canalyst2::send id:"<<data.can_id_<<" len:"<<int(data.len_)<<" data:"<<cComm::ByteToHexString(data.data_,8)<<std::endl;
	int ret = 0;
	
	if ( can_index == 0){
		boost::mutex::scoped_lock lock(mu_rw_0_);
		ret = VCI_Transmit(VCI_USBCAN2,0,can_index,&can_data,1);
	}else
	{
		boost::mutex::scoped_lock lock(mu_rw_1_);
		ret = VCI_Transmit(VCI_USBCAN2,0,can_index,&can_data,1);
	}

	if(ret < 0 ){
		std::cout<<"canalyst2 send error"<<ret<<std::endl;
		return false;
	}

	return true;
}

bool canalyst2::send(U32 can_index, std::vector<SCanframe> &frame_list, U8 send_type){

	int i_size = frame_list.size();
	if (i_size < 1){
		return false;
	}

	VCI_CAN_OBJ* can_data = new VCI_CAN_OBJ[i_size];
	memset(can_data,0,sizeof(VCI_CAN_OBJ)*i_size);

	for ( int i = 0 ; i < frame_list.size() ; ++i ){

		SCanframe &data = frame_list[i];
		can_data[i].ID = data.can_id_;
		can_data[i].DataLen = data.len_;
		can_data[i].TimeStamp  = 0x00;
		can_data[i].TimeFlag = 0x00;
		can_data[i].SendType = send_type;   //
		can_data[i].RemoteFlag = 0x00;     //
		can_data[i].ExternFlag = 0x00;     //
		can_data[i].Reserved[0]= 0x00;
		can_data[i].Reserved[1]= 0x00;
		can_data[i].Reserved[2]= 0x00;

		for(int j = 0;j<data.len_;j++){
			can_data[i].Data[j] = data.data_[j];
		}

	}
	
	//std::cout<<"canalyst2::send id:"<<data.can_id_<<" len:"<<int(data.len_)<<" data:"<<cComm::ByteToHexString(data.data_,8)<<std::endl;
	int ret = 0;

	if ( can_index == 0){
		boost::mutex::scoped_lock lock(mu_rw_0_);
		ret = VCI_Transmit(VCI_USBCAN2,0,can_index,can_data,i_size);
	}else
	{
		boost::mutex::scoped_lock lock(mu_rw_1_);
		ret = VCI_Transmit(VCI_USBCAN2,0,can_index,can_data,i_size);
	}
	if (can_data){
		delete[] can_data;
		can_data = 0;
	}
	if(ret < 0 ){
		std::cout<<"canalyst2 send error"<<ret<<std::endl;
		return false;
	}

	return true;
}

bool canalyst2::read(U32 can_index, std::vector<SCanframe> &frame_list){

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
	}else if ( can_index == 1 ){
		SCanframe frame;
		while( can1_list_.size() > 0){
			can1_list_.get(frame);
			frame_list.push_back(frame);
		}
		if (frame_list.size() > 0){
			return true;
		}
	}
	return false;
}
