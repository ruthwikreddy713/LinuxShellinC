#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
void BG(int len);
void CDF();
void echow();
void lspr(int n, char inp[]);
void prompt();
void PWDS();
//void funtoprex();
void psc(int len);
void kjob(int len);
void jobs(int len);
int check_redir(char line[]);
int check_pipe(char line[]);
void pipeexec(char inp[]);
void breakinpintolines(char *line,char *lines[]);
void breakinspace(char * gline,char * parameters[]);
void Redirectfun(int len,char ** parameters);
void overkill(int len);
void bg(int len);
void fg(int len);
void ctrlz(int sig_num);
void ctrlc(int sig_num);
#endif