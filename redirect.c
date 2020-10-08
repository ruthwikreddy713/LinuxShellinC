#include "header.h"
#include "functions.h"
void Redirectfun(int len,char ** parameters){
//	printf("%s\n",parameters[0]);
	int nprc=fork();
	if(nprc==0){	
	for(int i=0;i<len;i++){
		if(strcmp(parameters[i],">")==0){
			int nf=open(parameters[i+1],O_WRONLY | O_TRUNC | O_CREAT,0644);
			if(nf<0){
				perror("can't open ");
				return;
			}
			dup2(nf,1);
			parameters[i]=NULL;
			close(nf);
		}
		else if (strcmp(parameters[i],">>")==0){
			int nf=open(parameters[i+1],O_WRONLY | O_APPEND | O_CREAT,0644);
			if(nf<0){
				perror("can't open ");
				return;
			}
			dup2(nf,1);
			parameters[i]=NULL;
			close(nf);			
		}
		else if (strcmp(parameters[i],"<")==0){
		//	printf("ok\n");
			int nf=open(parameters[i+1],O_RDONLY);
			if(nf<0){
				perror("can't open ");
				return;
			}
			dup2(nf,0);
			parameters[i]=NULL;
			close(nf);
		}
	}
//	printf("%s\n",parameters[0]);
	if(execvp(parameters[0],parameters)<0)
//		printf("%s\n",parameters[0]);
		perror("failed execvp");
		return;
	}
	else  {
		wait(NULL);
	}
	return;
}