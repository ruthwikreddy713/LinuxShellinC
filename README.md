# LinuxShellinC
Run using make then run the executable a.out using ./a.out <br /> 
Files: <br />
	redirect.c has the function which is  used to redirect. <br />
	echo.c has  the  execution of echo command. br </>
	jobs.c has the implementation for jobs command which prints the bg processes. <br />
	pinfs.c has implementation of pinfo <br />
	kjob.c has implementation of kjob <br />
	pipeexec.c  has implementation  of pipe along with  redirection <br />
	prompt.c has the prompt function basically the newline <br />
	ls.c has ls implementation <br />
	pwd.c has pwd implementation <br />
	cd.c  has cd  implementation <br />
	main.c is the main file which has loop it also has signal handlers too <br />
	overkill.c has  overkilll implementation. <br />
	help.c has functions to  break wrt ; or " " also  bg  and fg <br />
Work: <br />
Basically extended the assignment 2 and in the same way given  commands are implemented with it's functions in other files and for redirection and piping used dup2 and pipe  commands to duplicate and  execute pipe,  For bg processes a struct array which has all bg process is named "procs" and "tpid" is the size of the array using this kjob jobs overkill bg and fg are implemented for others used functions  available.Implemented last working directory "cd -" too. 

