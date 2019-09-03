/************************************************************************

*
* Description :	Server code which sends a text message to the receiver
*
*
*************************************************************************/


#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>


struct msgbuf {
	long mtype;
	char mtext[80];
};

int main() {

	int qid;
	key_t msgkey;
	struct msgbuf msg;
	int msgtype = 3;
	
	printf("Enter message: ");
	fgets(msg.mtext, sizeof(msg.mtext), stdin);
	printf("\nChoose the client  1.Client 1    2.Client 2 : ");
	scanf("%ld", &msg.mtype);	
	msgkey = ftok("key_file.txt", 'b');
	
	qid = msgget(msgkey, 0666 | IPC_CREAT);
	msgsnd(qid, (void *) &msg, sizeof(msg.mtext),IPC_NOWAIT);
	memset(msg.mtext, 0, 80);
	while(1) 
	{	
	msgrcv(qid, (void *) &msg, sizeof(msg.mtext), 3, MSG_NOERROR | IPC_NOWAIT);
	}
	printf("message received: %s \n", msg.mtext);
 	msgctl(qid, IPC_RMID, NULL); 
		
}
