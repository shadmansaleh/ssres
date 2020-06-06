#include <stdio.h>
#include <string.h>

int htoi(char *hax){
	int i=0;
	int val=0;
	int len;
	if(*hax=='0'&&(*(hax+1)=='x'||*(hax+1)=='X'))
		hax+=2;
	len = strlen(hax) - 1;
	int l=0;
	while(l<=len){
		switch(*(hax+l)){
			case '0':
				val=0;
				break;
			case '1':
				val=1;
				break;
			case '2':
				val=2;
				break;
			case '3':
				val=3;
				break;
			case '4':
				val=4;
				break;
			case '5':
				val=5;
				break;
			case '6':
				val=6;
				break;
			case '7':
				val=7;
				break;
			case '8':
				val=8;
				break;
			case '9':
				val=9;
				break;
			case 'a':
			case 'A':
				val=10;
				break;
			case 'b':
			case 'B':
				val=11;
				break;
			case 'c':
			case 'C':
				val=12;
				break;
			case 'd':
			case 'D':
				val=13;
				break;
			case 'e':
			case 'E':
				val=14;
				break;
			case 'F':
			case 'f':
				val=15;
				break;
			default:
				return -1;
		}
		i=16*i+val;
		l++;
	}
	return i;
}

/*int main(){
	char h1[]="0x3f54";
	char h2[]="0X354";
	char h3[]="354";
	printf("%s=%d\n",h1,htoi(h1));
	printf("%s=%d\n",h2,htoi(h2));
	printf("%s=%d\n",h3,htoi(h3));
	printf("%s=%d\n","t27h",htoi("t27h"));
}*/


