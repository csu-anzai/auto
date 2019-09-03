/************************************************************************
* Filename :        server.c
*
* Description :	Server code which sends a text message to the receiver
*
*
*************************************************************************/

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

// structure for message queue 
struct message_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid,a;
	printf("Choose the Client 1.Client_1 2.Client_2\n");
	scanf("%d",&a);
	//Creating a message queue
	msgid = msgget(1, 0666 | IPC_CREAT); 
	message.mesg_type = a;
	printf("Enter the data to be sent: \n"); 
	scanf("%s", message.mesg_text); 

	//Sending message to the message queue for receiver
	msgsnd(msgid, &message, sizeof(message), 0); 
	//Displaying the message being sent
	printf("Data sent to Client %d :\t\t : %s \n", a, message.mesg_text);

	//Receiving the acknowledgment from the client   
	msgrcv(msgid, &message, sizeof(message), a, 0); 
	printf("%s", message.mesg_text);
	msgctl(msgid, IPC_RMID, NULL);
  	return 0; 
} 

