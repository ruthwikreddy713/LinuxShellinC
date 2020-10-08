#include "functions.h"
#include "header.h"
void psc(int len){
	FILE * pfile;
	char pstatus[100];
	int pid;
	char memory[100];
	char temp2[100];
	char temp[200];	
	if (len==1){
		pfile=fopen("/proc/self/status","r");
	//	printf("ok\n");
		for(int i=0;i<2;i++)
		fgets(temp,100,pfile);
	//	printf("%s\n",pstatus);
		fscanf(pfile,"%s %s",temp,pstatus);
		while(1){
			fgets(temp,100,pfile);
			if (strstr(temp,"VmPeak")!=NULL)
				break;
		}
	//	printf("ok\n");
		fscanf(pfile,"%s %s",temp2,memory);
		int cur_pid=getpid();
		printf("PID -- %d\n",cur_pid);
		printf("Process status -- %s\n",pstatus);
		printf("memory -- %s\n",memory);
		printf("Executable path -- %s\n","./a.out");
		fclose(pfile);
	}
	else {
		char path[500];
		char fpathforname[500];
		char excpath[200];
		sprintf(path,"/proc/%s/status",parameters[1]);
		sprintf(fpathforname,"/proc/%s/cmdline",parameters[1]);
		FILE * pfile;
		pfile = fopen(fpathforname,"r");
		fgets(excpath,200,pfile);
		fclose(pfile);
//		printf("%s\n",excpath);
		pfile= fopen(path,"r");
		for(int i=0;i<2;i++)
		fgets(temp,100,pfile);
	//	printf("%s\n",pstatus);
		fscanf(pfile,"%s %s",temp,pstatus);
		while(1){
			fgets(temp,100,pfile);
			if (strstr(temp,"VmPeak")!=NULL)
				break;
		}
	//	printf("ok\n");
		fscanf(pfile,"%s %s",temp2,memory);
		//int cur_pid=getpid();
		printf("PID -- %s\n",parameters[1]);
		printf("Process status -- %s\n",pstatus);
		printf("memory -- %s\n",memory);
		printf("Executable path -- %s\n",excpath);		
	}
}