#include "ssres.h"
#include <stdio.h>

extern FILE *outFile;

void giveResult(char *dbName,char *sortcondition,char *limitcondition){
	if(outFile){
	sqlite3 *db=NULL;
	int rc=0;
	char *zErrMsg=NULL;
	char sql[1025];
	memset(sql,0,1025);
	rc=sqlite3_open(dbName,&db);
	if(rc){
		fprintf(stdout,"Error: Cann't open %s for reading\n",dbName);
	}
	else{
		sprintf(sql,"SELECT * FROM SCIENCE %s %s;",limitcondition,sortcondition);
		rc=sqlite3_exec(db,sql,callback,0,&zErrMsg);
		if(rc!=SQLITE_OK){
			fprintf(stderr,"SQL Error : %s\n",zErrMsg);
			sqlite3_free(zErrMsg);
			sqlite3_close(db);
			return;
		}
	}
	}else{
		fprintf(stderr,"Out File Not Available ... exiting\n");
	}
	return;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   static int index=1;
   result res;
   memset(&res,0,sizeof(result));
   res.sn=index++;
   for(i=0;i<argc;i++){
	if(!strcmp(azColName[i],"Name"))
		memcpy(res.name,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Roll_NO"))
		memcpy(res.roll_no,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Board"))
		memcpy(res.board,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Fathers_Name"))
		memcpy(res.fname,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"_Group"))
		memcpy(res.group,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Mothers_Name"))
		memcpy(res.mname,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Session"))
		memcpy(res.session,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Registration_NO"))
		memcpy(res.regno,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Type"))
		memcpy(res.type,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Institution"))
		memcpy(res.institue,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"GPA"))
		memcpy(res.gpa,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Date_of_Birth"))
		memcpy(res.dob,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Bangla"))
		memcpy(res.bangla,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"English"))
		memcpy(res.english,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Mathmatics"))
		memcpy(res.math,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Bangladesh_and_Global_Studies"))
		memcpy(res.bgs,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Religious_Studies"))
		memcpy(res.rs,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Physics"))
		memcpy(res.physics,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Chemestry"))
		memcpy(res.chemestry,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Biology"))
		memcpy(res.biology,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"ICT"))
		memcpy(res.ict,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Optional"))
		memcpy(res.hm,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Physical_Education"))
		memcpy(res.pehs,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Career_Education"))
		memcpy(res.cc,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Total_without_CA"))
		memcpy(res.tow,argv[i],strlen(argv[i]));
	else if(!strcmp(azColName[i],"Total"))
		memcpy(res.to,argv[i],strlen(argv[i]));
	else{
		fprintf(stderr,"Unkown column : %s\n",azColName[i]);
	}
   }
   writeData(outFile,&res,1);
   return 0;
}

