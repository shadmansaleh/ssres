#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
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


result *readData(char *fname,int *size);
int countlines(char *fname);
void getStructData(result *res,FILE *fp);
void error(char *msg); 


int countlines(char *fname){
	FILE *fp=fopen(fname,"r");
	if(fp==NULL)
		return -1;
	int c;
	int count=0;
	int stin=dup(0);
	dup2(fileno(fp),0);
	while((c=getchar())!=EOF)
		if(c==']')
			if((c=getchar())!=EOF)
				if(c=='\n')
					count++;
//	printf("%d lines",count);
	dup2(stin,0);
	fclose(fp);
	close(stin);
	return count;
}

void getStructData(result *res,FILE *fp){
//	fscanf(fp,"[{Name=\"%s\",Roll.No=\"%s\",Board=\"%s\",Father'sName=\"%s\",Group=\"%s\",Mother'sName=\"%s\",session=\"%s\",Reg.No=\"%s\",Type=\"%s\",Institue=\"%s\",GPA=\"%s\",DataOfBirth=\"%s\",BANGLA=\"%s\",ENGLISH=\"%s\",MATHEMATICS=\"%s\",BANGLADESHANDGLOBALSTUDIES=\"%s\",RELIGIOUSSTADIES=\"%s\",PHYSICS=\"%s\",CHEMESTRY=\"%s\",BIOLOGY=\"%s\",InformationAndCommunicationTechnology=\"%s\",HIGHERMATHEMATICS=\"%s\",PHYSICALEDUCATIONHEALTHANDSPORTS=\"%s\",CareerEducation=\"%s\",TotalWithoutCA=\"%s\",Total=\"%s\"}]\n",res->name,res->roll_no,res->board,res->fname,res->group,res->mname,res->session,res->regno,res->type,res->institue,res->gpa,res->dob,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
	
	char *getStructDataVal(char *str,char *key,char *val);
	char line[1025];
	char val[150];
	memset(line,0,1025);
	fgets(line,1024,fp);
	char *l=line;
//	char lineBack[1025];
//	memset(lineBack,0,1025);
//	memmove(lineBack,line,strlen(line));
	if(getStructDataVal(l,"Name",val)){
		memmove(res->name,val,strlen(val));
	}
	if(getStructDataVal(l,"Roll.No",val)){
		memmove(res->roll_no,val,strlen(val));
	}
	if(getStructDataVal(l,"Board",val)){
		memmove(res->board,val,strlen(val));
	}
	if(getStructDataVal(l,"Father'sName",val)){
		memmove(res->fname,val,strlen(val));
	}
	if(getStructDataVal(l,"Group",val)){
		memmove(res->group,val,strlen(val));
	}
	if(getStructDataVal(l,"Mother'sName",val)){
		memmove(res->mname,val,strlen(val));
	}
	if(getStructDataVal(l,"Session",val)){
		memmove(res->session,val,strlen(val));
	}
	if(getStructDataVal(l,"Reg.No",val)){
		memmove(res->regno,val,strlen(val));
	}
//	memset(l,0,1025);
//	memmove(l,lineBack,strlen(lineBack));	
	if(getStructDataVal(l,"Type",val)){
		memmove(res->type,val,strlen(val));
	}
//	memset(l,0,1025);
//	memmove(l,lineBack,strlen(lineBack));
	if(getStructDataVal(l,"Institution",val)){
		memmove(res->institue,val,strlen(val));
	}
//	memset(l,0,1025);
//	memmove(l,lineBack,strlen(lineBack));	
	if(getStructDataVal(l,"GPA",val)){
		memmove(res->gpa,val,strlen(val));
	}
	if(getStructDataVal(l,"DataOfBirth",val)){
		memmove(res->dob,val,strlen(val));
	}
	if(getStructDataVal(l,"BANGLA",val)){
		memmove(res->bangla,val,strlen(val));
	}
	if(getStructDataVal(l,"ENGLISH",val)){
		memmove(res->english,val,strlen(val));
	}
	if(getStructDataVal(l,"MATHEMATICS",val)){
		memmove(res->math,val,strlen(val));
	}
	if(getStructDataVal(l,"BANGLADESHANDGLOBALSTUDIES",val)){
		memmove(res->bgs,val,strlen(val));
	}
	if(getStructDataVal(l,"RELIGIOUSSTADIES",val)){
		memmove(res->rs,val,strlen(val));
	}
	if(getStructDataVal(l,"PHYSICS",val)){
		memmove(res->physics,val,strlen(val));
	}
	if(getStructDataVal(l,"CHEMESTRY",val)){
		memmove(res->chemestry,val,strlen(val));
	}
	if(getStructDataVal(l,"BIOLOGY",val)){
		memmove(res->biology,val,strlen(val));
	}
	if(getStructDataVal(l,"InformationAndCommunicationTechnology",val)){
		memmove(res->ict,val,strlen(val));
	}
	if(getStructDataVal(l,"HIGHERMATHEMATICS",val)){
		memmove(res->hm,val,strlen(val));
	}
	if(getStructDataVal(l,"PHYSICALEDUCATIONHEALTHANDSPORTS",val)){
		memmove(res->pehs,val,strlen(val));
	}
	if(getStructDataVal(l,"CareerEducation",val)){
		memmove(res->cc,val,strlen(val));
	}
	if(getStructDataVal(l,"TWCA",val)){
		memmove(res->tow,val,strlen(val));
	}
	if(getStructDataVal(l,"Total",val)){
		memmove(res->to,val,strlen(val));
	}

}

char *getStructDataVal(char *str,char *key,char *val){
	memset(val,0,150);
	char *str2=str;
	char *st=strstr(str2,key);
	if(st!=NULL){
	while(*st!='"') st++;
	char *end=st+1;
	while(*end!='"') end++;
	st++;
	memcpy(val,st,(end-st));
	st=NULL;
	str2=NULL;
	char *ret=end+1;
	end=NULL;
	return ret;
	}
	else
		return NULL;
}

result *readData(char *fname,int *size){
	int lineno=countlines(fname);
	if(lineno<0)
		error("unable to read rawData");
	result *rs=(result*)calloc('\0',sizeof(result)*lineno);
	int i=0;
	FILE *fp=fopen(fname,"r");
	if(fp==NULL)
		error("unable to read rawData");
	while(i<lineno){
		getStructData(&rs[i],fp);
		i++;
	}
	*size=lineno;
	return rs;
}

