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
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

static void sigNotifier(union sigval sv)
{
	struct mq_attr attr;
	ssize_t nr;
	char *buf;
	mqd_t mqd = *((mqd_t *) sv.sival_ptr);

	printf ("Notification: There is a message in queue\n");

	if (mq_getattr(mqd, &attr) == -1)
		perror("mq_getattr");

	buf = malloc(attr.mq_msgsize);
	if (buf == NULL)
		perror("malloc");

	nr = mq_receive(mqd, buf, attr.mq_msgsize, NULL);
	if (nr == -1)
		perror("mq_receive");


	printf("Message from MQ: %s \n", buf);
	free(buf);
	exit(EXIT_SUCCESS);
}

int main()
{
	mqd_t mqd;
	struct sigevent sev;


	mqd = mq_open("/mque1",O_RDWR | O_CREAT, 0666, NULL);
	if (mqd == (mqd_t) -1)
		perror("mq_open");


	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = sigNotifier; 	
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &mqd;

	if (mq_notify(mqd, &sev) == -1)
		perror("mq_notify");

	pause();					

	mq_close(mqd);
	mq_unlink("/mque1");
}
