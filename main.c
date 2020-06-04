#include <stdio.h>


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




void dataGatherer(int rollLower,int rollHeigher);
int opensocket(char *host,char *port);
result *readData(char *fname,int *size);
void writeData(FILE *fp,result *res,int html);
void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);
void quickSort(void *v[],int left,int right,int (*eval)(void*,void*));

int sortTotalNum(void *res1,void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return (r1->to - r2->to);
}


int main(){
	dataGatherer(107612,107614);
	int len=0;
	result *res=readData("rawData",&len);
	quickSort((void*)res,0,len,sortTotalNum);
	int i;
	for(i=0;i<=len;i++)
		res[i].sn=i+1;
	FILE *fp=fopen("result.html","r");
	htmlStart(fp);
	for(i=0;i<=len;i++)
		writeData(fp,&res[i],1);
	htmlEnd(fp);
	fclose(fp);
	free(res);
	return 0;
}
