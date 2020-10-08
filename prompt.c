#include "functions.h"
#include "header.h"

void prompt(){
	char *user =  getenv("USER");
	char path[100];
	getcwd(path,100);
	char relpath[100];
	relpath[0]='~';
//	for(int i=0;i<)
	char sys_name[1024];
	gethostname(sys_name,1023);
	printf("<%s @%s:%s>",user,sys_name,path);	
}