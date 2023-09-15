mkdir build-r
cd build-r
#-DBUILD_GMAP=1 -DOPENCV=1
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=release -DBUILD_SDK=1  -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 ../source
