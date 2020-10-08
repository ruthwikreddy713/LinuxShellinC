#include "functions.h"
#include "header.h"



void echow(char * line) {
	int i=4;
	//printf("%c o\n",line[i]);
	while(line[i]==' ')
		i++;
	for(int j=i;j<strlen(line);j++){
		if (line[j]!='"'&&line[j]!= 39)
			printf("%c",line[j]);
	}
	printf("\n");
}