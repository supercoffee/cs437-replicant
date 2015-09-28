"""
This utility helps bootstrap the C program by reading the original C
file and outputting a #define statement with the entire program as
a string. Once the C program reads the file for the first time, it
can rebuild it's own source by including the defined string in the output
source.
"""
import sys
def main():

    args = sys.argv

    if len(args) > 2:
        print("Usage: prog_gen.py <source>")
        return

    source = args[1]
    with open(source, 'r') as content:
        lines = content.readlines();

    print('#define PROG ', end='')
    for line in lines:
        print('"{}"\\'.format(line
            .replace(chr(92), chr(92) + chr(92)) #rule for backslashes        
            .replace('"', r'\"')
            .replace('\n', '\\n')))



if __name__ == "__main__":
    main();
