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
//	FILE *fp=fopen("rawData","w");


	//open database
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	int dbAvailable=0;
//	remove("/sdcard/sscResult.db");
   	rc = sqlite3_open("/sdcard/sscResult.db", &db);

  	if( rc ) {
      		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); 
		db=NULL;
		exit(1);
	} else{
		dbAvailable=1;
	}

	for(int i=rollLower;i<=rollHeigher;i++){
		if(checkAvailable(db,i)){
			if(i==rollHeigher)
				return;
		}
		else{
			rollLower=i;
			break;
		}
	}	
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


//Name,Roll_NO,Board,Father\'s Name,_Group,Mother\'s Name,Session,Registration NO,Type,Institution,GPA,Date of Birth,Bangla,English,Mathmatics,Bangladesh & Global Studies,Religious Studies,Physics,Chemestry,Biology,ICT,Optional,Physical Education,Career Education,Total without CA,Total

	if(dbAvailable){
	char *sql ="CREATE TABLE SCIENCE("  \
      "Name           TEXT," \
      "Roll_NO      NUMBER(6) PRIMARY KEY NOT NULL," \
      "Board        TEXT,"\
      "Fathers_Name        TEXT,"\
      "Mothers_Name        TEXT,"\
      "_Group        TEXT," \
      "Registration_NO        INT," \
      "Session        TEXT," \
      "Type        TEXT," \
      "Institution        TEXT," \
      "GPA        NUMBER(1,2)," \
      "Date_of_Birth        TEXT," \
      "Bangla        INT(3)," \
      "English        INT(3)," \
      "Mathmatics        INT(3)," \
      "Bangladesh_and_Global_Studies        INT(3)," \
      "Religious_Studies        INT(3)," \
      "Physics        INT(3)," \
      "Chemestry        INT(3)," \
      "Biology        INT(3)," \
      "ICT        INT(3)," \
      "Optional        INT(3)," \
      "Physical_Education        INT(3)," \
      "Career_Education        INT(3)," \
      "Total_without_CA        INT(4)," \
      "Total       INT(4));";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   	if( rc != SQLITE_OK && !strstr(zErrMsg,"exists")){
      		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      		sqlite3_free(zErrMsg);
		dbAvailable=0;
		sqlite3_close(db);
		db=NULL;
		exit(1);
	}
	}
/*	char fname[100];
	char *fc=NULL;
	FILE *fn;
	memset(fname,0,100);*/
	int j=0;
	for(int i=rollLower;i<=rollHeigher;i++,j++){
redo:		
//		soc=opensocket(host,port);
		if(checkAvailable(db,i))
			continue;
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
			else if((w2-w1)<7&&(w2-w1)>2){
				memmove(w1,w2+2,(w2+2-w1));
				recvBack-=(w2-w1+2);
				w2=NULL;
				w1=NULL;
			}
			else{
				w1=w2;
				w2=NULL;
			}
			recvBack+=2;
		}
		recvBack=NULL;
		w2=NULL;

		/*sprintf(fname,"/sdcard/tmp/result/roll_%d.html",i);
		fn=fopen(fname,"w");
		fc=recvData;
		fc=strstr(fc,"<!DOCTYPE");
		fputs(fc,fn);
		fc=NULL;
		fclose(fn);
		memset(fname,0,100)*/;
//		printf("\tWriting...");
		handleData(recvData,db);
		printf("Done\n");
//		close(soc);
	}
	close(soc);
	if(dbAvailable)
		sqlite3_close(db);
//	fclose(fp);
	return;
}
