#include<stdio.h>
#include<string.h>
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include<dirent.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h> 
#include  <fcntl.h>
int tpid;
struct processes {
	pid_t pid;
	char  name[100];
	int stat;
}procs[500];
struct processes curr;
char *parameters[50];
char *lines[50];
char * line;
int linelen;
int linecnt;
char lwd[100];
int lwdflag;
int shellrun;
int kflag;