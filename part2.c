//Alex Wowk
//GitLab Part 2 CAT



//handle command line arguments properly
//read in data from standard input to end of file
//output the data to standard output

//add character option that takes in filename as argument
//access contents of the file and output contents to standard output



//required includes:
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MAX 1024 //set max buffer length to be 1024 bytes


int catfile(); /*takes bytes from standard input and writes to standard output*/

int main(int argc, char *argv[])
{
  catfile(argv[1]);
  return(0);
}


int catfile(char* file) //process the file
{
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

