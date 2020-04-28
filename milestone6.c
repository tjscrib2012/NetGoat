//milestone 6


// Required Includes
#include <libname.h>  // <Library Name>: <Uses: constants, variables, system calls, library routines>...
#include <unistd.h>  // POSIX Standard Library: close(2), read(2), write(2)
#include <stdlib.h>  // Standard Library: EXIT_*
// New Uses
#include <unistd.h>  // POSIX Standard Library: pipe(2); close(2), read(2), write(2)

// Global Constants
#define STD_ERR_RETURN    -1
#define PIPE_READ_FROM     0
#define PIPE_WRITE_TO      1
#define MAX_BUFF_LEN    1024

//GOALS:
//fork and set up pipes like this:

/* 1) data read from NetGoat standard input (parent) needs to be redirected to standard input of executed command (child)
   2) data written to executed command's standard output(child) must be
   redirected to netgoat standard output (parent)*/

//finaly, secure the path



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

      write(STDOUT_FILENO, buffPipe, pipeData);//write what came from the parent to the child STDOUT

      close( ParentToChild[PIPE_READ_FROM] ); //close used end


      break;

    default : //parent process (NetGoat)


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


    
