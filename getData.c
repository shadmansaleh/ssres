#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ssres.h"

/*int getData(int soc,char *sendData,char *recvData,int recvSize);
int opensocket(char *host,char *port);
void error(char *msg); 
*/


void error(char *msg) { 
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1); 
}



int opensocket(char *host,char *port){
	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=PF_UNSPEC;
//	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;
///	hints.ai_socktype=SOCK_DGRAM;
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



int getDatawithnc(char *sendData,char *recvData,int recvSize){
	pid_t p;
	int r[2];
	int w[2];
	int exit_status;
	pipe(r);
	pipe(w);
	if((p=fork()))//fork failed
			return -1;
	else if(p==0){//child
		close(r[0]);
		close(w[1]);
		dup2(r[1],1);
		dup2(w[0],0);
		execlp("ncat","ncat","sresult.bise-ctg.gov.bd","80",(char *)NULL);					
	}
	else{
		close(r[1]);
		close(w[0]);
		waitpid(p,&exit_status,WNOHANG);
		write(w[1],sendData,strlen(sendData));
		char buffer[1001];
		memset(buffer,0,1001);
		int c=0;
		while(!strstr(recvData,"\n0")){
			c=read(r[0],buffer,1000);
			if(c<=0)
				break;
			buffer[c]='\0';
			strcat(recvData,buffer);
			memset(buffer,0,1001);
		}
		kill(p,SIGTERM);
		waitpid(p,&exit_status,WNOHANG);
	}
	return 0;
}


int getData(int soc,char *sendData,char *recvData,int recvSize){
//	char buff[1000];
	int c;
	if(soc<=0){
  		fprintf(stderr,"connection failed : %s\n",strerror(errno));
		exit(1);
	}
	char *b=sendData;
//	char *bufferBack=NULL;
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
/*	char buffer[1001];
	memset(buffer,0,1001);
//	int c=0;
	while(!strstr(recvData,"\n0")){
		c=read(soc,buffer,1000);
		if(c<0){
 			printf("read error");
			return -1;
		}
		else if(c==0)
			break;
		buffer[c]='\0';
		strcat(recvData,buffer);
		memset(buffer,0,1001);
		c=0;
	}
	return 0;*/


	char *buffer=recvData;
	while((c=read(soc,buffer,recvSize))!=0){
		if(c<0){
 			printf("read error");
		//	sleep(1);
		//	recv(soc,buffer,recvSize,MSG_DONTWAIT);
		//	return -1;
			break;
		}
		if(strstr(buffer,"</html>"))
			break;
/*		bufferBack=buffer+c-1;
		while(*bufferBack){
			if(*(bufferBack)=='\n'&&*(bufferBack-1)&&*(bufferBack-1)=='\r'){
				bufferBack-=1;				
				break;
			}
			bufferBack--;
		}
		if(*bufferBack){
			buffer=bufferBack;
			memset(bufferBack,0,(recvSize-(bufferBack-recvData)));
		}
		else{
			printf("sliped through\n");
			buffer+=c;
		}*/
		buffer+=c;
		recvSize-=c;
///		strcpy(buffer,"<chunk-end>");
//		buffer+=strlen("<chunk-end>");
//		recvSize-=(c+strlen("<chunk-end>"));
		c=0;
	}
	*buffer='\0';
	if(!strcmp(recvData,"[null]")){
		printf("Data not found\n");
		return -1;
	}
	return 0;

}
