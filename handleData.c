#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ssres.h"
#include <sqlite3.h>
#define valSize 100


//int callback(void *NotUsed, int argc, char **argv, char **azColName);

/*char * getValue(char *Data,char *key,char *value);
int getnumber(char *s);
void setupstruct(char *Data,result *res);
char* itoa(int num, char* str, int base);
void writeData(FILE *fp,result *res,int html);
void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);
*/
void  handleData(char *recvData,sqlite3 *db){
	result res;
	memset(&res,0,sizeof(res));

	setupstruct(recvData,&res);
	if(db)
		if(!strcmp(res.group,"SCIENCE"))
			writeIntoDB(&res,db);
	if(!strcmp(res.rs,"0"))
		fprintf(stderr,"Relegious studies empty");
	if(!strcmp(res.hm,"0"))
		fprintf(stderr,"Optional empty");

	//	writeData(fp,&res,0);
//	printf("%s\n",recvData);
	return;
}

void setupstruct(char *Data,result *res){
	static int sn=1;
	char *c=strstr(Data,"<!DOCTYPE");
	if(c != NULL)
		Data=c;
	char val[valSize];
	memset(val,0,valSize);
	if((c=getValue(Data,"Roll No",val))!=NULL){
		memmove(res->roll_no,val,strlen(val));
	}
/*		Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Name",val))!=NULL){
		memmove(res->name,val,strlen(val));
	}
//		Data=c;
//	}else{
//		c=Data;
//	}
	memset(val,0,valSize);
	if((c=getValue(Data,"Board",val))!=NULL){
		memmove(res->board,val,strlen(val));
	}
//		Data=c;
//	}else{
//		c=Data;
//	}
	memset(val,0,valSize);
	if((c=getValue(Data,"Father's Name",val))!=NULL){
		memmove(res->fname,val,strlen(val));
	}
//		Data=c;
//	}else{
//		c=Data;
//	}
	memset(val,0,valSize);
	if((c=getValue(Data,"Group",val))!=NULL){
		memmove(res->group,val,strlen(val));
	}/*		Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Mother's Name",val))!=NULL){
		memmove(res->mname,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Session",val))!=NULL){
		memmove(res->session,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Reg. NO",val))!=NULL){
		memmove(res->regno,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Type",val))!=NULL){
		memmove(res->type,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Institute",val))!=NULL){
		memmove(res->institue,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"Result",val))!=NULL){
		memmove(res->gpa,val+4,strlen(val+4));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	memset(val,0,valSize);
	if((c=getValue(Data,"DATE OF BIRTH",val))!=NULL){
		memmove(res->dob,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"BANGLA-I",val))!=NULL){
		removeGrade(val);
		memmove(res->bangla,val,strlen(val));
	}
	}while(atoi(res->bangla) > 200);
	/*	Data=c;
	}else{
		c=Data;
	}*/
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"ENGLISH-I",val))!=NULL){
		removeGrade(val);
		memmove(res->english,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->english) > 200);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"MATHEMATICS",val))!=NULL){
		removeGrade(val);
		memmove(res->math,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->math) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"BANGLADESH AND GLOBAL STUDIES",val))!=NULL){
		removeGrade(val);
		memmove(res->bgs,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->bgs) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"BUDDHIST RELIGION AND MORAL EDUCATION",val))!=NULL){
		removeGrade(val);
		memmove(res->rs,val,strlen(val));
	}/*	Data=c;
	}
	else{
		c=Data;
	}*/
	else if((c=getValue(Data,"HINDU RELIGION AND MORAL EDUCATION",val))!=NULL){
		removeGrade(val);
		memmove(res->rs,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	else if((c=getValue(Data,"ISLAM AND MORAL EDUCATION",val))!=NULL){
		removeGrade(val);
		memmove(res->rs,val,strlen(val));
	}
	}while(atoi(res->rs) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"PHYSICS",val))!=NULL){
		removeGrade(val);
		memmove(res->physics,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->physics) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"CHEMISTRY",val))!=NULL){
		removeGrade(val);
		memmove(res->chemestry,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->chemestry) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"BIOLOGY",val))!=NULL){
		removeGrade(val);
		memmove(res->biology,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->biology) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"Information And Communication Technology",val))!=NULL){
		removeGrade(val);
		memmove(res->ict,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->ict) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"HIGHER MATHEMATICS",val))!=NULL){
/*		if(!strcmp(val,""))
			continue;*/
		removeGrade(val);
		memmove(res->hm,val,strlen(val));
	}
	else if((c=getValue(Data,"AGRICULTURE STUDIES",val))!=NULL){
/*		if(!strcmp(val,""))
			continue;*/
		removeGrade(val);
		memmove(res->hm,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->hm) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"PHYSICAL EDUCATION, HEALTH AND SPORTS",val))!=NULL){
/*		if(!strcmp(val,""))
			continue;*/
		removeGrade(val);
		memmove(res->pehs,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
	}while(atoi(res->pehs) > 100);
	do{
	memset(val,0,valSize);
	if((c=getValue(Data,"Career Education",val))!=NULL){
/*		if(!strcmp(val,""))
			continue;*/
		removeGrade(val);
		memmove(res->cc,val,strlen(val));
	}/*	Data=c;
	}else{
		c=Data;
	}*/
//exit(0);
	}while(atoi(res->cc) > 100);
	int total=0;
	total+=getnumber(res->bangla);
	total+=getnumber(res->english);
	total+=getnumber(res->math);
	total+=getnumber(res->bgs);
	total+=getnumber(res->rs);
	total+=getnumber(res->physics);
	total+=getnumber(res->chemestry);
	total+=getnumber(res->biology);
	total+=getnumber(res->ict);
	total+=getnumber(res->hm);

	char tot[10];
	itoa(total,tot,10);
	memmove(res->tow,tot,strlen(tot));

	total+=getnumber(res->pehs);
	total+=getnumber(res->cc);

	itoa(total,tot,10);
	memmove(res->to,tot,strlen(tot));
	
	res->sn=sn;
	sn++;
}


