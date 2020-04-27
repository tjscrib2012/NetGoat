//Alex Wowk
//Milestone 5: heartbeat processes



//required includes:
#include <stdio.h>      // Standard I/O Library
#include <stdlib.h>     // Standard Library
#include <string.h>     // String Library

#include <signal.h>     // Signal Library
#include <sys/types.h>  // System Types Library 
#include <unistd.h>
#include <time.h> 


void heartbeat_handler(int signum); //signal handler prototype

int main(int argc, char *argv[]){

  printf("This function creates a grandchild process that sends heartbeat
      signals to the grandparent process every 60 seconds");

  //structure of the heartbeat handler
  struct sigaction heartbeat;
  heartbeat.sa_handler = &heartbeat_handler;
  heartbeat.sa_flags = SA_RESTART; 
  
  pid_t first = fork(); //fork and create a child PID
  int grandparent = getppid(); //PID of grandparent


  if (first  ==  0){ //first child

    pid_t second = fork(); //create a grandchild by forking another time

    if (second == 0){ //grandchild

      //kill( getppid(), SIGKILL); //dont need parent anymore so kill it
      
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
        //restartHeart = execvp(args[0], args); //execute program again
      }
    }
    

  return(0);
}

void heartbeat_handler(int signum){ //handle the heartbeat

  if (signum == SIGABRT){
    printf("heartbeat recieved");
  }
}

    


  
