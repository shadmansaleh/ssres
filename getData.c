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
	int c;
	if(soc<=0){
  		fprintf(stderr,"connection failed : %s\n",strerror(errno));
		exit(1);
	}
	char *b=sendData;
s:
	c=send(soc,b,strlen(b),0);
	if(c<strlen(b)){
 		b+=c;
		c=0;
		goto s;
	}
//	if(recvData)
	memset(recvData,'\0',recvSize);
	c=0;
	char *buffer=recvData;
	while(!(strstr(recvData,"\r\n0\r\n"))){
		if((c=recv(soc,buffer,recvSize,0))<0){
			printf("read error\n");
			return -1;
		}
		else if(c==0){
			printf("Server closed connection\n");
			return -1;
		}

		buffer+=c;
		recvSize-=c;
	}
/*	char buffer[1001];
	char size[21];
	int sizei=0;
	memset(buffer,0,1001);
	memset(size,0,21);
	c=0;
	int failCount=0;
	char *cP=NULL,*Bu=buffer,*BuBak=buffer,*rD=recvData;//,*rDBak=recvData;
	while((cP=strstr(BuBak,"\r\n\r\n"))==NULL){
		c+=recv(soc,Bu,1000,0);
		if(c==0&&failCount<5){
			failCount++;
		}
		else if(c!=0)
			failCount=0;
		else
			return -1;
		Bu+=c;
	}
	memcpy(headerData,buffer,(cP-buffer));
	memmove(buffer,(cP+4),strlen(cP+4));
	cP=NULL;
	int l=0;
//	Bu=buffer;
//	BuBak=buffer;
	while(recvData && !strstr(recvData,"</html>")){
//	Bu=buffer;
	BuBak=buffer;
	sizei=0;
	memset(size,0,21);
//	c=0;
	while((cP=strstr(BuBak,"\r\n"))==NULL){
		c+=recv(soc,Bu,1000,0);
		Bu+=c;
	}
	if((BuBak-buffer)>20){
		printf("Error:Chunk Size Too Big\n");
		return -1;
	}	
	else
		memcpy(size,buffer,(cP-buffer));
	sizei=htoi(size);
//	c-=(cP+2-buffer);
	if(c>=sizei+2){
		char *ptr1=strstr((cP+2),"\r\n");
		if(ptr1){
			memmove(rD,(cP+2),(ptr1-cP-2));
			rD+=(ptr1-cP-2);
			l=(ptr1+2-buffer);
			memmove(buffer,ptr1+2,strlen(ptr1+2));
			Bu-=l;
			continue;			
		}
	}
	sizei-=c;
	memcpy(rD,cP+2,(Bu-cP-2));
//	int l=cP+2-buffer;
//	memmove(buffer,cP+2,(Bu-cP-2));
//	Bu-=l;
	rD+=(Bu-cP-2);
	memset(buffer,0,1001);
	Bu=buffer;
	c=0;
	while(c<sizei){
		if((c=recv(soc,buffer,(sizei>1000)?1000:sizei,0))<0)
			return -1;
		sizei-=c;
		memmove(rD,buffer,c);
		memset(buffer,0,1001);
		rD+=c;
		c=0;
	}
	recv(soc,buffer,2,0);
	memset(buffer,0,2);
	if(strcmp(buffer,"\r\n"))
		perror("Read error occured");
//	Bu=buffer;
	c=0;
}*/
	return 0;

}
