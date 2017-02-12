// NAME       :  DIPUNJ GUPTA
// REG. NO.   :  20154061
// GROUP      :  CS-A2
// SEMESTER   :  IVth
// LAB        :  PROGRAMMING TOOLS - II(SYSTEM CALLS)
// DATE       :  FEB 9TH, 2017
// ASSIGNMENT :  5
//
// PROBLEM    :  #3-CLIENT-B
// CODED IN   :  C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

//	CLIENT FILE
int main()
{
	char s[300];
	char resp_buff[1000];
	int num_read,num_write;
	int fd_WK,fd_CL[1];

	mknod("WELL_KNOWN",S_IFIFO|0666,0);
	fd_WK = open("WELL_KNOWN",O_RDWR);
	mknod("SRVR_2_CLB",S_IFIFO|0666,0);
	fd_CL[1] = open("SRVR_2_CLB",O_RDWR);

	printf("Created the pipe...\nEnter some text :: ");

	// SEND REQUEST
	while (gets(s),!feof(stdin))
	{
		if((num_read = write(fd_WK,s,strlen(s))) == -1)
			perror("write");
		else
		{
			printf("CLIENT: Request sent to server :::bytes written :: %dBytes\n",num_read);
			break;
		}
	}	
	
	// OUTPUT THE RESPONSE FROM SERVER
	{
		if((num_write = read(fd_CL[1],resp_buff,1000)) == -1)
			perror("read");
		else
		{
			s[num_write] = '\0';
			printf("CLIENT: Recieved : %dBytes\n\n\t\t=======SERVER RESPONSE========\n\n %s \n\n",num_write,resp_buff);
		}
	}
	return 0;
}
