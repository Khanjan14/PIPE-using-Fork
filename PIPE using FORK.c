/*******************************/
/*    Titel : Assignment1.c    */
/*    Author: Khanjan Desai    */
/*    Date  : Feb  5, 2016     */
/*Implementation of 'ls -l| wc'*/
/*******************************/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
        int     fd[2];
        pid_t   childpid;
	
	// Create Pipe
        pipe(fd);

        childpid = fork();
	// Errorcheck for fork
        if(childpid == -1)
        {
                perror("fork");
                exit(1);
        }
	// Errorcheck for Pipe fd
	if(*fd == -1)
        {
                perror("pipe");
                exit(1);
        }
	// The code will execute 'ls -l| wc' in command line.
	// IF 0 Enter child process.
	// Child will execute command lin 'ls -l' and instede of printing output stores in fd[1]
	if(childpid == 0)
        {	
		dup2(fd[1],STDOUT_FILENO);	
                close(fd[0]);
		execl("/bin/ls","ls","-l",NULL);  
     
	}
	// If 1 Enter parent process.
	// Parent process reads from fd[0] which is same as fd[1] due to pipe(fd) and give it in the input of 'wc' 
        else
        {
                
		dup2(fd[0],STDIN_FILENO);
		close(fd[1]);
		execl("/usr/bin/wc","wc",NULL);
	}
        return(0);

}
