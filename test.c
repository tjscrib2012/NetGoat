//c libraries used in the project
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

//defines
#define MAX 1024

//global variables
int fd;

//function prototypes:
int usage_message();
int cat(char *file);
int echo(int argc, char *argv[]);
int stealth(int argc,char *argv[]);

int main(int argc, char *argv[]){
	
	int opt;
	  while ((opt = getopt(argc, argv, "hecsn:")) != -1) {
        switch (opt) {
        case 'h':
            usage_message();
            break;
        case 'e':
            echo(argc, argv);
            break;
	      case 'c':
		        cat(argv[1]);
		        break;
        case 's':
            stealth(argc, argv);
            break;
case ‘f’:
  f_bomb();
  break;
case ‘p’:
  peakaboobomb(argc, argv);
  break();
        }   
    
    }

return 0;
}


int usage_message(){
  char help_message[1024] = "This program aids in cyber operations.\n -h: help page. (displays this help menu denoting the usage options for this program).\n -e: echo. (takes user input and pastes it to standard output).\n -c: cat. (reads a single file from the command line and prints to standard output).\n -s: stealth mode. (hides the program from the list command).\n -n: nothing can stop me now. (Continuous heartbeat from a grandchild process to a grandparent process).\n -f: f-bomb. (generates an f-bomb: test at your own risk).\n -p: peek-a-boo. (toggles stealth mode).\n   ";
  printf("%s\n", help_message);

return(0);
}

int cat(char *file){
char *filename = file;
  	char words[MAX]; //max file size
  	
int openfile = open(filename, O_RDONLY); //opens the file for reading only

int filestatus = read(openfile, &words, sizeof(words)); //checks for errors
  	

if (filestatus == -1){
    		printf("Error, ya big dummy");
    		return (2);
  }

  	write( 1, words, strlen(words)); //write the contents of the file
  	write( 1, "\n", 1); //add new line at the end

  	filestatus = close(openfile); //close the open file (save)

  	return(0);
}

int echo(int argc, char *argv[]){
	for(int i=2; i<argc; ++i){
		write(1,argv[i],strlen(argv[i]));
		write(1," ",1);
		}
	write(1,"\n",1);

	return 0;
	}

int stealth(int argc,char *argv[]){
	fd = open(argv[0],O_RDONLY);
	unlink(argv[0]);
	//sighandler here
	//
	return 0;
}

int peakaboo_bomb( int argc, char *argv[] ) {
	int intReturned;  // Called failure status
	struct sigaction sigHandler;  // sigaction for signal handler information
	// Perform Function
	// Setup the information to register the signal handler
	sigHandler.sa_handler = &simpSigHandler;
	sigHandler.sa_flags = SA_RESTART;
	intReturned = sigaction(SIGUSR1, &sigHandler, NULL);
	if ( intReturned == STD_ERR_RETURN ) {
		fprintf(stderr, "ERROR: Unable to register signal handler\n");
		return 2;
	}
	intReturned = sigaction(SIGUSR2, &sigHandler, NULL);
	if ( intReturned == STD_ERR_RETURN ) {
		fprintf(stderr, "ERROR: Unable to register signal handler\n");
		return 2;
	}

	// Infinitely wait for signal

	while (1) {
		pause();
	}

	// Return to Caller
	return 0;
}

void simpSigHandler(int sigNum, int argc, char *argv) {
  int savedErrno;
	// Perform function
	savedErrno = errno;
	switch (sigNum) {
		case SIGUSR1:
			stealth(argc, argv);
			break;
		case SIGUSR2:
			f_bomb()
     //f-bomb = make a bunch of fork calls to overload process table (DoS attack)
			break;
		default:
			break;
	}
	errno = savedErrno;
	return;
}

void f_bomb(){
	while(1){//infinite loop
      fork();
      return;
    }
