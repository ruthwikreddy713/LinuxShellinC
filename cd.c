#include "functions.h"
#include "header.h"
void CDF(char *temp[]){   
//		printf("\nok\n");
		char tbuf[100];
		if (strcmp(temp[1],"-")==0){
			if (lwdflag){
				sprintf(tbuf,"%s",lwd);
				printf("%s\n",tbuf);
			}
			else {
				printf("You haven't gone to  any other directory yet\n");
			}
		}
		else {
			sprintf(tbuf,"%s",temp[1]);
		}
		getcwd(lwd,100);
		if(chdir(tbuf)==-1){
			perror("cannot open");					
			return;
		}
		else {
		//	printf("%s\n",lwd);
			lwdflag=1;
		}
}