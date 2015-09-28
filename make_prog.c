/*
* This utility will stringify the main program
* to avoid doing all that work by hand.
* This program is will not work on files with lines over 200 chars longs.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MAX_LENGTH = 200;

int main(int argc, char * argv[]){

  //read contents of main.c

  if (argc != 1){
    //print usage
    printf("%s\n", "Usage: cat file > make_prog");
    return -1;
  }
  char buf [MAX_LENGTH + 1];

  while (fgets(buf, MAX_LENGTH, stdin) != NULL){

    //output escaped contents to stdout
    printf("\"%s\n\"\\", buf);
  }


}
