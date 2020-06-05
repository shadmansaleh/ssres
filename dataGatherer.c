#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define sendDataSize 2025
#define recvDataSize 10241


int getData(int soc,char *sendData,char *recvData,int recvSize);
int opensocket(char *host,char *port);
void error(char *msg); 
void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);
void handleData(FILE *fp,char *recvData);


void dataGatherer(int rollLower,int rollHeigher){
	char sendData[sendDataSize];
	char recvData[recvDataSize];
	int soc;
	int retry=0;
	char *w=NULL,*recvBack=NULL;
	char *host="sresult.bise-ctg.gov.bd";
	char *port="80";
//	FILE *fp=fopen("result.html","w");
	FILE *fp=fopen("./rawData","w");//stdout;
	memset(sendData,0,sendDataSize);

	int k=0;
//	htmlStart(fp);

	soc=opensocket(host,port);
	sprintf(sendData,"GET /individual/index.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\n\r\n");
	if(getData(soc,sendData,recvData,recvDataSize)==-1){
		close(soc);
		exit(1);
	}
	char Cookie[500];
	memset(Cookie,0,500);
	char *c=recvData;
	c=strstr(c,"Set-Cookie:");
//	printf("'%s'",c);
	c+=sizeof("Set-Cookie:");
	char *d=strchr(c,';');
	memmove(Cookie,c,(d-c));
//	printf("Got Cookie=%s",Cookie);
	for(int i=rollLower;i<=rollHeigher;i++){
redo:		
	//	soc=opensocket(host,port);
		printf("Feteching Roll: %d ...",i);
//redo2:
		sprintf(sendData,"POST /individual/result.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\nCookie: %s\r\nUser-Agent: HTTPTool/1.0\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 11\r\n\r\nroll=%d\r\n",Cookie,i);
		if((k=getData(soc,sendData,recvData,recvDataSize))==-1){
			if(retry<6){
				printf("\nRetring....");
				retry++;
				goto redo;
			}
			else continue;
	//		close(soc);
	//		exit(1);
		}
/*		else if(k==-2){
				if(retry<10){
	//			printf("\nRetring....");
				retry++;
				goto redo2;
			}
			else continue;
		
		}*/
		retry=0;
		recvBack=recvData;
		while((w=strstr(recvBack,"\r\n"))){
			recvBack=w+1;
			memmove(w,w+2,strlen((w+2)));
		}
		recvBack=NULL;
		w=NULL;
		printf("\tWriting...");
		handleData(fp,recvData);
		printf("Done\n");
	//	close(soc);
	}
	close(soc);
//	htmlEnd(fp);
	fclose(fp);
	return;
}
