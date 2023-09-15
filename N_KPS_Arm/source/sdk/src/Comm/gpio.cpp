#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>


#include <string.h>

#include "Comm.h"




#if defined(_WINDOWS)
#else
#include <unistd.h>
#endif

#include "Comm/gpio.h"

gpio::gpio(){

}

gpio::~gpio(){

}

void gpio::init_DI(std::vector<int> pin_list){

	std::vector<int>::iterator it = pin_list.begin();
	for( ; it != pin_list.end() ; ++it ){
		int pin = *it;
		export_gpio(pin,false);
		std::cout<<"export DI:"<<pin<<std::endl;
	}
}
void gpio::init_DO(std::vector<int> pin_list){

	std::vector<int>::iterator it = pin_list.begin();
	for( ; it != pin_list.end() ; ++it ){
		int pin = *it;
		export_gpio(pin,true);
		std::cout<<"export DO:"<<pin<<std::endl;
	}

}
bool gpio::set_gpio_on(int pin){

#if defined(_WINDOWS)
	return false;
#else
	FILE* valuefd;

	char v[200];
	// Get the GPIO value ready to be toggled
	sprintf(v,"/sys/class/gpio/gpio%d/value",pin);
	//valuefd = open("/sys/class/gpio/gpio240/value", O_RDWR);
	valuefd = fopen((const char*)v, "w");
	if (valuefd < 0)
	{
		printf("Cannot open GPIO value\n");
		return false;
	}
	fprintf(valuefd,"1");
	fclose(valuefd);
	//printf("GPIO:%d  On!\n",pin);

	return true;

#endif

}
bool gpio::set_gpio_off(int pin){

#if defined(_WINDOWS)
	return false;
#else
	FILE* valuefd;

	char v[200];
	// Get the GPIO value ready to be toggled
	sprintf(v,"/sys/class/gpio/gpio%d/value",pin);
	//valuefd = open("/sys/class/gpio/gpio240/value", O_RDWR);
	valuefd = fopen((const char*)v, "w");
	if (valuefd < 0)
	{
		printf("Cannot open GPIO value:%d \n",pin);
		return false;
	}
	fprintf(valuefd,"0");
	fclose(valuefd);
	//printf("GPIO:%d  Off!\n",pin);

	return true;

#endif

}
int gpio::get_gpio(int pin){

#if defined(_WINDOWS)
	return 0;
#else
	char value_str[3];
	int fd;

	char v[200];
	// Get the GPIO value ready to be toggled
	sprintf(v,"/sys/class/gpio/gpio%d/value",pin);
		//valuefd = open("/sys/class/gpio/gpio240/value", O_RDWR);
	fd = open(v, O_RDONLY);
	if (fd < 0) {
		printf("Cannot open GPIO value:%d \n",pin);
		return -1;
	}

	if (read(fd, value_str, 3) < 0) {
		printf("Cannot read GPIO pin:%d \n",pin);
		return -1;
	}

	close(fd);
	return (atoi(value_str));
#endif
}

bool gpio::export_gpio(int pin,bool b_out){

#if defined(_WINDOWS)
	return false;
#else
	FILE* exportfd;
	FILE* directionfd;

	//printf("GPIO test running...\n");

	// The GPIO has to be exported to be able to see it
	// in sysfs

	exportfd = fopen("/sys/class/gpio/export", "w");
	if (exportfd < 0)
	{
		printf("Cannot open GPIO to export it\n");
		return false;
	}

	fprintf(exportfd,"%d",pin);

	fclose(exportfd);

	//printf("GPIO:%d exported successfully\n",pin);

	char d[200];
	// Update the direction of the GPIO to be an output
	sprintf(d,"/sys/class/gpio/gpio%d/direction",pin);
	//directionfd = open("/sys/class/gpio/gpio240/direction", O_RDWR);
	directionfd = fopen((const char*)d, "w");
	if (directionfd < 0)
	{
		printf("Cannot open GPIO direction it\n");
		return false;
	}
	if(b_out){
		fprintf(directionfd,"out");
		//printf("GPIO:%d direction set out successfully\n",pin);
	}else{
		fprintf(directionfd,"in");
		//printf("GPIO:%d direction set in successfully\n",pin);
	}

	fclose(directionfd);
#endif

}

bool gpio::unexport_gpio(int pin){

#if defined(_WINDOWS)
	return false;
#else
	FILE* exportfd;
	exportfd = fopen("/sys/class/gpio/unexport","w");
	fprintf(exportfd,"%d",pin);
	fclose(exportfd);

	//printf("GPIO:%d  unexport!\n",pin);

	return true;

#endif

}
