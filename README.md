# LinuxShellinC
#Run using make then run the executable a.out using ./a.out 
Files: 
	redirect.c has the function which is  used to redirect.
	echo.c has  the  execution of echo command.
	jobs.c has the implementation for jobs command which prints the bg processes.
	pinfs.c has implementation of pinfo
	kjob.c has implementation of kjob
	pipeexec.c  has implementation  of pipe along with  redirection
	prompt.c has the prompt function basically the newline
	ls.c has ls implementation
	pwd.c has pwd implementation
	cd.c  has cd  implementation
	main.c is the main file which has loop it also has signal handlers too
	overkill.c has  overkilll implementation.
	help.c has functions to  break wrt ; or " " also  bg  and fg
#Work:
Basically extended the assignment 2 and in the same way given  commands are implemented with it's functions in other files and for redirection and piping used dup2 and pipe  commands to duplicate and  execute pipe,  For bg processes a struct array which has all bg process is named "procs" and "tpid" is the size of the array using this kjob jobs overkill bg and fg are implemented for others used functions  available.Implemented last working directory "cd -" too. 

