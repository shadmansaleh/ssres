#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define valSize 100


typedef struct {
	char name[100];
	char roll_no[10];
	char board[20];
	char fname[100];
	char mname[100];
	char group[10];
	char regno[20];
	char session[10];
	char type[10];
	char institue[100];
	char gpa[10];
	char dob[15];
	char bangla[10];
	char english[10];
	char math[10];
	char bgs[10];
	char rs[10];
	char physics[10];
	char chemestry[10];
	char biology[10];
	char ict[10];
	char hm[10];
	char pehs[10];
	char cc[10];
	char tow[10];
	char to[10];
	int sn;
}result;


char * getValue(char *Data,char *key,char *value);
int getnumber(char *s);
void setupstruct(char *Data,result *res);
char* itoa(int num, char* str, int base);
void writeData(FILE *fp,result *res,int html);
void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);

void handleData(FILE *fp,char *recvData){
	result res;
	memset(&res,0,sizeof(res));

	setupstruct(recvData,&res);
	writeData(fp,&res,0);
//	printf("%s\n",recvData);
	return;
}

void setupstruct(char *Data,result *res){
	static int sn=1;
	char *c=strstr(Data,"<!DOCTYPE");
	char val[valSize];
	memset(val,0,valSize);
	if((c=getValue(c,"Roll No",val))!=NULL){
		memmove(res->roll_no,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Name",val))!=NULL){
		memmove(res->name,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Board",val))!=NULL){
		memmove(res->board,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Father's Name",val))!=NULL){
		memmove(res->fname,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Group",val))!=NULL){
		memmove(res->group,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Mother's Name",val))!=NULL){
		memmove(res->mname,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Session",val))!=NULL){
		memmove(res->session,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Reg. NO",val))!=NULL){
		memmove(res->regno,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Type",val))!=NULL){
		memmove(res->type,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Institute",val))!=NULL){
		memmove(res->institue,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Result",val))!=NULL){
		memmove(res->gpa,val+4,strlen(val+4));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"DATE OF BIRTH",val))!=NULL){
		memmove(res->dob,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"BANGLA-I",val))!=NULL){
		memmove(res->bangla,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"ENGLISH-I",val))!=NULL){
		memmove(res->english,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"MATHEMATICS",val))!=NULL){
		memmove(res->math,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"BANGLADESH AND GLOBAL STUDIES",val))!=NULL){
		memmove(res->bgs,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"ISLAM AND MORAL EDUCATION",val))!=NULL){
		memmove(res->rs,val,strlen(val));
		Data=c;
	}
	else if((c=getValue(c,"HINDU RELIGION AND MORAL EDUCATION",val))!=NULL){
		memmove(res->rs,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"PHYSICS",val))!=NULL){
		memmove(res->physics,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"CHEMISTRY",val))!=NULL){
		memmove(res->chemestry,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"BIOLOGY",val))!=NULL){
		memmove(res->biology,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Information And Communication Technology",val))!=NULL){
		memmove(res->ict,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"HIGHER MATHEMATICS",val))!=NULL){
		memmove(res->hm,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"PHYSICAL EDUCATION, HEALTH AND SPORTS",val))!=NULL){
		memmove(res->pehs,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
	memset(val,0,valSize);
	if((c=getValue(c,"Career Education",val))!=NULL){
		memmove(res->cc,val,strlen(val));
		Data=c;
	}else{
		c=Data;
	}
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
	fprintf(fp,"[{Name=\"%s\",Roll.No=\"%s\",Board=\"%s\",Father'sName=\"%s\",Group=\"%s\",Mother'sName=\"%s\",Session=\"%s\",Reg.No=\"%s\",Type=\"%s\",Institue=\"%s\",GPA=\"%s\",DataOfBirth=\"%s\",BANGLA=\"%s\",ENGLISH=\"%s\",MATHEMATICS=\"%s\",BANGLADESHANDGLOBALSTUDIES=\"%s\",RELIGIOUSSTADIES=\"%s\",PHYSICS=\"%s\",CHEMESTRY=\"%s\",BIOLOGY=\"%s\",InformationAndCommunicationTechnology=\"%s\",HIGHERMATHEMATICS=\"%s\",PHYSICALEDUCATION,HEALTHANDSPORTS=\"%s\",CareerEducation=\"%s\",TotalWithoutCA=\"%s\",Total=\"%s\"}]\n",res->name,res->roll_no,res->board,res->fname,res->group,res->mname,res->session,res->regno,res->type,res->institue,res->gpa,res->dob,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
	return;
	}
	else if(html==1){
		fprintf(fp,"<tr>\n\n<td>%d</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n\n</tr>\n",res->sn,res->name,res->roll_no,res->group,res->institue,res->gpa,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
		return;
	}
}

void htmlStart(FILE *fp){
	fprintf(fp,"<!DOCTYPE html>\n\n<html>\n\n<head>\n\t<title>SSC Result</title>\n</head>\n\n\n<body>\n\n\t<H3>SSC RESULT</H3>\n\n\t<table border=\"1\" width=\"80%%\">\n\t<tr>\n\n<th>Serial No</th>\n<th>Name</th>\n<th>Roll. No</th>\n<th>Group</th>\n<th>Inistitue</th>\n<th>GPA</th>\n<th>BANGLA</th>\n<th>ENGLISH</th>\n<th>MATHEMATICS</th>\n<th>SOCIAL STUDIES</th>\n<th>RELIGIOUS STUDIES</th>\n<th>PHYSICS</th>\n<th>CHEMESTRY</th>\n<th>BIOLOGY</th>\n<th>ICT</th>\n<th>HIGHER MATH</th>\n<th>PHYSICAL EDUCATION</th>\n<th>CAREER EDUCATION</th>\n<th>Total without CA</th>\n<th>Total</th>\n\n</tr>\n");
}
void htmlEnd(FILE *fp){
	fprintf(fp,"\n\n\t</table>\n</body>");
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
		return end+5;
	}
	return NULL;
}
