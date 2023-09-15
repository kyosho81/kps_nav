mkdir build-sr
cd build-sr
#-DBUILD_GMAP=1 DSURO=1 -DOPENCV=1
#N_KPS_Arm/source/sdk/include/suro/message/genProto.sh
export SURODIR=/home/tony/pack_x86
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=release -DSURO=1 -DBUILD_SDK=1 -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8  ../source
