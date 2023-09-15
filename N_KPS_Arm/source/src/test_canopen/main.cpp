
#include <stdlib.h>
#include "Comm/Rand.hpp"

#include "trans_dev.h"
#include "Comm.h"
#include <iostream>
#include <fstream>

#ifdef USE_XENO
#define eprintf(...)
#else
#define eprintf(...) printf (__VA_ARGS__)
#endif

#ifdef __cplusplus
extern "C" {
#endif


#include "can_festival/timers_driver.h"
#include "can_festival/can_driver.h"
#include "can_festival/canfestival.h"
#include "can_festival/nmtMaster.h"

#ifdef __cplusplus
};
#endif

#include "trans_dev/can_base.h"
#include "trans_dev/canalyst2.h"
#include "trans_dev/can_tcp.h"


#include "win32test.h"

#ifdef WIN32
#define sleep_proc(ms) Sleep(ms)
#define uptime_ms_proc() GetTickCount()
#else
#include <time.h> 
#define sleep_proc(ms)
#define uptime_ms_proc (1000*(time()%86400))  // TOD
#endif

s_BOARD MasterBoard = {"canalyst2", "500000"};
UNS8 slavenodeid = 2;

UNS8 GetChangeStateResults(UNS8 node_id, UNS8 expected_state, unsigned long timeout_ms)
{
	unsigned long start_time = 0;

	// reset nodes state
	win32test_Data.NMTable[node_id] = Unknown_state;

	// request node state
	masterRequestNodeState(&win32test_Data, node_id);

	start_time = uptime_ms_proc();
	while(uptime_ms_proc() - start_time < timeout_ms)
	{
		if (getNodeState(&win32test_Data, node_id) == expected_state)
			return 0;
		sleep_proc(1);   
	}
	return 0xFF;
}

UNS8 ReadSDO(UNS8 nodeId, UNS16 index, UNS8 subIndex, UNS8 dataType, void* data, UNS32* size)
{
	UNS32 abortCode = 0;
	UNS8 res = SDO_UPLOAD_IN_PROGRESS;
	// Read SDO
	UNS8 err = readNetworkDict (&win32test_Data, nodeId, index, subIndex, dataType, 0);
	if (err)
		return 0xFF;
	for(;;)
	{
		res = getReadResultNetworkDict (&win32test_Data, nodeId, data, size, &abortCode);
		if (res != SDO_UPLOAD_IN_PROGRESS)
			break;   
		sleep_proc(1);
		continue;
	}
	closeSDOtransfer(&win32test_Data, nodeId, SDO_CLIENT);
	if (res == SDO_FINISHED)
		return 0;
	return 0xFF;   
}

/* Write a slave node object dictionnary entry */
void WriteDeviceEntry()
{
	int ret=0;
	int nodeid;
	int index;
	int subindex;
	int size;
	int data;


	if (ret == 5)
	{
		printf("##################################\n");
		printf("#### Write SDO                ####\n");
		printf("##################################\n");
		printf("NodeId   : %2.2x\n", nodeid);
		printf("Index    : %4.4x\n", index);
		printf("SubIndex : %2.2x\n", subindex);
		printf("Size     : %2.2x\n", size);
		printf("Data     : %x\n", data);

		writeNetworkDictCallBack(&win32test_Data, nodeid, index, subindex, size, 0, &data, CheckWriteSDO, 0);
	}

}

/***************************  CLEANUP  *****************************************/
void Exit(CO_Data* d, UNS32 nodeid)
{
	/* Reset all nodes on the network */
	masterSendNMTstateChange(&win32test_Data, 0 , NMT_Reset_Node);

	/* Stop master */
	setState(&win32test_Data, Stopped);
}
/***************************  INIT  *****************************************/
void InitNodes(CO_Data* d, UNS32 id)
{
	/****************************** INITIALISATION MASTER *******************************/
	if(MasterBoard.baudrate){
		/* Defining the node Id */
		//setNodeId(&TestMaster_Data, 0x01);

		/* init */
		setState(&win32test_Data, Initialisation);
	}
}


/*****************************************************************************/
void TestMaster_heartbeatError(CO_Data* d, UNS8 heartbeatID)
{
	eprintf("TestMaster_heartbeatError %d\n", heartbeatID);
}

