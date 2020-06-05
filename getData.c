#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>



int getData(int soc,char *sendData,char *recvData,int recvSize);
int opensocket(char *host,char *port);
void error(char *msg); 



void error(char *msg) { 
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1); 
}



int opensocket(char *host,char *port){
	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=PF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	if(getaddrinfo(host,port,&hints,&res)!=0){
		fputs("Can't resolve the address\n",stderr);
		exit(1);
	}
	int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
	if (s == -1)
		error("Can't open socket");
	int serv=connect(s,res->ai_addr,res->ai_addrlen);
	if (serv == -1)   
		error("Can't connect to socket");
	freeaddrinfo(res);
	return s;

}





int getData(int soc,char *sendData,char *recvData,int recvSize){
	char buff[1000];
	int c;
	if(soc<=0){
  		fprintf(stderr,"connection failed : %s\n",strerror(errno));
		exit(1);
	}
	char *b=sendData;
//	printf("'%s'\n",b);
s:
	c=send(soc,b,strlen(b),0);
	if(c<strlen(b)){
 		b+=c;
		c=0;
		goto s;
	}
	memset(recvData,'\0',recvSize);
	c=0;
	char *buffer=recvData;
//	sleep(2);
	while((c=read(soc,buffer,recvSize))!=0){
		if(c<0){
 			printf("read error");
			return -1;
		}
		if(strstr(buffer,"</html>"))
			break;
/*		else{
			char b[2];
	//		sleep(2);
			while((recv(soc,b,1,MSG_DONTWAIT))>0);
			return -2;
		}*/
//		c-=10;
		buffer+=c;
		recvSize-=c;
		c=0;
	}
	if(!strcmp(buff,"[null]")){
		printf("Data not found\n");
		return -1;
	}
	return 0;

}
