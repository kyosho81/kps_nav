#ifndef _SERIALPORT_KYOSHO_20110904_
#define _SERIALPORT_KYOSHO_20110904_

#include "trans_dev.h"

class cSerialPort : cTransferDevice
{
private:
	boost::asio::serial_port* m_pSerialPort;

	void setRTS(bool enabled);
	void setDTR(bool enabled);


	void BaudSleep(int len);
	F32 sleep_one_byte_per_ms_;//rs485 sleep for one byte / ms

public:
	cSerialPort(void);
	~cSerialPort(void);
	
	enum { Type = Object::SERIAL };
	int type() const
	{ return Type;};

	bool Open();
	virtual bool Close();

	void Read();
	bool Write();

};

#endif //_SERIALPORT_KYOSHO_20110904_
