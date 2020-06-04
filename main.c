#include <stdio.h>


void dataGatherer(int rollLower,int rollHeigher);
int opensocket(char *host,char *port);


int main(){
//	char *host="sresult.bise-ctg.gov.bd";
//	char *port="80";
	
//	int soc=opensocket(host,port);

	dataGatherer(107612,107614);
	return 0;
}
