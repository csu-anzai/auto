/**************************************************************************
* Filename :  client1.c      	
*
* Description : 
* 	
*
*
**************************************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main()
{

	int qid;
	key_t msgkey;
	struct msgbuf msg;
	int msgtype = 1;
	
	msgkey = ftok("key_file.txt", 'b');
	qid = msgget(msgkey, 0666 | IPC_CREAT);
	msgrcv(qid, (void *) &msg, sizeof(msg.mtext), msgtype, MSG_NOERROR | IPC_NOWAIT);
	printf("message received: %s\n", msg.mtext);
	msg.mtype = 3;
	memset(msg.mtext,0,80);
	snprintf(msg.mtext, sizeof(msg.mtext), "Acknowledement by client 2\n");
 	msgctl(qid, IPC_RMID, NULL); 
	return 0;
}
