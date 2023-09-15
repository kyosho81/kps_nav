mkdir build-r
cd build-r
cmake -G "Visual Studio 10 2010" -DCMAKE_BUILD_TYPE=release -DBUILD_SDK=1 -DOPENCV=1 ../source
