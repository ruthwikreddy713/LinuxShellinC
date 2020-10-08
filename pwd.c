#include "functions.h"
#include "header.h"

void PWDS(){
				char path[100];
				getcwd(path,100);
				printf("%s\n",path);	
}