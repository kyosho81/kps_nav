#sudo apt-get install sshpass
#sudo apt-get install expect
#! /usr/bin/expect
function check_yes() {
	echo "cmd: $1"
	str=""
	read -p "y?n (n)" str
 	echo "prass: $str"
	if [ "$str" == "y" ]; then
		$1
		echo "update over!"
       
		return 1
	fi
	
	return 0
}




check_yes "sshpass -p ubuntu scp -P 10003 kps_core            ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
check_yes "sshpass -p ubuntu scp -P 10003 kps_data_server     ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
check_yes "sshpass -p ubuntu scp -P 10003 kps_action_manage   ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
check_yes "sshpass -p ubuntu scp -P 10003 suro_localization   ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
check_yes "sshpass -p ubuntu scp -P 10003 suro_dynamic_nav    ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
check_yes "sshpass -p ubuntu scp -P 10003 kps_keygen          ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"

#check_yes "sshpass -p ubuntu scp -P 10003 kps_core            ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
#check_yes "sshpass -p ubuntu scp -P 10003 kps_core            ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"

#echo "update kps_core              "
#check_yes "sshpass -p ubuntu scp -P 10003 kps_core            ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin"
#if [ "$?" = "1" ]; then

#fi 
#sshpass -p ubuntu scp -P 10003 kps_core            ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin
#sshpass -p ubuntu scp -P 10003 kps_data_server     ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin
#echo "update kps_data_server       over!"
#sshpass -p ubuntu scp -P 10003 kps_action_manage   ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin
#echo "update kps_action_manage     over!"
#sshpass -p ubuntu scp -P 10003 suro_localization   ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin
#echo "update suro_localization     over!"
#sshpass -p ubuntu scp -P 10003 suro_dynamic_nav    ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin
#echo "update suro_dynamic_nav      over!"
#sshpass -p ubuntu scp -P 10003 kps_keygen          ubuntu@tuvwx.xyz:/home/ubuntu/lib/AGVCar/bin
#echo "update kps_keygen            over!"
