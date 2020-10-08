#include "header.h"
void jobs(int len){
	int count=0;
	if(len!=1){
		printf("error:just type jobs\n");
		return;
	}
	for(int i=0;i<tpid;i++){
		if (procs[i].stat == 1){
			count++;
			char path[512];
			sprintf(path,"/proc/%d/stat",procs[i].pid);
			FILE * fd = fopen(path,"r");
			if (fd==0)
				procs[i].stat=0;
			else {
			char condn[200];
			char status[200];
		//	printf("%s\n",pstatus);
			fscanf(fd,"%*d%*s%s",status);
			if (strcmp(status,"R")==0 || strcmp(status,"S")==0)
				strcpy(status,"Running");
			else if  (strcmp(status,"T")==0)
				strcpy(status,"Stopped");
			printf("[%d] %s %s [%d]\n",count,status,procs[i].name,procs[i].pid);
			}
			fclose(fd);
		}
	}
}