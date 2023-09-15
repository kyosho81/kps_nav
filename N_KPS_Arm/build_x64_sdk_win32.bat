mkdir build-d
cd build-d
cmake -G "Visual Studio 10 2010" -DCMAKE_BUILD_TYPE=debug -DBUILD_SDK=1 -DOPENCV=1 ../source
