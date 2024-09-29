# Assignment 3 - Creating an Interactive User Defined Shell

## Follow the steps to run the shell:
   make
   ./shell

## C Files

1. main.c
This is the program through which the whole shell is executed. 

2. read.c
Read function.

3. getargs.c
For getting arguments by the user.

4. loop.c
This contains the infinite loop. Also includes signal handlers for Ctrl-C and Ctrl-Z.

5. start.c
To execute any command including background processes.

6. pwd.c
Getting the Present Working Directory

7. run.c
Executes all commands.

8. cd.c
Changing the Directory.

9. pinfo.c
Getting the process information.

10. ls.c
Getting the list of files. This includes various ls flags.

11. echo.c
Printing a message.

12. redirection.c
Redirection Function.

13. piping.c
Pipe Function and redirection + pipe function.

14. setenv.c
Set Environment Variable. Including Error Handling.

15. unsetenv.c
Unset Environment Variable. Including Error Handling.

16. jobs.c
Prints all the background processes.

17. kjob.c
Give a signal to a process.

18. fg.c
Brings a running or a stopped background job with given job number to foreground.

19. bg.c 
Changes a stopped background job to a running background job.

20. overkill.c 
Kill all the background processes at once.

21. main.h
Contains all the functions.







