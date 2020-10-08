#include "header.h" 
#include "functions.h"
void kjob(int len){
	if (len!=3){
		printf("2 arguments only!\n");
		return;
	}
	int i=atoi(parameters[1]);
	if (i<=tpid){
		i--;
		if (procs[i].stat==1){
			int k=kill(procs[i].pid,atoi(parameters[2]));
		//	printf("ok\n");
			if (k<0){
				perror("can't kill");
				return;
			}
			else{
				procs[i].stat=0;
				struct processes temp;
				for(int j=i+1;j<tpid;j++){
					temp=procs[i];
					procs[i]=procs[i+1];
					procs[i+1]=temp;
//					swapstr(procs[i],procs[i+1]);
				}
				tpid--;
				kflag=1;
			}
		}
	}
	else {
		printf("No such process!\n");
	}
}