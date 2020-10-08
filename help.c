#include "functions.h"
#include "header.h"
int check_redir (char line[]) {
	for(int i=0;i<strlen(line)-1;i++){
		if (line[i]=='<' || line[i]=='>')
			return 1;
	}
	return 0;
}
int check_pipe (char line[]) {
	for(int i=0;i<strlen(line)-1;i++){
		if (line[i]=='|')
			return 1;
	}
	return 0;
}
void ctrlz(int sig_num){
//	printf("%d\n",tpid);
	if (curr.stat==1){
		printf("ok\n");
		int k1=kill(curr.pid,SIGTTIN);
		if (k1<0){ 
			perror("can't kill!");
			return;
		}
		int k2=kill(curr.pid,SIGTSTP);
		if(k2<0){ 
			perror("can't kill!");
			return;
		}
		curr.stat=0;
		procs[tpid].stat=1;
		strcpy(procs[tpid].name,curr.name);
		procs[tpid].pid=curr.pid;
		tpid++;
//		prompt();
		return;
	}	
	else {
		printf("nNoFGprocess\n");
	}
	signal(SIGTSTP,ctrlz);
}
void ctrlc(int sig_num){
	int nowproc=getpid();
	if(nowproc ^ shellrun){
		return;
	}
	else if (curr.stat==0){
		printf("\nNoFGprocess\n");
//		prompt();
		return;
	}
	else {
		if (curr.stat==1){
			int k1=kill(curr.pid,SIGINT);
			if (k1<0){
				perror("can't kill!");
				return;
			}
			curr.stat=0;
			printf("\n");
			prompt();
		}
	}
	signal(SIGINT,ctrlc);
}
void breakinpintolines(char *line,char *lines[]){
	linecnt=0;
	char * temp=strtok(line,";\n");
	while(temp!=NULL){
		lines[linecnt++]=strdup(temp);
		temp=strtok(NULL,";\n");
	}
	lines[linecnt]=NULL;
}
void breakinspace(char * gline,char * parameters[]){
	linelen=0;
	char * temp=strtok(gline," \t\n");
	while(temp!=NULL){
		parameters[linelen++]=strdup(temp);
		temp=strtok(NULL," \t\n");
	}
	parameters[linelen]=NULL;	
}
void bg(int len){
	if (len!=2){ 
		perror("Only 1 argument!");
		return;
	}
	int ind=atoi(parameters[1]);
	if (ind <= tpid) {
		ind--;
		if (procs[ind].stat==1){
			int k1=kill(procs[ind].pid,SIGCONT);
			if (k1<0){
				perror("can't kill!");
				return;
			}
		}
	}
	else {
		printf("No such process give correct number!!\n");
	}
}
void fg(int len){
	if (len!=2){ 
		perror("Only 1 argument!");
		return;
	}
	int ind=atoi(parameters[1]);
//	printf("%d %d\n",ind,tpid);
	if (ind <= tpid) {
		ind--;
		if (procs[ind].stat==1){
			int k2=kill(procs[ind].pid,SIGCONT);
			if (k2<0){
				perror("can't kill!");
				return;
			}
			procs[ind].stat=0;
			curr.pid=procs[ind].pid;
			strcpy(curr.name,procs[ind].name);
			tpid--;
    		signal(SIGTTIN, SIG_IGN);
    		signal(SIGTTOU, SIG_IGN);
			curr.stat=1;
    		int status;
			waitpid(procs[ind].pid, &status, WUNTRACED);
			signal(SIGINT,ctrlc);
			signal(SIGTSTP,ctrlz);
			curr.stat=0;
		}
	}
	else {
		perror("No such process give correct number!!");
	}
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTTOU,SIG_IGN);

}