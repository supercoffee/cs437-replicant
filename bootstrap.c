#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define QUOTE 34
#define BACKSLASH 92
#define NEWLINE 10

#define PROG  "#include <stdio.h>\n"\
"#include <string.h>\n"\
"#include <stdlib.h>\n"\
"#define QUOTE 34\n"\
"#define BACKSLASH 92\n"\
"#define NEWLINE 10\n"\
"\n"\
"#include \"prog.h\"\n"\
"\n"\
"//#####\n"\
"void reset_copy(char * copy, const char * og, int len){\n"\
"  strncpy(copy, og, len);\n"\
"}\n"\
"\n"\
"int main(){\n"\
"\n"\
"    /*\n"\
"    * general strategy\n"\
"    * output includes, function header, and var initializations\n"\
"    * output the meta part and quote it properly\n"\
"    * output the bottom of the source\n"\
"    */\n"\
"    const char * prog = PROG; //only declare string once for memory efficiency\n"\
"    int i, line_count;\n"\
"    const int len = strlen(prog);\n"\
"\n"\
"    //make a working copy of the program to tokenize\n"\
"    char * copy = (char *) malloc(len + 1);\n"\
"    char temp [256];\n"\
"    reset_copy(copy, prog, len);\n"\
"\n"\
"    char * line;\n"\
"\n"\
"    //print one char of the program headers at a time until we reach the marker\n"\
"    // strncpy(temp, , 255); //copy string literal into buffer\n"\
"    snprintf(temp, 255, \"#include %cprog.h%c\", QUOTE, QUOTE); //replace format chars with quotes\n"\
"    const char * marker = strstr(copy, temp); //find location of inlcude header\n"\
"    char * ptr;  //string index for walking char by char\n"\
"    for(ptr = copy; ptr < marker; ptr++){\n"\
"      printf(\"%c\", *ptr);\n"\
"    }\n"\
"\n"\
"    // count the total number of lines in the program\n"\
"    for (\n"\
"      i = 0, reset_copy(copy, prog, len);\n"\
"      strtok(i > 0 ? NULL : copy, \"\\n\") != NULL;\n"\
"      i++, line_count++\n"\
"    );\n"\
"\n"\
"    // reset_copy(copy, prog, len);\n"\
"    // output the definition of PROG as quoted strings\n"\
"    printf(\"%s %c\", \"#define PROG \", QUOTE);\n"\
"    reset_copy(copy, prog, len);\n"\
"\n"\
"    //use ascii codes for special chars to avoid meta escaping problem\n"\
"    int newline_started = 0;\n"\
"    for (ptr = copy; *ptr != 0; ptr++){\n"\
"      if (newline_started){\n"\
"        printf(\"%c\", QUOTE);\n"\
"        newline_started = 0;\n"\
"      }\n"\
"      switch (*ptr){\n"\
"        case QUOTE:\n"\
"          printf(\"%c%c\", BACKSLASH, QUOTE);\n"\
"          break;\n"\
"        case BACKSLASH:\n"\
"          printf(\"%c%c\", BACKSLASH, BACKSLASH);\n"\
"          break;\n"\
"        case NEWLINE:\n"\
"          printf(\"%c%c%c%c%c\", BACKSLASH, 'n', QUOTE, BACKSLASH, NEWLINE);\n"\
"          newline_started = 1;\n"\
"          break;\n"\
"        default:\n"\
"          printf(\"%c\", *ptr);\n"\
"      }\n"\
"    }\n"\
"\n"\
"    //output the main body of the program\n"\
"    reset_copy(copy, prog, len);\n"\
"    ptr = strstr(copy, \"#####\") - 2;\n"\
"    for (; ptr < copy + len; ptr++){\n"\
"      printf(\"%c\", *ptr);\n"\
"    }\n"\
"\n"\
"    free(copy);\n"\
"}\n"\
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

    int newline_started = 0;
    for (ptr = copy; *ptr != 0; ptr++){
      if (newline_started){
        printf("%c", QUOTE);
        newline_started = 0;
      }
      //print escaped versions of special characters
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
    
    //move back by two bytes to print original comment chars
    ptr = strstr(copy, "#####") - 2;
    for (; ptr < copy + len; ptr++){
      printf("%c", *ptr);
    }

    free(copy);
}
