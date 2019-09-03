
B
/************************************************************************
* Filename :        receiver2.c
*
* Description :	Client2 code 2 receives the message sent from the 
*		server and acknowledges it
*
*
*************************************************************************/






struct mesg_buffer
{ 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid;
	//Creating a message queue 
	msgid = msgget(1, 0666 | IPC_CREAT); 

	//Receiving message sent by the server 
	msgrcv(msgid, &message, sizeof(message), 2, 0); 

	//Displaying the message received
	printf("Data Received is : %s \n",message.mesg_text);
	//Sending acknowlegment back to server  
	strcpy(message.mesg_text ,"Acknowledged\n");
	msgsnd(msgid, &message, sizeof(message), 0);
	return 0; 
} 


