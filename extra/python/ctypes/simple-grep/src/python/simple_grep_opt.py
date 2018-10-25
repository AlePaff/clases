import sys
from grep_wrap import grepWrap

def main():
    if len(sys.argv) < 3:
        print("Uso: %s, <file> <expr>" % sys.argv[0])
    with open(sys.argv[1]) as file:
        grepWrap(file, sys.argv[2])

if __name__ == '__main__':
    main()