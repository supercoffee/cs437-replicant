#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define QUOTE 34
#define BACKSLASH 92
#define NEWLINE 10

#include "prog.h"

//#####
void reset_copy(char * copy, const char * og, int len){
  strncpy(copy, og, len);
}

int main(){

    /*
    * general strategy
    * output includes, function header, and var initializations
    * output the meta part and quote it properly
    * output the bottom of the source
    */
    const char * prog = PROG; //only declare string once for memory efficiency
    int i, line_count;
    const int len = strlen(prog);

    //make a working copy of the program to tokenize
    char * copy = (char *) malloc(len + 1);
    char temp [256];
    reset_copy(copy, prog, len);

    char * line;

    //print one char of the program headers at a time until we reach the marker
    // strncpy(temp, , 255); //copy string literal into buffer
    snprintf(temp, 255, "#include %cprog.h%c", QUOTE, QUOTE); //replace format chars with quotes
    const char * marker = strstr(copy, temp); //find location of inlcude header
    char * ptr;  //string index for walking char by char
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
    // output the definition of PROG as quoted strings
    printf("%s %c", "#define PROG ", QUOTE);
    reset_copy(copy, prog, len);

    //use ascii codes for special chars to avoid meta escaping problem
    int newline_started = 0;
    for (ptr = copy; *ptr != 0; ptr++){
      if (newline_started){
        printf("%c", QUOTE);
        newline_started = 0;
      }
      switch (*ptr){
        case QUOTE:
          printf("%c%c", BACKSLASH, QUOTE);
          break;
        case BACKSLASH:
          printf("%c%c", BACKSLASH, BACKSLASH);
          break;
        case NEWLINE:
          printf("%c%c%c%c%c", BACKSLASH, 'n', QUOTE, BACKSLASH, NEWLINE);
          newline_started = 1;
          break;
        default:
          printf("%c", *ptr);
      }
    }

    //output the main body of the program
    reset_copy(copy, prog, len);
    ptr = strstr(copy, "#####") - 2;
    for (; ptr < copy + len; ptr++){
      printf("%c", *ptr);
    }

    free(copy);
}
