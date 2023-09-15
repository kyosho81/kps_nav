 
#include <stdio.h>
#include <string.h>

 #include "protobuf_msg/protobuf_bag.h"

int main(int argc,char **argv)
{

	Singleton_ProtoBuf_Bag::get_mutable_instance().init();

    return 0;
}

