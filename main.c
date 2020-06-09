#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ssres.h"
#include <fcntl.h>
#include <sqlite3.h>
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
//	int onlySort=0;
	int help=0;
	int ch;
//	int alg=0;
//	char out[200]="/sdcard/result.html";
//	int(*sortAlg)(const void*,const void*);
	//while((ch=getopt(argc,argv,":f:t:o:hs01234"))!=-1){
	while((ch=getopt(argc,argv,":f:t:"))!=-1){
		switch(ch){
			case 'f':
				from=atoi(optarg);
				break;
			case 't':
				to=atoi(optarg);
				break;
			case 's':
/*				onlySort=1;
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
				break;*/
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
		printf("ssres  -- ssc result fetcher\n\n\t-f\tfrom(roll)\n\t-t\tto(roll)\n\n");//\n\t-s\tsort currently available rawData\n\t-0\tSort based on total number without CA(default)\n\t-1\tSort based on Total number\n\t-2\tSort based on GPA\n\t-3\tSort based on name\n\t-4\tSort based on roll\n\n");
		return 0;
	}
/*	switch(alg){
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
	}*/
//	int count=0;
//	result *rr=NULL;
//	if(!onlySort){
//	count=to-from+1;
//	rr=(result*)calloc('\0',(sizeof(result)*count));
//	remove("rawData");

	dataGatherer(from,to);
/*	char buffer[20];
	memset(buffer,0,20);
	sprintf(buffer,"%d\n",count);
	int fp=open("rawData",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	if(fp<0)
		perror("Cann't write rawData");
	else{
	write(fp,buffer,strlen(buffer));
	int size=sizeof(rr);
	int c=0;
	result *r=rr;
	while(size>0){
	c=write(fp,r,size);
	size-=c;
	r+=c;
	}
	close(fp);
	}
	}
	else{
		char buffer[20];
		memset(buffer,0,20);
		int fp=open("rawData",O_RDONLY,O_TRUNC);
		if(fp<0)
			error("Cann't read rawData");
		else{
			char *b=buffer;
			int c=1;
			while(c){
				c=read(fp,b,1);
				if(*b=='\n'){
					*b='\0';
					break;
				}
				else
					b++;
				
			}
		}
		count=atoi(buffer);
		if(count>0){
			rr=calloc('\0',(sizeof(result)*count));
			int c=read(fp,rr,(sizeof(result)*count));
			if(count != c/sizeof(result))
				count=c/sizeof(result);
			else
				perror("Not all data Available");
		}
		else{
			close(fp);
			error("Count not available");
		}
		close(fp);
	}*/
//	int len=0;
/*	printf("Reading...");
	result *res=readData("rawData",&len);*/
//	printf("\nSorting...");
//	qsort((void*)rr,(count),sizeof(*rr),sortAlg);
//	quickSort((void*)res,0,(len),sortTotalNum);
/*	int i;
	for(i=0;i<count;i++)
		rr[i].sn=i+1;*/
//	printf("Done\nWriting...");
//	int f=open(out,O_RDWR|O_CREAT);
//	printf("f=%d\n",f);
//	FILE *fp2=fdopen(f,"w");
/*	FILE *fp2=fopen(out,"w");
	if(fp2==NULL)
		error("Unable to open output file.");
	htmlStart(fp2);
	for(i=0;i<count;i++)
		writeData(fp2,&rr[i],1);
	htmlEnd(fp2);
	printf("Done\n");
	fclose(fp2);*/
//	close(f);
//	free(rr);
	return 0;
}
