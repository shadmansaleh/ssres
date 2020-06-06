#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssres.h"
#include <fcntl.h>
#define sendDataSize 2025
#define recvDataSize 10241

void dataGatherer(int rollLower,int rollHeigher){
	char sendData[sendDataSize];
	char recvData[recvDataSize];
	int soc;
	int retry=0;
	char *w1=NULL,*recvBack=NULL,*w2=NULL;
	char *host="sresult.bise-ctg.gov.bd";
	char *port="80";
	FILE *fp=fopen("rawData","w");
	memset(sendData,0,sendDataSize);
	memset(recvData,0,recvDataSize);
	int k=0;

	soc=opensocket(host,port);
getCokkie:
	sprintf(sendData,"GET /individual/index.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\n\r\n");
	if(getData(soc,sendData,recvData,recvDataSize)==-1){
		close(soc);
		exit(1);
	}
	char Cookie[500];
	memset(Cookie,0,500);
	char *c=recvData;
	if((c=strstr(c,"Set-Cookie:"))){
		c+=sizeof("Set-Cookie:");
		char *d=strchr(c,';');
		memmove(Cookie,c,(d-c));
	}
	else{
		if(retry<5){
			retry++;
			goto getCokkie;
		}
		else{
			close(soc);
			error("Server not responding");
		}
	}
	for(int i=rollLower;i<=rollHeigher;i++){
redo:		
//		soc=opensocket(host,port);
		printf("Feteching Roll: %d ...",i);

		sprintf(sendData,"POST /individual/result.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\nCookie: %s\r\nUser-Agent: HTTPTool/1.0\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 11\r\n\r\nroll=%d\r\n",Cookie,i);


//		sprintf(sendData,"POST /individual/result.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\nUser-Agent: HTTPTool/1.0\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 11\r\n\r\nroll=%d\r\n",i);
		if((k=getData(soc,sendData,recvData,recvDataSize))==-1){
			if(retry<6){
				printf("\nRetring....\n");
				retry++;
	//			close(soc);
				goto redo;
			}
			else {
				retry=0;
				continue;
			}
	//		close(soc);
	//		exit(1);
		}
		retry=0;
		recvBack=recvData;
		while((w2=strstr(recvBack,"\r\n"))){
			if(w1==NULL){
				w1=w2;
				w2=NULL;
				
			}
			else if((w2-w1)<7){
				memmove(w1,w2+2,(w2+2-w1));
				recvBack-=(w2-w1+2);
				w2=NULL;
				w1=NULL;
			}
			recvBack+=2;
		}
		recvBack=NULL;
		w2=NULL;
		printf("\tWriting...");
		handleData(fp,recvData);
		printf("Done\n");
//		close(soc);
	}
	close(soc);
	fclose(fp);
	return;
}
