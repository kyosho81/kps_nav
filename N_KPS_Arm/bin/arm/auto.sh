export LD_LIBRARY_PATH=/home/pi/kps_nav
echo $LD_LIBRARY_PATH
sudo chmod a+wr /dev/ttyAMA3
./kps_core &
sleep 3s
./kps_data_server shared &
#sleep 5s
#./kps_localization shared &
#sleep 5s
#./kps_loopclosure shared &
echo "init kps over!!"
