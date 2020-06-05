#include <stdio.h>

//void swap(int[],int,int);
void quickSort(void *v[],int left,int right,int (*eval)(const void*,const void*));
//int eval(char *i,char *j);

static void qswap(void *v[],int i1,int i2){
	void *temp=v[i1];
	v[i1]=v[i2];
	v[i2]=temp;
}

void quickSort(void *v[],int left,int right,int (*eval)(const void*,const void*)){
	int i,last;
	if(right<=left)
		return;
	qswap(v,left,((left+right)/2));
	last=left;
	i=left+1;
	for(;i<=right;i++){
		if(eval(v[i],v[left]) < 0){
			qswap(v,i,++last);
		}
	}
	qswap(v,left,last);
	quickSort(v,left,(last-1),eval);
	quickSort(v,(last+1),right,eval);
}

/*inline int eval(char *i,char *j){
	return -(strcmp(i,j));
}*/
//test
/*int main(){
//	int v[]={3,5,1,75,34,2,98,3,123,643,25,50,100};
//	int len =sizeof(v)/sizeof(int);
//	--len;
	char *v[5];
	char a1[30]="Hellow";
	char a2[30]="who?";
	char a3[30]="Do";
	char a4[30]="who the hell";
	char a5[30]="Are you !!";
	v[0]=a1;
	v[1]=a2;
	v[2]=a3;
	v[3]=a4;
	v[4]=a5;
	int len=4;
	int i;
	quickSort(v,0,len);
	for (i=0;i<=len;i++)
		printf("%s\n",v[i]);
	putchar('\n');
	return 0;
}*/
