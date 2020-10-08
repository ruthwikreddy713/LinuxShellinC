#include "functions.h"
#include "header.h"
//#include "Mf.h"
void funtoprex(){
	int status,tempi;
	while(1){
		tempi=waitpid((pid_t)-1,&status,WNOHANG);
		if (tempi==0 || tempi==-1)
			return;
		else if (tempi > 0){
			if (!kflag)
				tpid--;
			kflag=0;
			fprintf(stderr,"\nProcess with pid %d exited normally",tempi);
		}
	}
}

int main(){
	shellrun=getpid();
	tpid=0;
	char *ltemp;
	line = (char *) malloc (500*sizeof(char));
	ltemp = (char *) malloc (500*sizeof(char));
	while(1){
		fflush(stdin);
		fflush(stdout);	
//		printf("%d\n",tpid);		
		signal(SIGINT,ctrlc);
		signal(SIGTSTP,ctrlz);	
		prompt();
		signal(SIGCHLD,funtoprex);
		fgets(line,100,stdin);
		if(feof(stdin)) exit(0);
		strcpy(ltemp,line);
		breakinpintolines(line,lines);
		for(int i=0;i<linecnt;i++){
		//	printf("%s\n",lines[i]);
			char *temp2;
			temp2 = (char *) malloc (100*sizeof(char));
			strcpy(temp2,lines[i]);
			breakinspace(temp2,parameters);
			int tlen=linelen;
			if (lines[i][0]!='\n'){
		//		printf("ok\n");
				if (strcmp(parameters[tlen-1],"&")==0){
				//	BG(parameters);
					int prc=fork();
					if (prc<0) {
						printf("fork failed!\n");
					}
					if (prc==0){
						setpgid(0,0);
						parameters[tlen-1]=NULL;
						free(parameters[tlen]);				
						tlen--;
						int k=execvp(parameters[0],parameters);				
						if (k<0) perror("command not found");
						exit(0);
					}
					else {
						procs[tpid].pid=prc;
						procs[tpid].stat=1;
						char *  temp3;
						temp3 =  (char *) calloc(100,sizeof(char));
				//		printf("ok\n");
						strcpy(temp3,lines[i]);
						for(int j=0;j<strlen(lines[i]);j++){
							if(temp3[j]=='&'){
								temp3[j]='\0';
								break;
							}
						}
					//	printf("ok\n");
						strcpy(procs[tpid].name,temp3);
						tpid++;
					}

				}
				else if (check_pipe(lines[i])){
					pipeexec(lines[i]);
				}
				else if (check_redir(lines[i])) {
			//		printf("%s %s %s\n",parameters[0],parameters[1],parameters[2]);
					Redirectfun(linelen,parameters);
				}
				else { 
		//			printf("ok\n");
			        if (strcmp(parameters[0],"cd")==0 ){			        	
			       		CDF(parameters);
					}
					else if(strcmp(parameters[0],"quit")==0)
						exit(0);
					else if(strcmp(parameters[0],"overkill")==0){
						overkill(linelen);
					//	tpid=0;
					}
					else if (strcmp(parameters[0],"jobs")==0)
						jobs(linelen);
					else if (strcmp(parameters[0],"bg")==0)
						bg(linelen);
					else if (strcmp(parameters[0],"fg")==0)
						fg(linelen);
					else if (strcmp(parameters[0],"kjob")==0){
					//	printf("ok %s\n",parameters[1]);
						kjob(linelen);
					}
					else if (strcmp(parameters[0],"unsetenv")==0){
						if (linelen !=2) printf("Only 1 argument!\n");
						if (unsetenv(parameters[1])==-1)
							perror("unsetenv error");
					}
					else if (strcmp(parameters[0],"setenv")==0){
						if (linelen != 3) printf("Only 2 arguments!\n");
						else if (linelen==2){
							if (setenv(parameters[1],"",1)==-1)
								perror("setenv error");
						}
						else if(setenv(parameters[1],parameters[2],1)==-1)
							perror("setenv error\n");			
					}
					else if (strcmp(parameters[0],"pwd")==0){			
						PWDS();
					//	exit(0);
					}
					else if (strcmp(parameters[0],"echo")==0) {
				
						if (linelen==1) printf("\n");
						else {
							echow(lines[i]);
						}
					//	exit(0);
					}
					else if (strcmp(parameters[0],"ls")==0){
					//	printf("%s\n",lines[i]);
						lspr(linelen,lines[i]);
					//	exit(0);
					}
					else if (strcmp(parameters[0],"pinfo")==0){
						psc(linelen);
					//	exit(0);
					}
					else {
				//		printf("ok\n");
						int pr = fork();
					//	printf("%d\n",pr);
						if (pr<0) perror("fork failed");
						else if (pr==0){
					//		printf("ok");
							curr.pid=getpid();
							strcpy(curr.name,lines[i]);
							curr.stat=1;
					//		printf("ok\n");
					//		write(1,parameters[1],strlen(parameters[1]));
							int k=execvp(parameters[0],parameters);
							if (k<0) perror("command not found");
							exit(0);
						}
						else{
							curr.pid=pr;
							strcpy(curr.name,lines[i]);
							curr.stat=1;
							waitpid(-1,NULL,WUNTRACED);
							curr.stat=0;
						}
					}			
				}
			}
	//     	printf("%s %d\n",parameters[0],len);
		}
	fflush(stdout);
	fflush(stdout);
	}
}