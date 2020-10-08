#include "header.h"
#include "functions.h"
void overkill(int len){
	if(len!=1)
		printf("error:just type overkill\n");
	for(int i=0;i<tpid;i++){
		if (procs[i].stat==1){
			int k=kill(procs[i].pid,9);
			if(k<0) perror("Can't Kill!");
			else procs[i].stat=0;
		}
	}
}