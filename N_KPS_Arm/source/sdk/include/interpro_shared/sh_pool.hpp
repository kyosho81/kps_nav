#ifndef _SHARED_POOL_KYOSHO_2020_11_20_
#define _SHARED_POOL_KYOSHO_2020_11_20_

#include "interpro_shared/msg_shared_pool.hpp"
#include "interpro_shared/pipe_shared_pool.hpp"
#include "interpro_shared/block_shared_pool.hpp"
#include "interpro_shared/locker_shared_pool.hpp"

typedef struct _sclose{
	int over;
}sclose;

#define REG_POOL(argv) \
msg_shared_pool::init(argv); \
pipe_shared_pool::init(argv); \
block_shared_pool::init(argv); \
locker_shared_pool::init(argv); \
pub_view_data::init(argv)

#define SUB_MSG_SH_POOL(msg_name, fnc) msg_shared_pool::sub_sh_msg(msg_name,fnc)
#define PUB_MSG_SH_POOL(msg_name, data) msg_shared_pool::pub_sh_msg(msg_name, data )
#define END_MSG_SH_POOL(type,msg_name) msg_shared_pool::end_sub_msg<type>(msg_name)

#define SUB_PIPE_SH_POOL(pipe_name,fnc) pipe_shared_pool::sub_pipe(pipe_name,fnc)
#define PUB_PIPE_SH_POOL(pipe_name,data_name, data,len) pipe_shared_pool::push_back(pipe_name, data_name, data, len ,false )
#define END_PIPE_SH_POOL(pipe_name) pipe_shared_pool::end_sub_msg(pipe_name)

#define REG_BLOCK_SH_POOL(block_name,len) block_shared_pool::Reg_sh_range(block_name,len)
#define SET_BLOCK_SH_POOL(block_name,in,offset,len) block_shared_pool::set_block_data(block_name,in,offset,len)
#define GET_BLOCK_SH_POOL(block_name,out,offset,len) block_shared_pool::get_block_data(block_name,out,offset,len)

#define REG_LOCKER_SH_POOL(locker_name) locker_shared_pool::reg_locker(locker_name)
#define SET_LOCKER_SH_POOL(locker_name,lock) locker_shared_pool::set_locker(locker_name,lock)

#define PUB_VIEW_DATA_MERGE(data_name,pos) pub_view_data::pub(data_name,pos)
#define PUB_VIEW_DATA_NEW(data_name,pos) pub_view_data::pub(data_name,pos,false)

#endif//_SHARED_POOL_KYOSHO_2020_11_20_
