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



int main(int argc, char *argv[]){
  
  int pipeData; //status of pipe
  int ChildToParent[2]; //listen and talk from child to parent
  int ParentToChild[2]; //listen and talk from parent to child

  pid_t fork = fork(); //fork to create child
  
  switch(fork){

    case 0 : //child process (executed command)
      
      //execute to become command from CLA?
      //data written to executed commands STDOUT -> parent STDOUT ?

      close (pfdPipe[PIPE_WRITE_TO]); //close unused pipe side
      
      pipeData = read( ParentToChild[PIPE_READ_FROM] ); //read data from parent
      
      //redirect that information to STDIN?

      pipeData = close( ParentToChild[PIPE_READ_FROM] ); //close used end
      
      
      break;
    
    default : //parent process (NetGoat)
      
      //data written to NetGoat STDIN -> executed command STDIN ?

      close ( pfdPipe[PIPE_WRITE_TO] ); //close reading pipe

      pipeData = read( ChildToParent[PIPE_READ_FROM] ); //read data from child

      //redirect read data to standard output

      pipeData = close( ChildToParent[PIPE_READ_FROM] ); //close used end

      break;
  }

  return(0);
}

    
