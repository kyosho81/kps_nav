#ifndef ASYNC_CLIENT9_H
#define ASYNC_CLIENT9_H
#include <iostream>
#include <stdio.h>
#include <time.h>
//#include <ros/ros.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
//#include <unistd.h>
#include <vector>
#include "vanjee_719_lidar_protocol.h"

using namespace std ;
using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace wj_lidar;
#define MAX_LENGTH 50000
class Async_Client9
{
public:

  Async_Client9(vanjee_719_lidar_protocol *protocol);
  ~Async_Client9();
  bool connect(string ip, int port);
  bool disconnect();
  void recvData();
  void reconnect();
  void checklinkstate();
  bool sendMsg(unsigned char buf[], int length); 

  bool        m_bConnected;
  bool        m_bReconnecting;

private:
  vanjee_719_lidar_protocol *m_ptrProtocol;
  string m_sServerIp;
  int m_iServerPort;
  io_service m_io;
  ip::tcp::endpoint m_ep;
  boost::shared_ptr<ip::tcp::socket> m_pSocket;
  boost::system::error_code ec;

  char        data_[MAX_LENGTH];
};

#endif // ASYNC_CLIENT9_H
