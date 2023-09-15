#include "interpro_shared/msg_shared_pool.hpp"
#include "interpro_shared/pipe_shared_pool.hpp"
#include "interpro_shared/locker_shared_pool.hpp"
#include "interpro_shared/block_shared_pool.hpp"

std::map<std::string,void*> msg_shared_pool::m_global_shared_data_ptr_;
sh_multimap msg_shared_pool::g_sh_multimap_("core_shared_msg_list");
std::string msg_shared_pool::nm_;

std::map<std::string,void*> pipe_shared_pool::m_global_shared_data_ptr_;
sh_multimap pipe_shared_pool::g_sh_multimap_("core_sh_pipe_list_list");
std::string pipe_shared_pool::nm_;

std::map<std::string,shared_locker*> locker_shared_pool::m_global_shared_data_ptr_;
sh_multimap locker_shared_pool::g_sh_multimap_("core_shared_locker_list");

std::map<std::string,void*> block_shared_pool::m_global_shared_data_ptr_;
sh_multimap block_shared_pool::g_sh_multimap_("core_sh_block_list_list");

