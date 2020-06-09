#include <stdio.h>
#include <sqlite3.h>

typedef struct {
	char name[100];
	char roll_no[100];
	char board[200];
	char fname[100];
	char mname[100];
	char group[100];
	char regno[100];
	char session[100];
	char type[100];
	char institue[100];
	char gpa[100];
	char dob[100];
	char bangla[100];
	char english[100];
	char math[100];
	char bgs[100];
	char rs[100];
	char physics[100];
	char chemestry[100];
	char biology[100];
	char ict[100];
	char hm[100];
	char pehs[100];
	char cc[100];
	char tow[100];
	char to[100];
	int sn;
}result;

result *readData(char *fname,int *size);
int countlines(char *fname);
void getStructData(result *res,FILE *fp);
void error(char *msg); 

int getData(int soc,char *sendData,char *recvData,int recvSize);
int opensocket(char *host,char *port); 

void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);
void handleData(char *recvData,sqlite3 *db);


void dataGatherer(int rollLower,int rollHeigher);
void writeData(FILE *fp,result *res,int html);
void quickSort(void *v[],int left,int right,int (*eval)(const void*,const void*));

char * getValue(char *Data,char *key,char *value);
int getnumber(char *s);
void setupstruct(char *Data,result *res);
char* itoa(int num, char* str, int base);

int countlines(char *fname);
void getStructData(result *res,FILE *fp);


int getDatawithnc(char *sendData,char *recvData,int recvSize);


int htoi(char *hax);

void writeIntoDB(result *res,sqlite3 *db);
int callback(void *NotUsed, int argc, char **argv, char **azColName);

void removeGrade(char *val);

int checkAvailable(sqlite3 *db,int roll);

void giveResult(char *dbName,char *sortcondition,char* limitcondition);

