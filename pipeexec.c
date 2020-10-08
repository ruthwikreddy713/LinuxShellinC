#include "functions.h"
#include "header.h"
void pipeexec(char inp[]){
	char * toks[20];
	int i=0;
	char * temp=strtok(inp,"|");
	while(temp!=NULL){
		toks[i++]=temp;
		temp=strtok(NULL,"|");
	}
	toks[i]=NULL;
	i--;
	int ain=dup(0);
	int aout=dup(1);
//	int count=splitter(toks,inp,"|");	
	for(int j=0;j<i;j++){
		int for_vp[2];
		pipe(for_vp);
		int prc=fork();
		if  (prc<0){
			perror("Fork Failed!");
			return;
		}
		else  if (prc==0){
			dup2(for_vp[1],1);
			close(for_vp[0]);
			close(for_vp[1]);
			int tlen=linelen;
			char * tempbreak[20];
			breakinspace(toks[j],tempbreak);
			Redirectfun(linelen,tempbreak);
			linelen=tlen;
			exit(0);
			//if ()
		}
		else if(prc){
			wait(NULL);
			dup2(for_vp[0],0);
			close(for_vp[0]);
			close(for_vp[1]);
		}
	}
	dup2(aout,1);
	char * tempbreak[20];
	breakinspace(toks[i],tempbreak);
	Redirectfun(linelen,tempbreak);
	dup2(ain,0);	
	dup2(aout,1);
}