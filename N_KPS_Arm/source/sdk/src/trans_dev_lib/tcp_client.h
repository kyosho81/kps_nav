#ifndef _TCP_CLIENT_KYOSHO_20110904_
#define _TCP_CLIENT_KYOSHO_20110904_

#include "trans_dev.h"

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;

class cTCPClient : cTransferDevice
{
private:

	ip::tcp::socket* m_sock;
	ip::tcp::endpoint* m_endpoint;

public:
	enum { Type = Object::TCP_CLIENT };
	int type() const
	{ return Type;};

	cTCPClient(void);
	~cTCPClient(void);

	bool Open();
	bool Close();

	void Read();
	bool Write();

};
#endif //_TCP_CLIENT_KYOSHO_20110904_
