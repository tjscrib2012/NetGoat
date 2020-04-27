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
	fd = open(argv[o],O_RDONLY);
	unlink(argv[0]);
	//sighandler here
	//
	return 0;
}
