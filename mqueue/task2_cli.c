/**************************************************************************
* Filename :  client_posix.c            
*	
* Description : Client program that sends user input message to server (POSIX API)
*
*
***************************************************************************/

#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	mqd_t mqd;
	ssize_t ret;
	char buf[30];

	printf("Enter message to server: ");
	fgets(buf,30,stdin);

	mqd = mq_open("/mque1", O_RDWR);
	if (mqd == (mqd_t) -1)
		perror("mq_open");

	ret = mq_send (mqd, buf, 30, 0);
	if (ret == -1)
		perror("mq_receive");
}