/********************************************************
 * ConfigureSlaveNode is responsible to
 *  - setup master RPDO 1 to receive TPDO 1 from id 0x40
 *  - setup master TPDO 1 to send RPDO 1 to id 0x40
 ********************************************************/
void TestMaster_initialisation(CO_Data* d)
{
	UNS32 PDO1_COBID = 0x0180 + slavenodeid; 
	UNS32 PDO2_COBID = 0x0200 + slavenodeid;
	UNS32 size = sizeof(UNS32); 

	eprintf("TestMaster_initialisation\n");

	/*****************************************
	 * Define RPDOs to match slave ID=0x40 TPDOs*
	 *****************************************/
	writeLocalDict( &win32test_Data, /*CO_Data* d*/
			0x1400, /*UNS16 index*/
			0x01, /*UNS8 subind*/ 
			&PDO1_COBID, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
			

	/*****************************************
	 * Define TPDOs to match slave ID=0x40 RPDOs*
	 *****************************************/
	writeLocalDict( &win32test_Data, /*CO_Data* d*/
			0x1800, /*UNS16 index*/
			0x01, /*UNS8 subind*/ 
			&PDO2_COBID, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
}

static int init_step = 0;

/*Froward declaration*/
static void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId);

/**/
static void CheckSDOAndContinue(CO_Data* d, UNS8 nodeId)
{
	UNS32 abortCode;

	if(getWriteResultNetworkDict (d, nodeId, &abortCode) != SDO_FINISHED)
		eprintf("Master : Failed in initializing slave %2.2x, step %d, AbortCode :%4.4x \n", nodeId, init_step, abortCode);

	/* Finalise last SDO transfer with this node */
	closeSDOtransfer(&win32test_Data, nodeId, SDO_CLIENT);

	ConfigureSlaveNode(d, nodeId);
}

/********************************************************
 * ConfigureSlaveNode is responsible to
 *  - setup slave TPDO 1 transmit time
 *  - setup slave TPDO 2 transmit time
 *  - setup slave Heartbeat Producer time
 *  - switch to operational mode
 *  - send NMT to slave
 ********************************************************
 * This an example of :
 * Network Dictionary Access (SDO) with Callback 
 * Slave node state change request (NMT) 
 ********************************************************
 * This is called first by TestMaster_preOperational
 * then it called again each time a SDO exchange is
 * finished.
 ********************************************************/
static void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId)
{
	UNS8 res;
	eprintf("Master : ConfigureSlaveNode %2.2x\n", nodeId);
	printf("nodeid slave=%x\n",nodeId);
	switch(++init_step){
		case 1: 
		{	/*disable Slave's TPDO 1 */
			UNS32 TPDO_COBId = 0x80000180 + nodeId;
			
			eprintf("Master : disable slave %2.2x TPDO 1 \n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1800, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
        }			
		break;

		case 2: 
		{	/*setup Slave's TPDO 1 to be transmitted on SYNC*/
			UNS8 Transmission_Type = 0x01;
			
			eprintf("Master : set slave %2.2x TPDO 1 transmit type\n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1800, /*UNS16 index*/
					0x02, /*UNS8 subindex*/
					1, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&Transmission_Type,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;

		case 3: 
		{	/*re-enable Slave's TPDO 1 */
			UNS32 TPDO_COBId = 0x00000180 + nodeId;
			
			eprintf("Master : re-enable slave %2.2x TPDO 1\n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1800, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;
					
		case 4: 
		{	/*disable Slave's TPDO 2 */
			UNS32 TPDO_COBId = 0x80000200 + nodeId;
			
			eprintf("Master : disable slave %2.2x RPDO 1\n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1400, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;

					
		case 5:
		{	
			UNS8 Transmission_Type = 0x01;
			
			eprintf("Master : set slave %2.2x RPDO 1 receive type\n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1400, /*UNS16 index*/
					0x02, /*UNS8 subindex*/
					1, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&Transmission_Type,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}	
		break;

		case 6: 
		{	/*re-enable Slave's TPDO 1 */
			UNS32 TPDO_COBId = 0x00000200 + nodeId;
			
			eprintf("Master : re-enable %2.2x RPDO 1\n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1400, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;
		
		case 7:	
		{
			UNS16 Heartbeat_Producer_Time = 0x03E8; 
			eprintf("Master : set slave %2.2x heartbeat producer time \n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1017, /*UNS16 index*/
					0x00, /*UNS8 subindex*/
					2, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&Heartbeat_Producer_Time,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;

		case 8: 
		{	/*disable Slave's TPDO 2 */
			UNS32 TPDO_COBId = 0x80000280 + nodeId;
			
			eprintf("Master : disable slave %2.2x TPDO 2 \n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1801, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;

		case 9: 
		{	/*disable Slave's TPDO 3 */
			UNS32 TPDO_COBId = 0x80000380 + nodeId;
			
			eprintf("Master : disable slave %2.2x TPDO 3 \n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1802, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}
		break;			

		case 10: 
		{	/*disable Slave's TPDO 2 */
			UNS32 TPDO_COBId = 0x80000480 + nodeId;
			
			eprintf("Master : disable slave %2.2x TPDO 4 \n", nodeId);
			res = writeNetworkDictCallBack (d, /*CO_Data* d*/
					/**TestSlave_Data.bDeviceNodeId, UNS8 nodeId*/
					nodeId, /*UNS8 nodeId*/
					0x1803, /*UNS16 index*/
					0x01, /*UNS8 subindex*/
					4, /*UNS8 count*/
					0, /*UNS8 dataType*/
					&TPDO_COBId,/*void *data*/
					CheckSDOAndContinue, /*SDOCallback_t Callback*/
                    0); /* use block mode */
		}			
		break;			
		
		case 11:
			/* Put the master in operational mode */
			setState(d, Operational);
			  
			/* Ask slave node to go in operational mode */
			masterSendNMTstateChange (d, nodeId, NMT_Start_Node);
	}
			
}

void TestMaster_preOperational(CO_Data* d)
{

	eprintf("TestMaster_preOperational\n");
	ConfigureSlaveNode(&win32test_Data, slavenodeid);
	
}

void TestMaster_operational(CO_Data* d)
{
	eprintf("TestMaster_operational\n");
}

void TestMaster_stopped(CO_Data* d)
{
	eprintf("TestMaster_stopped\n");
}

void TestMaster_post_sync(CO_Data* d)
{
// 	DO++;
// 	
// 	AO1 = AI1 / 2;
// 	AO2 = AI2 / 2;
// 	AO3 = AI3 / 2;
// 	AO4 = AI4 / 2;
// 	eprintf("MicroMod Digital Out: %2.2x\n",DO);
// 	eprintf("MicroMod Analogue Out1: %d\n",AO1);
// 	eprintf("MicroMod Analogue Out2: %d\n",AO2);
// 	eprintf("MicroMod Analogue Out3: %d\n",AO3);
// 	eprintf("MicroMod Analogue Out4: %d\n",AO4);
// 	eprintf("MicroMod Digital In (by bit): DI1: %2.2x DI2: %2.2x DI3: %2.2x DI4: %2.2x DI5: %2.2x DI6: %2.2x DI7: %2.2x DI8: %2.2x\n",DI1,DI2,DI3,DI4,DI5,DI6,DI7,DI8);
// 	eprintf("MicroMod Analogue In1: %d\n", AI1);
// 	eprintf("MicroMod Analogue In2: %d\n", AI2);
// 	eprintf("MicroMod Analogue In3: %d\n", AI3);
// 	eprintf("MicroMod Analogue In4: %d\n", AI4);
// 	eprintf("MicroMod Analogue In5: %d\n", AI5);
// 	eprintf("MicroMod Analogue In6: %d\n", AI6);
// 	eprintf("MicroMod Analogue In7: %d\n", AI7);
// 	eprintf("MicroMod Analogue In8: %d\n", AI8);
}

void TestMaster_post_TPDO(CO_Data* d)
{
//	eprintf("TestMaster_post_TPDO\n");	
}
int main(int argc, char *argv[])
{
	TimerInit();

	win32test_Data.heartbeatError = TestMaster_heartbeatError;
	win32test_Data.initialisation = TestMaster_initialisation;
	win32test_Data.preOperational = TestMaster_preOperational;
	win32test_Data.operational = TestMaster_operational;
	win32test_Data.stopped = TestMaster_stopped;
	win32test_Data.post_sync = TestMaster_post_sync;
	win32test_Data.post_TPDO = TestMaster_post_TPDO;
	

	if (canOpen(&MasterBoard,&win32test_Data)){
		


		/* Defining the node Id */
		setNodeId(&win32test_Data, 0x01);

		// Start timer thread
		StartTimerLoop(&InitNodes);

		/* init */
		//setState(&win32test_Data, Initialisation);

		/****************************** START *******************************/
		/* Put the master in operational mode */
		setState(&win32test_Data, Operational);

		/* Ask slave node to go in operational mode */
		masterSendNMTstateChange (&win32test_Data, 0, NMT_Start_Node);

		printf("\nStarting node %d (%xh) ...\n",(int)slavenodeid,(int)slavenodeid);

		system("PAUSE");
		/* wait untill mode will switch to operational state*/
		if (GetChangeStateResults(slavenodeid, Operational, 3000) != 0xFF)
		{
			/* modify Client SDO 1 Parameter */
			UNS32 COB_ID_Client_to_Server_Transmit_SDO = 0x600 + slavenodeid;
			UNS32 COB_ID_Server_to_Client_Receive_SDO  = 0x580 + slavenodeid;
			UNS8 Node_ID_of_the_SDO_Server = slavenodeid;
			UNS32 ExpectedSize = sizeof(UNS32);
			UNS32 ExpectedSizeNodeId = sizeof (UNS8);

			if (OD_SUCCESSFUL ==  writeLocalDict(&win32test_Data, 0x1280, 1, &COB_ID_Client_to_Server_Transmit_SDO, &ExpectedSize, RW) 
				&& OD_SUCCESSFUL ==  writeLocalDict(&win32test_Data, 0x1280, 2, &COB_ID_Server_to_Client_Receive_SDO, &ExpectedSize, RW) 
				&& OD_SUCCESSFUL ==  writeLocalDict(&win32test_Data, 0x1280, 3, &Node_ID_of_the_SDO_Server, &ExpectedSizeNodeId, RW))
			{
				UNS32 dev_type = 0;
				char device_name[64]="";
				char hw_ver[64]="";
				char sw_ver[64]="";   
				UNS32 vendor_id = 0;            
				UNS32 prod_code = 0;
				UNS32 ser_num = 0;
				UNS32 size;
				UNS8 res;

				printf("\nnode_id: %d (%xh) info\n",(int)slavenodeid,(int)slavenodeid);
				printf("********************************************\n");

				size = sizeof (dev_type);
				res = ReadSDO(slavenodeid, 0x1000, 0, uint32, &dev_type, &size);
				printf("device type: %d\n",dev_type & 0xFFFF);

				size = sizeof (device_name);
				res = ReadSDO(slavenodeid, 0x1008, 0, visible_string, device_name, &size);
				printf("device name: %s\n",device_name);

				size = sizeof (hw_ver);
				res = ReadSDO(slavenodeid, 0x1009, 0, visible_string, hw_ver, &size);
				printf("HW version: %s\n",hw_ver);

				size = sizeof (sw_ver);
				res = ReadSDO(slavenodeid, 0x100A, 0, visible_string, sw_ver, &size);
				printf("SW version: %s\n",sw_ver);            

				size = sizeof (vendor_id);
				res = ReadSDO(slavenodeid, 0x1018, 1, uint32, &vendor_id, &size);
				printf("vendor id: %d\n",vendor_id);

				size = sizeof (prod_code);
				res = ReadSDO(slavenodeid, 0x1018, 2, uint32, &prod_code, &size);
				printf("product code: %d\n",prod_code);

				size = sizeof (ser_num);
				res = ReadSDO(slavenodeid, 0x1018, 4, uint32, &ser_num, &size);
				printf("serial number: %d\n",ser_num);

				printf("********************************************\n");
			} 
			else
			{
				printf("ERROR: Object dictionary access failed\n");
			}
		}
		else
		{
			printf("ERROR: node_id %d (%xh) is not responding\n",(int)slavenodeid,(int)slavenodeid);
		}

		masterSendNMTstateChange (&win32test_Data, 0x02, NMT_Stop_Node);

		setState(&win32test_Data, Stopped);

	}
	// Stop timer thread
	StopTimerLoop(&Exit);

	/* Close CAN board */
	canClose(&win32test_Data);

init_fail:
	TimerCleanup();

}

