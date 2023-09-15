#ifndef VANJEE_ABSTRACT_PROTOCOL_H
#define VANJEE_ABSTRACT_PROTOCOL_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "lidar_struct_type.h"

namespace wj_lidar
{
    #define MAX_LENGTH_DATA_PROCESS 200000
    typedef struct TagDataCache
    {
        unsigned char cache_data[MAX_LENGTH_DATA_PROCESS];
        unsigned int cache_in;
        unsigned int cache_out;
    } DataCache;

    class VanjeeAbstractProtocol
    {
        public:
            VanjeeAbstractProtocol();
            virtual ~VanjeeAbstractProtocol(){};
            bool dataProcess(unsigned char *data, const int reclen);
            bool OnRecvProcess(unsigned char *data, int len);
            bool checkXor(unsigned char *recvbuf, int recvlen);
            bool heartstate;
        protected:
           
            virtual bool protocl(unsigned char *data, const int len) = 0;
            lidar_base_struct_type base_param;

        private:
            void moveData(DataCache &sdata);
            DataCache data_;
    };
}
#endif // VANJEE_ABSTRACT_PROTOCOL_H
