
#ifndef __POPEN_H__
#define __POPEN_H__

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>

#ifndef _WINDOWS

class system{
public:

	static int cmd(const std::string cmd, std::string &output)
	{
	    FILE * fp;
	    int res = -1;
	    if ((fp = popen(cmd.c_str(), "r") ) == NULL)
	    {
	        printf("Popen Error!\n");
	        return -2;
	    }
	    else
	    {
	        char pRetMsg[10240]={0};
	        //get lastest result
	        while(fgets(pRetMsg,10240, fp) != NULL)
	        {
	            output+=pRetMsg;
	        }

	        if ( (res = pclose(fp)) == -1)
	        {
	            printf("close popenerror!\n");
	            return -3;
	        }
	        return 0;
	    }
	};
};

#endif
#endif//__POPEN_H__
