#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssres.h"

#define sendDataSize 2025
#define recvDataSize 10241


/*int getData(int soc,char *sendData,char *recvData,int recvSize);
int opensocket(char *host,char *port);
void error(char *msg); 
void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);
void handleData(FILE *fp,char *recvData);
*/

void dataGatherer(int rollLower,int rollHeigher){
	char sendData[sendDataSize];
	char recvData[recvDataSize];
	int soc;
	int retry=0;
//	char *w=NULL,*recvBack=NULL;//,*lc=NULL;
//	int l=0;
	char *host="sresult.bise-ctg.gov.bd";
	char *port="80";
//	FILE *fp=fopen("result.html","w");
	FILE *fp=fopen("rawData","w");
	memset(sendData,0,sendDataSize);

	int k=0;
//	htmlStart(fp);

//	soc=opensocket(host,port);
/*getCokkie:
	sprintf(sendData,"GET /individual/index.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\n\r\n");
	if(getData(soc,sendData,recvData,recvDataSize)==-1){
		close(soc);
		exit(1);
	}
	char Cookie[500];
	memset(Cookie,0,500);
	char *c=recvData;
	if((c=strstr(c,"Set-Cookie:"))){
//		printf("'%s'",c);
		c+=sizeof("Set-Cookie:");
		char *d=strchr(c,';');
		memmove(Cookie,c,(d-c));
//		printf("Got Cookie=%s",Cookie);
	}
	else{
		if(retry<5){
			retry++;
			goto getCokkie;
		}
		else{
			close(soc);
			printf("%s\n",recvData);
			error("Server not responding");
		}
	}*/
	for(int i=rollLower;i<=rollHeigher;i++){
redo:		
		soc=opensocket(host,port);
		printf("Feteching Roll: %d ...",i);
//redo2:
//		sprintf(sendData,"POST /individual/result.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\nCookie: %s\r\nUser-Agent: HTTPTool/1.0\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 11\r\n\r\nroll=%d\r\n",Cookie,i);

		sprintf(sendData,"POST /individual/result.php HTTP/1.1\r\nHost: sresult.bise-ctg.gov.bd\r\nUser-Agent: HTTPTool/1.0\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 11\r\n\r\nroll=%d\r\n",i);
		if((k=getData(soc,sendData,recvData,recvDataSize))==-1){
//		if((k=getDatawithnc(sendData,recvData,recvDataSize))==-1){
			if(retry<6){
				printf("\nRetring....\n");
				retry++;
				close(soc);
				goto redo;
			}
			else {
				retry=0;
				continue;
			}
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
/*		recvBack=recvData;
		while((w=strstr(recvBack,"\r\n"))){
			recvBack=w+1;
			l=2;
			if((lc=strstr(w,"<chunk-end>"))){
				if((lc-w)<20){
					l=(lc-w)+strlen("<chunk-end>");
//					memmove(w,w+l,strlen((w+l)));
				}	
			}
			memmove(w,w+l,strlen((w+l)));
		}
		recvBack=NULL;
		w=NULL;*/
		printf("\tWriting...");
		handleData(fp,recvData);
		printf("Done\n");
		close(soc);
	}
	close(soc);
//	htmlEnd(fp);
	fclose(fp);
	return;
}
