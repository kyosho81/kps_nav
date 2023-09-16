#win32 vs2010 compile
1. compile boost
   
   decompess boost_1_58_0.tar.gz
   
   bootstrap.bat
   
   b2.exe

2. cmake project
   
   decompress kps_nav-main.zip
   
   edit file "N_KPS_Arm/source/CMakeX64_Boost.txt" 
   replace the path>>link_directories("e:/N_KPS_Arm/lib")
   replace the path>>set(BOOST_ROOT "e:/boost_1_58_0")
   replace the path>>set(BOOST_LIBRARYDIR "e:/boost_1_58_0/stage")
   
   cd N_KPS_Arm
   
   mkdir build-d
   
   cd build-d
   
   cmake ../source


3 dump
ulimit -c unlimited
编译的时候添加-g选项
gdb [执行程序] [coredump文件]
