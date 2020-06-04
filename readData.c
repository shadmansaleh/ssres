#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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


int countlines(char *fname){
	FILE *fp=fopen(fname,"r");
	if(fp==NULL)
		return -1;
	int c;
	int count=0;
	while((c=getchar())!=EOF)
		if(c==']')
			if((c=getchar())!=EOF)
				if(c=='\n')
					count++;
	return count;
}

void getStructData(result *res,FILE *fp){
	fscanf(fp,"[{Name=\"%s\",Roll.No=\"%s\",Board=\"%s\",Father'sName=\"%s\",Group=\"%s\",Mother'sName=\"%s\",Session=\"%s\",Reg.No=\"%s\",Type=\"%s\",Institue=\"%s\",GPA=\"%s\",DataOfBirth=\"%s\",BANGLA=\"%s\",ENGLISH=\"%s\",MATHEMATICS=\"%s\",BANGLADESHANDGLOBALSTUDIES=\"%s\",RELIGIOUSSTADIES=\"%s\",PHYSICS=\"%s\",CHEMESTRY=\"%s\",BIOLOGY=\"%s\",InformationAndCommunicationTechnology=\"%s\",HIGHERMATHEMATICS=\"%s\",PHYSICALEDUCATION,HEALTHANDSPORTS=\"%s\",CareerEducation=\"%s\",TotalWithoutCA=\"%s\",Total=\"%s\"}]\n",res->name,res->roll_no,res->board,res->fname,res->group,res->mname,res->session,res->regno,res->type,res->institue,res->gpa,res->dob,res->bangla,res->english,res->math,res->bgs,res->rs,res->physics,res->chemestry,res->biology,res->ict,res->hm,res->pehs,res->cc,res->tow,res->to);
}

result *readData(char *fname,int *size){
	int lineno=countlines(fname);
	result *rs=(result*)calloc('\0',sizeof(result)*lineno);
	int i=0;
	FILE *fp=fopen(fname,"r");
	while(i<=lineno){
		getStructData(&rs[i],fp);
	}
	*size=lineno;
	return rs;
}

