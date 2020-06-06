#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssres.h"

/*void dataGatherer(int rollLower,int rollHeigher);
int opensocket(char *host,char *port);
result *readData(char *fname,int *size);
void writeData(FILE *fp,result *res,int html);
void htmlStart(FILE *fp);
void htmlEnd(FILE *fp);
void quickSort(void *v[],int left,int right,int (*eval)(const void*,const void*));
void error(char *msg); 
*/

int sortTotalNumWCA(const void *res1,const void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return (atoi(r2->tow) - atoi(r1->tow));
}
int sortTotal(const void *res1,const void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return (atoi(r2->to) - atoi(r1->to));
}
int sortName(const void *res1,const void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return strcmp(r2->name,r1->name);
}
int sortRoll(const void *res1,const void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return (atoi(r2->roll_no) - atoi(r1->roll_no));
}
int sortGPA(const void *res1,const void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return (atoi(r2->gpa) - atoi(r1->gpa));
}
/*int sortTotalNumWCA(const void *res1,const void *res2){
	result *r1=(result*)res1;
	result *r2=(result*)res2;
	return (atoi(r2->tow) - atoi(r1->tow));
}
*/

int main(int argc,char *argv[]){
	int from=0;
	int to=0;
	int onlySort=0;
	int help=0;
	int ch;
	int alg=0;
	char out[200]="/sdcard/result.html";
	int(*sortAlg)(const void*,const void*);
	while((ch=getopt(argc,argv,":f:t:o:hs01234"))!=-1){
		switch(ch){
			case 'f':
				from=atoi(optarg);
				break;
			case 't':
				to=atoi(optarg);
				break;
			case 's':
				onlySort=1;
				break;
			case 'h':
				help=1;
				break;
			case 'o':
				strcpy(out,optarg);
				break;
			case '1':
				alg=1;
				break;
			case '2':
				alg=2;
				break;
			case '3':
				alg=3;
				break;
			case '4':
				alg=4;
				break;
/*			case '5':
				alg=5;
				break;*/

			case ':':
                                printf("some arguments are missing\n");
                                help=1;
                                break;
                        case '?':
                                printf("Unknown option %c",optopt);

                }
        }
	if(argc==1)
		help=1;
        argc-=optind;
        argv+=optind;
	if(help==1){
		printf("ssres  -- ssc result fetcher\n\n\t-f\tfrom(roll)\n\t-t\tto(roll)\n\t-s\tsort currently available rawData\n\t-0\tSort based on total number without CA(default)\n\t-1\tSort based on Total number\n\t-2\tSort based on GPA\n\t-3\tSort based on name\n\t-4\tSort based on roll\n\n");
		return 0;
	}
	switch(alg){
		case 0:
			sortAlg=sortTotalNumWCA;
			break;
		case 1:
			sortAlg=sortTotal;
			break;
		case 2:
			sortAlg=sortGPA;
			break;
		case 3:
			sortAlg=sortName;
			break;
		case 4:
			sortAlg=sortRoll;
			break;
		default:
			sortAlg=sortTotalNumWCA;
			break;
	}
	if(!onlySort){
	remove("rawData");
	dataGatherer(from,to);
	}
	int len=0;
	printf("Reading...");
	result *res=readData("rawData",&len);
	printf("\nSorting...");
	qsort((void*)res,(len),sizeof(*res),sortAlg);
//	quickSort((void*)res,0,(len),sortTotalNum);
	int i;
	for(i=0;i<len;i++)
		res[i].sn=i+1;
	printf("Done\nWriting...");
//	int f=open(out,O_RDWR|O_CREAT);
//	printf("f=%d\n",f);
//	FILE *fp2=fdopen(f,"w");
	FILE *fp2=fopen(out,"w");
	if(fp2==NULL)
		error("Unable to open output file.");
	htmlStart(fp2);
	for(i=0;i<len;i++)
		writeData(fp2,&res[i],1);
	htmlEnd(fp2);
	printf("Done\n");
	fclose(fp2);
//	close(f);
	free(res);
	return 0;
}
