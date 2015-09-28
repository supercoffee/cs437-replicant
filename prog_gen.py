
import sys
def main():

    args = sys.argv

    if len(args) > 2:
        print("Usage: prog_gen.py <source>")
        return

    source = args[1]
    with open(source, 'r') as content:
        lines = content.readlines();

    for line in lines:
        print('"{}"\\'.format(line.replace('\n', '\\n')));


if __name__ == "__main__":
    main();
