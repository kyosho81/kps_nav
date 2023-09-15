D:\MyRobot\N_KPS_Arm\bin\x64\Debug
start kps_core.exe
timeout /T 5 /NOBREAK
start kps_data_server.exe shared
timeout /T 5 /NOBREAK
start kps_localization.exe shared
timeout /T 5 /NOBREAK
start kps_dio.exe COM3
timeout /T 5 /NOBREAK
#kps_action_manage can set project ,but action lift err will stop agv!!!!!!!!! 
#start kps_action_manage.exe shared
#timeout /T 5 /NOBREAK 
#start kps_dynamic_loc.exe shared
#timeout /T 5 /NOBREAK 
#start kps_keygen
#timeout /T 5 /NOBREAK
start kps_monitor.exe shared