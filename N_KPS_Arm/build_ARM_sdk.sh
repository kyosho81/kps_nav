mkdir build-ar
cd build-ar
#-DBUILD_GMAP=1
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=release -DARM=1 -DBUILD_SDK=1 -DOPENCV=1 -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 ../source
