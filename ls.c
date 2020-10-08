#include "functions.h"
#include "header.h"


int lexi_sort(const struct dirent **a ,const struct dirent **b)
{   int p= strcasecmp( (*a)->d_name,(*b)->d_name);
    if(p>0)
     return 1;
    else if(p<0)
     return -1;
    else 
     return 0;
}

void flagfix(char inp[],int * l,int * a){
	for(int i=2;i<strlen(inp)-1;i++){
		if (inp[i]=='-' && ((inp[i+1]=='a' &&inp[i+2]=='l')||(inp[i+1]=='l' && inp[i+2]=='a') )){
			*l=1;
			*a=1;
		}
		if (inp[i]=='-' && inp[i+1]=='l'){
			*l=1;
		}
		if (inp[i]=='-' && inp[i+1]=='a'){
			*a=1;
		}		
	}
}
void Makestr(char * opl,struct stat buffer,char * filename){
	char temp[20];
	temp[0]= (S_ISDIR(buffer.st_mode) ? 'd' : '-');
	temp[1]=((buffer.st_mode & S_IRUSR )? 'r' : '-');
	temp[2]=((buffer.st_mode & S_IWUSR )? 'w' : '-');
	temp[3]=((buffer.st_mode & S_IXUSR) ? 'x' : '-');
	temp[4]=((buffer.st_mode & S_IRGRP) ? 'r' : '-');
	temp[5]=((buffer.st_mode & S_IWGRP) ? 'w' : '-');
	temp[6]=((buffer.st_mode & S_IXGRP) ? 'x' : '-');
	temp[7]=((buffer.st_mode & S_IROTH) ? 'r' : '-');
	temp[8]=((buffer.st_mode & S_IWOTH) ? 'w' : '-');
	temp[9]=((buffer.st_mode & S_IXOTH) ? 'x' : '-');
	temp[10]=' ';
//	printf("%c\n",temp[11]);
//	printf("%s %s\n",temp, filename);
	char *usr = (getpwuid(buffer.st_uid)->pw_name);
	char *grp = (getgrgid(buffer.st_gid)->gr_name);
	sprintf(opl,"%s %1ld %6s %6s %5ld %.12s %s\n",temp,buffer.st_nlink,usr,grp, (buffer.st_size),ctime(&buffer.st_mtime)+4,filename);	
//	printf("%s\n",opl);
}
void lspr(int n, char inp[]){
	struct dirent ** answer;
	int len;
	struct stat buffer;
	char *buft;
	int dire=1;
	buft = (char *) malloc (100*sizeof(char));
	if (n==1)
		sprintf(buft,".");
	if (n > 1){
		if (parameters[n-1][0]=='-'){
			dire=0;
			sprintf(buft,".");
		}
		else if (parameters[n-1][0]!='/' || parameters[n-1][0]!='~' || parameters[n-1][0]=='-'){
			sprintf(buft,"./%s",parameters[n-1]);	
		}
		else if (parameters[n-1][0]=='~'){
			sprintf(buft,"/home");
		}
		else if (parameters[n-1][0]=='/')
			sprintf(buft,"/");
	}
	len=scandir(buft,&answer,NULL,&lexi_sort);
	if (len<0){
		perror(" ok");
		return;
	}	
	if (n==1 || (dire==1 && n==2)){	
		for(int i=2;i<len;i++)
			printf("%s ",answer[i]->d_name);
		printf("\n");	
	}
	else {
		char ** Outp;
		Outp= (char **) malloc(50 * sizeof(char *));
		int l=0,a=0;
	//	printf("%s\n",inp);
		flagfix(inp,&l,&a);
	//	printf("%d %d\n",l,a);
		if (a==1 && l==0){
			for(int i=0;i<len;i++)
				printf("%s ",answer[i]->d_name);
			printf("\n");			
		}
		else if (l==1) {
			char * textbuf;
			char ** final;
		//	printf("ok\n");
			final = (char **) malloc(500 * sizeof(char*));
			int strt=2;
			int total=0;
			if (a){
				strt=0;
			}
		//	printf("%d\n",strt);
			int j=0;
			for(int i=strt;i<len;i++){				
				Outp[j]=(char *) malloc (100*sizeof(char));
				textbuf = (char *) malloc (50*sizeof(char));
		//		printf("ok\n");
				sprintf (textbuf,"%s",answer[i]->d_name);								
		//		printf("ok\n");
				stat(textbuf,&buffer);
		//		printf("ok\n");
		//		printf("ok\n");
				Makestr(Outp[j],buffer,answer[i]->d_name);
		//		printf("%s\n",Outp[j]);
				total+=buffer.st_blocks;
		//		printf("%s\n",Outp[j]);
				free(answer[i]);
				j++;
			}
			printf("total %d\n",total/2);
			for(int i=0;i<j;i++){
				printf("%s",Outp[i]);
			}
		}
		else {
			printf("command not found\n");
		}
	}
//	printf("ok\n");
//	free(answer);
	return;
}