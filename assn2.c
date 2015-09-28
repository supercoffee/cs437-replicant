#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prog.h"

void reset_copy(char * copy, char * og, int len){
  strncpy(copy, og, len);
}

int main(){

    /*
    * general strategy
    * output includes, function header, and var initializations
    * output the meta part and quote it properly
    * output the bottom of the source
    */
    char * prog = PROG; //only declare string once for memory efficiency
    int i, line_count, len = strlen(prog);

    //make a working copy of the program to tokenize
    char * copy = (char *) malloc(len + 1);
    reset_copy(copy, prog, len);

    char * line;

    //print one char of the program headers at a time until we reach the marker
    const char * marker = strstr(copy, "#include \"prog.h\"");
    char * ptr;
    for(ptr = copy; ptr < marker; ptr++){
      printf("%c", *ptr);
    }

    // count the total number of lines in the program
    for (
      i = 0, reset_copy(copy, prog, len);
      strtok(i > 0 ? NULL : copy, "\n") != NULL;
      i++, line_count++
    );

    // reset_copy(copy, prog, len);
    // // output the definition of PROG as quoted strings
    // for (i = 0; i < line_count; i++){
    //   line = strtok(i > 0 ? NULL : copy, "\n");
    //   printf("\"%s\"\n", line);
    // }

    free(copy);
}
