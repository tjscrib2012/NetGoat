//Hells Debels

#include <unistd.h>//include UNIX standard library
#include <stdlib.h>//defines variables such as size_t to execute functions
#include <string.h>//defines variables types and macros for input/output
#include <getopt.h>//defines the function getopt() which parses command-line arguments
#include <stdio.h>//defines standard input/output library functions
#include <errno.h>// sets errno to report the error that occurred
#include <sys/types.h>//defines pid_t variable type

#define BUF 1024
char help_message[1024] = "This program aids in cyber operations.\n -h Prints this help message\n ";
int usage_message();

int usage_message(){
  char help_message[1024] = "This program aids in cyber operations.\n -h Prints this help message\n ";
  printf("%s\n", help_message);

return(0);
}


int main(int argc, char *argv[]){
  printf("Welcome to Hells Debels netGoat program!\n");
  int i = 0;

  for (i; i < argc; ++i){
  printf("%s\n", argv[i]);
    if (argv[i] == "h"){
      usage_message();
      return(0);
    }
    if (argc == 0){
      usage_message();
      return(0);
  }
}


  return(0);
}