void writeData(FILE *fp,result *res,int html){
	if(html==0){
	fprintf(fp,"[{Name=\"%s\",Roll.No=\"%s\",Board=\"%s\",Father'sName=\"%s\",Group=\"%s\",Mother'sName=\"%s\",Session=\"%s\",Reg.No=\"%s\",Type=\"%s\",Institution=\"%s\",GPA=\"%s\",DataOfBirth=\"%s\",BANGLA=\"%s\",ENGLISH=\"%s\",MATHEMATICS=\"%s\",BANGLADESHANDGLOBALSTUDIES=\"%s\",RELIGIOUSSTADIES=\"%s\",PHYSICS=\"%s\",CHEMESTRY=\"%s\",BIOLOGY=\"%s\",InformationAndCommunicationTechnology=\"%s\",HIGHERMATHEMATICS=\"%s\",PHYSICALEDUCATIONHEALTHANDSPORTS=\"%s\",CareerEducation=\"%s\",TWCA=\"%s\",Total=\"%s\"}]\n",res->name,res->roll_no,res->board,res->fname,res->group,res->mname,res->session,res->regno,res->type,res->institue,res->gpa,res->dob,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);

	//printf("[{Name=\"%s\",Roll.No=\"%s\",Board=\"%s\",Father'sName=\"%s\",Group=\"%s\",Mother'sName=\"%s\",Session=\"%s\",Reg.No=\"%s\",Type=\"%s\",Institue=\"%s\",GPA=\"%s\",DataOfBirth=\"%s\",BANGLA=\"%s\",ENGLISH=\"%s\",MATHEMATICS=\"%s\",BANGLADESHANDGLOBALSTUDIES=\"%s\",RELIGIOUSSTADIES=\"%s\",PHYSICS=\"%s\",CHEMESTRY=\"%s\",BIOLOGY=\"%s\",InformationAndCommunicationTechnology=\"%s\",HIGHERMATHEMATICS=\"%s\",PHYSICALEDUCATIONHEALTHANDSPORTS=\"%s\",CareerEducation=\"%s\",TotalWithoutCA=\"%s\",Total=\"%s\"}]\n",res->name,res->roll_no,res->board,res->fname,res->group,res->mname,res->session,res->regno,res->type,res->institue,res->gpa,res->dob,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
	return;
	}
	else if(html==1){
		fprintf(fp,"<tr>\n\n<td>%d</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n\n</tr>\n",res->sn,res->name,res->roll_no,res->group,res->institue,res->gpa,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
		return;
	}
}

void writeIntoDB(result *res,sqlite3 *db){
	char sql[5121];
	int rc;
	char *zErrMsg;
	memset(sql,0,5121);
	static int id=1;
	sprintf(sql,"INSERT INTO SCIENCE (Name,Roll_NO,Board,Fathers_Name,_Group,Mothers_Name,Session,Registration_NO,Type,Institution,GPA,Date_of_Birth,Bangla,English,Mathmatics,Bangladesh_and_Global_Studies,Religious_Studies,Physics,Chemestry,Biology,ICT,Optional,Physical_Education,Career_Education,Total_without_CA,Total)"\
			"VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');",res->name,res->roll_no,res->board,res->fname,res->group,res->mname,res->session,res->regno,res->type,res->institue,res->gpa,res->dob,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
  	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
  	    sqlite3_free(zErrMsg);
	   } else {
		   id++;
  //	    fprintf(stdout, "Records created successfully\n");
	   }
	return ;
}
void htmlStart(FILE *fp){
	fprintf(fp,"<!DOCTYPE html>\n\n<html>\n\n<head>\n\t<title>SSC Result</title>\n<style>\nth {\ntext-align:center\n}\ntd {\ntext-align:center\n}\n</style>\n</head>\n\n\n<body>\n\n\t<H3>SSC RESULT</H3>\n\n\t<CENTER>\n\n\t<table border=\"1\" width=\"80%%\">\n\t<tr>\n\n<th>Serial No</th>\n<th>Name</th>\n<th>Roll. No</th>\n<th>Group</th>\n<th>Inistitution</th>\n<th>GPA</th>\n<th>BANGLA</th>\n<th>ENGLISH</th>\n<th>MATHEMATICS</th>\n<th>SOCIAL STUDIES</th>\n<th>RELIGIOUS STUDIES</th>\n<th>PHYSICS</th>\n<th>CHEMESTRY</th>\n<th>BIOLOGY</th>\n<th>ICT</th>\n<th>HIGHER MATH</th>\n<th>PHYSICAL EDUCATION</th>\n<th>CAREER EDUCATION</th>\n<th>Total without CA</th>\n<th>Total</th>\n\n</tr>\n");
}
void htmlEnd(FILE *fp){
	fprintf(fp,"\n\n\t</table>\n\n</CENTER>\n</body>");
}
int getnumber(char *s){
	char *c=strdup(s);
	char *c2=c;
	while(*c2<='9'&&*c2>='0') c2++;
	*c2='\0';
	int num=atoi(c);
	free(c);
	return num;
}

void removeGrade(char *val){
//	printf("\n\tchanging \'%s\' to ",val);
	char *cpointer=val;
	int s;
	while(!(*cpointer<='9'&& *cpointer>='0')&& *cpointer!='\0') cpointer++;
	if(cpointer>val){
		s=strlen(cpointer);
		memmove(val,cpointer,s);
		*(val+s)='\0';
	}
	while(*cpointer<='9'&& *cpointer>='0') cpointer++;
	*cpointer='\0';
	if(!(*val<'9'&& *val>='0')){
		memmove(val,"0\0",2);
	}
//	printf("\'%s\'\n",val);
}

char * getValue(char *Data,char *key,char *value){
	char mKey[100];
	memset(mKey,0,100);
	sprintf(mKey,">%s</td>",key);
	char *start=strstr(Data,mKey);
	char *end=NULL;
	if(start!=NULL){
		start=strstr(start,"</td>");
		start+=5;
		start=strstr(start,"</td>");
		end=start;
		while(*start!='>')	start--;
		memmove(value,start+1,(end-start-1));
		char *c;
		int len=0;
		while((c=strchr(value,'\''))){
			len=strlen(c+1);
			memmove(c,c+1,len);
			*(c+len)='\0';
		}
		return end+5;
	}
	return NULL;
}

/*int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
*/
