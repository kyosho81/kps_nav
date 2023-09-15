
#include "interface/rpc_config_client.h"
#include "Comm/schedule.h"

int main(int argc, char* argv[])
{
	RPC_CONFIG_CLIENT_INIT("127.0.0.1");

	rpc_config_client* cfg_rpc = 0;
	pschedule ps;
	ps.init(cfg_rpc);
	
	ps.check_schedule(pschedule::SCHE_WANDER);

	return 0;
}
